/*
 * extract_vid_tests.c
 *
 * Tests for the video API in extract_vid.h, implemented in extract_vid.c.
 * Build them together and run:
 *
 *     cc -std=c11 -O2 -Wall -Wextra -DEXTRACT_VID_TRACK_HEAP \
 *         extract_vid.c extract_vid_tests.c -o extract_vid_tests && ./extract_vid_tests
 *
 * The tests check that:
 *   - every frame reads back byte-for-byte identical (lossless);
 *   - frames can be read in any order;
 *   - a minute of random noise needs at most ~1% more heap than raw 24-bit RGB;
 *   - a minute of a still scene, of flat changing colors, or of a small moving
 *     square each needs at most 5% of raw 24-bit RGB;
 *   - a full minute plays back (decodes) in less than a minute;
 *   - video_destroy() frees everything.
 *
 * Heap usage is measured by intercepting malloc/calloc/realloc/free in
 * extract_vid.c, so keep the video's data on the heap (no large static arrays).
 * This file has the program's main(), so extract_vid.c must not define one.
 */

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "extract_vid.h"

#ifndef EXTRACT_VID_TRACK_HEAP
#error "build with -DEXTRACT_VID_TRACK_HEAP so the tests can measure extract_vid.c's heap use"
#endif

/* extract_vid.h routes heap calls to the tracker below; the tests themselves use the real allocator. */
#undef malloc
#undef calloc
#undef realloc
#undef free

/* ------------------------------------------------------------------------- */
/* Heap tracker                                                              */
/* ------------------------------------------------------------------------- */

/* Stored in front of every tracked block so free() knows how much it releases. */
typedef union {
    size_t size;
    max_align_t alignment;
} BlockHeader;

static size_t heap_live_bytes;

void *tracked_malloc(size_t size) {
    if (size > SIZE_MAX - sizeof(BlockHeader)) {
        return NULL;
    }

    BlockHeader *header = malloc(sizeof *header + size);
    if (header == NULL) {
        return NULL;
    }

    header->size = size;
    heap_live_bytes += size;
    return header + 1;
}

void *tracked_calloc(size_t count, size_t size) {
    if (size != 0 && count > SIZE_MAX / size) {
        return NULL;
    }

    void *block = tracked_malloc(count * size);
    if (block != NULL) {
        memset(block, 0, count * size);
    }
    return block;
}

void *tracked_realloc(void *block, size_t size) {
    if (block == NULL) {
        return tracked_malloc(size);
    }
    if (size > SIZE_MAX - sizeof(BlockHeader)) {
        return NULL;
    }

    BlockHeader *old_header = (BlockHeader *)block - 1;
    size_t old_size = old_header->size;

    BlockHeader *header = realloc(old_header, sizeof *header + size);
    if (header == NULL) {
        return NULL;
    }

    header->size = size;
    heap_live_bytes = heap_live_bytes - old_size + size;
    return header + 1;
}

void tracked_free(void *block) {
    if (block == NULL) {
        return;
    }

    BlockHeader *header = (BlockHeader *)block - 1;
    heap_live_bytes -= header->size;
    free(header);
}

/* ------------------------------------------------------------------------- */
/* Test harness                                                              */
/* ------------------------------------------------------------------------- */

static int test_failed;

/* Fails the current test and returns from the enclosing function. */
#define CHECK(condition, ...)                                                  \
    do {                                                                       \
        if (!(condition)) {                                                    \
            printf("    %s:%d: ", __FILE__, __LINE__);                         \
            printf(__VA_ARGS__);                                               \
            printf("\n");                                                      \
            test_failed = 1;                                                   \
            return;                                                            \
        }                                                                      \
    } while (0)

static double seconds_since(clock_t start) {
    return (double)(clock() - start) / CLOCKS_PER_SEC;
}

static size_t raw_frame_bytes(int width, int height) {
    return (size_t)width * height * CHANNELS;
}

static size_t raw_minute_bytes(int width, int height) {
    return raw_frame_bytes(width, height) * FRAME_COUNT;
}

/* Prints the first differing pixel and returns 0, or returns 1 if the frames match. */
static int frames_match(int frame, const unsigned char *expected,
                        const unsigned char *actual, int width, int height) {
    if (memcmp(expected, actual, raw_frame_bytes(width, height)) == 0) {
        return 1;
    }

    size_t pixel = 0;
    while (memcmp(expected + pixel * CHANNELS, actual + pixel * CHANNELS, CHANNELS) == 0) {
        pixel++;
    }

    const unsigned char *e = expected + pixel * CHANNELS;
    const unsigned char *a = actual + pixel * CHANNELS;
    printf("    Frame %d | Pixel %zu | expected RGB (%d,%d,%d), got (%d,%d,%d)\n",
           frame, pixel, e[0], e[1], e[2], a[0], a[1], a[2]);
    return 0;
}

/* ------------------------------------------------------------------------- */
/* Test scenes: each fills `rgb` with frame `frame`, deterministically.      */
/* ------------------------------------------------------------------------- */

typedef void (*Scene)(unsigned char *rgb, int width, int height, int frame);

enum { SQUARE_SIDE = 8 };

/* Incompressible: every byte of every frame is pseudo-random. */
static void scene_noise(unsigned char *rgb, int width, int height, int frame) {
    uint32_t state = (uint32_t)frame * 2654435761u + 12345u;
    size_t bytes = raw_frame_bytes(width, height);

    for (size_t i = 0; i < bytes; i++) {
        state = state * 1664525u + 1013904223u;
        rgb[i] = (unsigned char)(state >> 24);
    }
}

/* Every pixel differs from its neighbours, but every frame is identical. */
static void scene_still(unsigned char *rgb, int width, int height, int frame) {
    (void)frame;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            unsigned char *pixel = rgb + ((size_t)y * width + x) * CHANNELS;
            pixel[0] = (unsigned char)(x * 7 + y);
            pixel[1] = (unsigned char)(y * 11 + x * 3);
            pixel[2] = (unsigned char)(x * y);
        }
    }
}

/* One solid color fills the frame, and that color changes every frame. */
static void scene_flat(unsigned char *rgb, int width, int height, int frame) {
    unsigned char color[CHANNELS] = {
        (unsigned char)frame,
        (unsigned char)(frame * 3),
        (unsigned char)(255 - frame),
    };

    size_t pixels = (size_t)width * height;
    for (size_t pixel = 0; pixel < pixels; pixel++) {
        memcpy(rgb + pixel * CHANNELS, color, CHANNELS);
    }
}

/* The still scene with a white square moving across it. */
static void scene_moving_square(unsigned char *rgb, int width, int height, int frame) {
    scene_still(rgb, width, height, frame);

    int left = (frame * 2) % (width - SQUARE_SIDE + 1);
    int top = (frame / 2) % (height - SQUARE_SIDE + 1);

    for (int y = top; y < top + SQUARE_SIDE; y++) {
        for (int x = left; x < left + SQUARE_SIDE; x++) {
            memset(rgb + ((size_t)y * width + x) * CHANNELS, 255, CHANNELS);
        }
    }
}

/*
 * Records a full minute of `scene`, checks the heap the video keeps against
 * `heap_budget`, then plays every frame back in order and checks it is exact
 * and that playback keeps up with real time.
 */
static void check_minute(Scene scene, int width, int height, size_t heap_budget) {
    size_t frame_bytes = raw_frame_bytes(width, height);
    unsigned char *expected = malloc(frame_bytes);
    unsigned char *actual = malloc(frame_bytes);
    CHECK(expected != NULL && actual != NULL, "test buffer allocation failed");

    size_t baseline = heap_live_bytes;
    Video *video = video_create(width, height);
    CHECK(video != NULL, "video_create(%d, %d) returned NULL", width, height);

    for (int frame = 0; frame < FRAME_COUNT; frame++) {
        scene(expected, width, height, frame);
        CHECK(video_append_frame(video, expected) == 0, "appending frame %d failed", frame);
    }
    CHECK(video_frame_count(video) == FRAME_COUNT, "expected %d frames, got %d",
          FRAME_COUNT, video_frame_count(video));

    size_t raw = raw_minute_bytes(width, height);
    size_t stored = heap_live_bytes - baseline;
    printf("    stored %zu bytes = %.2f%% of raw %zu (budget %zu)\n",
           stored, 100.0 * stored / raw, raw, heap_budget);
    CHECK(stored > 0, "no heap use was seen; extract_vid.c must #include \"extract_vid.h\" "
                      "and keep the video on the heap");
    CHECK(stored <= heap_budget, "video holds %zu heap bytes, budget is %zu", stored, heap_budget);

    clock_t playback_start = clock();
    for (int frame = 0; frame < FRAME_COUNT; frame++) {
        CHECK(video_read_frame(video, frame, actual) == 0, "reading frame %d failed", frame);

        scene(expected, width, height, frame);
        CHECK(frames_match(frame, expected, actual, width, height), "frame %d differs", frame);

        double elapsed = seconds_since(playback_start);
        CHECK(elapsed < SECONDS, "playback slower than real time: %.1fs for %d frames",
              elapsed, frame + 1);
    }
    printf("    played back %d frames in %.2fs\n", FRAME_COUNT, seconds_since(playback_start));

    stored = heap_live_bytes - baseline;
    CHECK(stored <= heap_budget, "after playback the video holds %zu heap bytes, budget is %zu",
          stored, heap_budget);

    video_destroy(video);
    free(expected);
    free(actual);
}

/* ------------------------------------------------------------------------- */
/* Tests                                                                     */
/* ------------------------------------------------------------------------- */

enum { MOVIE_WIDTH = 160, MOVIE_HEIGHT = 90 };

static void test_rejects_bad_dimensions(void) {
    int sizes[][2] = {{0, 90}, {160, 0}, {0, 0}, {-1, 90}, {160, -90}};

    for (size_t i = 0; i < sizeof sizes / sizeof sizes[0]; i++) {
        Video *video = video_create(sizes[i][0], sizes[i][1]);
        CHECK(video == NULL, "video_create(%d, %d) should return NULL", sizes[i][0], sizes[i][1]);
    }
}

static void test_empty_video(void) {
    enum { WIDTH = 4, HEIGHT = 3 };
    unsigned char rgb[WIDTH * HEIGHT * CHANNELS];

    Video *video = video_create(WIDTH, HEIGHT);
    CHECK(video != NULL, "video_create(%d, %d) returned NULL", WIDTH, HEIGHT);
    CHECK(video_frame_count(video) == 0, "new video has %d frames, expected 0",
          video_frame_count(video));
    CHECK(video_read_frame(video, 0, rgb) == -1, "reading frame 0 of an empty video should fail");

    video_destroy(video);
    video_destroy(NULL);
}

static void test_single_pixel_video(void) {
    enum { FRAMES = 4 };
    unsigned char colors[FRAMES][CHANNELS] = {{0, 0, 0}, {255, 255, 255}, {12, 34, 56}, {255, 0, 128}};
    unsigned char actual[CHANNELS];

    Video *video = video_create(1, 1);
    CHECK(video != NULL, "video_create(1, 1) returned NULL");

    for (int frame = 0; frame < FRAMES; frame++) {
        CHECK(video_append_frame(video, colors[frame]) == 0, "appending frame %d failed", frame);
    }
    CHECK(video_frame_count(video) == FRAMES, "expected %d frames, got %d",
          FRAMES, video_frame_count(video));

    for (int frame = 0; frame < FRAMES; frame++) {
        CHECK(video_read_frame(video, frame, actual) == 0, "reading frame %d failed", frame);
        CHECK(frames_match(frame, colors[frame], actual, 1, 1), "frame %d differs", frame);
    }

    video_destroy(video);
}

static void test_odd_dimensions(void) {
    enum { WIDTH = 37, HEIGHT = 23, FRAMES = 5 };
    unsigned char expected[WIDTH * HEIGHT * CHANNELS];
    unsigned char actual[WIDTH * HEIGHT * CHANNELS];

    Video *video = video_create(WIDTH, HEIGHT);
    CHECK(video != NULL, "video_create(%d, %d) returned NULL", WIDTH, HEIGHT);

    for (int frame = 0; frame < FRAMES; frame++) {
        scene_noise(expected, WIDTH, HEIGHT, frame);
        CHECK(video_append_frame(video, expected) == 0, "appending frame %d failed", frame);
    }

    for (int frame = 0; frame < FRAMES; frame++) {
        CHECK(video_read_frame(video, frame, actual) == 0, "reading frame %d failed", frame);
        scene_noise(expected, WIDTH, HEIGHT, frame);
        CHECK(frames_match(frame, expected, actual, WIDTH, HEIGHT), "frame %d differs", frame);
    }

    video_destroy(video);
}

static void test_append_copies_input(void) {
    enum { WIDTH = 8, HEIGHT = 8 };
    unsigned char first[WIDTH * HEIGHT * CHANNELS];
    unsigned char buffer[WIDTH * HEIGHT * CHANNELS];
    unsigned char actual[WIDTH * HEIGHT * CHANNELS];

    Video *video = video_create(WIDTH, HEIGHT);
    CHECK(video != NULL, "video_create(%d, %d) returned NULL", WIDTH, HEIGHT);

    scene_noise(first, WIDTH, HEIGHT, 1);
    memcpy(buffer, first, sizeof buffer);
    CHECK(video_append_frame(video, buffer) == 0, "appending frame 0 failed");

    /* Reuse the caller's buffer for the next frame, like a real capture loop would. */
    scene_noise(buffer, WIDTH, HEIGHT, 2);
    CHECK(video_append_frame(video, buffer) == 0, "appending frame 1 failed");

    CHECK(video_read_frame(video, 0, actual) == 0, "reading frame 0 failed");
    CHECK(frames_match(0, first, actual, WIDTH, HEIGHT), "frame 0 changed when the caller reused its buffer");

    CHECK(video_read_frame(video, 1, actual) == 0, "reading frame 1 failed");
    CHECK(frames_match(1, buffer, actual, WIDTH, HEIGHT), "frame 1 differs");

    video_destroy(video);
}

static void test_rejects_out_of_range_index(void) {
    enum { WIDTH = 8, HEIGHT = 8, FRAMES = 3 };
    unsigned char rgb[WIDTH * HEIGHT * CHANNELS];

    Video *video = video_create(WIDTH, HEIGHT);
    CHECK(video != NULL, "video_create(%d, %d) returned NULL", WIDTH, HEIGHT);

    for (int frame = 0; frame < FRAMES; frame++) {
        scene_noise(rgb, WIDTH, HEIGHT, frame);
        CHECK(video_append_frame(video, rgb) == 0, "appending frame %d failed", frame);
    }

    int bad_indexes[] = {-1, FRAMES, FRAMES + 1, FRAME_COUNT, -1000000, 1000000};
    for (size_t i = 0; i < sizeof bad_indexes / sizeof bad_indexes[0]; i++) {
        CHECK(video_read_frame(video, bad_indexes[i], rgb) == -1,
              "reading frame %d of a %d-frame video should fail", bad_indexes[i], FRAMES);
    }
    CHECK(video_frame_count(video) == FRAMES, "expected %d frames, got %d",
          FRAMES, video_frame_count(video));

    video_destroy(video);
}

static void test_reads_in_any_order(void) {
    enum { WIDTH = 32, HEIGHT = 18, STRIDE = 1931 };
    unsigned char expected[WIDTH * HEIGHT * CHANNELS];
    unsigned char actual[WIDTH * HEIGHT * CHANNELS];

    Video *video = video_create(WIDTH, HEIGHT);
    CHECK(video != NULL, "video_create(%d, %d) returned NULL", WIDTH, HEIGHT);

    for (int frame = 0; frame < FRAME_COUNT; frame++) {
        scene_moving_square(expected, WIDTH, HEIGHT, frame);
        CHECK(video_append_frame(video, expected) == 0, "appending frame %d failed", frame);
    }

    /* STRIDE shares no factor with FRAME_COUNT, so this visits every frame once, out of order. */
    for (int i = 0; i < FRAME_COUNT; i++) {
        int frame = (int)((long)i * STRIDE % FRAME_COUNT);
        CHECK(video_read_frame(video, frame, actual) == 0, "reading frame %d failed", frame);

        scene_moving_square(expected, WIDTH, HEIGHT, frame);
        CHECK(frames_match(frame, expected, actual, WIDTH, HEIGHT), "frame %d differs", frame);
    }

    /* Then backwards from the last frame. */
    for (int frame = FRAME_COUNT - 1; frame >= 0; frame--) {
        CHECK(video_read_frame(video, frame, actual) == 0, "reading frame %d failed", frame);

        scene_moving_square(expected, WIDTH, HEIGHT, frame);
        CHECK(frames_match(frame, expected, actual, WIDTH, HEIGHT), "frame %d differs", frame);
    }

    video_destroy(video);
}

static void test_minute_of_noise(void) {
    enum { WIDTH = 64, HEIGHT = 36 };
    size_t raw = raw_minute_bytes(WIDTH, HEIGHT);
    check_minute(scene_noise, WIDTH, HEIGHT, raw + raw / 100 + 64 * 1024);
}

static void test_minute_still(void) {
    check_minute(scene_still, MOVIE_WIDTH, MOVIE_HEIGHT, raw_minute_bytes(MOVIE_WIDTH, MOVIE_HEIGHT) / 20);
}

static void test_minute_flat_colors(void) {
    check_minute(scene_flat, MOVIE_WIDTH, MOVIE_HEIGHT, raw_minute_bytes(MOVIE_WIDTH, MOVIE_HEIGHT) / 20);
}

static void test_minute_moving_square(void) {
    check_minute(scene_moving_square, MOVIE_WIDTH, MOVIE_HEIGHT,
                 raw_minute_bytes(MOVIE_WIDTH, MOVIE_HEIGHT) / 20);
}

typedef struct {
    const char *name;
    void (*run)(void);
} Test;

static const Test TESTS[] = {
    {"rejects non-positive dimensions", test_rejects_bad_dimensions},
    {"empty video", test_empty_video},
    {"1x1 video", test_single_pixel_video},
    {"odd dimensions round-trip", test_odd_dimensions},
    {"append copies the caller's frame", test_append_copies_input},
    {"rejects out-of-range frame index", test_rejects_out_of_range_index},
    {"reads frames in any order", test_reads_in_any_order},
    {"minute of noise: at most ~1% over raw", test_minute_of_noise},
    {"minute of a still scene: at most 5% of raw", test_minute_still},
    {"minute of flat colors: at most 5% of raw", test_minute_flat_colors},
    {"minute of a moving square: at most 5% of raw", test_minute_moving_square},
};

int main(void) {
    int test_count = (int)(sizeof TESTS / sizeof TESTS[0]);
    int failures = 0;

    for (int i = 0; i < test_count; i++) {
        printf("[ RUN  ] %s\n", TESTS[i].name);
        fflush(stdout);

        /* A failed test may leak its video, so each test is measured against its own baseline. */
        size_t baseline = heap_live_bytes;
        test_failed = 0;
        clock_t start = clock();

        TESTS[i].run();

        if (!test_failed && heap_live_bytes != baseline) {
            printf("    heap went from %zu to %zu bytes; video_destroy() must free everything\n",
                   baseline, heap_live_bytes);
            test_failed = 1;
        }

        printf("[ %s ] %s (%.2fs)\n", test_failed ? "FAIL" : " OK ", TESTS[i].name, seconds_since(start));
        failures += test_failed;
    }

    printf("\n%d/%d tests passed\n", test_count - failures, test_count);
    return failures == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}

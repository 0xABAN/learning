#ifndef EXTRACT_VID_H
#define EXTRACT_VID_H

/*
 * Store a 60-second, 60 fps RGB video efficiently in C. No libraries beyond
 * the C standard library.
 *
 * Implement struct Video and the functions below in extract_vid.c, which must
 * #include "extract_vid.h". The tests are in extract_vid_tests.c.
 */

enum { FPS = 60, SECONDS = 60, FRAME_COUNT = FPS * SECONDS, CHANNELS = 3 };

/*
 * A frame is width * height pixels in row-major order, CHANNELS bytes per
 * pixel (R, G, B). Pixel (x, y) starts at byte (y * width + x) * CHANNELS.
 */
typedef struct Video Video;

/* Returns NULL if width or height is not positive, or if allocation fails. */
Video *video_create(int width, int height);

/* Copies one frame into the video. Returns 0 on success, -1 on failure. */
int video_append_frame(Video *video, const unsigned char *rgb);

/*
 * Writes frame `index` (0-based) into `rgb`. Returns 0 on success, -1 if
 * `index` is out of range.
 */
int video_read_frame(Video *video, int index, unsigned char *rgb);

int video_frame_count(const Video *video);

/* Frees the video and everything it owns. Passing NULL does nothing. */
void video_destroy(Video *video);

/*
 * The tests are built with -DEXTRACT_VID_TRACK_HEAP, which routes every
 * malloc/calloc/realloc/free in a file that includes this header to a counter
 * in extract_vid_tests.c, so the tests can measure how much memory the video
 * really holds. Other builds use the allocator as usual.
 *
 * <stdlib.h> is included first so its declarations are not rewritten by the
 * macros, and including it again afterwards does nothing.
 */
#ifdef EXTRACT_VID_TRACK_HEAP
#include <stdlib.h>

void *tracked_malloc(size_t size);
void *tracked_calloc(size_t count, size_t size);
void *tracked_realloc(void *block, size_t size);
void tracked_free(void *block);

#define malloc(size) tracked_malloc(size)
#define calloc(count, size) tracked_calloc(count, size)
#define realloc(block, size) tracked_realloc(block, size)
#define free(block) tracked_free(block)
#endif

#endif

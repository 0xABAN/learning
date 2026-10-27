#include "extract_vid.h"

#include <stdio.h> 
#include <stdlib.h> 

/*
 * A frame is width * height pixels in row-major order, CHANNELS bytes per
 * pixel (R, G, B). Pixel (x, y) starts at byte (y * width + x) * CHANNELS.
 */
struct Video {
  int width; 
  int height; 

  int seconds;  
  int fps; 

  int frame_size; 
  int n; 
  int cap; 

  unsigned char* curr; // byte of first frame we haven't yet filled 
  unsigned char* frames;
}; 

Video *video_create(int width, int height) {
  if(width <= 0 || height <= 0) return NULL; 
  
  Video* vp = malloc(sizeof(Video));
  if (!vp) return NULL; 
  
  vp->width = width; 
  vp->height = height; 

  vp->seconds = SECONDS; 
  vp->fps = FPS; 
  vp->cap = FRAME_COUNT; 
  vp->n = 0; 
  
  vp->frame_size = width * height * CHANNELS;
  vp->frames = malloc(vp->frame_size * FRAME_COUNT); 
  if(!vp->frames) {
    free(vp);
    return NULL; 
  } 
  vp->curr = vp->frames; 
  
  return vp; 
} 

int video_append_frame(Video *video, const unsigned char *rgb) {
  if(video->n+1 > video->cap) return -1; 
  
  unsigned char *frame = video->curr; 
  for(int i = 0; i < video->frame_size; i++) {
    *(frame) = *rgb;  
     
    rgb++; 
    frame++; 
  }   
  
  video->n++; 
  video->curr = frame; 
  return 0;
}

int video_read_frame(Video *video, int index, unsigned char *rgb) {
  if(index >= video->n || index < 0) return -1; 
  
  unsigned char *start = video->frames + video->frame_size * index;
  
  for(int i = 0; i < video->frame_size; i++) {
    *rgb = *start; 

    rgb++; 
    start++; 
  }
  
  return 0;
}

int video_frame_count(const Video *video) {
  return video->n; 
}

/* Frees the video and everything it owns. Passing NULL does nothing. */
void video_destroy(Video *video) {
  if (video == NULL) return; 
  
  free(video->frames);
  free(video);
}








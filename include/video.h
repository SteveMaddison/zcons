#ifndef __VIDEO_H__
#define __VIDEO_H__

#include <SDL/SDL.h>

int video_init();
void video_set_pixel(unsigned int x, unsigned int y, uint32_t pixel);
void video_flip();

#endif

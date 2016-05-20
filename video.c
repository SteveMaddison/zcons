#include "video.h"

static SDL_Surface *surface = NULL;
static SDL_VideoInfo saved_video;

static const int SDL_SCREEN_BPP = 32;
static const int SDL_SCREEN_WIDTH = 320;
static const int SDL_SCREEN_HEIGHT = 240;
static const int MAX_FRAME_RATE = 60;
static const char *title = "Emu";
static int frame_rate = 60;

int video_init() {
  int mode = SDL_SWSURFACE;

  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    fprintf(stderr, "Error: Unable to initialise SDL: %s\n", SDL_GetError());
    return 1;
  }

  /* SDL_ShowCursor(SDL_DISABLE); */
  memcpy(&saved_video, SDL_GetVideoInfo(), sizeof(SDL_VideoInfo));
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  /* mode |= SDL_FULLSCREEN; */

  surface = SDL_SetVideoMode(SDL_SCREEN_WIDTH, SDL_SCREEN_HEIGHT, SDL_SCREEN_BPP, mode);
  if (surface == NULL) {
    fprintf(stderr, "Error: Unable to set video mode: %s\n", SDL_GetError());
    return 1;
  }

  if (frame_rate < 0) {
    frame_rate = 0;
    fprintf( stderr, "Warning: Negative frame rate, setting to 0 (unlimited)\n" );
  }
  if (frame_rate > MAX_FRAME_RATE) {
    frame_rate = MAX_FRAME_RATE;
    fprintf( stderr, "Warning: Frame rate above maximum allowed (%d) setting to maximum\n", MAX_FRAME_RATE );
  }

  SDL_WM_SetCaption( title, NULL );

  return 0;
}

void video_set_pixel(unsigned int x, unsigned int y, uint32_t pixel) {
  Uint8 *target_pixel = (Uint8 *)surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel;
  *(Uint32 *)target_pixel = pixel;
}

void video_flip() {
  SDL_Flip(surface);
}

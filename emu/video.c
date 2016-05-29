#include "video.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL2_framerate.h>

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *texture = NULL;
static Uint32 *pixels;

static const int VIDEO_SCREEN_WIDTH = 320;
static const int VIDEO_SCREEN_HEIGHT = 240;
static const int MAX_FRAME_RATE = 60;
static const char *title = "Emu";
static int frame_rate = 60;
static FPSmanager manager;

int video_init() {
  int mode = SDL_SWSURFACE;

  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    fprintf(stderr, "Error: Unable to initialise SDL: %s\n", SDL_GetError());
    return 1;
  }

  window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
               VIDEO_SCREEN_WIDTH*2, VIDEO_SCREEN_HEIGHT*2, 0);
  if (window == NULL) {
    fprintf(stderr, "Error: Unable to create window: %s\n", SDL_GetError());
    return 1;
  }

  renderer = SDL_CreateRenderer(window, -1, 0);
  if (renderer == NULL) {
    fprintf(stderr, "Error: Unable to create renderer: %s\n", SDL_GetError());
    return 1;
  }

  texture = SDL_CreateTexture(renderer,
    SDL_PIXELFORMAT_RGBA8888,
    SDL_TEXTUREACCESS_STREAMING,
    VIDEO_SCREEN_WIDTH, VIDEO_SCREEN_HEIGHT);
  if (texture == NULL) {
    fprintf(stderr, "Error: Unable to create texture: %s\n", SDL_GetError());
    return 1;
  }

  pixels = malloc(VIDEO_SCREEN_WIDTH * VIDEO_SCREEN_HEIGHT * sizeof(Uint32));

  SDL_initFramerate(&manager);

  if (frame_rate < 0) {
    frame_rate = 0;
    fprintf( stderr, "Warning: Negative frame rate, setting to 0 (unlimited)\n" );
  }
  if (frame_rate > MAX_FRAME_RATE) {
    frame_rate = MAX_FRAME_RATE;
    fprintf( stderr, "Warning: Frame rate above maximum allowed (%d) setting to maximum\n", MAX_FRAME_RATE );
  }
  if (frame_rate) {
    SDL_setFramerate(&manager, frame_rate);
  }

  return 0;
}

void video_set_pixel(unsigned int x, unsigned int y, uint32_t pixel) {
  pixels[(VIDEO_SCREEN_WIDTH*y) + x] = pixel;
}

void video_flip() {
  SDL_UpdateTexture(texture, NULL, pixels, VIDEO_SCREEN_WIDTH * sizeof(Uint32));

  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);
}

void video_wait_frame() {
  if (frame_rate) {
    SDL_framerateDelay(&manager);
  }
}


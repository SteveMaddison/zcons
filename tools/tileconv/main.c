#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define TILE_WIDTH   8
#define TILE_HEIGHT  8
#define TILESET_SIZE 256

Uint32 get_pixel(SDL_Surface *surface, int x, int y) {
  Uint32 *pixels = (Uint32 *)surface->pixels;
  return pixels[( y * surface->w) + x];
}

int main(int argc, char *argv[]) {
  SDL_Surface *in_surface = NULL;
  SDL_Surface *surface = NULL;
  SDL_PixelFormat *rgba;
  const char *filename = argv[1];
  int cols = 0, rows = 0;
  int tile = 0;
  int px = 0, py = 0;
  int col = 0, row = 0;
  Uint8 tile_data[TILESET_SIZE*TILE_WIDTH*TILE_HEIGHT]; 

  if (filename == NULL) {
    fprintf(stderr, "No file name provided.\n");
    return 1;
  }

  in_surface = IMG_Load(filename);

  if (in_surface == NULL) {
    fprintf(stderr, "Couldn't load image from %s\n", filename);
    return 1;
  }

  cols = in_surface->w / TILE_WIDTH;
  rows = in_surface->h / TILE_HEIGHT;

  printf("Read %s (%d x %d x %dbpp)\n", filename, in_surface->w, in_surface->h, in_surface->format->BitsPerPixel);
  printf("Max %d x %d = %d tiles\n", cols, rows, cols * rows);

  rgba = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
  surface = SDL_ConvertSurface(in_surface, rgba, 0);

  while (tile < TILESET_SIZE) {
    int tile_byte = 0;

    for (py = 0; py < TILE_HEIGHT ; py++) {
      for (px = 0; px < TILE_WIDTH ; px++) {
        Uint32 pixel = get_pixel(surface, (col*TILE_WIDTH) + px, (row*TILE_HEIGHT) + py);
        Uint8 byte = 0;
        Uint8 red, green, blue = 0;

        red   = (pixel & 0xff000000) >> 24;
        green = (pixel & 0x00ff0000) >> 16;
        blue  = (pixel & 0x0000ff00) >> 8;

        byte |= (red/0x55)   << 6;
        byte |= (green/0x55) << 4;
        byte |= (blue/0x55)  << 2;

        tile_data[(tile*(TILE_WIDTH*TILE_HEIGHT)) + tile_byte] = byte;
        tile_byte++;
      }
    }

    col++;
    if (col == cols) {
      row++;
      col = 0;
    }

    tile++;
  }

  return 0;
}


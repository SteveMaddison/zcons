#include "vpu.h"
#include "video.h"
#include "memory.h"

static unsigned int tileset_offset = 1;
static unsigned int video_mode = 0;
static uint8_t palette_data[16] = {
  0x00,
  0xc0,
  0xf0,
  0x30,
  0x3c,
  0x0c,
  0x3c,
  0xcc,
  0xc0,
  0xf0,
  0x30,
  0x3c,
  0x0c,
  0x3c,
  0xcc,
  0xfc,
};

#define VPU_TILESET_BITS    14
#define VPU_TILESET_SIZE    (1<<(TILESET_BITS))
#define VPU_TILE_WIDTH      8
#define VPU_TILE_HEIGHT     8
#define VPU_SCREEN_TILES_X  40
#define VPU_SCREEN_TILES_Y  30

#define VPU_BITS_PER_PIXEL  8
#define VPU_PIXELS_PER_BYTE (8/(VPU_BITS_PER_PIXEL))
#define VPU_BYTES_PER_TILE  (((VPU_TILE_WIDTH)*(VPU_TILE_HEIGHT))/(VPU_PIXELS_PER_BYTE))

int vpu_init() {
  return 0;
}

void vpu_draw_line(unsigned int line) {
  unsigned int tile_row = line / VPU_TILE_HEIGHT;
  unsigned int tile_offset = line % VPU_TILE_HEIGHT;
  unsigned int vram_address = VRAM_BASE;
  unsigned int tile_address = 0;
  unsigned int tile_x = 0;
  unsigned int tile_pixel_segment = 0;
  unsigned int pixel_x = 0;
  uint8_t tile_data = 0;
  uint8_t pixel_data = 0;
  unsigned int scratch = 0;
  uint32_t pixel = 0;

  switch (video_mode) {
    case 0: {
      /* First tile in the row. */
      vram_address += tile_row * VPU_SCREEN_TILES_X;

      for (tile_x = 0; tile_x < VPU_SCREEN_TILES_X; tile_x++) {
        tile_address =  (memory_read(vram_address) * VPU_BYTES_PER_TILE);
        tile_address += (tile_offset * (VPU_TILE_WIDTH/VPU_PIXELS_PER_BYTE));
        tile_address |= tileset_offset << VPU_TILESET_BITS;

        for (tile_pixel_segment = 0; tile_pixel_segment < (VPU_TILE_WIDTH/VPU_PIXELS_PER_BYTE) ; tile_pixel_segment++ ) {
          pixel_data = memory_read(tile_address);
          pixel = (
            ((((pixel_data & 0xc0) >> 6) * 0x55) << 24) |
            ((((pixel_data & 0x3c) >> 4) * 0x55) << 16) |
            ((((pixel_data & 0x0c) >> 2) * 0x55) << 8)
          );
          video_set_pixel(pixel_x, line, pixel);
          pixel_x++;

          tile_address++;
        }

        vram_address++;
      }
      break;;
    }
    case 1: {
      /* First tile in the row. */
      vram_address += tile_row * VPU_SCREEN_TILES_X;

      for (tile_x = 0; tile_x < VPU_SCREEN_TILES_X; tile_x++) {
        tile_address =  (memory_read(vram_address) * VPU_BYTES_PER_TILE);
        tile_address += (tile_offset * (VPU_TILE_WIDTH/VPU_PIXELS_PER_BYTE));
        tile_address |= tileset_offset << VPU_TILESET_BITS;

        for (tile_pixel_segment = 0; tile_pixel_segment < (VPU_TILE_WIDTH/VPU_PIXELS_PER_BYTE) ; tile_pixel_segment++ ) {
          pixel_data = memory_read(tile_address);
          scratch = (pixel_data & 0xf0) >> VPU_BITS_PER_PIXEL;
          scratch = palette_data[scratch];
          pixel = (
            ((((scratch & 0xc0) >> 6) * 0x55) << 8 ) |
            ((((scratch & 0x3c) >> 4) * 0x55) << 16) |
            ((((scratch & 0x0c) >> 2) * 0x55) << 24)
          );
          video_set_pixel(pixel_x, line, pixel);
          pixel_x++;

          scratch = pixel_data & 0x0f;
          scratch = palette_data[scratch];
          pixel = (
            ((((scratch & 0xc0) >> 6) * 0x55) << 8 ) |
            ((((scratch & 0x3c) >> 4) * 0x55) << 16) |
            ((((scratch & 0x0c) >> 2) * 0x55) << 24)
          );
          video_set_pixel(pixel_x, line, pixel);
          pixel_x++;

          tile_address++;
        }

        vram_address++;
      }
      break;;
    }
  }
}

void vpu_draw_screen() {
  int line = 0;

  for (line = 0 ; line < (VPU_SCREEN_TILES_Y * VPU_TILE_HEIGHT) ; line++) {
    vpu_draw_line(line);
  }
}


#ifndef __VPU_H__
#define __VPU_H__

#define VPU_TILESET_BITS   8
#define VPU_TILESET_SIZE   (1<<(TILESET_BITS))
#define VPU_TILE_WIDTH     8
#define VPU_TILE_HEIGHT    8
#define VPU_SCREEN_TILES_X 40
#define VPU_SCREEN_TILES_Y 30

int vpu_init();
void vpu_draw_line(unsigned int line);
void vpu_draw_screen();

#endif

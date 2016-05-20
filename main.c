#include <stdio.h>
#include "memory.h"
#include "video.h"
#include "vpu.h"

int main(int argc, char* argv[]) {
  int i = 0;
  unsigned int frame = 0;

  video_init();

  memory_init();
  vpu_init();

  memory_write(0x0000, 0x11);
  memory_write(0x0001, 0x11);
  memory_write(0x0002, 0x11);
  memory_write(0x0003, 0x11);

  memory_write(0x0010, 0x22);
  memory_write(0x0011, 0x22);
  memory_write(0x0012, 0x22);
  memory_write(0x0013, 0x22);

  memory_write(0x0020, 0x33);
  memory_write(0x0021, 0x33);
  memory_write(0x0022, 0x33);
  memory_write(0x0023, 0x33);

  memory_write(0x0030, 0x44);
  memory_write(0x0031, 0x44);
  memory_write(0x0032, 0x44);
  memory_write(0x0033, 0x44);

  for (i = VRAM_BASE; i < VRAM_BASE+VRAM_SIZE ; i++) {
    memory_write(i, i % 4);
  }

  for (frame = 0 ; frame < 120 ; frame++) {
    //memory_write(VRAM_BASE+frame, 0x01);

    vpu_draw_screen();

    video_flip();
    video_wait_frame();
  }

  return 0;
}


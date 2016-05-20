#include <stdio.h>
#include <unistd.h>
#include "memory.h"
#include "video.h"
#include "vpu.h"

int main(int argc, char* argv[]) {
  int i = 0;

  video_init();

  memory_init();
  vpu_init();

  memory_write(0x0000, 0x33);
  memory_write(0x0001, 0x33);
  memory_write(0x0002, 0x33);
  memory_write(0x0003, 0x33);

  memory_write(0x0004, 0x30);
  memory_write(0x0007, 0x03);

  memory_write(0x0008, 0x30);
  memory_write(0x000b, 0x03);

  memory_write(0x000c, 0x30);
  memory_write(0x000f, 0x03);

  memory_write(0x0010, 0x30);
  memory_write(0x0013, 0x03);

  memory_write(0x0014, 0x30);
  memory_write(0x0017, 0x03);

  memory_write(0x0018, 0x30);
  memory_write(0x001b, 0x03);

  memory_write(0x001c, 0x33);
  memory_write(0x001d, 0x33);
  memory_write(0x001e, 0x33);
  memory_write(0x001f, 0x33);

  vpu_draw_screen();
  video_flip();

  sleep(1);

  return 0;
}


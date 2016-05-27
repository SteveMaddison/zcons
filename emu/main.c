#include <stdio.h>
#include "input.h"
#include "memory.h"
#include "video.h"
#include "vpu.h"


static int old_status[2][2];

int main(int argc, char* argv[]) {
  int i,j = 0;
  unsigned int frame = 0;

  video_init();

  input_init();
  memory_init();
  vpu_init();

  memory_write(0x0000, 0xc0);
  memory_write(0x0001, 0xc0);
  memory_write(0x0002, 0xc0);
  memory_write(0x0003, 0xc0);

  memory_write(0x0004, 0x30);
  memory_write(0x0005, 0x30);
  memory_write(0x0006, 0x30);
  memory_write(0x0007, 0x30);

  memory_write(0x0008, 0x0c);
  memory_write(0x0009, 0x0c);
  memory_write(0x000a, 0x0c);
  memory_write(0x000b, 0x0c);

  while (input_quit() == 0) {
    vpu_draw_screen();

    video_flip();
    video_wait_frame();

    input_process();

    if (
      input_controller_status(0,0) != old_status[0][0] ||
      input_controller_status(0,1) != old_status[0][1] ||
      input_controller_status(1,0) != old_status[1][0] ||
      input_controller_status(1,1) != old_status[1][1]
    ) {
      printf("%02x %02x %02x %02x\n",
        input_controller_status(0,0),
        input_controller_status(0,1),
        input_controller_status(1,0),
        input_controller_status(1,1)
      );
    }

    old_status[0][0] = input_controller_status(0,0);
    old_status[0][1] = input_controller_status(0,1);
    old_status[1][0] = input_controller_status(1,0);
    old_status[1][1] = input_controller_status(1,1);
  }

  return 0;
}

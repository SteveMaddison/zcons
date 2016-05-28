#include <stdio.h>
#include "input.h"
#include "memory.h"
#include "video.h"
#include "vpu.h"


int main(int argc, char* argv[]) {
  int i,j = 0;
  unsigned int frame = 0;
  char *rom_file = NULL;
  int rom_size = 0;

  if (argc < 2) {
    fprintf(stderr, "Usage: %s ROM_FILE\n", argv[0]);
    return 1;
  }

  rom_file = argv[1];
  memory_init();
  rom_size = memory_load(rom_file);

  if (rom_size < 0) {
    fprintf(stderr, "Couldn't read ROM file %s\n", rom_file);
    return 1;
  }

  printf("Read ROM %s (%d bytes)\n", rom_file, rom_size);

  video_init();
  input_init();
  vpu_init();

  while (input_quit() == 0) {
    vpu_draw_screen();

    video_flip();
    video_wait_frame();

    input_process();

  }

  return 0;
}


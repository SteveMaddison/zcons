#include <stdio.h>
#include "input.h"
#include "io.h"
#include "memory.h"
#include "video.h"
#include "vpu.h"
#include "z80emu/z80emu.h"

#define Z80_CPU_SPEED       (20 * 1000 * 1000) /* In Hz. */
#define Z80_CYCLES_PER_STEP (Z80_CPU_SPEED / 50)
Z80_STATE z80_state;

int main(int argc, char* argv[]) {
  int i,j = 0;
  unsigned int frame = 0;
  char *rom_file = NULL;
  int rom_size = 0;
  double z80_cycles = 0;

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

  io_init();
  video_init();
  input_init();
  vpu_init();

  Z80Reset(&z80_state);
  z80_state.pc = 0;

  while (input_quit() == 0) {
    vpu_draw_screen();

    video_flip();
    video_wait_frame();

    input_process();

    z80_cycles += Z80Emulate(&z80_state, Z80_CYCLES_PER_STEP);

    frame++;
  }

  printf("Ran %d frames and %f Z80 cycles.\n", frame, z80_cycles);

  return 0;
}


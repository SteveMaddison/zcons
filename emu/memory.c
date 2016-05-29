#include "memory.h"
#include <stdio.h>
#include <string.h>

static uint8_t memory[MEMORY_SIZE];

int memory_init() {
  memset(memory, 0, sizeof(memory));
  printf("memory: Initialised %lu bytes\n", sizeof(memory));

  return 0;
}

int memory_load(char *filename) {
  FILE *f = NULL;
  int rom_size = 0;

  f = fopen(filename, "rb");
  if (f == NULL) {
    return -1;
  }

  fseek(f, 0, SEEK_END);
  rom_size = ftell(f);

  fseek(f, 0, SEEK_SET);
  fread(memory, rom_size, 1, f);

  return rom_size;
}

uint8_t memory_read(unsigned int address) {
/*if (address >= 0xff00) {
    printf("< %04x %02x (%d)\n", address & (MEMORY_SIZE-1), memory[address& (MEMORY_SIZE-1)], memory[address& (MEMORY_SIZE-1)]);
  }*/
  return memory[address & (MEMORY_SIZE-1)];
}

void memory_write(unsigned int address, uint8_t data) {
/*if (address >= 0xf000) {
    printf("> %04x %02x (%d)\n", address, data, data);
  }*/
  memory[address & (MEMORY_SIZE-1)] = data;
}

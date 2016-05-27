#include "memory.h"
#include <stdio.h>
#include <string.h>

static uint8_t memory[MEMORY_SIZE];

int memory_init() {
  memset(memory, 0, sizeof(memory));
  printf("memory: Initialised %lu bytes\n", sizeof(memory));

  return 0;
}

uint8_t memory_read(unsigned int address) {
  return memory[address];
}

void memory_write(unsigned int address, uint8_t data) {
  memory[address] = data;
}

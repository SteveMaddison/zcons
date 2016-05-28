#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <stdint.h>

#define BUS_WIDTH 16
#define MEMORY_SIZE (1<<(BUS_WIDTH))

#define VRAM_BASE 0xf000
#define VRAM_SIZE 0x1000

int memory_init();

int memory_load(char *filename);
uint8_t memory_read(unsigned int address);
void memory_write(unsigned int address, uint8_t data);

#endif

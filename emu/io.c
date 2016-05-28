#include "io.h"
#include <stdio.h>
#include <string.h>

static uint8_t io_port[IO_PORTS];

int io_init() {
  memset(io_port, 0, sizeof(io_port));
  return 0;
}

uint8_t io_read(unsigned int address) {
  return io_port[address];
}

void io_write(unsigned int address, uint8_t data) {
  io_port[address & (IO_PORTS-1)] = data;
}

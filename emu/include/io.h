#ifndef __IO_H__
#define __IO_H__

#include <stdint.h>

#define IO_PORTS (1<<8)

int io_init();

uint8_t io_read(unsigned int address);
void io_write(unsigned int address, uint8_t data);

#endif

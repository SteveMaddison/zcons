#ifndef __INPUT_H__
#define __INPUT_H__

#include <stdint.h>

#define INPUT_CONTROLLERS 2

#define INPUT_CONTROLLER_BASE 0x20

void input_init();
void input_process();
int input_quit();

uint8_t input_controller_status(int player, int reg);

#endif

#include "input.h"

#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>

#define INPUT_KEY_QUIT     SDLK_ESCAPE

#define INPUT_KEY_P1_UP    SDLK_w
#define INPUT_KEY_P1_DOWN  SDLK_s
#define INPUT_KEY_P1_LEFT  SDLK_a
#define INPUT_KEY_P1_RIGHT SDLK_d
#define INPUT_KEY_P1_A     SDLK_i
#define INPUT_KEY_P1_B     SDLK_o
#define INPUT_KEY_P1_C     SDLK_p
#define INPUT_KEY_P1_START SDLK_SPACE

#define INPUT_KEY_P2_UP    SDLK_UP
#define INPUT_KEY_P2_DOWN  SDLK_DOWN
#define INPUT_KEY_P2_LEFT  SDLK_LEFT
#define INPUT_KEY_P2_RIGHT SDLK_RIGHT
#define INPUT_KEY_P2_A     SDLK_KP_1
#define INPUT_KEY_P2_B     SDLK_KP_2
#define INPUT_KEY_P2_C     SDLK_KP_3
#define INPUT_KEY_P2_START SDLK_KP_0

#define INPUT_STATUS_UP    0x01
#define INPUT_STATUS_DOWN  0x02
#define INPUT_STATUS_LEFT  0x03
#define INPUT_STATUS_RIGHT 0x04
#define INPUT_STATUS_A     0x08
#define INPUT_STATUS_START 0x10
#define INPUT_STATUS_B     0x08
#define INPUT_STATUS_C     0x10

static int quit = 0;
static uint8_t controller_status[INPUT_CONTROLLERS][2];

void input_init() {
  memset(controller_status, 0, sizeof(controller_status));
}

void input_process_key(SDL_KeyboardEvent *key) {
  if (key == NULL) {
    return;
  }

  if (key->keysym.sym == INPUT_KEY_QUIT ) {
    quit = 1;
  }

  if (key->type == SDL_KEYDOWN) {
    switch (key->keysym.sym) {
      /* P1 */
      case INPUT_KEY_P1_UP:
        controller_status[0][0] |= INPUT_STATUS_UP;
        controller_status[0][1] |= INPUT_STATUS_UP;
        break;;
      case INPUT_KEY_P1_DOWN:
        controller_status[0][0] |= INPUT_STATUS_DOWN;
        controller_status[0][1] |= INPUT_STATUS_DOWN;
        break;;
      case INPUT_KEY_P1_LEFT:
        controller_status[0][1] |= INPUT_STATUS_LEFT;
        break;;
      case INPUT_KEY_P1_RIGHT:
        controller_status[0][1] |= INPUT_STATUS_RIGHT;
        break;;
      case INPUT_KEY_P1_A:
        controller_status[0][0] |= INPUT_STATUS_A;
        break;;
      case INPUT_KEY_P1_B:
        controller_status[0][1] |= INPUT_STATUS_B;
        break;;
      case INPUT_KEY_P1_C:
        controller_status[0][1] |= INPUT_STATUS_C;
        break;;
      case INPUT_KEY_P1_START:
        controller_status[0][0] |= INPUT_STATUS_START;
        break;;
      /* P2 */
      case INPUT_KEY_P2_UP:
        controller_status[1][0] |= INPUT_STATUS_UP;
        controller_status[1][1] |= INPUT_STATUS_UP;
        break;;
      case INPUT_KEY_P2_DOWN:
        controller_status[1][0] |= INPUT_STATUS_DOWN;
        controller_status[1][1] |= INPUT_STATUS_DOWN;
        break;;
      case INPUT_KEY_P2_LEFT:
        controller_status[1][1] |= INPUT_STATUS_LEFT;
        break;;
      case INPUT_KEY_P2_RIGHT:
        controller_status[1][1] |= INPUT_STATUS_RIGHT;
        break;;
      case INPUT_KEY_P2_A:
        controller_status[1][0] |= INPUT_STATUS_A;
        break;;
      case INPUT_KEY_P2_B:
        controller_status[1][1] |= INPUT_STATUS_B;
        break;;
      case INPUT_KEY_P2_C:
        controller_status[1][1] |= INPUT_STATUS_C;
        break;;
      case INPUT_KEY_P2_START:
        controller_status[1][0] |= INPUT_STATUS_START;
        break;;
      default:
        break;;
    }
  }
  else if (key->type == SDL_KEYUP) {
    switch (key->keysym.sym) {
      /* P1 */
      case INPUT_KEY_P1_UP:
        controller_status[0][0] &= ~INPUT_STATUS_UP;
        controller_status[0][1] &= ~INPUT_STATUS_UP;
        break;;
      case INPUT_KEY_P1_DOWN:
        controller_status[0][0] &= ~INPUT_STATUS_DOWN;
        controller_status[0][1] &= ~INPUT_STATUS_DOWN;
        break;;
      case INPUT_KEY_P1_LEFT:
        controller_status[0][1] &= ~INPUT_STATUS_LEFT;
        break;;
      case INPUT_KEY_P1_RIGHT:
        controller_status[0][1] &= ~INPUT_STATUS_RIGHT;
        break;;
      case INPUT_KEY_P1_A:
        controller_status[0][0] &= ~INPUT_STATUS_A;
        break;;
      case INPUT_KEY_P1_B:
        controller_status[0][1] &= ~INPUT_STATUS_B;
        break;;
      case INPUT_KEY_P1_C:
        controller_status[0][1] &= ~INPUT_STATUS_C;
        break;;
      case INPUT_KEY_P1_START:
        controller_status[0][0] &= ~INPUT_STATUS_START;
        break;;
      /* P2 */
      case INPUT_KEY_P2_UP:
        controller_status[1][0] &= ~INPUT_STATUS_UP;
        controller_status[1][1] &= ~INPUT_STATUS_UP;
        break;;
      case INPUT_KEY_P2_DOWN:
        controller_status[1][0] &= ~INPUT_STATUS_DOWN;
        controller_status[1][1] &= ~INPUT_STATUS_DOWN;
        break;;
      case INPUT_KEY_P2_LEFT:
        controller_status[1][1] &= ~INPUT_STATUS_LEFT;
        break;;
      case INPUT_KEY_P2_RIGHT:
        controller_status[1][1] &= ~INPUT_STATUS_RIGHT;
        break;;
      case INPUT_KEY_P2_A:
        controller_status[1][0] &= ~INPUT_STATUS_A;
        break;;
      case INPUT_KEY_P2_B:
        controller_status[1][1] &= ~INPUT_STATUS_B;
        break;;
      case INPUT_KEY_P2_C:
        controller_status[1][1] &= ~INPUT_STATUS_C;
        break;;
      case INPUT_KEY_P2_START:
        controller_status[1][0] &= ~INPUT_STATUS_START;
        break;;
      default:
        break;;
    }
  }
}

void input_process() {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        quit = 1;
        break;;
      case SDL_KEYDOWN:
      case SDL_KEYUP:
        input_process_key(&event.key);
        break;;
      default:
        break;;
    }
  }
}

int input_quit() {
  return quit;
}

uint8_t input_controller_status(int player, int reg) {
  return controller_status[player][reg];
}

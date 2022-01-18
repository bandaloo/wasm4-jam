#include "engine.h"
#include "wasm4.h"

uint8_t previous_gamepad;

const uint8_t smiley[] = {
    0b11000011, 0b10000001, 0b00100100, 0b00100100,
    0b00000000, 0b00100100, 0b10011001, 0b11000011,
};

int frame = 0;

char *itoa(int val, int base) {
  static char buf[32] = {0};

  int i = 30;
  for (; val && i; --i, val /= base) {
    buf[i] = "0123456789abcdef"[val % base];
  }

  return &buf[i + 1];
}

void start() {
  PALETTE[0] = 0xfff6d3;
  PALETTE[1] = 0xf9a875;
  PALETTE[2] = 0xeb6b6f;
  PALETTE[3] = 0x7c3f58;

  *DRAW_COLORS = 0x2340;

  Entity *player = makePlayer(40, 40);
  addEntity(player);

  trace(itoa(999, 10));
}

void update() {
  doDrawSystem();
  frame++;
}

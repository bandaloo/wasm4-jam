#include "engine.h"
#include "sprites.h"
#include "wasm4.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

uint8_t previous_gamepad;

const uint8_t smiley[] = {
    0b11000011, 0b10000001, 0b00100100, 0b00100100,
    0b00000000, 0b00100100, 0b10011001, 0b11000011,
};

int frame = 0;

void start() {
  trace("START!");
  PALETTE[0] = 0xfff6d3;
  PALETTE[1] = 0xf9a875;
  PALETTE[2] = 0xeb6b6f;
  PALETTE[3] = 0x7c3f58;
  Entity *player = makePlayer(6, 6);
  PosComponentData *pos = (PosComponentData *)findComponent(player, POS);

  for (int i = 0; i < pos->pos.x; i++) {
    trace("tracing pos");
  }

  PhysicsComponentData *physics =
      (PhysicsComponentData *)findComponent(player, PHYSICS);

  for (int i = 0; i < physics->drag; i++) {
    trace("tracing physics");
  }
}

void update() {
  uint8_t gamepad = *GAMEPAD1;
  uint8_t pressed_this_frame = gamepad & (gamepad ^ previous_gamepad);

  // *DRAW_COLORS = 3;
  // text("Hello from C!", 10, 10);

  // if (gamepad & BUTTON_1) {
  //   *DRAW_COLORS = 1;
  // }

  *DRAW_COLORS = 0x2340;
  float test = 5 * cos(frame / 4.0);

  for (int i = 0; i < 32; i++) {
    blitSub(flower_spr,
            (SCREEN_SIZE - FLOWER_WIDTH) / 2 +
                i * 3.0 * cos(i / 300.0 * frame / 4.0),
            (SCREEN_SIZE - FLOWER_WIDTH) / 2 +
                i * 3.0 * sin(i / 300.0 * frame / 4.0),
            FLOWER_WIDTH, FLOWER_HEIGHT,
            (((i + frame / 10) / 5) % 2) * FLOWER_WIDTH, 0,
            FLOWER_WIDTH * FLOWER_FRAMES, FLOWER_FLAGS);
  }

  // blit(bunny_spr, -5.0, -5.0, BUNNY_WIDTH, BUNNY_HEIGHT, BUNNY_FLAGS);
  // text("Press X to blink", 16, 90);

  frame++;
}

#pragma once

#include "engine.h"
#include "wasm4.h"

#include <stdint.h>

const uint8_t FLOWER_DATA[128] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x3c, 0x00, 0x00, 0x0f, 0x0f, 0x00,
    0x00, 0xff, 0xff, 0x00, 0x03, 0xff, 0xff, 0xc0, 0x00, 0x3a, 0xab, 0x3c,
    0x03, 0xfa, 0xab, 0x00, 0x0f, 0xe9, 0xaa, 0xfc, 0x00, 0xe9, 0xaa, 0xfc,
    0x0f, 0xea, 0xa9, 0xbc, 0x0f, 0xea, 0xa9, 0xbf, 0x03, 0xf9, 0xaa, 0xbc,
    0x0f, 0xf9, 0xaa, 0xbf, 0x00, 0x3e, 0x5a, 0xb0, 0x00, 0x3e, 0x5a, 0xb0,
    0x14, 0xff, 0xea, 0xfc, 0x05, 0xff, 0xff, 0xfc, 0x15, 0xff, 0xff, 0xfc,
    0x16, 0xfb, 0xfe, 0xfc, 0x06, 0xaa, 0xfa, 0xfc, 0x16, 0xaa, 0xfa, 0x94,
    0x02, 0xaa, 0xaa, 0x94, 0x02, 0xaa, 0xaa, 0x94, 0x02, 0xaa, 0xaa, 0x90,
    0x00, 0x56, 0x65, 0x04, 0x00, 0x56, 0x65, 0x00, 0x00, 0xaa, 0xaa, 0x00,
    0x00, 0xaa, 0xaa, 0x00, 0x00, 0xaa, 0xaa, 0x00, 0x00, 0xaa, 0xaa, 0x00,
    0x00, 0xaa, 0xaa, 0x00, 0x00, 0xaa, 0xaa, 0x00};

const Sprite FLOWER_SPRITE = {.width = 16,
                              .height = 16,
                              .frames = 2,
                              .flags = BLIT_2BPP,
                              .data = FLOWER_DATA};

const uint8_t BLOCKS_DATA[256] = {
    0x15, 0x55, 0x55, 0x54, 0x02, 0xab, 0xfa, 0x80, 0xaa, 0x6a, 0xaa, 0xaa,
    0x00, 0x55, 0x55, 0x00, 0x6a, 0xaa, 0xaa, 0xa9, 0x2a, 0x95, 0xfa, 0x94,
    0xff, 0x6f, 0xff, 0xff, 0x05, 0x55, 0x55, 0x50, 0x65, 0x55, 0x55, 0x5d,
    0xaa, 0x57, 0xfa, 0x55, 0xff, 0x6f, 0xff, 0xff, 0x15, 0xa9, 0x55, 0x54,
    0x66, 0xaa, 0xaa, 0x9d, 0xff, 0xff, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55,
    0x16, 0xa5, 0x55, 0x54, 0x66, 0x55, 0x55, 0xdd, 0xa9, 0xfa, 0xaa, 0xbf,
    0xaa, 0xaa, 0xa9, 0xaa, 0x5a, 0x95, 0x55, 0x55, 0x66, 0x6a, 0xa9, 0xdd,
    0x97, 0xea, 0x55, 0xff, 0xff, 0xff, 0xfd, 0xbf, 0x5a, 0x55, 0x55, 0x55,
    0x66, 0x65, 0x5d, 0xdd, 0xbf, 0xa5, 0x5f, 0xe7, 0xff, 0xff, 0xfd, 0xbf,
    0x59, 0x55, 0x55, 0x55, 0x66, 0x66, 0x9d, 0xdd, 0xfe, 0x97, 0xfe, 0x97,
    0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x57, 0x66, 0x66, 0xdd, 0xdd,
    0xff, 0xff, 0xea, 0x5f, 0xaa, 0x6a, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x57,
    0x66, 0x65, 0x5d, 0xdd, 0xea, 0xab, 0xff, 0xff, 0xff, 0x6f, 0xff, 0xff,
    0x55, 0x55, 0x55, 0x57, 0x66, 0x6f, 0xfd, 0xdd, 0xfe, 0x96, 0xaa, 0xff,
    0xff, 0x6f, 0xff, 0xff, 0x55, 0x55, 0x55, 0x57, 0x66, 0x55, 0x55, 0xdd,
    0xbf, 0xd5, 0x57, 0xff, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x57,
    0x66, 0xff, 0xff, 0xdd, 0xab, 0xff, 0xff, 0xa5, 0xaa, 0xaa, 0xa9, 0xaa,
    0x15, 0x55, 0x55, 0x5c, 0x65, 0x55, 0x55, 0x5d, 0xaa, 0xa9, 0xea, 0x95,
    0xff, 0xff, 0xfd, 0xbf, 0x15, 0x55, 0x55, 0x5c, 0x7f, 0xff, 0xff, 0xfd,
    0x2a, 0x95, 0xe9, 0x54, 0xff, 0xff, 0xfd, 0xbf, 0x05, 0x55, 0x55, 0xf0,
    0x15, 0x55, 0x55, 0x54, 0x01, 0x57, 0xf5, 0x40, 0x55, 0x55, 0x55, 0x55,
    0x00, 0x57, 0xff, 0x00};

const Sprite BLOCKS_SPRITE = {.width = 16,
                              .height = 16,
                              .frames = 4,
                              .flags = BLIT_2BPP,
                              .data = BLOCKS_DATA};

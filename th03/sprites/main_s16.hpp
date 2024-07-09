// SPRITE16 sprite area contents for MAIN.EXE.

#include "th03/main/sprite16.hpp"

#define XY(x, y) ((y * ROW_SIZE) + (x / BYTE_DOTS))

// Base position for all attack sprites
static const sprite16_offset_t SO_ATTACK_P1 = XY(0,   0);
static const sprite16_offset_t SO_ATTACK_P2 = XY(320, 0);

static const sprite16_offset_t SO_HITCIRCLE = XY(128, 80);

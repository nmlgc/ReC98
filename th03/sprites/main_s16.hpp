// SPRITE16 sprite area contents for MAIN.EXE.

#include "th03/main/sprite16.hpp"

static const int EXPLOSION_CELS = 4;

#define XY(x, y) ((y * ROW_SIZE) + (x / BYTE_DOTS))

static const pixel_t PELLET_CLOUD_W = 32;
static const pixel_t PELLET_CLOUD_H = 32;
static const int PELLET_CLOUD_CELS = 3;
static const unsigned int BULLET16_CELS = 4;
static const unsigned int BULLET16_TRAIL_CELS = 3;

// Base position for all attack sprites
static const sprite16_offset_t SO_ATTACK_P1 = XY(0,   0);
static const sprite16_offset_t SO_ATTACK_P2 = XY(320, 0);

// Character-specific 16×16 bullet, with [BULLET16_CELS] horizontally adjacent
// cels that either animate the same bullet, or provide [BULLET16_TRAIL_CELS]
// trail sprites for a single main bullet sprite.
static const sprite16_offset_t SO_BULLET16 = XY(64, 0);

static const sprite16_offset_t SO_HITCIRCLE = XY(128, 80);

static const sprite16_offset_t SO_PELLET_CLOUD = XY(528, 80);

extern const sprite16_offset_t SO_EXPLOSIONS[][EXPLOSION_CELS];

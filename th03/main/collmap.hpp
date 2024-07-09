/// Collision bitmap
/// ----------------
/// TH03 tracks collidable areas by maintaining a bitmap of each playfield,
/// where each set bit corresponds to a tile occupied by a collidable entity.
/// To save a bit of memory, these bitmaps are reduced to a quarter of the
/// screen resolution: Every bit corresponds to a tile of 2×2 screen pixels,
// or 2×1 VRAM pixels.

#include "th03/main/playfld.hpp"
#include <stddef.h>

typedef int collmap_tile_amount_t;

// Constants
// ---------

static const pixel_t COLLMAP_TILE_W = 2;
static const pixel_t COLLMAP_TILE_H = 2;
static const char COLLMAP_TILE_W_BITS = 1;
static const char COLLMAP_TILE_H_BITS = 1;

static const size_t COLLMAP_MEMORY_W = ((PLAYFIELD_W / COLLMAP_TILE_W) / 8);
static const size_t COLLMAP_H = (PLAYFIELD_H / COLLMAP_TILE_H);
static const size_t COLLMAP_SIZE = (COLLMAP_MEMORY_W * COLLMAP_H);

// Matches the size of the player hitbox. Increasing this distance beyond that
// size turns these stripes from an optimization into something that actually
// affects game difficulty.
static const collmap_tile_amount_t COLLMAP_RECT_VSTRIPE_DISTANCE = 4;

static const collmap_tile_amount_t COLLMAP_SLOPE_VSTRIPE_DISTANCE = 2;
// ---------

// Function parameters
// -------------------

// MODDERS: These two are stored at the same address in memory. Not having to
// use a union here is one advantage of emitting these in an undecompilable ASM
// translation unit, I guess...
extern PlayfieldPoint collmap_center;
extern PlayfieldPoint collmap_topleft;

extern collmap_tile_amount_t collmap_stripe_tile_w;
extern collmap_tile_amount_t collmap_tile_h;
extern PlayfieldPoint collmap_bottomright;
extern pid_t collmap_pid;

// Stored as columns from left to right, not rows from top to bottom.
extern uint8_t collmap[PLAYER_COUNT][COLLMAP_MEMORY_W][COLLMAP_H];
// -------------------

// Sets all bits on every [COLLMAP_RECT_VSTRIPE_DISTANCE]th row of a
// rectangle, clipped at all sides of the collision bitmap.
// Takes the following parameters:
// • [collmap_center] (X and Y)
// • [collmap_stripe_tile_w] (width of the rectangle)
// • [collmap_tile_h] (height of the rectangle)
// • [collmap_pid]
void collmap_set_rect_striped();

// Sets all bits on a straight 1-tile wide vertical line, clipped to the
// height of the collision bitmap. Takes the following parameters:
// • [collmap_topleft] (X and Y)
// • [collmap_tile_h] (height of the line)
// • [collmap_pid]
void collmap_set_vline();

// Sets all bits on every [COLLMAP_SLOPE_VSTRIPE_DISTANCE]th row of a
// potentially sloped vertical line across one whole playfield.
// Takes the following parameters:
// • [collmap_topleft.x] (always uses 0 for [y])
// • [collmap_bottomright.x] (always uses to_sp(PLAYFIELD_H) for [y])
// • [collmap_stripe_tile_w] (between 0 and 7)
// • [collmap_pid]
void collmap_set_slope_striped();
/// ----------------

/// Collision bitmap
/// ----------------
/// TH03 tracks collidable areas by maintaining a bitmap of each playfield,
/// where each set bit corresponds to a tile occupied by a collidable entity.
/// To save a bit of memory, these bitmaps are reduced to a quarter of the
/// screen resolution: Every bit corresponds to a tile of 2×2 screen pixels,
// or 2×1 VRAM pixels.

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
extern unsigned char collmap_pid;

// Stored as columns from left to right, not rows from top to bottom.
extern uint8_t collmap[PLAYER_COUNT][COLLMAP_MEMORY_W][COLLMAP_H];
// -------------------
/// ----------------

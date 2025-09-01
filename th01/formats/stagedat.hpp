#include "platform.h"

/// STAGE?.DAT format, describing the object layout of *all* stages in a scene
/// --------------------------------------------------------------------------

// We *don't* define these in terms of the playfield width and height, for two
// reasons:
// 1) Having a file in /formats/ depend on a constant from /main/ breaks the
//    subsystem hierarchy.
// 2) It's definitely imaginable to mod playfield metrics independent of stage
//    object counts or vice versa. In such a case, we shouldn't break
//    compatibility with the original data files by default.
#define STAGEOBJS_X 20
#define STAGEOBJS_Y 10

static const int STAGEOBJS_COUNT = (STAGEOBJS_X * STAGEOBJS_Y);

#define CARDS_PER_BYTE 4

#if ((STAGEOBJS_X % CARDS_PER_BYTE) != 0)
#error STAGEOBJS_X must be divisible by the amount of cards per byte
#endif

#define STAGEDAT_MAGIC "STAGE"

// Nothing in here is actually read, and none of the referenced file names are
// even part of the released game. Beta content right here!
struct stagedat_header_t {
	char magic[sizeof(STAGEDAT_MAGIC) - 1];
	int8_t id;
	char bgm_fn[8];
	char grf_fn[8];
};

typedef enum {
	OT_NONE = 0,
	OT_BUMPER = 1,

	// On ≥Normal difficulty, these fire the given pellet group (see
	// pellet_group_t) either every [TURRET_SLOW_INTERVAL] frames...
	OT_TURRET_SLOW_1_AIMED = 2,
	OT_TURRET_SLOW_1_RANDOM_NARROW_AIMED = 3,
	OT_TURRET_SLOW_2_SPREAD_WIDE_AIMED = 4,
	OT_TURRET_SLOW_3_SPREAD_WIDE_AIMED = 5,
	OT_TURRET_SLOW_4_SPREAD_WIDE_AIMED = 6,
	OT_TURRET_SLOW_5_SPREAD_WIDE_AIMED = 7,

	// ...or every [TURRET_QUICK_INTERVAL] frames.
	OT_TURRET_QUICK_1_AIMED = 8,
	OT_TURRET_QUICK_1_RANDOM_NARROW_AIMED = 9,
	OT_TURRET_QUICK_2_SPREAD_WIDE_AIMED = 10,
	OT_TURRET_QUICK_3_SPREAD_WIDE_AIMED = 11,
	OT_TURRET_QUICK_4_SPREAD_WIDE_AIMED = 12,
	OT_TURRET_QUICK_5_SPREAD_WIDE_AIMED = 13,

	// ZUN insisted on the card array being just a 1-bit indicator whether a
	// tile is a card or not. Cards with ≥1 HP therefore abuse obstacle types
	// to store their HP value. These apply to the card at the same (x, y)
	// position as the obstacle this enum would have otherwise described.
	// And yes, this means that it's impossible to overlap such a non-0 HP
	// card with an obstacle.
	OT_ACTUALLY_A_CARD = 14,
	OT_ACTUALLY_A_2FLIP_CARD = OT_ACTUALLY_A_CARD,
	OT_ACTUALLY_A_3FLIP_CARD = 15,
	OT_ACTUALLY_A_4FLIP_CARD = 16,

	OT_PORTAL = 17,
	OT_BAR_TOP = 18,
	OT_BAR_BOTTOM = 19,
	OT_BAR_LEFT = 20,
	OT_BAR_RIGHT = 21,
} obstacle_type_t;

struct stagedat_stage_t {
	// Stores the cards of [CARDS_PER_BYTE] horizontal tiles in the lower
	// [CARDS_PER_BYTE] bits. The other bits are unused.
	uint8_t cards[STAGEOBJS_Y][STAGEOBJS_X / CARDS_PER_BYTE];

	int8_t obstacles[STAGEOBJS_Y][STAGEOBJS_X]; // obstacle_type_t
};
/// --------------------------------------------------------------------------

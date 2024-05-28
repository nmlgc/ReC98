/// Stage 3 Boss - Five Magic Stones
/// --------------------------------

#include "pc98.h"

enum stone_t {
	STONE_INNER_WEST = 0,
	STONE_INNER_EAST = 1,
	STONE_OUTER_WEST = 2,
	STONE_OUTER_EAST = 3,
	STONE_NORTH = 4,
	STONE_COUNT,
};

// Coordinates
// -----------

static const pixel_t STONE_W = 32;

extern screen_x_t stone_left[STONE_COUNT];
extern screen_y_t stone_top[STONE_COUNT];
// -----------

// Stage 3 midboss and boss state
// ------------------------------

#include "pc98.h"

static const int MIDBOSS3_COUNT = 2;

enum stone_t {
	STONE_INNER_WEST = 0,
	STONE_INNER_EAST = 1,
	STONE_OUTER_WEST = 2,
	STONE_OUTER_EAST = 3,
	STONE_NORTH = 4,
	STONE_COUNT,
};

extern int16_t stone_damage[STONE_COUNT];
#define midboss3_damage stone_damage
// ------------------------------

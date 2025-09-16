// Stage 3 midboss and boss state
// ------------------------------

#include "pc98.h"

enum midboss3_flag_t {
	M3F_ALIVE = 0,
	M3F_KILL_ANIM = 1,
	M3F_REMOVED = 2,

	_midboss3_flag_t_FORCE_UINT8 = 0xFF
};

static const int MIDBOSS3_COUNT = 2;

enum stone_flag_t {
	SF_DORMANT = 0,
	SF_ACTIVE = 1,
	SF_KILL_ANIM = 2,
	SF_REMOVE = 3, // One more tile invalidation, then transitions to SF_REMOVED
	SF_REMOVED = 4,

	_stone_flag_t_FORCE_UINT8 = 0xFF
};

enum stone_t {
	STONE_INNER_WEST = 0,
	STONE_INNER_EAST = 1,
	STONE_OUTER_WEST = 2,
	STONE_OUTER_EAST = 3,
	STONE_NORTH = 4,
	STONE_COUNT,
};

extern stone_flag_t stone_flag[STONE_COUNT];
#define midboss3_flag reinterpret_cast<midboss3_flag_t*>(stone_flag)

extern int16_t stone_damage[STONE_COUNT];
#define midboss3_damage stone_damage
// ------------------------------

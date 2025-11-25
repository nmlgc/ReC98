/// Gauge and Boss Attacks
/// ----------------------

#include "th03/common.h"

enum gba_flag_t {
	GBAF_NONE = 0,
	GBAF_GAUGE_PELLET_INIT = 1,
	GBAF_GAUGE_PELLET_ACTIVE = 2,
	GBAF_GAUGE_BULLET_INIT = 3,
	GBAF_GAUGE_BULLET_ACTIVE = 4,
	GBAF_BOSS = 5,

	GBAF_PELLET_TO_BULLET = (GBAF_GAUGE_BULLET_INIT - GBAF_GAUGE_PELLET_INIT),

	_gba_flag_t_FORCE_UINT8 = 0xFF
};

extern gba_flag_t gba_flag_next[PLAYER_COUNT];
extern gba_flag_t gba_flag_active[PLAYER_COUNT];

// Gauge Attack levels are 1-based and have 16 possible levels.
static const uint8_t GBA_GAUGE_LEVEL_MIN = 1;
static const uint8_t GBA_GAUGE_LEVEL_MAX = 16;
extern uint8_t gba_gauge_level[PLAYER_COUNT];

// Gauge Attacks are character-specific patterns made up of primarily
// • pellets ("Level 2", available at 50% gauge, consuming 25% gauge) or
// • bullets ("Level 3", available at 75% gauge, consuming 50% gauge),
// and can't include custom entities.
// ZUN bloat: All 9 characters use the same code layout of calling a common
// function that handles both types. Refactoring this to use a single pointer
// would eliminate the resulting 18 boilerplate functions.
extern farfunc_t_near gba_gauge_pattern_pellet[PLAYER_COUNT];
extern farfunc_t_near gba_gauge_pattern_bullet[PLAYER_COUNT];

// ZUN bloat: But how many possible levels does this one have? A
// [gba_boss_level] of 1 would render as 2 next to the gauge, but as 1 in
// the WARNING popup. Since firing a Boss Attack always increments the level,
// it would seem that the popup indicates the level of the *incoming* attack
// while the gauge indicates the level of the *next* one. However, this
// interpretation would contradict 夢時空.TXT, which explicitly describes the
// level next to the gauge as the 「現在のＢＯＳＳアタックのレベル」.
// In any case, this could have been solved more cleanly with a separate
// variable.
// TODO: Look at this again once we've decompiled a few of the Boss Attacks and
// can confirm how they use this variable.
static const uint8_t GBA_BOSS_LEVEL_MAX = 16;
extern uint8_t gba_boss_level;

extern farfunc_t_near gba_boss_update[PLAYER_COUNT];
extern farfunc_t_near gba_boss_render[PLAYER_COUNT];

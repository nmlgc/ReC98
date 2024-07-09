#ifndef TH01_RESIDENT_HPP
#define TH01_RESIDENT_HPP

#include "th01/main/bullet/pellet_s.hpp"
#include "th01/common.h"
#include "th01/score.h"

enum bgm_mode_t {
	BGM_MODE_OFF,
	BGM_MODE_MDRV2,
	BGM_MODE_COUNT,
};

#define BGM_MODES_CENTERED { \
	"  OFF ", \
	"  FM  ", \
}

typedef enum {
	ROUTE_MAKAI,
	ROUTE_JIGOKU,
	ROUTE_COUNT,
} route_t;

enum end_sequence_t {
	ES_NONE,
	ES_MAKAI,
	ES_JIGOKU,
};

enum debug_mode_t {
	DM_OFF = 0,
	DM_STAGESELECT = 1,
	DM_TEST = 2,
	DM_FULL = 3,
};

#define RES_ID "ReiidenConfig"
struct resident_t {
	char id[sizeof(RES_ID)];
	uint8_t rank;
	bgm_mode_t bgm_mode;
	int8_t rem_bombs;
	int8_t credit_lives_extra; // Add 2 for the actual number of lives
	end_sequence_t end_flag; /* ZUN symbol [Strings] */
	int8_t unused_1;
	route_t route;
	int8_t rem_lives;
	int8_t snd_need_init; // ACTUAL TYPE: bool
	int8_t unused_2;
	int8_t debug_mode; // ACTUAL TYPE: debug_mode_t
	pellet_speed_t pellet_speed;
	unsigned long rand;
	score_t score;
	int32_t unused_3;
	uint16_t continues_per_scene[SCENE_COUNT];

	// of the current scene, without the boss stage
	score_t bonus_per_stage[STAGES_PER_SCENE - 1];

	unsigned int stage_id;
	unsigned long hiscore;
	score_t score_highest; // among all continues
	uint16_t point_value;
};

extern resident_t far *resident;

// Redundant copies of resident structure fields to static data
// ------------------------------------------------------------

extern uint8_t rank;
extern int8_t rem_bombs;
extern int8_t credit_lives_extra;
extern end_sequence_t end_flag; /* ZUN symbol [Strings] */
extern int rem_lives; // ZUN bloat: The resident structure just uses int8_t.

// Current gameplay frame plus resident_t::rand, without any frame_delay().
// Displayed as "rand" in the debug output, but can't be /* ZUN symbol */'d
// like that, due to obviously colliding with the C standard library function.
extern unsigned long frame_rand;

extern uscore_t score;
extern int32_t continues_total;

// ZUN bloat: The resident structure just uses uint16_t.
extern int32_t continues_per_scene[SCENE_COUNT];

extern score_t score_highest;

inline void resident_continue_use(void) {
	resident->continues_per_scene[resident->stage_id / STAGES_PER_SCENE]++;
}
// ------------------------------------------------------------

#endif /* TH01_RESIDENT_HPP */

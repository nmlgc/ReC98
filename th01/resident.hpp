#include "th01/common.h"

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

	_route_t_FORCE_INT16 = 0x7FFF
} route_t;

enum end_sequence_t {
	ES_NONE,
	ES_MAKAI,
	ES_JIGOKU,
};

enum debug_mode_t {
	DM_OFF = 0,
	DM_TEST = 1,
	DM_FULL = 3,

	_debug_mode_t_FORCE_INT16 = 0x7FFF
};

// Much like subpixels, pellet speeds are stored pre-multiplied by 40 to allow
// an effective resolution of 0.025 pixels to be losslessly stored in an
// integer. This pre-multiplication is reverted by the pellet spawning
// functions.
typedef int pellet_speed_t;

static const pellet_speed_t PELLET_SPEED_MULTIPLIER = 40;

#define to_pellet_speed(pixel_v) \
	static_cast<pellet_speed_t>(pixel_v * PELLET_SPEED_MULTIPLIER)

#define RES_ID "ReiidenConfig"
typedef struct {
	char id[sizeof(RES_ID)];
	int8_t rank;
	bgm_mode_t bgm_mode;
	int8_t bombs;
	int8_t start_lives_extra; // Add 2 for the actual number of lives
	end_sequence_t end_flag; /* ZUN symbol [Strings] */
	int8_t unused_1;
	int8_t route; // ACTUAL TYPE: route_t
	int8_t rem_lives;
	int8_t snd_need_init; // ACTUAL TYPE: bool
	int8_t unused_2;
	int8_t debug_mode; // ACTUAL TYPE: debug_mode_t
	pellet_speed_t pellet_speed;
	unsigned long rand;
	int32_t score;

	// ZUN bloat: Never actually read from. Even FUUIN.EXE, who does care
	// about this value, manually derives it from [continues_per_scene].
	long continues_total;

	unsigned int continues_per_scene[SCENE_COUNT];

	// of the current scene, without the boss stage
	long bonus_per_stage[STAGES_PER_SCENE - 1];

	unsigned int stage_id;
	unsigned long hiscore;
	long score_highest; // among all continues
	uint16_t point_value;
} resident_t;

extern long continues_total;

extern int8_t route; // ACTUAL TYPE: route_t
extern resident_t far *resident;

inline void resident_continue_use(void) {
	resident->continues_total++;
	continues_total++;
	resident->continues_per_scene[resident->stage_id / STAGES_PER_SCENE]++;
}

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
struct resident_t {
	char id[sizeof(RES_ID)];
	int8_t rank;
	bgm_mode_t bgm_mode;
	int8_t rem_bombs;
	int8_t credit_lives_extra; // Add 2 for the actual number of lives
	end_sequence_t end_flag; /* ZUN symbol [Strings] */
	int8_t unused_1;
	int8_t route; // ACTUAL TYPE: route_t
	int8_t rem_lives;
	int8_t snd_need_init; // ACTUAL TYPE: bool
	int8_t unused_2;
	int8_t debug_mode; // ACTUAL TYPE: debug_mode_t
	pellet_speed_t pellet_speed;
	unsigned long rand;
	score_t score;

	// ZUN bloat: Never actually read from. Even FUUIN.EXE, who does care
	// about this value, manually derives it from [continues_per_scene].
	int32_t continues_total;

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

// ACTUAL TYPE: rank_t
#if (BINARY == 'M')
	extern int8_t rank;
#elif (BINARY == 'E')
	extern uint8_t rank;
#endif

extern bgm_mode_t bgm_mode;
extern int8_t rem_bombs;
extern int8_t credit_lives_extra;
extern end_sequence_t end_flag; /* ZUN symbol [Strings] */
extern int8_t route; // ACTUAL TYPE: route_t
extern int rem_lives; // ZUN bloat: The resident structure just uses int8_t.

// Current gameplay frame plus resident_t::rand, without any frame_delay().
// Displayed as "rand" in the debug output, but can't be /* ZUN symbol */'d
// like that, due to obviously colliding with the C standard library function.
extern unsigned long frame_rand;

#if (BINARY == 'M')
	extern uscore_t score;
#elif (BINARY == 'E')
	extern score_t score;
#endif
extern int32_t continues_total;

// ZUN bloat: The resident structure just uses uint16_t.
extern int32_t continues_per_scene[SCENE_COUNT];

extern score_t score_highest;

inline void resident_continue_use(void) {
	resident->continues_total++;
	continues_total++;
	resident->continues_per_scene[resident->stage_id / STAGES_PER_SCENE]++;
}
// ------------------------------------------------------------

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
	DM_TEST = 1,
	DM_FULL = 3
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
	char rank;
	char bgm_mode; // 0 = off, 1 = FM
	char bombs;
	char start_lives_extra; // Add 2 for the actual number of lives
	end_sequence_t end_flag; /* ZUN symbol [Strings] */
	char unused_1;
	char route;
	char rem_lives;
	char snd_need_init;
	char unused_2;
	debug_mode_t debug_mode;
	pellet_speed_t pellet_speed;
	long rand;
	long score;
	long continues_total;
	unsigned int continues_per_scene[SCENE_COUNT];

	// of the current scene, without the boss stage
	long bonus_per_stage[STAGES_PER_SCENE - 1];

	int stage;
	unsigned long hiscore;
	long score_highest; // among all continues
	uint16_t point_value;
} resident_t;

// ZUN bloat: Synced with the one in the resident structure anyway.
extern long continues_total;

extern route_t route;
extern resident_t far *resident;

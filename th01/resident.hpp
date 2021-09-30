typedef enum {
	ROUTE_MAKAI,
	ROUTE_JIGOKU
} route_t;

typedef enum {
	MODE_REGULAR = 0,
	MODE_TEST = 1,
	MODE_DEBUG = 3
} mode_t;

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
	char end_flag; /* ZUN symbol [Strings] */
	char unused_1;
	char route;
	char rem_lives;
	char snd_need_init;
	char unused_2;
	char mode;
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

extern resident_t *resident;

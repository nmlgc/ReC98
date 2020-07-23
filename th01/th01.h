/* ReC98
 * -----
 * Include file for TH01
 */

#include "ReC98.h"

#include "th01/common.h"

// Graphics
// --------
#include "th01/hardware/egc.h"
#include "th01/hardware/graph.h"
// --------

// Resident structure
#define RES_ID "ReiidenConfig"

typedef enum {
	ROUTE_MAKAI,
	ROUTE_JIGOKU
} route_t;

typedef enum {
	MODE_REGULAR = 0,
	MODE_TEST = 1,
	MODE_DEBUG = 3
} mode_t;

typedef struct {
	char id[RES_ID_LEN];
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
	int pellet_speed;
	long rand;
	long score;
	long continues_total;
	unsigned int continues_per_scene[SCENE_COUNT];
	long bonus_per_stage[STAGES_PER_SCENE]; // of the current scene
	int stage;
	unsigned long hiscore;
	long score_highest; // among all continues
	unsigned int p_value;
} resident_t;

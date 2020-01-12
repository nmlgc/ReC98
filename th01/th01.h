/* ReC98
 * -----
 * Include file for TH01
 */

#include "ReC98.h"

// Graphics
// --------
#include "th01/hardware/egc.h"
#include "th01/hardware/graph.h"
// --------

// master.lib text function reimplementations
// ------------------------------------------
typedef enum {
	CURSOR_HIDE,
	CURSOR_BLOCK,
	CURSOR_UNDERLINE
} z_text_cursor_t;

void z_test_init(void);
void z_text_25line(void);
void z_text_20line(void);
void z_text_systemline_show(void);
void z_text_systemline_hide(void);
void z_text_clear(void);
void z_text_show(void);
void z_text_hide(void);
void z_text_setcursor(z_text_cursor_t type);
void z_text_print(const char *cmd);
// ----

// Game
#define STAGES_PER_SCENE 4
#define SCENE_COUNT 4

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

#pragma option -a1
typedef struct {
	char id[RES_ID_LEN];
	char rank;
	char bgm_mode; // 0 = off, 1 = FM
	char bombs;
	char start_lives_extra; // Add 2 for the actual number of lives
	char end_flag;
	char unused_1;
	char route;
	char rem_lives;
	char snd_need_init;
	char unused_2;
	char mode;
	int bullet_speed;
	long rand;
	long score;
	long continues_total;
	int continues_per_scene[SCENE_COUNT];
	long bonus_per_stage[STAGES_PER_SCENE]; // of the current scene
	int stage;
	long hiscore;
	long score_highest; // among all continues
	unsigned int p_value;
} resident_t;
#pragma option -a2

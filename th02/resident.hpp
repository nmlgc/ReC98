#include "th02/score.h"

static const int8_t LIVES_MAX = 5;
static const int8_t BOMBS_MAX = 5;

#define RES_ID "MIKOConfig"
struct resident_t {
	char id[sizeof(RES_ID)];
	unsigned char stage;
	char debug;
	int8_t padding_1;
	score_t score;
	unsigned int continues_used;
	char rem_bombs;
	char rem_lives;
	char rank;
	char start_power;
	char bgm_mode;
	char start_bombs;
	char start_lives;
	int8_t padding_2;
	long frame;
	int unused_1;
	char unused_2;
	unsigned char op_main_retval;
	bool reduce_effects;
	char unused_3;
	char shottype;
	char demo_num;
	int skill;
	int unused_4;
	long score_highest;
};

extern resident_t *resident;

// Redundant copies of resident structure fields to static data
// ------------------------------------------------------------

extern int8_t bombs;
extern int8_t lives;
extern bool reduce_effects;
// ------------------------------------------------------------

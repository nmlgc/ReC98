/// Stage 1 Boss - Sara
/// -------------------

#pragma option -zCB1_UPDATE_TEXT -zPmain_03

#include "platform.h"
#include "pc98.h"
#include "th01/math/area.hpp"
#include "th01/math/subpixel.hpp"
extern "C" {
#include "th04/math/motion.hpp"
#include "th04/snd/snd.h"
#include "th04/main/playfld.hpp"
#include "th04/main/pattern.hpp"
#include "th04/main/bullet/bullet.hpp"
}
#include "th04/main/gather.hpp"
#include "th05/main/boss/boss.hpp"

// Constants
// ---------

static const int PHASE_2_PATTERN_START_FRAME = 16;

enum sara_colors_t {
	COL_GATHER_1 = 9,
	COL_GATHER_2 = 8,
};
// ---------

// State
// -----

union sara_state_t {
	struct {
		/* -------------------- */ int8_t _unused_1[9];
		uint8_t fly_delay;
		uint8_t pattern_prev;
		/* -------------------- */ int8_t _unused_2;
		/* -------------------- */ int8_t _unused_3;
		unsigned char angle_stacks;
		unsigned char angle_clockwise;
		unsigned char angle_counterclockwise;
	} phase_2;

	struct {
		/* -------------------- */ int8_t _unused_1[9];
		uint8_t pattern_duration;
		uint8_t pattern_prev;
		/* -------------------- */ int8_t _unused_2;
		/* -------------------- */ int8_t _unused_3;
		SubpixelLength8 ring_speed;
		unsigned char angle_counterclockwise;
		unsigned char angle_clockwise;
	} phase_3;

	struct {
		/* -------------------- */ int8_t _unused[13];
		uint8_t laser_angle_interval;
		uint8_t random_ball_count;
		unsigned char spread_angle;
	} phase_4;
};

#define state reinterpret_cast<sara_state_t *>(boss_statebyte)

#define phase_2_3_pattern sara_phase_2_3_pattern
extern pattern_loop_func_t phase_2_3_pattern;
// -----

void near phase_2_with_pattern(void)
{
	if(boss.phase_frame < PHASE_2_PATTERN_START_FRAME) {
		gather_add_only_3stack(
			(boss.phase_frame - 1), COL_GATHER_1, COL_GATHER_2
		);
		if(boss.phase_frame == 1) {
			snd_se_play(8);
			state->phase_2.angle_counterclockwise = 0x80;
			state->phase_2.angle_clockwise = 0x00;
			state->phase_2.angle_stacks = 0x08;
		}
		return;
	}
	if(boss_flystep_random(boss.phase_frame - PHASE_2_PATTERN_START_FRAME)) {
		boss.phase_frame = 0;
		boss.mode = 0;
	}
	phase_2_3_pattern();
}

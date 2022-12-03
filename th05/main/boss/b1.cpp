/// Stage 1 Boss - Sara
/// -------------------

#pragma option -zCB1_UPDATE_TEXT -zPmain_03

#include "platform.h"
#include "pc98.h"
#include "th01/math/subpixel.hpp"
#include "th04/main/pattern.hpp"

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

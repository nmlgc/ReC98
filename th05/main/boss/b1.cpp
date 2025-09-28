/// Stage 1 Boss - Sara
/// -------------------

#pragma option -zCB1_UPDATE_TEXT -zPmain_03

#include "th01/math/dir.hpp"
#include "th02/formats/tile.hpp"
#include "th04/formats/bb.h"
#include "th04/math/randring.hpp"
#include "th04/snd/snd.h"
#include "th04/main/pattern.hpp"
#include "th04/main/bg.hpp"
#include "th04/main/frames.h"
#include "th04/main/gather.hpp"
#include "th04/main/homing.hpp"
#include "th04/main/hud/hud.hpp"
#include "th04/main/tile/bb.hpp"
#include "th05/sprites/main_pat.h"
#include "th05/main/boss/bosses.hpp"
#include "th05/main/bullet/laser.hpp"

// Constants
// ---------

static const int PHASE_2_PATTERN_START_FRAME = 16;
static const int PHASE_3_PATTERN_START_FRAME = 32;

enum sara_colors_t {
	COL_GATHER_1 = 9,
	COL_GATHER_2 = 8,
};

// Always denotes the last phase that ends with that amount of HP.
enum sara_hp_t {
	HP_TOTAL = 4650,
	HP_PHASE_2_END = 2550,
	HP_PHASE_3_END = 450,
	HP_PHASE_4_END = 0,
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

static void near phase_2_with_pattern(void)
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

#define pattern_blue(pattern_angle, angle_delta) { \
	if((boss.phase_frame % 2) == 0) { \
		bullet_template.spawn_type = BST_CLOUD_FORWARDS; \
		bullet_template.patnum = PAT_BULLET16_N_BALL_BLUE; \
		bullet_template.group = BG_SINGLE; \
		bullet_template.angle = pattern_angle; \
		bullet_template.speed.set(1.5f); \
		bullet_template_tune(); \
		bullets_add_regular(); \
		pattern_angle = (pattern_angle + angle_delta); \
	} \
}

void near pattern_blue_curve_counterclockwise(void)
{
	pattern_blue(state->phase_2.angle_counterclockwise, -0x0A);
}

void near pattern_blue_curve_clockwise(void)
{
	pattern_blue(state->phase_2.angle_clockwise, +0x0A);
}

void near pattern_aimed_red_spread_stack(void)
{
	if(boss.phase_frame == (PHASE_2_PATTERN_START_FRAME + 16)) {
		bullet_template.spawn_type = (BST_CLOUD_FORWARDS | BST_NO_DECELERATE);
		bullet_template.patnum = PAT_BULLET16_N_BALL_RED;
		bullet_template.group = BG_SPREAD_STACK_AIMED;
		bullet_template.angle = 0;
		bullet_template.set_spread_stack(5, 0x10, 5, 0.4375f);
		bullet_template.speed.set(1.0f);
		bullet_template_tune();
		bullets_add_regular();
		snd_se_play(15);
	}
}

void near pattern_red_stacks(void)
{
	if((boss.phase_frame % 8) == 0) {
		bullet_template.spawn_type = (BST_CLOUD_FORWARDS | BST_NO_DECELERATE);
		bullet_template.patnum = PAT_BULLET16_N_BALL_RED;
		bullet_template.group = BG_STACK;
		bullet_template.angle = (
			boss.angle + state->phase_2.angle_stacks - 0x80
		);
		bullet_template.set_stack(8, 0.375f);
		bullet_template.speed.set(1.0f);
		bullet_template_tune();
		bullets_add_regular();
		state->phase_2.angle_stacks -= 0x08;
		snd_se_play(15);
	}
}

static void near phase_3_with_pattern(void)
{
	if(boss.phase_frame < PHASE_3_PATTERN_START_FRAME) {
		gather_add_only_3stack(
			(boss.phase_frame - 16), COL_GATHER_1, COL_GATHER_2
		);
		if(boss.phase_frame == 16) {
			snd_se_play(8);
			boss.sprite = PAT_SARA_SPIN;
			state->phase_3.angle_clockwise = (0x40 - 0x08);
			state->phase_3.angle_counterclockwise = (0x40 + 0x08);
			state->phase_3.ring_speed.set(1.5f);
		}
		return;
	}

	if(boss.phase_frame < 64) {
		boss.sprite++;
	} else if(boss.phase_frame < 96) {
		if((boss.phase_frame % 2) == 0) {
			boss.sprite++;
		}
	} else if(boss.phase_frame < 128) {
		if((boss.phase_frame % 4) == 0) {
			boss.sprite++;
		}
	} else if((boss.phase_frame < 160)) {
		if((boss.phase_frame % 8) == 0) {
			boss.sprite++;
		}
	}

	if(boss.sprite >= (PAT_SARA_SPIN_last + 1)) {
		boss.sprite = PAT_SARA_SPIN;
	}
	phase_2_3_pattern();
	if(boss.phase_frame >= state->phase_3.pattern_duration) {
		boss.phase_frame = 0;
		boss.mode = 0;
		boss.sprite = PAT_SARA_STAY;
	}
}

void near pattern_pellet_arcs_at_expanding_random_angles(void)
{
	if((boss.phase_frame % 8) == 0) {
		bullet_template.spawn_type = BST_NO_DECELERATE;
		bullet_template.patnum = 0;
		bullet_template.group = BG_SPREAD;
		bullet_template.angle = (
			randring2_next16_mod(boss.phase_frame * 2) - boss.phase_frame + 0x40
		);
		bullet_template.set_spread(3, 0x3);
		bullet_template.special_motion = BSM_EXACT_LINEAR;
		bullet_template.speed.v = randring2_next8_and_ge_lt_sp(1.0f, 3.0f);
		bullet_template_tune();
		bullets_add_special();

		bullet_template.spawn_type = BST_CLOUD_BACKWARDS;
		bullet_template.patnum = PAT_BULLET16_N_BALL_BLUE;
		bullet_template.group = BG_SINGLE;
		bullet_template.angle = (
			randring2_next16_mod(boss.phase_frame * 2) - boss.phase_frame + 0x40
		);
		bullet_template.speed.v = randring2_next8_and_ge_lt_sp(1.5f, 3.5f);
		bullet_template_tune();
		bullets_add_regular();

		snd_se_play(3);
	}
}

void near pattern_random_red_rings(void)
{
	if((boss.phase_frame % 16) == 0) {
		bullet_template.spawn_type = BST_CLOUD_FORWARDS;
		bullet_template.patnum = PAT_BULLET16_N_BALL_RED;
		bullet_template.group = BG_RING;
		bullet_template.angle = randring2_next16();
		bullet_template.speed.set(2.0f);
		bullet_template.spread = 12;
		bullet_template_tune();
		bullets_add_regular();
		snd_se_play(3);
	}
}

#define pattern_accelerating_rings(pattern_angle, angle_delta) { \
	if((boss.phase_frame % 8) == 0) { \
		bullet_template.spawn_type = BST_NORMAL; \
		bullet_template.group = BG_RING; \
		bullet_template.spread = 3; \
		bullet_template.patnum = PAT_BULLET16_N_BALL_BLUE; \
		bullet_template.angle = pattern_angle; \
		bullet_template.speed = state->phase_3.ring_speed; \
		if((boss.phase_frame % 16) == 0) { \
			bullet_template.speed.v /= 2; \
		} \
		bullet_template_tune(); \
		bullets_add_regular(); \
		snd_se_play(3); \
		\
		pattern_angle += angle_delta; \
		state->phase_3.ring_speed.v += to_sp(0.25f); \
	} \
}

void near pattern_accelerating_spirals_clockwise(void)
{
	pattern_accelerating_rings(state->phase_3.angle_clockwise, +0x06);
}

void near pattern_accelerating_spirals_counterclockwise(void)
{
	pattern_accelerating_rings(state->phase_3.angle_counterclockwise, -0x06);
}

void near pattern_dense_spreads_and_random_balls_within_laser_walls(void)
{
	enum {
		CORRIDOR_ANGLE = 0x14, // centered around 0x40
	};

	if(boss.phase_frame == 1) {
		boss.sprite = PAT_SARA_SPIN;
	}

	if(boss.phase_frame == 32) {
		laser_template.coords.origin = boss.pos.cur;
		laser_template.coords.angle = (-0x40 + 0x20);
		laser_template.col = 8;
		laser_template.coords.width.nonshrink = 8;
		laser_manual_fixed_spawn(X_RIGHT);

		laser_template.coords.angle = (-0x40 - 0x20);
		laser_manual_fixed_spawn(X_LEFT);
		state->phase_4.spread_angle = 0x00;
		state->phase_4.random_ball_count = 1;
		state->phase_4.laser_angle_interval = 1;
		return;
	}
	if(boss.phase_frame <= 32) {
		return;
	}

	if(boss.phase_frame == 64) {
		laser_manual_grow(X_RIGHT);
		laser_manual_grow(X_LEFT);
	}

	if(
		((boss.phase_frame % state->phase_4.laser_angle_interval) == 0) &&
		(lasers[X_LEFT].coords.angle > (0x40 + (CORRIDOR_ANGLE / 2)))
	) {
		lasers[X_RIGHT].coords.angle += 0x01;
		lasers[X_LEFT].coords.angle -= 0x01;
		if(
			(lasers[X_LEFT].coords.angle == 0x80) ||
			(lasers[X_LEFT].coords.angle == 0x60) ||
			(lasers[X_LEFT].coords.angle == 0x58) ||
			(lasers[X_LEFT].coords.angle == 0x50)
		) {
			state->phase_4.laser_angle_interval++;
		}
	}

	if(stage_frame_mod16 == 0) {
		bullet_template.spawn_type = BST_NO_DECELERATE;
		bullet_template.angle = state->phase_4.spread_angle;
		bullet_template.group = BG_SPREAD;
		bullet_template.special_motion = BSM_EXACT_LINEAR;
		bullet_template.set_spread_for_rank(
			5, 0x1,
			6, 0x1,
			7, 0x1,
			8, 0x1
		);
		bullet_template.speed.set(2.0f);
		bullet_template.patnum = 0;
		bullets_add_special();

		bullet_template.group = BG_RANDOM_ANGLE_AND_SPEED;
		bullet_template.speed.set(1.0f);
		bullet_template.spread = state->phase_4.random_ball_count;
		bullet_template.patnum = PAT_BULLET16_N_BALL_BLUE;
		bullets_add_regular();

		state->phase_4.spread_angle += 0x0E;
	}

	if(
		((boss.phase_frame % 64) == 0) &&
		(state->phase_4.random_ball_count < 8)
	) {
		state->phase_4.random_ball_count++;
	}
}

extern const pattern_loop_func_t SARA_PATTERNS_PHASE_2_3[2][4];

#define phase_2_3_wait_fly_and_select_pattern( \
	pattern_prev, phase, fly_delay, patterns_max, timeout_label \
) { \
	if(boss_flystep_random(boss.phase_frame - fly_delay)) { \
		boss.phase_frame = 0; \
		boss.phase_state.patterns_seen++; \
		\
		/* Timeout condition */ \
		if(boss.phase_state.patterns_seen >= patterns_max) { \
			goto timeout_label; \
		} \
		do { \
			boss.mode = randring2_next8_mod_ge_lt(1, 5); \
		} while(boss.mode == pattern_prev); \
		pattern_prev = boss.mode; \
		phase_2_3_pattern = SARA_PATTERNS_PHASE_2_3[phase - 2][boss.mode - 1]; \
	} \
}

#pragma option -a2

void pascal sara_update(void)
{
	homing_target.x = boss.pos.cur.x;
	homing_target.y = boss.pos.cur.y;
	boss.phase_frame++;
	bullet_template.spawn_type = BST_NORMAL; // ZUN bloat
	bullet_template.origin = boss.pos.cur;
	gather_template.center = boss.pos.cur;

	switch(boss.phase) {
	case PHASE_HP_FILL:
		enum {
			KEYFRAME_GATHER_SPAWN_START = (HUD_HP_FILL_FRAMES + 96),
			KEYFRAME_GATHER_SPAWN_END = (KEYFRAME_GATHER_SPAWN_START + 32),
		};

		if(boss.phase_frame == 1) {
			boss.hp = HP_TOTAL;
			boss.phase_end_hp = HP_PHASE_2_END;
		}
		boss_hittest_shots_invincible();
		if(boss.phase_frame >= KEYFRAME_GATHER_SPAWN_START) {
			if(boss.phase_frame == KEYFRAME_GATHER_SPAWN_START) {
				gather_template.center.x = boss.pos.cur.x;
				gather_template.center.y = boss.pos.cur.y;
				gather_template.radius.set(RES_X / 2.0f);
				gather_template.ring_points = 32;
				gather_template.angle_delta = 0x03;
				gather_template.col = COL_GATHER_1;
			}
			if((boss.phase_frame & 7) == 0) {
				gather_add_only();
			}
			if(boss.phase_frame == KEYFRAME_GATHER_SPAWN_START) {
				gather_template.col = COL_GATHER_2;
			}
		}

		// Timeout condition
		if(boss.phase_frame >= KEYFRAME_GATHER_SPAWN_END) {
			// Next phase
			gather_template.radius.set(BOSS_W / 1.0f);
			gather_template.angle_delta = 0x02;
			gather_template.ring_points = 8;
			boss.phase++;
			boss.phase_frame = 0;
			snd_se_play(13);
			bg_render_bombing_func = sara_bg_render;
		}
		break;

	case PHASE_BOSS_ENTRANCE_BB:
		boss_hittest_shots_invincible();

		// Timeout condition
		if(boss.phase_frame >= (
			ENTRANCE_BB_TRANSITION_FRAMES_PER_CEL * TILES_BB_CELS
		)) {
			// Next phase
			boss.phase++;
			boss.phase_frame = 0;
			boss.mode = 0;
			boss.phase_state.patterns_seen = 0;
			state->phase_2.pattern_prev = -1;
			state->phase_2.fly_delay = 64;

			// ZUN bloat: Already set at the end of the previous phase, and
			// it's not set at any other place.
			bg_render_bombing_func = sara_bg_render;
		}
		break;

	case 2:
		switch(boss.mode) {
		case 0:
			phase_2_3_wait_fly_and_select_pattern(
				state->phase_2.pattern_prev,
				2,
				state->phase_2.fly_delay,
				32,
				phase_2_timed_out
			);
			break;

		default:
			phase_2_with_pattern();
			if((boss.phase_frame == 0) && (state->phase_2.fly_delay > 12)) {
				state->phase_2.fly_delay -= 12;
			}
			break;
		}
		if(!boss_hittest_shots()) {
			break;
		}

		// Next phase
		boss_score_bonus(5);
	phase_2_timed_out:
		boss_phase_next(ET_NW_SE, HP_PHASE_3_END);
		state->phase_3.pattern_duration = 80;
		break;

	case 3:
		switch(boss.mode) {
		case 0:
			phase_2_3_wait_fly_and_select_pattern(
				state->phase_3.pattern_prev, 3, 16, 24, phase_3_timed_out
			);
			break;

		default:
			phase_3_with_pattern();
			if(
				(boss.phase_frame == 0) &&
				(state->phase_3.pattern_duration < 180)
			) {
				state->phase_3.pattern_duration += 24;
			}
			break;
		}
		if(!boss_hittest_shots()) {
			break;
		}

		// Next phase
		boss_score_bonus(5);
	phase_3_timed_out:
		boss_phase_next(ET_SW_NE, HP_PHASE_4_END);
		break;

	case 4:
		pattern_dense_spreads_and_random_balls_within_laser_walls();

		// Timeout condition
		if(boss.phase_frame >= 1300) {
			boss.phase_state.defeat_bonus = false;
		} else {
			// Boss defeated?
			if(!boss_hittest_shots()) {
				break;
			}
			boss.phase_state.defeat_bonus = true;
		}

		// Boss defeated
		laser_stop(0);
		laser_stop(1);
		boss.phase_frame = 0;
		boss.phase = PHASE_BOSS_EXPLODE_SMALL;
		break;

	default:
		boss_defeat_update(10);
		break;
	}
	hud_hp_update_and_render(boss.hp, HP_TOTAL);
}

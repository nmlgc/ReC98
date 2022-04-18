/// Stage 6 Boss - Shinki
/// ---------------------

#include "platform.h"
#include "pc98.h"
#include "master.hpp"
#include "th01/math/area.hpp"
#include "th01/math/subpixel.hpp"
#include "th03/hardware/palette.hpp"
#include "th04/main/frames.h"
#include "th04/main/pattern.hpp"
#include "th04/math/motion.hpp"
extern "C" {
#include "th04/math/randring.hpp"
#include "th04/math/vector.hpp"
#include "th04/snd/snd.h"
#include "th04/main/rank.hpp"
#include "th04/main/playfld.hpp"
#include "th04/main/bullet/bullet.hpp"
#include "th04/main/gather.hpp"
}
#include "th05/main/custom.h"
#include "th05/main/bullet/b6ball.hpp"
#include "th05/main/bullet/cheeto.hpp"
#include "th05/main/bullet/laser.hpp"
#include "th05/main/boss/boss.hpp"
#include "th05/main/player/player.hpp"
#include "th05/sprites/main_pat.h"

// Constants
// ---------

static const int PHASE_2_3_PATTERN_START_FRAME = 32;
// ---------

// Coordinates
// -----------

inline subpixel_t shinki_wing_random_x(void) {
	return (
		randring2_next16_mod(to_sp(SHINKI_WING_W)) +
		boss.pos.cur.x.v -
		to_sp(SHINKI_WING_W / 2)
	);
}

// Limited to the top 3/2rds of the wing area.
inline subpixel_t shinki_wing_random_y(void) {
	return (
		boss.pos.cur.y.v -
		randring2_next16_mod((to_sp(SHINKI_WING_H) / 3) * 2) +
		to_sp((SHINKI_WING_H - BOSS_H) / 2)
	);
}
// -----------

// State
// -----

#define phase_2_3_pattern shinki_phase_2_3_pattern
extern pattern_oneshot_func_t phase_2_3_pattern;
// -----

bool near pattern_curved_rings(void)
{
	#define delta_angle static_cast<unsigned char>(boss_statebyte[15])

	if(boss.phase_frame == PHASE_2_3_PATTERN_START_FRAME) {
		bullet_template.spawn_type = (BST_CLOUD_FORWARDS | BST_NO_SLOWDOWN);
		bullet_template.patnum = PAT_BULLET16_N_OUTLINED_BALL_BLUE;
		bullet_template.speed.set(2.0f);
		bullet_template.group = BG_RING;
		bullet_template.special_motion = BSM_EXACT_LINEAR;
		bullet_template.angle = randring2_next16();
		bullet_template.spread = 16;
		delta_angle = randring2_next16_and(1) ? 0x02 : -0x02;
		bullet_template_tune();
		snd_se_play(15);
	}
	if((boss.phase_frame % 4) == 0) {
		bullets_add_special();
		bullet_template.speed.v = (bullet_template.speed + 0.5f);
		bullet_template.angle += delta_angle;
	}
	return (boss.phase_frame == (PHASE_2_3_PATTERN_START_FRAME + 28));

	#undef delta_angle
}

bool near pattern_dualspeed_rings(void)
{
	#define interval boss_statebyte[15]

	if(boss.phase_frame == PHASE_2_3_PATTERN_START_FRAME) {
		bullet_template.spawn_type = (BST_CLOUD_FORWARDS | BST_NO_SLOWDOWN);
		bullet_template.patnum = PAT_BULLET16_N_BLUE;
		bullet_template.group = BG_RING;
		bullet_template.angle = randring2_next16();
		bullet_template.spread = 16;
		interval = select_for_rank(16, 12, 8, 4);
	}
	if((boss.phase_frame % interval) == 0) {
		vector2_at(
			bullet_template.origin,
			boss.pos.cur.x,
			boss.pos.cur.y,
			randring2_next16_mod(to_sp(32.0f)),
			bullet_template.angle
		);
		bullet_template.speed.set(2.0f);
		bullets_add_regular();

		bullet_template.speed.set(4.0f);
		bullet_template.angle += 0x08;
		bullets_add_regular();

		snd_se_play(3);
	}
	return (boss.phase_frame == (PHASE_2_3_PATTERN_START_FRAME + 64));

	#undef interval
}

void near gather_then_phase_2_3_pattern(void)
{
	if(boss.phase_frame < PHASE_2_3_PATTERN_START_FRAME) {
		gather_add_only_3stack((boss.phase_frame - 16), 7, 6);
		if(boss.phase_frame == 2) {
			boss.sprite = PAT_SHINKI_CAST;

			// What's this, part of an unused pattern? Actually, it's just
			// copy-pasted from a similar function in Yumeko's fight, which
			// does fire bullets based on that template.
			bullet_template.spawn_type = (
				BST_CLOUD_BACKWARDS | BST_NO_SLOWDOWN
			);
			bullet_template.patnum = PAT_BULLET16_N_RED;
			bullet_template.group = BG_RING;
			bullet_template.speed.set(3.75f);
			bullet_template.spread = 16;
			bullet_template_tune();
			snd_se_play(8);
		}
	} else if(phase_2_3_pattern()) {
		boss.sprite = PAT_SHINKI_STILL;
		boss.phase_frame = 0;
		boss.mode = 0;
	}
}

bool near pattern_random_directional_and_kunai(void)
{
	if(boss.phase_frame == PHASE_2_3_PATTERN_START_FRAME) {
		bullet_template.spawn_type = (BST_CLOUD_FORWARDS | BST_NO_SLOWDOWN);
		bullet_template.speed.set(1.75f);
		bullet_template.group = BG_RANDOM_ANGLE_AND_SPEED;
		bullet_template.spread = 3;
		bullet_template_tune();
		snd_se_play(15);
	}
	if((boss.phase_frame % 2) == 0) {
		bullet_template.patnum = PAT_BULLET16_D_BLUE;
		bullet_template.origin.x -= (BOSS_W / 4.0f);
		bullets_add_regular();

		bullet_template.patnum = PAT_BULLET16_V_BLUE;
		bullet_template.origin.x += ((BOSS_W / 4.0f) * 2.0f);
		bullets_add_regular();
	}
	return boss_flystep_random(
		boss.phase_frame - PHASE_2_3_PATTERN_START_FRAME - 32
	);
}

bool near pattern_dense_blue_stacks(void)
{
	if(boss.phase_frame == PHASE_2_3_PATTERN_START_FRAME) {
		bullet_template.spawn_type = (BST_CLOUD_FORWARDS | BST_NO_SLOWDOWN);
		bullet_template.patnum = PAT_BULLET16_N_BLUE;
		bullet_template.group = BG_SPREAD_STACK_AIMED;
		bullet_template.angle = 0x00;
		bullet_template.set_spread(2, 0x04);
		bullet_template.set_stack_for_rank(
			12, 12, 13, 13,
			to_sp8(0.3125f), to_sp8(0.375f), to_sp8(0.375f), to_sp8(0.4375f)
		);
		bullet_template.speed.set(2.0f);
	}
	if((boss.phase_frame % 4) == 0) {
		bullets_add_regular();
		snd_se_play(15);
	}
	return boss_flystep_random(
		boss.phase_frame - PHASE_2_3_PATTERN_START_FRAME - 32
	);
}

bool near pattern_wing_preparation(void)
{
	enum {
		LASERS_USED = 6,
	};
	#define tone       	boss_statebyte[14]
	#define wing_frames	boss_statebyte[15]

	int i;

	if(boss.phase_frame == 16) {
		// Still assumed to be set to this value by Yumeko. Original gameplay
		// relies on this value to be < 8 to ensure that the lasers will kill
		// the player if they move to the side of the wings. (Lasers only kill
		// if they finished growing, they grow by 2 pixels every 2 frames, and
		// the ones in this pattern are kept alive for 8 frames.)
		// MODDERS: Uncomment to clearly define the original behavior.
		// laser_template.coords.width = 6;
		laser_template.coords.angle = 0x50;	laser_manual_fixed_spawn(0);
		laser_template.coords.angle = 0x48;	laser_manual_fixed_spawn(1);
		laser_template.coords.angle = 0x40;	laser_manual_fixed_spawn(2);
		laser_template.coords.angle = 0x40;	laser_manual_fixed_spawn(3);
		laser_template.coords.angle = 0x38;	laser_manual_fixed_spawn(4);
		laser_template.coords.angle = 0x30;	laser_manual_fixed_spawn(5);
		snd_se_play(8);
		boss.sprite = PAT_SHINKI_CAST;
		wing_frames = 0;
		tone = 100;
	}
	if(boss.phase_frame <= 16) {
		return false;
	}
	if(lasers[2].coords.angle < 0x80) {
		if(stage_frame_mod2) {
			lasers[0].coords.angle += 0x01;
			lasers[1].coords.angle += 0x01;
			lasers[2].coords.angle += 0x01;
			lasers[3].coords.angle -= 0x01;
			lasers[4].coords.angle -= 0x01;
			lasers[5].coords.angle -= 0x01;
			palette_settone_deferred(tone);
			tone++;
		}
		return false;
	}
	if(wing_frames == 0) {
		bullet_template.spawn_type = (BST_CLOUD_FORWARDS | BST_NO_SLOWDOWN);
		bullet_template.patnum = PAT_BULLET16_N_BLUE;
		bullet_template.group = BG_SINGLE;
		bullet_template_tune();
		for(i = 0; i < 50; i++) {
			bullet_template.origin.x.v = shinki_wing_random_x();
			bullet_template.origin.y.v = shinki_wing_random_y();
			bullet_template.angle = randring2_next8_ge_lt(0x10, 0x70);
			bullet_template.speed.v = randring2_next8_and_ge_lt_sp(1.5f, 5.5f);
			bullets_add_regular();
		}
		boss.sprite = PAT_SHINKI_WINGS_WHITE;
		for(i = 0; i < LASERS_USED; i++) {
			laser_manual_grow(i);
		}
		snd_se_play(15);
		playfield_shake_anim_time = 8;
	} else {
		if(stage_frame_mod2) {
			palette_settone_deferred(150);
		} else {
			palette_settone_deferred(100);
		}
		if(wing_frames >= 8) {
			palette_settone_deferred(100);
			for(i = 0; i < LASERS_USED; i++) {
				laser_stop(i);
			}
			return true;
		}
	}
	wing_frames++;
	return false;

	#undef wing_frames
	#undef tone
}

void near pattern_random_rain_and_spreads_from_wings(void)
{
	if(boss.phase_frame <= 128) {
		return;
	}
	if((boss.phase_frame % 8) == 0) {
		b6ball_template.origin.x.v = randring2_next16_mod(to_sp(PLAYFIELD_W));
		b6ball_template.origin.y.v = randring2_next16_ge_lt_sp(
			((2 / 23.0f) * PLAYFIELD_H), ((6 / 23.0f) * PLAYFIELD_H)
		);
		b6ball_template.angle = 0x40;
		b6ball_template.speed.v = randring2_next8_and_ge_lt_sp(3.0f, 5.0f);
		b6ball_template.patnum_tiny = PAT_B6BALL_BLUE_1;
		b6balls_add();
		snd_se_play(3);
	}
	if((boss.phase_frame % 24) == 0) {
		bullet_template.origin.x.v = shinki_wing_random_x();
		bullet_template.origin.y.v = (
			boss.pos.cur.y.v - randring2_next16_mod(to_sp(BOSS_H))
		);
		bullet_template.spawn_type = (BST_CLOUD_FORWARDS | BST_NO_SLOWDOWN);
		bullet_template.patnum = PAT_BULLET16_N_BLUE;
		bullet_template.group = BG_SPREAD_AIMED;
		bullet_template.spread = 5;
		bullet_template.spread_angle_delta = select_for_rank(
			0x10, 0x0C, 0x0A, 0x08
		);
		bullet_template.angle = 0x00;
		bullet_template.speed.set(3.0f);
		bullet_template_tune();
		bullets_add_regular();
	}
}

void near pattern_cheetos_within_spread_walls(void)
{
	#define interval	boss_statebyte[14]
	#define unused  	boss_statebyte[15]

	if(boss.phase_frame < 128) {
		return;
	}
	if(boss.phase_frame == 128) {
		// Expected to be a multiple of 8.
		interval = select_for_rank(128, 48, 32, 24);

		unused = select_for_rank(32, 40, 48, 56);
	}
	int frame_in_cycle = (boss.phase_frame % interval);
	if((frame_in_cycle & 7) == 0) {
		bullet_template.patnum = PAT_BULLET16_N_OUTLINED_BALL_BLUE;
		bullet_template.spawn_type = (BST_CLOUD_FORWARDS | BST_NO_SLOWDOWN);
		bullet_template.group = BG_SPREAD;
		bullet_template.speed.v = randring2_next8_and_ge_lt_sp(3.0f, 5.0f);
		bullet_template.set_spread(6, 0x08);
		bullet_template.angle = 0x68;
		bullets_add_regular();

		bullet_template.angle = 0x18;
		bullets_add_regular();
		if(frame_in_cycle == 0) {
			cheeto_template.col = 11;
			cheeto_template.speed.set(4.0f);
			// Firing either right, down, or left.
			cheeto_template.angle = (randring2_next16_mod(3) * 0x40);
			cheetos_add();
			snd_se_play(3);
		}
	}

	#undef unused
	#undef interval
}

bool near pattern_wings_to_purple(void)
{
	if(boss.phase_frame < 160) {
		return false;
	} else if(boss.phase_frame < 192) {
		if(boss.phase_frame == 128) {
			snd_se_play(8);
		}
		if(boss.phase_frame & 1) {
			boss.pos.cur.y += 2.0f;
		} else {
			boss.pos.cur.y -= 2.0f;
		}
	} else if(boss.phase_frame == 192) {
		b6ball_template.patnum_tiny = PAT_B6BALL_PURPLE;
		for(int i = 0; i < 16; i++) {
			b6ball_template.origin.x.v = shinki_wing_random_x();
			b6ball_template.origin.y.v = shinki_wing_random_y();
			b6ball_template.angle = randring2_next8_ge_lt(0x20, 0x60);
			b6ball_template.speed.v = randring2_next8_and_ge_lt_sp(2.0f, 6.0f);
			b6balls_add();
		}
		boss.sprite = PAT_SHINKI_WINGS_PURPLE;
		snd_se_play(15);
		playfield_shake_anim_time = 8;
	}
	return (boss.phase_frame == 200);
}

void near pattern_aimed_b6balls_and_symmetric_spreads(void)
{
	#define b6ball_interval boss_statebyte[15]

	if(boss.phase_frame <= 128) {
		return;
	}
	if(boss.phase_frame == 129) {
		b6ball_interval = select_for_rank(96, 32, 28, 24);
	}

	int spread_cycle = (boss.phase_frame % (0x40 * 2));

	if((boss.phase_frame % b6ball_interval) == 0) {
		b6ball_template.angle = player_angle_from(b6ball_template.origin);
		b6ball_template.speed.set(4.0f);
		b6ball_template.patnum_tiny = PAT_B6BALL_PURPLE;
		b6balls_add();
	}
	if((boss.phase_frame % 4) == 0) {
		bullet_template.origin.x -= (SHINKI_WING_W / 2);
		bullet_template.group = BG_SPREAD;
		bullet_template.special_motion = BSM_EXACT_LINEAR;
		bullet_template.set_spread(3, 0x02);
		bullet_template.spawn_type = (BST_CLOUD_FORWARDS | BST_NO_SLOWDOWN);
		bullet_template.speed.set(2.5f);
		bullet_template.patnum = PAT_BULLET16_V_RED;
		if(spread_cycle < 0x40) {
			bullet_template.angle = (spread_cycle * 3);
		} else {
			bullet_template.angle = (0x40 - (spread_cycle * 3));
		}
		bullets_add_special();

		bullet_template.angle = (0x80 - bullet_template.angle);
		bullet_template.origin.x += SHINKI_WING_W;
		bullets_add_special();

		snd_se_play(15);
	}

	#undef b6ball_interval
}

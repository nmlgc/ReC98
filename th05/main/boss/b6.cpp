/// Stage 6 Boss - Shinki
/// ---------------------

#pragma option -zCB6_UPDATE_TEXT -zPmain_03

#include "platform.h"
#include "decomp.hpp"
#include "pc98.h"
#include "master.hpp"
#include "th01/math/area.hpp"
#include "th01/math/dir.hpp"
#include "th01/math/subpixel.hpp"
#include "th02/main/tile/tile.hpp"
#include "th02/main/player/bomb.hpp"
#include "th03/hardware/palette.hpp"
#include "th04/formats/bb.h"
#include "th04/main/frames.h"
#include "th04/main/pattern.hpp"
#include "th04/math/motion.hpp"
extern "C" {
#include "th04/math/randring.hpp"
#include "th04/math/vector.hpp"
#include "th04/snd/snd.h"
#include "th04/main/bg.hpp"
#include "th04/main/homing.hpp"
#include "th04/main/rank.hpp"
#include "th04/main/playfld.hpp"
#include "th04/main/bullet/bullet.hpp"
}
#include "th04/main/gather.hpp"
#include "th04/main/phase.hpp"
#include "th04/main/hud/hud.hpp"
#include "th04/main/tile/bb.hpp"
#include "th05/playchar.h"
#include "th05/main/bullet/cheeto.hpp"
#include "th05/main/bullet/laser.hpp"
#include "th05/main/boss/boss.hpp"
#include "th05/main/boss/bosses.hpp"
#include "th05/main/player/player.hpp"
#include "th05/sprites/main_pat.h"

// Constants
// ---------

static const int PHASE_2_3_PATTERN_START_FRAME = 32;

// Always denotes the last phase that ends with that amount of HP.
enum shinki_hp_t {
	HP_TOTAL = 22800,
	HP_PHASE_2_END = 20600,
	HP_PHASE_3_END = 18400,
	HP_PHASE_6_END = 14600,
	HP_PHASE_7_END = 11600,
	HP_PHASE_9_END = 8600,
	HP_PHASE_10_DEVIL_LASER = 5600,
	HP_PHASE_10_DEVIL_FAST = 3800,
	HP_PHASE_10_END = 2800,
	HP_PHASE_12_END = 0,
};
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
#define wing_pattern shinki_wing_pattern
extern pattern_oneshot_func_t phase_2_3_pattern;
extern pattern_loop_func_t wing_pattern;
// -----

// Rendering
// ---------

#pragma codeseg main_0_TEXT

void pascal near shinki_custombullets_render()
;
// ---------

// Game logic
// ----------

#pragma codeseg

#include "th05/main/bullet/b6ball.cpp"

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

static void near phase_2_3_with_pattern(void)
{
	if(boss.phase_frame < PHASE_2_3_PATTERN_START_FRAME) {
		gather_add_only_3stack((boss.phase_frame - 16), 7, 6);
		if(boss.phase_frame == 2) {
			boss.sprite = PAT_SHINKI_CAST;

			// ZUN bloat: What's this, part of an unused pattern? Actually,
			// it's just copy-pasted from a similar function in Yumeko's fight,
			// which does fire bullets based on that template.
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

void near pattern_devil(void)
{
	enum {
		COLUMN_COUNT = 4,
		SHINKI_TO_LAST_COLUMN_DISTANCE = (
			(SHINKI_WING_W / 2) - (SHINKI_WING_W / 8)
		),
		COLUMN_W = (SHINKI_WING_W / 4),
	};

	// Since the columns are symmetrical, it's only necessary to track the
	// inner and outer angles for spread bullets and lasers.
	#define laser_direction  	boss_statebyte[7]
	#define laser_angle_inner	boss_statebyte[8]
	#define laser_angle_outer	boss_statebyte[9]

	// Careful, collides with [phase_relative] in shinki_update()! *Must* be
	// set to 1 before ending the pattern to ensure that the remaining phases
	// run in their expected order. Guaranteed in the original code by setting
	// HP_PHASE_10_DEVIL_LASER to a much higher value than HP_PHASE_10_END.
	#define lasers_active    	static_cast<bool>(boss_statebyte[10])

	#define bullet_direction 	boss_statebyte[11]
	#define bullet_intro_done	static_cast<bool>(boss_statebyte[12])
	#define b6ball_interval  	boss_statebyte[13]
	#define bullet_angle_inner	boss_statebyte[14]
	#define bullet_angle_outer	boss_statebyte[15]

	#define laser_grow_delay shinki_devil_laser_grow_delay
	extern int laser_grow_delay;

	if(boss.phase_frame < 192) {
		return;
	}

	int phase_frame_minus_startup_delay = (boss.phase_frame - 192);

	// Laser activation
	if((boss.hp <= HP_PHASE_10_DEVIL_LASER) || (boss.phase_frame >= 1800)) {
		if(laser_grow_delay == 0) {
			laser_template.coords.width = 6;
			laser_template.coords.angle = 0x40;
			laser_template.col = 0xE;

			// Assign laser IDs from right to left
			laser_template.coords.origin.x += SHINKI_TO_LAST_COLUMN_DISTANCE;
			laser_manual_fixed_spawn(0);

			laser_template.coords.origin.x -= COLUMN_W;
			laser_manual_fixed_spawn(1);

			laser_template.coords.origin.x -= COLUMN_W;
			laser_manual_fixed_spawn(2);

			laser_template.coords.origin.x -= COLUMN_W;
			laser_manual_fixed_spawn(3);
			laser_grow_delay++;
			boss_explode_small(ET_CIRCLE);
		}
	}

	// Spread bullets
	if((boss.phase_frame % 4) == 0) {
		if(phase_frame_minus_startup_delay == 0) {
			bullet_angle_inner = 0x20;
			bullet_angle_outer = 0x00;
			b6ball_interval = select_for_rank(64, 40, 32, 28);
			bullet_intro_done = false;
			bullet_direction = CLOCKWISE;
			lasers_active = false;
			laser_angle_inner = 0x40;
			laser_angle_outer = 0x40;
			laser_direction = CLOCKWISE;
		}
		bullet_template.spawn_type = (BST_CLOUD_FORWARDS | BST_NO_SLOWDOWN);
		bullet_template.patnum = PAT_BULLET16_V_RED;
		bullet_template.group = BG_SPREAD;
		if((bullet_angle_outer == 0x40) && (bullet_intro_done == 0)) {
			bullet_intro_done++;
		}
		if(!bullet_intro_done) {
			bullet_template.spread = 1;
		} else {
			bullet_template.spread = 3;
		}
		bullet_template.spread_angle_delta = 0x30;
		bullet_template.speed.set(7.0f);

		bullet_template.origin.x += SHINKI_TO_LAST_COLUMN_DISTANCE;
		bullet_template.angle = bullet_angle_outer;
		bullets_add_regular_fixedspeed();

		bullet_template.origin.x -= COLUMN_W;
		bullet_template.angle = bullet_angle_inner;
		bullets_add_regular_fixedspeed();

		bullet_template.origin.x -= COLUMN_W;
		bullet_template.angle = (0x80 - bullet_angle_inner);
		bullets_add_regular_fixedspeed();

		bullet_template.origin.x -= COLUMN_W;
		bullet_template.angle = (0x80 - bullet_angle_outer);
		bullets_add_regular_fixedspeed();

		if(!bullet_intro_done) {
			bullet_angle_outer += 0x04;
			bullet_angle_inner += 0x02;
		} else {
			// "Decorative" pellets aimed to the top of the playfield
			bullet_template.patnum = 0;
			bullet_template.spawn_type = BST_NO_SLOWDOWN;
			bullet_template.set_spread(3, 0x30); // technically redundant

			bullet_template.angle = (0x80 + bullet_angle_outer);
			bullet_template.origin.x += (COLUMN_W * (COLUMN_COUNT - 1)),
			bullets_add_regular_fixedspeed();

			bullet_template.origin.x -= COLUMN_W,
			bullet_template.angle = (0x80 + bullet_angle_inner);
			bullets_add_regular_fixedspeed();

			bullet_template.origin.x -= COLUMN_W,
			bullet_template.angle = (0x00 - bullet_angle_inner);
			bullets_add_regular_fixedspeed();

			bullet_template.origin.x -= COLUMN_W,
			bullet_template.angle = (0x00 - bullet_angle_outer);
			bullets_add_regular_fixedspeed();

			if(bullet_direction == CLOCKWISE) {
				bullet_angle_outer -= 0x02;
				bullet_angle_inner--;
				if(bullet_angle_outer == 0x30) {
					bullet_direction++; // = COUNTERCLOCKWISE;
				}
			} else /* if(bullet_direction == COUNTERCLOCKWISE) */ {
				bullet_angle_outer += 0x02;
				bullet_angle_inner++;
				if(bullet_angle_outer == 0x40) {
					bullet_direction--; // = CLOCKWISE;
				}
			}
		}

		// Aimed 32×32 balls
		if(bullet_intro_done && ((boss.phase_frame % b6ball_interval) == 0)) {
			b6ball_template.origin.x.v = shinki_wing_random_x();
			b6ball_template.origin.y.v = shinki_wing_random_y();
			b6ball_template.angle = player_angle_from(b6ball_template.origin);
			b6ball_template.speed.set(3.75f);
			b6ball_template.patnum_tiny = PAT_B6BALL_PURPLE;
			b6balls_add();
		}

		snd_se_play(3);
	}

	// Lasers
	if(laser_grow_delay == 0) {
		return;
	} else if(laser_grow_delay < 64) {
		laser_grow_delay++;
	} else if(laser_grow_delay == 64) {
		// MODDERS: Turn into a loop
		laser_manual_grow(0);
		laser_manual_grow(1);
		laser_manual_grow(2);
		laser_manual_grow(3);
		laser_grow_delay++;
	} else if(!lasers_active) {
		if(bullet_angle_outer == 0x30) {
			// Pattern can now be safely ended
			lasers_active++;
		}
	} else if((boss.phase_frame % 8) == 0) {
		lasers[0].coords.angle = laser_angle_outer;
		lasers[1].coords.angle = laser_angle_inner;
		lasers[2].coords.angle = (0x80 - lasers[1].coords.angle);
		lasers[3].coords.angle = (0x80 - lasers[0].coords.angle);
		if(laser_direction == CLOCKWISE) {
			laser_angle_outer++;
			laser_angle_inner--;
			if(laser_angle_inner == 0x38) {
				laser_direction++; // = COUNTERCLOCKWISE;
			}
		} else /* if(laser_direction == COUNTERCLOCKWISE) */ {
			laser_angle_outer--;
			laser_angle_inner++;
			if(laser_angle_inner == 0x41) {
				laser_direction--; // = CLOCKWISE;
			}
		}
		if((boss.hp <= HP_PHASE_10_DEVIL_FAST) || (boss.phase_frame >= 2500)) {
			if((laser_grow_delay++) == 65) {
				b6ball_interval = select_for_rank(52, 20, 16, 12);
				boss_explode_small(ET_CIRCLE);
			}
		}
	}

	#undef laser_grow_delay
	#undef bullet_angle_outer
	#undef bullet_angle_inner
	#undef b6ball_interval
	#undef bullet_intro_done
	#undef bullet_direction
	#undef lasers_active
	#undef laser_angle_outer
	#undef laser_angle_inner
	#undef laser_direction
}

void near pattern_circles_and_alternating_spirals(void)
{
	#define pellet_angle	 boss_statebyte[14]
	#define red_angle   	 boss_statebyte[15]

	int frame_in_cycle;

	if(boss.phase_frame < 128) {
		return;
	}
	if(boss.phase_frame == 128) {
		b6ball_template.angle = 0x00;
		red_angle = 0x00;
		pellet_angle = 0x00;
	}
	if((boss.phase_frame % 8) == 0) {
		// Still assumed to be set to this value from pattern_devil().
		// MODDERS: Uncomment.
		// b6ball_template.speed.set(3.75f);
		b6ball_template.patnum_tiny = PAT_B6BALL_BLUE_1;
		vector2_at(
			b6ball_template.origin,
			boss.pos.cur.x,
			boss.pos.cur.y,
			to_sp(BOSS_W),
			b6ball_template.angle
		);
		b6balls_add();

		b6ball_template.angle += 0x80;
		vector2_at(
			b6ball_template.origin,
			boss.pos.cur.x,
			boss.pos.cur.y,
			to_sp(BOSS_W),
			b6ball_template.angle
		);
		b6balls_add();

		b6ball_template.angle -= 0x78;
		snd_se_play(3);
	}
	if(boss.phase_frame >= 256) {
		frame_in_cycle = (boss.phase_frame % 256);
		if(((boss.phase_frame % 8) == 0) && (frame_in_cycle < 128)) {
			bullet_template.spawn_type = (BST_CLOUD_FORWARDS | BST_NO_SLOWDOWN);
			bullet_template.group = BG_RING;
			bullet_template.angle = red_angle;
			bullet_template.patnum = PAT_BULLET16_V_RED;
			bullet_template.speed.set(2.0f);
			bullet_template.spread = 12;
			bullets_add_regular();

			red_angle -= 0x02;
		}
		if(boss.phase_frame >= 512) {
			if(((boss.phase_frame % 8) == 0) && (frame_in_cycle >= 128)) {
				bullet_template.spawn_type = (
					BST_CLOUD_FORWARDS | BST_NO_SLOWDOWN
				);
				bullet_template.group = BG_RING;
				bullet_template.angle = pellet_angle;
				bullet_template.patnum = 0;
				bullet_template.speed.set(2.0f);
				bullet_template.spread = 12;
				bullets_add_regular();

				pellet_angle += 0x04;
			}
		}
	}
	if(boss.phase_frame >= 720) {
		frame_in_cycle = ((boss.phase_frame - 720) % 128);
		boss_flystep_random(frame_in_cycle - 96);
	}

	#undef red_angle
	#undef pellet_angle
}

void near shinki_move_float(void)
{
	#define float_direction shinki_float_direction
	extern bool float_direction;

	if(stage_frame_mod4 != 0) {
		return;
	}
	if(float_direction == 0) {
		boss.pos.velocity.y += 0.0625f;
		if(boss.pos.velocity.y.v >= to_sp(1.0f)) {
			float_direction++;
		}
	} else {
		boss.pos.velocity.y -= 0.0625f;
		if(boss.pos.velocity.y.v <= to_sp(-1.0f)) {
			float_direction--;
		}
	}
	boss.pos.cur.y.v += boss.pos.velocity.y.v;

	#undef float_direction
}

#pragma option -a2

void pascal shinki_update(void)
{
	// A completely unnecessary variable to differentiate between multiple
	// phases that share the same `switch` body, because [boss.phase] itself
	// is not good enough?
	// Careful, collides with [lasers_active] in pattern_devil()!
	// MODDERS: Just use [boss.phase].
	#define phase_relative boss_statebyte[10]

	enum {
		PHASE_11_FRAMES = 16,
	};

	bool16 phase_done;

	homing_target = boss.pos.cur;
	bullet_template.origin = boss.pos.cur;
	gather_template.center = boss.pos.cur;
	laser_template.coords.origin = boss.pos.cur;
	b6ball_template.origin = boss.pos.cur;

	boss.phase_frame++;

	switch(boss.phase) {
	case PHASE_HP_FILL:
		if(boss.phase_frame == 1) {
			boss.hp = HP_TOTAL;
			boss.phase_end_hp = HP_PHASE_2_END;
			gather_template_init();
			boss.sprite = PAT_SHINKI_STILL;

			// Redundant here, only needs to be part of the phase 5→6
			// transition for completeness.
			boss.pos.velocity.y.set(0.0f);

			boss_sprite_left = PAT_SHINKI_LEFT;
			boss_sprite_right = PAT_SHINKI_RIGHT;
			boss_sprite_stay = PAT_SHINKI_STILL;
			b6balls_load();
		}
		boss_hittest_shots_invincible();

		// Timeout condition
		if(boss.phase_frame >= (HUD_HP_FILL_FRAMES + 64)) {
			// Next phase
			boss.phase_frame = 0;
			boss.phase++;
			snd_se_play(13);
			bg_render_bombing_func = shinki_bg_render;
		}
		break;

	case PHASE_BOSS_ENTRANCE_BB:
		boss_hittest_shots_invincible();
		if(boss.phase_frame == (
			ENTRANCE_BB_FRAMES_PER_CEL * (TILES_BB_CELS / 2)
		)) {
			Palettes[0].set(0x0, 0x0, 0x0);
			palette_changed = true;
		}

		// Timeout condition
		if(boss.phase_frame >= (ENTRANCE_BB_FRAMES_PER_CEL * TILES_BB_CELS)) {
			// Next phase
			boss.phase++;
			boss.mode = 1;
			boss.phase_frame = 0;
			phase_2_3_pattern = pattern_curved_rings;
			phase_relative = 0;
		}
		break;

	case 2:
	case 3:
		switch(boss.mode) {
		case 0:
			if(boss_flystep_random(
				boss.phase_frame - PHASE_2_3_PATTERN_START_FRAME
			)) {
				#define PATTERNS SHINKI_PATTERNS_PHASE_2_3
				extern const pattern_oneshot_func_t PATTERNS[2][2];

				boss.phase_frame = 0;
				boss.phase_state.patterns_seen++;
				boss.mode++;
				phase_2_3_pattern = PATTERNS[phase_relative][
					boss.phase_state.patterns_seen & 1
				];

				// Timeout condition
				if(boss.phase_state.patterns_seen >= 16) {
					goto phase_2_3_timed_out;
				}

				#undef PATTERNS
			}
			break;
		case 1:
			phase_2_3_with_pattern();
			break;
		}
		if(!boss_hittest_shots()) {
			break;
		}
		boss_score_bonus(10);

	phase_2_3_timed_out:
		// Next phase
		if(phase_relative == 0) {
			boss_phase_next(ET_NW_SE, HP_PHASE_3_END);
			boss.mode = 1;
			phase_2_3_pattern = pattern_random_directional_and_kunai;
		} else {
			boss_phase_next(ET_NW_SE, HP_PHASE_6_END);
		}
		phase_relative++;
		break;

	case 4:
		boss_hittest_shots();

		// Timeout condition
		if(boss_flystep_towards(
			to_sp(PLAYFIELD_W / 2), to_sp(playfield_fraction_y(5 / 23.0f))
		)) {
			// Next phase
			boss.phase++;
			boss.phase_frame = 0;
		}
		break;

	case 5:
		boss_hittest_shots();

		// Timeout condition
		if(pattern_wing_preparation()) {
			// Next phase
			boss.phase++;
			boss.phase_frame = 0;
			boss.pos.velocity.y.set(0.0f);
			boss_custombullets_render = shinki_custombullets_render;
			// How generous for Yuuka players!
			boss_hitbox_radius.x.v = select_for_playchar(
				to_sp(50.0f), to_sp(35.0f), to_sp(45.0f), to_sp(50.0f)
			);
			wing_pattern = pattern_random_rain_and_spreads_from_wings;
			phase_relative = 0;
		}
		break;

	case 6:
	case 7:
		if(Palettes[0].c.b < 0x80) {
			if(stage_frame_mod16 == 0) {
				Palettes[0].c.b++;
			}
			palette_changed = true;
		}
		shinki_move_float();
		wing_pattern();

		// Timeout condition
		if(boss.phase_frame < 3000) {
			if(boss_hittest_shots()) {
				boss_score_bonus(25);
			} else {
				break;
			}
		}

		// Next phase
		if(phase_relative == 0) {
			boss_phase_next(ET_SW_NE, HP_PHASE_7_END);
			wing_pattern = pattern_cheetos_within_spread_walls;
			boss.phase_frame = 0; // redundant
			phase_relative++;
		} else {
			boss_phase_next(ET_HORIZONTAL, HP_PHASE_9_END);
		}
		break;

	case 8:
		if(Palettes[0].c.b > 0x00) {
			if(stage_frame_mod8 == 0) {
				Palettes[0].c.b--;
			}
			palette_changed = true;
		}
		boss_hittest_shots();

		// Timeout condition
		if(pattern_wings_to_purple()) {
			// Next phase
			boss.phase++;
			boss.phase_frame = 0;
			wing_pattern = pattern_aimed_b6balls_and_symmetric_spreads;
			phase_relative = 0;
		}
		break;

	case 9:
	case 10:
		if(Palettes[0].c.b > 0x00) {
			if(stage_frame_mod8 == 0) {
				Palettes[0].c.b--;
			}
			palette_changed = true;
		} else if(Palettes[0].c.r < 0x80) {
			if(stage_frame_mod16 == 0) {
				Palettes[0].c.r++;
			}
			palette_changed = true;
		}
		shinki_move_float();
		wing_pattern();

		// Timeout condition
		if(boss.phase_frame < 3000) {
			phase_done = boss_hittest_shots();
			// Reduce per-frame damage to 1 HP during bombs
			if(bombing) {
				boss.hp += (boss.damage_this_frame - 1);
				phase_done = false;
			}
			if(!phase_done) {
				break;
			}
			boss_score_bonus(25);
		}

		// Next phase
		if(phase_relative == 0) {
			boss_phase_next(ET_SW_NE, HP_PHASE_10_END);
			shinki_wing_pattern = pattern_devil;
			boss.phase_frame = 0; // redundant
			phase_relative++;
		} else {
			boss_phase_next(ET_HORIZONTAL, HP_PHASE_12_END);
			playfield_shake_anim_time = PHASE_11_FRAMES;
			// The pattern_devil() lasers. Should ideally be stopped inside the
			// pattern, but since it's a looping one without a clear end,
			// there's no easy way with the original architecture.
			laser_stop(0);
			laser_stop(1);
			laser_stop(2);
			laser_stop(3);
		}
		break;

	case 11:
		boss_hittest_shots();
		if((boss.phase_frame % 2) == 0) {
			palette_settone_deferred(150);
		} else {
			palette_settone_deferred(100);
		}

		// Timeout condition
		if(boss.phase_frame > PHASE_11_FRAMES) {
			// Next phase
			boss.phase++;
			boss.sprite = PAT_SHINKI_STILL;
			boss_hitbox_radius.x.v = to_sp(BOSS_HITBOX_DEFAULT_W);
			Palettes[0].c.r = 0x60;
			Palettes[0].c.b = 0x00;
			snd_se_play(13);
		}
		break;

	case 12:
		pattern_circles_and_alternating_spirals();
		// Timeout condition
		if(boss.phase_frame < 3000) {
			// Boss defeated?
			if(!boss_hittest_shots()) {
				break;
			}
			boss.phase_state.defeat_bonus = true;
		}
		// Boss defeated
		boss_explode_small(ET_VERTICAL);
		boss.phase_frame = 0;
		boss.phase = PHASE_BOSS_EXPLODE_SMALL;
		break;

	default:
		boss_defeat_update(65);
		break;
	}
	b6balls_update();
	cheetos_update();
	hud_hp_update_and_render(boss.hp, HP_TOTAL);

	#undef phase_relative
}
// ----------

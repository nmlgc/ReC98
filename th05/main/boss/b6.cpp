/// Stage 6 Boss - Shinki
/// ---------------------

#include "platform.h"
#include "pc98.h"
#include "th01/math/area.hpp"
#include "th01/math/subpixel.hpp"
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
#include "th05/main/boss/boss.hpp"
#include "th05/sprites/main_pat.h"

// Constants
// ---------

static const int PHASE_2_3_PATTERN_START_FRAME = 32;
// ---------

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

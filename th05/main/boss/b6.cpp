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
}
#include "th05/main/boss/boss.hpp"
#include "th05/sprites/main_pat.h"

// Constants
// ---------

static const int PHASE_2_3_PATTERN_START_FRAME = 32;
// ---------

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

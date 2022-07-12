#include "platform.h"
#include "pc98.h"
#include "th01/math/subpixel.hpp"
extern "C" {
#include "th04/math/randring.hpp"
}
#include "th04/math/motion.hpp"
#include "th04/sprites/main_pat.h"
#include "th04/main/phase.hpp"
#include "th04/main/score.hpp"
#include "th04/main/playfld.hpp"
#include "th04/main/pointnum/pointnum.hpp"
#include "th04/main/midboss/midboss.hpp"
#include "th04/main/boss/boss.hpp"

static const subpixel_t BONUS_AREA_W = TO_SP(PLAYFIELD_W / 3);
static const subpixel_t BONUS_AREA_H = TO_SP(PLAYFIELD_W / 3);

#define bonus_pointnum_add(base_left, base_top, points) { \
	subpixel_t center_x = (base_left + randring2_next16_mod(BONUS_AREA_W)); \
	if(center_x < to_sp(0.0f)) { \
		center_x = to_sp(0.0f); \
	} else if(center_x > to_sp(PLAYFIELD_W)) { \
		center_x = to_sp(PLAYFIELD_W); \
	} \
	pointnums_add_yellow( \
		center_x, (base_top + randring2_next16_mod(BONUS_AREA_H)), points \
	); \
}

#define score_bonus(units, value, center) { \
	score_delta += (units * value); \
	pointnum_times_2 = false; \
	subpixel_t base_left = (center.x.v - (BONUS_AREA_W / 2)); \
	subpixel_t base_top = (center.y.v - (BONUS_AREA_H / 2)); \
	for(unsigned int i = 0; i < units; i++) { \
		bonus_pointnum_add(base_left, base_top, value); \
	} \
}

void pascal near midboss_score_bonus(unsigned int units)
{
	score_bonus(units, MIDBOSS_BONUS_UNIT_VALUE, midboss.pos.cur);
}

// Probably only here because the code is identical to the midboss version.
void pascal near boss_score_bonus(unsigned int units)
{
	score_bonus(units, BOSS_BONUS_UNIT_VALUE, boss.pos.cur);
	boss_phase_timed_out = false;
}

void near midboss_defeat_update(void)
{
	if(midboss.phase == PHASE_EXPLODE_BIG) {
		if(midboss.phase_frame == ((GAME == 5) ? 1 : 0)) {
			playfield_shake_anim_time = ((GAME == 5) ? 10 : 12);
			#if (GAME == 5)
				// Deferred to midboss_reset() in TH04.
				midboss_active = false;
			#endif
		}

		#if (GAME == 4)
			midboss.phase_frame++;
		#endif

		if((midboss.phase_frame % 16) == 0) {
			midboss.sprite++;
			if(midboss.sprite >= (PAT_ENEMY_KILL_last + 1)) {
				midboss.phase = PHASE_NONE;
			}
		}
	} else {
		/* TODO: Replace with the decompiled call
		 * 	midboss_reset();
		 * if we ever decide to put that function into the same translation
		 * unit */
		_asm { push cs; call near ptr midboss_reset; }
	}
}

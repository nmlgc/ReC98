#include "th01/main/extend.hpp"

void score_extend_update_and_render(void)
{
	if(score >= (extend_next * SCORE_PER_EXTEND)) {
		if(rem_lives < LIVES_MAX) {
			rem_lives++;
			resident->rem_lives = rem_lives;
			hud_lives_put(rem_lives - 1);
			mdrv2_se_play(15);
			pellet_speed_raise(1);
		}
		extend_next++;
	}
}


#include "th02/main/score.hpp"

// State
// -----

// Amount of points transferred from [score_delta] to [score] during the
// previous frame.
extern unsigned int score_delta_transferred_prev;
// -----

#define score_render_and_process_hiscore_and_extends() { \
	hud_score_put(HUD_SCORE_Y, score); \
	if(score > hiscore) { \
		hiscore = score; \
		hud_score_put(HUD_HISCORE_Y, hiscore); \
	} \
	if(EXTEND_SCORES[extends_gained] <= score) { \
		if(lives < LIVES_MAX) { \
			lives++; \
			hud_lives_put(); \
			snd_se_play(8); \
		} \
		extends_gained++; \
	} \
}

void score_grant_current_delta_as_bonus(void)
{
	score += score_delta;
	score_render_and_process_hiscore_and_extends();
}

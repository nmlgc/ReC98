#include "th02/main/score.hpp"

// State
// -----

// Amount of points transferred from [score_delta] to [score] during the
// previous frame.
extern unsigned int score_delta_transferred_prev;
// -----

void near score_extend_init(void)
{
	extends_gained = 0;
	while(EXTEND_SCORES[extends_gained] <= score) {
		extends_gained++;
	}
	score_delta = 0;
}

void score_delta_commit(void)
{
	score += score_delta;
	score_delta = 0;
	score_delta_transferred_prev = 0;
}

void near score_reset(void)
{
	extern int32_t score_reset_unknown_40000;

	score = 0;
	score_delta = 0;
	score_delta_transferred_prev = 0;
	score_reset_unknown_40000 = 40000;
}

// Due to how the branches below are nested, it's not worth it to try working
// around these warnings.
#if defined(__TURBOC__) && defined(__MSDOS__)
	#pragma warn -rch
	#pragma warn -ccc
#endif

#define score_render_and_process_hiscore_and_extends( \
	turn_capped_lives_into_bombs \
) { \
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
		} else if(turn_capped_lives_into_bombs) { \
			if(bombs < BOMBS_MAX) { \
				bombs++; \
				hud_bombs_put(); \
			} \
			\
			/* ZUN quirk: Playing a sound even if the player got nothing? */ \
			snd_se_play(8); \
		} \
		extends_gained++; \
	} \
}

void near score_update_and_render(void)
{
	if(score_delta != 0) {
		if(!reduce_effects) {
			// ZUN bloat: score_delta_transferred_prev = max(
			// 	score_delta_transferred_prev,
			// 	min(max((score_delta / 32), 1), 1111)
			// );
			score_t to_transfer = score_delta;
			if(to_transfer < 32) {
				to_transfer = 32;
			}
			to_transfer >>= 5;
			if(score_delta_transferred_prev < to_transfer) {
				if(to_transfer > 1111) {
					to_transfer = 1111;
				}
				score_delta_transferred_prev = to_transfer;
			}
		} else {
			score_delta_transferred_prev = 3111;
		}

		// ZUN bloat: score_delta_transferred_prev = max(
		// 	score_delta_transferred_prev, score_delta
		// );
		// score_delta -= score_delta_transferred_prev;
		//
		// (In fact, the original algorithm requires `score_t` to be signed.)
		score_t delta_rem = score_delta;
		delta_rem -= score_delta_transferred_prev;
		if(delta_rem < 0) {
			score_delta_transferred_prev = score_delta;
			delta_rem = 0;
		}
		score_delta = delta_rem;

		score += score_delta_transferred_prev;
		score_render_and_process_hiscore_and_extends(true);
	} else {
		score_delta_transferred_prev = 0;
	}
}

void score_grant_current_delta_as_bonus(void)
{
	score += score_delta;
	score_render_and_process_hiscore_and_extends(false);
}

#if defined(__TURBOC__) && defined(__MSDOS__)
	#pragma warn .rch
	#pragma warn .ccc
#endif

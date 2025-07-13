#include "th04/main/hiscore.hpp"
#include "th04/main/stage/stage.hpp"
#include "th04/main/slowdown.hpp"
#include "th04/common.h"

void near hiscore_continue_enter_raw(void)
{
	struct hack {
		gaiji_th04_t x[8];
	};
	extern struct hack gCONTINUE_;

	int c;
	int i;

	// ZUN bloat: Not `static`, gets needlessly copied into a local variable.
	const struct hack gCONTINUE = gCONTINUE_;

	// ZUN bloat: Could have been local.
	extern uint8_t entered_place;

	for(i = (SCOREDAT_PLACES - 1); i >= 0; i--) {
		for(c = (SCORE_DIGITS - 1); c >= 0; c--) {
			// ZUN bug: The subtraction causes C to promote the right-hand side
			// of these comparisons to `int`, which leads to the same overflow
			// issue that causes the rendering bug in the High Score viewer. In
			// this instance, gaiji-offsetted digits ≥96 that overflowed to 0
			// will get interpreted as negative. And since any un-offsetted
			// [score] is larger than a negative digit, it always gets sorted
			// into the list *above* such an overflowed score, thus gradually
			// pushing the latter out of the list with each new call to this
			// function.
			// This bug reinforces the High Score viewer's soft score limit of
			// 959,999,999, or `A9 A9 A9 A9 A9 A9 A9 FF` in the gaiji-offsetted
			// [hi.score] list.
			if(score.digits[c] > (hi.score.g_score[i].digits[c] - gb_0)) {
				break;
			}
			if(score.digits[c] < (hi.score.g_score[i].digits[c] - gb_0)) {
				goto found_place;
			}
		}
	}
	entered_place = 0;
	goto shift;

found_place:
	if(i == (SCOREDAT_PLACES - 1)) {
		entered_place = -1; // ZUN bloat
		return;
	}
	entered_place = (i + 1);

	// ZUN bloat: How about memcpy()? The next three inner loops perform a
	// total of 24 multiplications and 16 bit shifts.
shift:
	for(i = (SCOREDAT_PLACES - 2); i >= entered_place; i--) {
		for(c = (SCOREDAT_NAME_LEN - 1); c >= 0; c--) {
			hi.score.g_name[i + 1][c] = hi.score.g_name[i][c];
		}
		for(c = (SCORE_DIGITS - 1); c >= 0; c--) {
			hi.score.g_score[i + 1].digits[c] = hi.score.g_score[i].digits[c];
		}
		hi.score.g_stage[i + 1] = hi.score.g_stage[i];
	}

	static_assert(sizeof(gCONTINUE) == SCOREDAT_NAME_LEN);
	for(c = (SCOREDAT_NAME_LEN - 1); c >= 0; c--) {
		hi.score.g_name[entered_place][c] = gCONTINUE.x[c];
	}

	for(c = (SCORE_DIGITS - 1); c >= 0; c--) {
		hi.score.g_score[entered_place].digits[c] = (score.digits[c] + gb_0);
	}

	if(stage_id != STAGE_EXTRA) {
		hi.score.g_stage[entered_place] = (gb_1 + stage_id);
	} else {
		hi.score.g_stage[entered_place] = gb_1;
	}

	hiscore_scoredat_save();
}

void near hiscore_continue_enter(void)
{
	hiscore_scoredat_load_for_cur();
	if(turbo_mode) {
		hiscore_continue_enter_raw();
	}
}

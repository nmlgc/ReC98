#include <dos.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "th01/formats/ptn.hpp"
extern "C" {
#include "th01/snd/mdrv2.h"
}

/// Coordinates
/// -----------

// TOTLE
// -----

static const vram_word_amount_t TOTLE_METRIC_VRAM_WORD_LEFT = (224 / 16);
static const pixel_t TOTLE_METRIC_DIGIT_W = PTN_QUARTER_W;
// -----
/// -----------

// ZUN quirk: No ([digit] % 10) for the quarter calculation? As a result, we
// get scrambled numerals if [digit % 20] is between 10 and 19 inclusive:
//
// | 10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 |   18   |   19   |
// |  2 |  3 |  0 |  1 |  6 |  7 |  4 |  5 | (none) | (none) |
#define totle_metric_digit_scramble_if_ge_10_and_put_8(left, top, digit) { \
	ptn_put_quarter_8( \
		left, top, (PTN_TOTLE_NUMERAL_16 + ((digit % 10) / 4)), (digit % 4) \
	); \
} \

// [digit] must be a value from 0 to 9, but [place] can be negative.
void pascal near totle_metric_digit_animate(
	int digit, int place, screen_y_t top
)
{
	enum {
		DIGIT_LOOPS = 2, // Number of full loops from 0 to 9
	};

	int loops_done = 0;
	screen_x_t left = (
		(TOTLE_METRIC_VRAM_WORD_LEFT * 16) + (place * TOTLE_METRIC_DIGIT_W)
	);

	// The only place in the game where this hack is appropriate… but even
	// here, that's only because the left coordinate is always word-aligned.
	ptn_sloppy_unput_before_alpha_put = true;

	for(int i = 0; i < (DIGIT_LOOPS * 10); i++) {
		totle_metric_digit_scramble_if_ge_10_and_put_8(left, top, i);
		if((i % 10) == (digit % 10)) {
			loops_done++;
		}
		if(loops_done >= DIGIT_LOOPS) {
			break;
		}
		delay(4);
		mdrv2_se_play(2);
	}

	// Only necessary because the last numeral rendered in the loop is
	// guaranteed to be a scrambled one.
	totle_metric_digit_scramble_if_ge_10_and_put_8(left, top, digit);

	ptn_sloppy_unput_before_alpha_put = false;
}

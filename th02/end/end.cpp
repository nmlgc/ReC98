#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "master.hpp"
#include "shiftjis.hpp"
#include "th01/hardware/grppsafx.h"
#include "th02/score.h"
#include "th02/v_colors.hpp"
#include "th02/hardware/frmdelay.h"
#include "th02/hardware/input.hpp"
#include "th02/formats/end.hpp"
#include "th02/gaiji/gaiji.h"
#include "th02/gaiji/score_p.hpp"

// State
// -----

shiftjis_t end_text[100][END_LINE_SIZE];
int8_t line_col_and_fx;
bool line_type_allow_fast_forward_and_automatically_clear_end_line;
// -----

// Function ordering fails
// -----------------------

void near end_line_clear(void);
// -----------------------

void pascal near end_load(const char *fn)
{
	file_ropen(fn);

	// ZUN landmine: No check to ensure that the size is ≤ sizeof(end_text).
	// Dynamic allocation would have made more sense...
	size_t size = file_size();
	file_read(end_text, size);

	file_close();
}

void pascal near verdict_value_score_put(
	screen_x_t left, screen_y_t top, score_t score
)
{
	#define on_digit(i, gaiji) { \
		graph_gaiji_putc((left + (GAIJI_W * i)), top, gaiji, V_WHITE); \
	}
	gaiji_score_put(score, on_digit, false);
	#undef on_digit
}

void pascal near line_type(
	screen_x_t left,
	screen_y_t top,
	shiftjis_ank_amount_t len,
	shiftjis_t* str,
	int frames_per_kanji
) {
	// ZUN landmine: Susceptible to buffer overflows if [len] is larger.
	shiftjis_t buf[RES_X / GLYPH_HALF_W] = { '\0' };
	int i = 0;
	for(int loop = 0; loop < len; loop += int(sizeof(shiftjis_kanji_t))) {
		// ZUN bug: Does not address the PC-98 keyboard quirk documented in the
		// `Research/HOLDKEY` example. As a result, the eventual key release
		// scancode won't be filtered and will get through to [key_det], ...
		input_reset_sense();

		buf[i] = str[i];
		i++;
		buf[i] = str[i];
		i++;
		buf[i] = '\0';
		graph_putsa_fx(left, top, line_col_and_fx, buf);

		// …which leads to the code taking the branch with the longer delay
		// every once in a while, even if the player still holds a key. While
		// the condition checks for *any* key being held, the probability of
		// taking the wrong branch remains identical regardless of how many
		// keys are held down, as the key release scancodes are only sent for
		// the last key that was pressed.
		if(
			line_type_allow_fast_forward_and_automatically_clear_end_line &&
			(key_det != INPUT_NONE)
		) {
			// As [loop] increases by 2 on each iteration, the loop will
			// alternate between this delay and no delay at all, resulting in
			// two kanji every ([frames_per_kanji] / 3) frames.
			if(loop & 3) {
				frame_delay(frames_per_kanji / 3);
			}
		} else {
			frame_delay(frames_per_kanji);
		}
	}
	for(i = 0; i < 20; i++) {
		input_reset_sense();
		if(
			line_type_allow_fast_forward_and_automatically_clear_end_line &&
			(key_det != INPUT_NONE)
		) {
			// ZUN bloat: Technically, a 0-frame delay is not a no-op. Because
			// it still resets [vsync_Count1], it forms a frame boundary in
			// case the current frame didn't finish rendering within a single
			// VSync interrupt.
			// In this context though, this function call might as well be a
			// `break`. Without the 614.4 µs delay to address the PC-98
			// keyboard quirk documented in the `Research/HOLDKEY` example, a
			// single call to input_reset_sense() encompasses
			//
			// • 8 INT 18h, AH=04h calls,
			// • 18 comparisons, and
			// • 14 branches with OR assignments.
			//
			// The exact implementation of INT 18h varies between PC-98 models,
			// so there's no point in precisely counting CPU cycles here. But
			// given that this blocking loop does nothing else *and* we're sure
			// to get here at the very start of a frame, it makes sense to
			// assume that 20 of those calls can easily fit within the ≈600,000
			// cycles we have for every frame on the game's target 33 MHz CPUs.
			frame_delay(0);
		} else {
			frame_delay(2);
		}
	}
	if(line_type_allow_fast_forward_and_automatically_clear_end_line) {
		end_line_clear();
	}
}

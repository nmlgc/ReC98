#include <stddef.h>
#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "shiftjis.hpp"
#include "libs/kaja/kaja.h"
#include "th01/hardware/egc.h"
#include "th01/hardware/grppsafx.h"
#include "th01/formats/cutscene.hpp"
#include "th02/score.h"
#include "th02/v_colors.hpp"
#include "th02/hardware/frmdelay.h"
#include "th02/hardware/input.hpp"
#include "th02/formats/end.hpp"
#include "th02/gaiji/gaiji.h"
#include "th02/gaiji/score_p.hpp"
extern "C" {
#include "th02/snd/snd.h"
}
#include "th02/end/staff.hpp"
#include "th02/sprites/verdict.hpp"

// Coordinates
// -----------

static const screen_y_t CUTSCENE_PIC_TOP = ((RES_Y / 2) - (CUTSCENE_PIC_H / 2));
static const pixel_t END_LINE_W = (END_LINE_LENGTH * GLYPH_HALF_W);

static const screen_x_t END_LINE_LEFT = ((RES_X / 2) - (END_LINE_W / 2));
static const screen_y_t END_LINE_TOP = (
	CUTSCENE_PIC_TOP + CUTSCENE_PIC_H + (GLYPH_H * 2)
);
static const screen_x_t END_LINE_RIGHT = (END_LINE_LEFT + END_LINE_W);
static const screen_y_t END_LINE_BOTTOM = (END_LINE_TOP + GLYPH_H);
// -----------

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

void verdict_kanji_1_to_0_masked(
	screen_x_t left, screen_y_t top, const dots16_t mask[VERDICT_MASK_H]
)
{
	static_assert(VERDICT_MASK_H == GLYPH_H);
	Planar<dots_t(VERDICT_MASK_W)> dots;
	vram_offset_t vo = vram_offset_shift(left, top);
	for(pixel_t row = 0; row < VERDICT_MASK_H; row++) {
		// ZUN bloat: Thanks to the blit functions being macros, `mask[row]` is
		// evaluated a total of 5 times. Once would be enough.
		graph_accesspage(1);
		VRAM_SNAP_PLANAR(dots, vo, VERDICT_MASK_W);

		graph_accesspage(0);

		grcg_setcolor(GC_RMW, 0);
		grcg_put(vo, mask[row], VERDICT_MASK_W);
		grcg_off();

		vram_or_planar_masked(vo, dots, VERDICT_MASK_W, mask[row]);

		vo += ROW_SIZE;
	}
}

void verdict_row_1_to_0_animate(
	screen_x_t left, screen_y_t top, shiftjis_kanji_amount_t len
)
{
	// ZUN bloat: This array is not `static`, and will be needlessly copied
	// into a local variable at every call to the function.
	#include "th02/sprites/verdict.csp"

	shiftjis_kanji_amount_t i;
	for(int mask = 0; mask < VERDICT_MASK_COUNT; mask++) {
		for(i = 0; i < len; i++) {
			verdict_kanji_1_to_0_masked(
				(left + (i * GLYPH_FULL_W)),
				top,
				&sVERDICT_MASKS[mask][0]
			);
		}
		frame_delay(10);
	}
}

void pascal near gaiji_boldfont_str_from_positive_3_digit_value(
	int value, // ZUN bloat: Not meant to support unsigned values.
	gaiji_th02_t str[4]
)
{
	enum {
		DIGITS = 3,
	};
	int divisor = 100; // Must match DIGITS!
	int8_t digit;
	uint8_t past_leading_zeroes = 0;
	int i = 0;
	while(i < DIGITS) {
		digit = (value / divisor);
		if(past_leading_zeroes == 0) {
			past_leading_zeroes = digit;
		}
		if(past_leading_zeroes || (i == (DIGITS - 1))) {
			str[i] = gaiji_th02_t(gb_0_ + digit);
		} else {
			str[i] = gb_SP;
		}
		value -= (digit * divisor);
		i++;
		divisor /= 10;
	}
	str[i] = gs_NULL;
}

// ZUN bloat: Same algorithm as in TH01, same problems. Also could be a
// single proper function.
#define pic_put(left, top, rows, quarter, quarter_offset_y) { \
	uvram_offset_t vram_offset_src = ( \
		(quarter == 0) ? vram_offset_shift(0, 0) : \
		(quarter == 1) ? vram_offset_shift(CUTSCENE_PIC_W, 0) : \
		(quarter == 2) ? vram_offset_shift(0, CUTSCENE_PIC_H) : \
		/*quarter == 3*/ vram_offset_shift(CUTSCENE_PIC_W, CUTSCENE_PIC_H) \
	); \
	uvram_offset_t vram_offset_dst = vram_offset_shift(left, top); \
	vram_offset_src += (quarter_offset_y * ROW_SIZE); \
	\
	egc_start_copy(); \
	\
	pixel_t y = quarter_offset_y; \
	vram_byte_amount_t vram_x; \
	while(y < (rows + quarter_offset_y)) { \
		vram_x = 0; \
		while(vram_x < CUTSCENE_PIC_VRAM_W) { \
			egc_temp_t d; \
			\
			graph_accesspage(1);	d = egc_chunk(vram_offset_src); \
			graph_accesspage(0);	egc_chunk(vram_offset_dst) = d; \
			\
			vram_x += EGC_REGISTER_SIZE; \
			vram_offset_src += EGC_REGISTER_SIZE; \
			vram_offset_dst += EGC_REGISTER_SIZE; \
		} \
		y++; \
		vram_offset_dst += (ROW_SIZE - CUTSCENE_PIC_VRAM_W); \
		vram_offset_src += (ROW_SIZE - CUTSCENE_PIC_VRAM_W); \
	} \
	egc_off(); \
}

void pascal near end_pic_show(int quarter)
{
	pic_put(CUTSCENE_PIC_LEFT, CUTSCENE_PIC_TOP, CUTSCENE_PIC_H, quarter, 0);
}

void pascal near staffroll_pic_put(screen_x_t left, screen_y_t top, int quarter)
{
	pic_put(left, top, CUTSCENE_PIC_H, quarter, 0);
}

void pascal near end_pic_put_rows(
	int quarter, pixel_t quarter_offset_y, pixel_t rows
)
{
	pic_put(
		CUTSCENE_PIC_LEFT, CUTSCENE_PIC_TOP, rows, quarter, quarter_offset_y
	);
}

void near end_line_clear(void)
{
	screen_y_t y;
	screen_y_t x;

	grcg_setcolor(GC_RMW, 0);
	for(y = END_LINE_TOP; y < END_LINE_BOTTOM; y++) {
		for(x = END_LINE_LEFT; x < END_LINE_RIGHT; x += GLYPH_FULL_W) {
			vram_offset_t vo = vram_offset_shift(x, y);
			grcg_put(vo, 0xFFFF, GLYPH_FULL_W);
		}
	}
	grcg_off();
}

void near end_to_staffroll_animate(void)
{
	enum {
		VELOCITY = 4,

		// ZUN bloat: (CUTSCENE_PIC_H - 1) would have been enough.
		SHIFT_H = (RES_Y - 1 - CUTSCENE_PIC_TOP),
	};
	end_load("end3.txt");
	frame_delay(30);

	palette_white_out(1);

	snd_load("ending.m", SND_LOAD_SONG);
	snd_kaja_func(KAJA_SONG_PLAY, 0);
	end_line_clear();
	palette_white_in(4);

	snd_delay_until_measure(5);

	screen_x_t left_prev = CUTSCENE_PIC_LEFT;

	// ZUN quirk: Off by 4? Did you mean ">="?
	while(left_prev > (STAFFROLL_PIC_LEFT + VELOCITY)) {
		// ZUN bloat: Could have made use of the fact that this image is
		// surrounded by black pixels. Shifting [CUTSCENE_PIC_W + VELOCITY]
		// pixels would have avoided the need to use the GRCG below, as well
		// as the subsequent...
		egc_shift_left(
			left_prev,
			CUTSCENE_PIC_TOP,
			(left_prev + CUTSCENE_PIC_W - 1),
			SHIFT_H,
			VELOCITY
		);

		grcg_setcolor(GC_RMW, 0);
		grcg_boxfill(
			// ZUN bug: …which cuts off [VELOCITY] pixels at the right side.
			(left_prev + CUTSCENE_PIC_W - (VELOCITY * 2)),
			CUTSCENE_PIC_TOP,
			(left_prev + CUTSCENE_PIC_W - 1),
			SHIFT_H
		);
		grcg_off();
		frame_delay(1);
		left_prev -= VELOCITY;
	}
}

#include "platform.h"
#include "pc98.h"
#include "master.hpp"
#include "shiftjis.hpp"
#include "th01/math/clamp.hpp"
#include "th01/hardware/egc.h"
#include "th02/v_colors.hpp"
extern "C" {
#include "th02/hardware/frmdelay.h"
#include "th04/score.h"
#if (GAME == 5)
	#include "th05/resident.hpp"
#else
	#include "th04/resident.hpp"
#endif
#include "th04/hardware/grppsafx.h"
#include "th04/hardware/input.h"
#include "th04/snd/snd.h"
}
#include "th04/shiftjis/m_setup.hpp"

// MSWIN.BFT sprites
enum setup_window_patnum_t {
	MSWIN_INSIDE,
	MSWIN_MIDDLE_TOP,
	MSWIN_MIDDLE_LEFT,
	MSWIN_MIDDLE_BOTTOM,
	MSWIN_MIDDLE_RIGHT,
	MSWIN_LEFT_TOP,
	MSWIN_LEFT_BOTTOM,
	MSWIN_RIGHT_BOTTOM,
	MSWIN_RIGHT_TOP,
};

static const vc2 COL_INACTIVE = 0;
static const vc2 COL_ACTIVE = V_WHITE;

// Coordinates
// -----------

static const pixel_t MSWIN_BORDER_H = 8;
static const pixel_t MSWIN_W = 16;
static const pixel_t MSWIN_H = 16;

#define window_w_for_content_w(content_w) (\
	MSWIN_W + content_w + MSWIN_W \
)

static const pixel_t DROP_SPEED = (MSWIN_H / 2);
static const int DROP_FRAMES_PER_TILE = (MSWIN_H / DROP_SPEED);

static const screen_x_t CAPTION_LEFT = ((RES_X / 2) - (CAPTION_W / 2));
static const screen_y_t CAPTION_TOP = 88;

inline void assert_that_all_choices_are_equally_wide(void) {
	static_assert(shiftjis_w(BGM_CHOICE_FM86) == shiftjis_w(BGM_CHOICE_FM26));
	static_assert(shiftjis_w(BGM_CHOICE_FM86) == shiftjis_w(BGM_CHOICE_OFF));
	static_assert(shiftjis_w(BGM_CHOICE_FM86) == shiftjis_w(SE_CHOICE_BEEP));
	static_assert(shiftjis_w(BGM_CHOICE_FM86) == shiftjis_w(SE_CHOICE_FM));
	static_assert(shiftjis_w(BGM_CHOICE_FM86) == shiftjis_w(SE_CHOICE_OFF));
}

static const pixel_t CHOICE_W = shiftjis_w(BGM_CHOICE_FM86);
static const pixel_t CHOICE_WINDOW_W = window_w_for_content_w(CHOICE_W);

static const screen_x_t CHOICE_LEFT = 48; // Not quite centered...
static const screen_x_t CHOICE_TOP = 136;
static const screen_x_t HELP_LEFT = (CHOICE_LEFT + CHOICE_WINDOW_W);
static const screen_x_t HELP_TOP = CHOICE_TOP;
// -----------

typedef int mswin_tile_amount_t;

static Palette8 palette_unused; // ZUN bloat
struct {
	mswin_tile_amount_t w;
	mswin_tile_amount_t h;

	pixel_t pixel_w(void) const {
		return (w * MSWIN_W);
	}
	pixel_t pixel_h(void) const {
		return (h * MSWIN_H);
	}
} window;

// Blits ([DROP_SPEED] + [MSWIN_H]) pixels in the Y direction.
void pascal near window_dropdown_put(
	screen_x_t left, screen_y_t bottom_tile_top
)
{
	egc_copy_rect_1_to_0_16(left, bottom_tile_top, window.pixel_w(), MSWIN_H);

	super_put(left, bottom_tile_top, MSWIN_MIDDLE_LEFT);
	super_put(left, (bottom_tile_top + DROP_SPEED), MSWIN_LEFT_BOTTOM);
	left += MSWIN_W;
	for(mswin_tile_amount_t x = 1; x < (window.w - 1); (x++, left += MSWIN_W)) {
		super_put(left, bottom_tile_top, MSWIN_INSIDE);
		super_put(left, (bottom_tile_top + DROP_SPEED), MSWIN_MIDDLE_BOTTOM);
	}
	super_put(left, bottom_tile_top, MSWIN_MIDDLE_RIGHT);
	super_put(left, (bottom_tile_top + DROP_SPEED), MSWIN_RIGHT_BOTTOM);
}

void pascal near window_rollup_put(screen_x_t left, screen_y_t bottom_tile_top)
{
	egc_copy_rect_1_to_0_16(
		left, (bottom_tile_top + DROP_SPEED), window.pixel_w(), MSWIN_H
	);

	super_put(left, bottom_tile_top, MSWIN_LEFT_BOTTOM);
	left += MSWIN_W;
	for(mswin_tile_amount_t x = 1; x < (window.w - 1); (x++, left += MSWIN_W)) {
		super_put(left, bottom_tile_top, MSWIN_MIDDLE_BOTTOM);
	}
	super_put(left, bottom_tile_top, MSWIN_RIGHT_BOTTOM);
}

void pascal near dropdown(screen_x_t left, screen_y_t top_)
{
	mswin_tile_amount_t i;
	screen_x_t tile_left = left;
	screen_y_t top = top_; // ZUN bloat

	super_put(tile_left, top, MSWIN_LEFT_TOP);
	tile_left += MSWIN_W;
	for(i = 1; i < (window.w - 1); (i++, tile_left += MSWIN_W)) {
		super_put(tile_left, top, MSWIN_MIDDLE_TOP);
	}
	super_put(tile_left, top, MSWIN_RIGHT_TOP);

	top += MSWIN_H;
	i = 1;
	while(i < ((window.h * DROP_FRAMES_PER_TILE) - DROP_FRAMES_PER_TILE - 1)) {
		window_dropdown_put(left, top);
		frame_delay(1);
		i++;
		top += DROP_SPEED;
	}
}

void pascal near singleline(screen_x_t left, screen_y_t top)
{
	egc_copy_rect_1_to_0_16(left, top, window.pixel_w(), (MSWIN_H * 2));

	super_put(left, (top + (0 * MSWIN_H)), MSWIN_LEFT_TOP);
	super_put(left, (top + (1 * MSWIN_H)), MSWIN_LEFT_BOTTOM);
	left += MSWIN_W;
	for(mswin_tile_amount_t x = 1; x < (window.w - 1); (x++, left += MSWIN_W)) {
		super_put(left, (top + (0 * MSWIN_H)), MSWIN_MIDDLE_TOP);
		super_put(left, (top + (1 * MSWIN_H)), MSWIN_MIDDLE_BOTTOM);
	}
	super_put(left, (top + (0 * MSWIN_H)), MSWIN_RIGHT_TOP);
	super_put(left, (top + (1 * MSWIN_H)), MSWIN_RIGHT_BOTTOM);
}

void pascal near rollup(screen_x_t left, screen_y_t top)
{
	screen_y_t bottom_tile_top = top;
	bottom_tile_top += (window.pixel_h() - MSWIN_H);

	mswin_tile_amount_t i = 1;
	while(i < ((window.h * DROP_FRAMES_PER_TILE) - DROP_FRAMES_PER_TILE)) {
		window_rollup_put(left, bottom_tile_top);
		frame_delay(1);
		i++;
		bottom_tile_top -= DROP_SPEED;
	}
}

inline void window_animate(
	screen_x_t content_left,
	screen_y_t content_top,
	pixel_t content_w,
	int content_lines,
	void (near pascal *near animate_func)(screen_x_t, screen_y_t)
) {
	window.w = (window_w_for_content_w(content_w) / MSWIN_W);
	if(content_lines != 1) {
		window.h = (
			((MSWIN_BORDER_H * 2) + (content_lines * GLYPH_H)) / MSWIN_H
		);
	}
	animate_func((content_left - MSWIN_W), (content_top - MSWIN_BORDER_H));
}

// ZUN bloat: Could have been a single function with a value/string array
// parameter.
void pascal near bgm_choice_put(int bgm_mode, vc2 col)
{
	screen_y_t top = CHOICE_TOP;
	const shiftjis_t* str;
	static_assert(SND_BGM_MODE_COUNT == 3);
	switch(bgm_mode) {
	case SND_BGM_FM86:	str = BGM_CHOICE_FM86;	top += (0 * GLYPH_H);	break;
	case SND_BGM_FM26:	str = BGM_CHOICE_FM26;	top += (1 * GLYPH_H);	break;
	case SND_BGM_OFF:	str = BGM_CHOICE_OFF; 	top += (2 * GLYPH_H);	break;
	}
	graph_putsa_fx(CHOICE_LEFT, top, col, str);
}

void pascal near se_choice_put(int se_mode, vc2 col)
{
	screen_y_t top = CHOICE_TOP;
	const shiftjis_t* str;
	static_assert(SND_SE_MODE_COUNT == 3);
	switch(se_mode) {
	case SND_SE_FM:  	str = SE_CHOICE_FM;  	top += (0 * GLYPH_H);	break;
	case SND_SE_BEEP:	str = SE_CHOICE_BEEP;	top += (1 * GLYPH_H);	break;
	case SND_SE_OFF: 	str = SE_CHOICE_OFF; 	top += (2 * GLYPH_H);	break;
	}
	graph_putsa_fx(CHOICE_LEFT, top, col, str);
}

// ZUN bloat: Could have been inlined into setup_submenu().
void near bgm_help_put(void)
{
	screen_y_t top = HELP_TOP;
	for(int i = 0; i < HELP_LINES; (i++, top += GLYPH_H)) {
		graph_putsa_fx(HELP_LEFT, top, V_WHITE, BGM_HELP[i]);
	}
}

void near se_help_put(void)
{
	screen_y_t top = HELP_TOP;
	for(int i = 0; i < HELP_LINES; (i++, top += GLYPH_H)) {
		graph_putsa_fx(HELP_LEFT, top, V_WHITE, SE_HELP[i]);
	}
}

#define setup_submenu( \
	sel, \
	caption, \
	choice_count, \
	choice_default, \
	choice_put, \
	help_put, \
	increment_input \
) { \
	window_animate(CAPTION_LEFT, CAPTION_TOP, CAPTION_W, 1, singleline); \
	graph_putsa_fx(CAPTION_LEFT, CAPTION_TOP, V_WHITE, caption); \
	\
	window_animate(CHOICE_LEFT, CHOICE_TOP, CHOICE_W, choice_count, dropdown); \
	for(sel = 0; sel < choice_count; sel++) { \
		choice_put( \
			sel, ((sel == choice_default) ? COL_ACTIVE : COL_INACTIVE) \
		); \
	} \
	\
	window_animate(HELP_LEFT, HELP_TOP, HELP_W, HELP_LINES, dropdown); \
	help_put(); \
	\
	sel = choice_default; \
	while(1) { \
		input_wait_for_change(0); \
		frame_delay(1); \
		if((key_det & INPUT_OK) || (key_det & INPUT_SHOT)) { \
			break; \
		} \
		if(key_det & increment_input) { \
			choice_put(sel, COL_INACTIVE); \
			if(sel == (choice_count - 1)) { \
				sel = 0; \
			} else { \
				sel++; \
			} \
			choice_put(sel, COL_ACTIVE); \
		} \
		if(key_det & (~increment_input & (INPUT_UP | INPUT_DOWN))) { \
			choice_put(sel, COL_INACTIVE); \
			if(sel == 0) { \
				sel = (choice_count - 1); \
			} else { \
				sel--; \
			} \
			choice_put(sel, COL_ACTIVE); \
		} \
	} \
	\
	window_animate(HELP_LEFT, HELP_TOP, HELP_W, HELP_LINES, rollup); \
	window_animate(CHOICE_LEFT, CHOICE_TOP, CHOICE_W, choice_count, rollup); \
}

void near setup_bgm_menu(void)
{
	int sel;
	setup_submenu(
		sel,
		SETUP_BGM_CAPTION,
		SND_BGM_MODE_COUNT,
		SND_BGM_FM86,
		bgm_choice_put,
		bgm_help_put,
		INPUT_UP
	);
	resident->bgm_mode = sel;
}

void near setup_se_menu(void)
{
	int sel;
	setup_submenu(
		sel,
		SETUP_SE_CAPTION,
		SND_SE_MODE_COUNT,
		SND_SE_FM,
		se_choice_put,
		se_help_put,
		INPUT_DOWN
	);
	resident->se_mode = sel;
}

/* ReC98
 * -----
 * TH04 player character selection menu
 */

#pragma option -zCop_01_TEXT

#include <stddef.h>
#include "game/bgimage.hpp"
#include "th01/hardware/grcg.hpp"
#include "th02/v_colors.hpp"
#include "th02/hardware/frmdelay.h"
#include "th04/common.h"
#include "th04/formats/scoredat/scoredat.hpp"
#include "th04/resident.hpp"
#include "th04/hardware/input.h"
#include "th04/hardware/grppsafx.h"
#include "th04/op/clear.hpp"
#include "th04/op/op.hpp"
#include "th04/op/impl.hpp"
#include "th04/sprites/op_cdg.hpp"

#include "th04/shiftjis/m_char.cpp"

static const pixel_t PIC_W = 256;
static const pixel_t PIC_H = 244;

static const vc2 COL_SELECTED = V_WHITE;
static const vc2 COL_NOT_SELECTED = 3;
static const vc2 COL_BOX = 2;
static const vc2 COL_SHADOW = 1;

// Raised edge
// -----------

static const pixel_t RAISE_W = 8;
static const pixel_t RAISE_H = 8;

inline vram_offset_t raise(vram_offset_t vram_offset) {
	return (vram_offset - vram_offset_shift(RAISE_W, RAISE_H));
}

inline void dropshadow_put(screen_x_t raised_left, vram_y_t raised_top) {
	grcg_setcolor(GC_RMW, COL_SHADOW);
	grcg_boxfill_8(
		(raised_left + PIC_W),
		(raised_top + RAISE_W),
		(raised_left + PIC_W),
		(raised_top + PIC_H - 1)
	);
	grcg_boxfill_8(
		(raised_left + RAISE_W),
		(raised_top + PIC_H),
		(raised_left + PIC_W),
		(raised_top + PIC_H + RAISE_H - 1)
	);
	grcg_off();
}
// -----------

// Boxes
// -----

static const pixel_t SHADOW_DISTANCE = 8;
static const pixel_t BOX_ROUND = 8;

#define box_put(left, top, w, h, padding_y) \
	grcg_round_boxfill( \
		(left), (top), (left + w), (top + (padding_y * 2) + h), BOX_ROUND \
	)

#define box_shadow_put(left, top, w, h, padding_y) \
	box_put((SHADOW_DISTANCE + left), (SHADOW_DISTANCE + top), w, h, padding_y)
// -----

// Player character selection
// --------------------------

static const screen_x_t PLAYCHAR_LEFT[PLAYCHAR_COUNT] = {
	 48, // Reimu
	336, // Marisa
};
static const screen_y_t PLAYCHAR_TOP = 52;

inline screen_x_t playchar_title_left(screen_x_t playchar_left) {
	return (playchar_left + 32);
}
static const vram_y_t PLAYCHAR_TITLE_TOP = 312;
static const pixel_t PLAYCHAR_TITLE_W = (PLAYCHAR_TITLE_LEN * GLYPH_HALF_W);
static const pixel_t PLAYCHAR_TITLE_H = ((PLAYCHAR_TITLE_LINES + 1) * GLYPH_H);
// --------------------------

// Shot type selection
// -------------------

static const screen_x_t SHOTTYPE_PIC_LEFT = 184;
static const vram_y_t SHOTTYPE_PIC_TOP = 44;

static const vram_y_t SHOTTYPE_BOX_TOP = 312;
static const pixel_t SHOTTYPE_BOX_PADDING_Y = 4;

static const screen_x_t SHOTTYPE_CHOOSE_LEFT = 128;
static const pixel_t SHOTTYPE_CHOOSE_PADDING_LEFT = (3 * GLYPH_HALF_W);

static const screen_x_t SHOTTYPE_TITLE_LEFT = 320;

static const pixel_t SHOTTYPE_CHOOSE_W = (
	(SHOTTYPE_CHOOSE_LEN * GLYPH_HALF_W) + SHOTTYPE_CHOOSE_PADDING_LEFT
);
static const pixel_t SHOTTYPE_TITLE_W = (SHOTTYPE_TITLE_LEN * GLYPH_HALF_W);

inline vram_y_t shottype_title_top(shottype_t shottype) {
	return (SHOTTYPE_BOX_TOP + (
		shottype * (GLYPH_H + (SHOTTYPE_BOX_PADDING_Y * 2))
	));
}
// -------------------

// State
// -----

playchar_t playchar_menu_sel;
unsigned char shottype_menu_sel;

bool selectable_with[PLAYCHAR_COUNT][SHOTTYPE_COUNT];
// -----

void near pascal raise_bg_put(playchar_t playchar_lowered)
{
	const upixel_t left = (PLAYCHAR_LEFT[playchar_lowered] - RAISE_W);
	bgimage.write_bg_region(left, (PLAYCHAR_TOP - RAISE_H), PIC_W, RAISE_H);
	bgimage.write_bg_region(left, (PLAYCHAR_TOP - RAISE_H), RAISE_W, PIC_H);
}

#include "th04/op/darken.cpp"

void near pascal pic_darken(playchar_t playchar)
{
	vram_offset_t vo = vram_offset_shift(PLAYCHAR_LEFT[playchar], PLAYCHAR_TOP);
	darken(vo, PIC_W, PIC_H, 1);
}

void near pascal playchar_titles_put(int sel)
{
	screen_x_t left = playchar_title_left(PLAYCHAR_LEFT[sel]);
	vram_y_t top;

	#define put(left, top, col, playchar) \
		graph_putsa_fx( \
			(left + BOX_ROUND), (top + BOX_ROUND), col, PLAYCHAR_TITLE[sel][0] \
		); \
		graph_putsa_fx( \
			(left + BOX_ROUND), \
			((top + BOX_ROUND) + (GLYPH_H * 2)), \
			col, \
			PLAYCHAR_TITLE[sel][1] \
		);

	// Selected character
	top = PLAYCHAR_TITLE_TOP;
	put(left, top, COL_SELECTED, sel);

	// Other character
	sel = (PLAYCHAR_MARISA - sel);
	left = playchar_title_left(PLAYCHAR_LEFT[sel]);
	put(left, top, COL_NOT_SELECTED, sel);

	#undef put
}

void near pascal playchar_title_box_put(int playchar)
{
	screen_x_t left = playchar_title_left(PLAYCHAR_LEFT[playchar]);
	vram_y_t top = PLAYCHAR_TITLE_TOP;

	grcg_setcolor(GC_RMW, COL_SHADOW);
	box_shadow_put(left, top, PLAYCHAR_TITLE_W, PLAYCHAR_TITLE_H, BOX_ROUND);
	grcg_setcolor(GC_RMW, COL_BOX);
	box_put(left, top, PLAYCHAR_TITLE_W, PLAYCHAR_TITLE_H, BOX_ROUND);
	grcg_off();
}

void near pic_put(void)
{
	const playchar_t sel = playchar_menu_sel;
	const playchar_t other = playchar_other(sel);
	const screen_x_t sel_left = (PLAYCHAR_LEFT[sel] - RAISE_W);
	const screen_x_t other_left = PLAYCHAR_LEFT[other];

	cdg_put_noalpha_8(sel_left, (PLAYCHAR_TOP - RAISE_H), (CDG_PIC + sel));
	raise_bg_put(other);
	cdg_put_noalpha_8(other_left, PLAYCHAR_TOP, (CDG_PIC + other));
	pic_darken(other);
	dropshadow_put(sel_left, (PLAYCHAR_TOP - RAISE_H));
	playchar_titles_put(sel);
}

#define shottype_title_top_and_clearflag_for(top, clearflag, shottype) \
	switch(shottype) { \
	case SHOTTYPE_A: \
		top = shottype_title_top(SHOTTYPE_A); \
		clearflag = SCOREDAT_CLEARED_A; \
		break; \
	case SHOTTYPE_B: \
		top = shottype_title_top(SHOTTYPE_B); \
		clearflag = SCOREDAT_CLEARED_B; \
		break; \
	}

void near pascal shottype_titles_put(int sel)
{
	vram_y_t top;
	screen_x_t left;
	int rank = ((resident->stage == STAGE_EXTRA) ? RANK_EXTRA : resident->rank);
	uint8_t clearflag;

	#define put(left, top, clearflag, rank, col) \
		if(cleared_with[playchar_menu_sel][rank] & clearflag) { \
			graph_putsa_fx_func = FX_WEIGHT_NORMAL; \
			graph_putsa_fx( \
				(left - GLYPH_HALF_W), \
				(top + SHOTTYPE_BOX_PADDING_Y), \
				COL_SELECTED, \
				SHOTTYPE_CLEARED \
			); \
			graph_putsa_fx_func = FX_WEIGHT_BOLD; \
		} \
		graph_putsa_fx( \
			(left + GLYPH_HALF_W), \
			(top + SHOTTYPE_BOX_PADDING_Y), \
			col, \
			SHOTTYPE_TITLE[playchar_menu_sel][sel] \
		);

	// Selected shot type
	shottype_title_top_and_clearflag_for(top, clearflag, sel);
	left = SHOTTYPE_TITLE_LEFT;
	put(left, top, clearflag, rank, COL_SELECTED);

	// Other shot type
	sel = (SHOTTYPE_B - sel);
	shottype_title_top_and_clearflag_for(top, clearflag, sel);
	put(left, top, clearflag, rank, COL_NOT_SELECTED);

	#undef put
}

void near shottype_title_box_put(void)
{
	vram_y_t top = SHOTTYPE_BOX_TOP;
	screen_x_t left = SHOTTYPE_TITLE_LEFT;

	#define box_top(top, i) \
		(top + (i * (GLYPH_H + (SHOTTYPE_BOX_PADDING_Y * 2))))

	#define put(func, left, top, w) \
		func(left, top, w, (GLYPH_H - 1), SHOTTYPE_BOX_PADDING_Y)

	grcg_setcolor(GC_RMW, COL_SHADOW);
	put(box_shadow_put, left, box_top(top, 0), (SHOTTYPE_TITLE_W - 1));
	put(box_shadow_put, left, box_top(top, 1), (SHOTTYPE_TITLE_W - 1));
	put(box_shadow_put, SHOTTYPE_CHOOSE_LEFT, top, (SHOTTYPE_CHOOSE_W - 1));

	grcg_setcolor(GC_RMW, COL_BOX);
	put(box_put, left, box_top(top, 0), SHOTTYPE_TITLE_W);
	put(box_put, left, box_top(top, 1), SHOTTYPE_TITLE_W);
	put(box_put, SHOTTYPE_CHOOSE_LEFT, top, (SHOTTYPE_CHOOSE_W - 1));

	grcg_off();

	graph_putsa_fx(
		(SHOTTYPE_CHOOSE_LEFT + SHOTTYPE_CHOOSE_PADDING_LEFT),
		(top + SHOTTYPE_BOX_PADDING_Y),
		COL_NOT_SELECTED,
		SHOTTYPE_CHOOSE
	);

	#undef put
	#undef box_top
}

void near shottype_menu_put_initial(void)
{
	if(playchar_menu_sel == PLAYCHAR_REIMU) {
		cdg_put_noalpha_8(
			SHOTTYPE_PIC_LEFT, SHOTTYPE_PIC_TOP, (CDG_PIC + PLAYCHAR_REIMU)
		);
	} else {
		cdg_put_noalpha_8(
			SHOTTYPE_PIC_LEFT, SHOTTYPE_PIC_TOP, (CDG_PIC + PLAYCHAR_MARISA)
		);
	}
	dropshadow_put(SHOTTYPE_PIC_LEFT, SHOTTYPE_PIC_TOP);
	shottype_title_box_put();
	shottype_titles_put(shottype_menu_sel);
}

void near playchar_menu_put_initial(void)
{
	palette_settone(0);
	GrpSurface_LoadPI(bgimage, &Palettes, "slb1.pi");
	graph_accesspage(1);
	graph_showpage(0);
	bgimage.write(0, 0);
	playchar_title_box_put(PLAYCHAR_REIMU);
	playchar_title_box_put(PLAYCHAR_MARISA);
	pic_put();
	graph_copy_page(0);
	palette_black_in(1);
}

inline bool16 near playchar_menu_leave(bool16 retval) {
	palette_black_out(1);
	bgimage.free();
	return retval;
}

bool16 near playchar_menu(void)
{
	int rank;
	int playchar;
	uint8_t input_prev;
	bool extra_unlocked;

	if(resident->stage == STAGE_EXTRA) {
		for(playchar = PLAYCHAR_REIMU; playchar < PLAYCHAR_COUNT; playchar++) {
			#define set_selectable_with(playchar, shottype, flag) \
				extra_unlocked = false; \
				for(rank = RANK_NORMAL; rank < RANK_EXTRA; rank++) { \
					extra_unlocked |= cleared_with[playchar][rank] & flag; \
				} \
				selectable_with[playchar][shottype] = (extra_unlocked != false);

			set_selectable_with(playchar, SHOTTYPE_A, SCOREDAT_CLEARED_A);
			set_selectable_with(playchar, SHOTTYPE_B, SCOREDAT_CLEARED_B);

			#undef set_selectable_with
		}
	} else {
		selectable_with[PLAYCHAR_REIMU][SHOTTYPE_A] = true;
		selectable_with[PLAYCHAR_REIMU][SHOTTYPE_B] = true;
		selectable_with[PLAYCHAR_MARISA][SHOTTYPE_A] = true;
		selectable_with[PLAYCHAR_MARISA][SHOTTYPE_B] = true;
	}

	playchar_menu_sel = (
		selectable_with[PLAYCHAR_REIMU][SHOTTYPE_A] ||
		selectable_with[PLAYCHAR_REIMU][SHOTTYPE_B]
	)
		? PLAYCHAR_REIMU
		: PLAYCHAR_MARISA;

	while(1) {
		playchar_menu_put_initial();

		// Character
		while(1) {
			input_reset_sense();
			if(input_prev == INPUT_NONE) {
				if((key_det & INPUT_LEFT) || (key_det & INPUT_RIGHT)) {
					snd_se_play_force(1);
					playchar_menu_sel = playchar_other(playchar_menu_sel);
					if(
						!selectable_with[playchar_menu_sel][SHOTTYPE_A] &&
						!selectable_with[playchar_menu_sel][SHOTTYPE_B]
					) {
						playchar_menu_sel = playchar_other(playchar_menu_sel);
					}
					graph_accesspage(1);
					pic_put();
					sync_pages_and_delay();
				}
				if((key_det & INPUT_OK) || (key_det & INPUT_SHOT)) {
					snd_se_play_force(11);
					shottype_menu_sel = (
						selectable_with[playchar_menu_sel][SHOTTYPE_A]
					)
						? SHOTTYPE_A
						: SHOTTYPE_B;

					graph_accesspage(1);
					palette_settone(200);
					bgimage.write(0, 0);
					shottype_menu_put_initial();
					graph_copy_page(0);
					palette_white_in(1);
					break;
				}
				if(key_det & INPUT_CANCEL) {
					return playchar_menu_leave(true);
				}
				input_prev = key_det;
			} else {
				if(key_det == INPUT_NONE) {
					input_prev = INPUT_NONE;
				}
			}
			frame_delay(1);
		}

		// Shot type
		while(1) {
			input_reset_sense();
			if(input_prev == INPUT_NONE) {
				if((key_det & INPUT_UP) || (key_det & INPUT_DOWN)) {
					shottype_menu_sel = (1 - shottype_menu_sel);
					if(!selectable_with[playchar_menu_sel][shottype_menu_sel]) {
						shottype_menu_sel = (1 - shottype_menu_sel);
					}
					graph_accesspage(1);
					shottype_titles_put(shottype_menu_sel);
					sync_pages_and_delay();
					snd_se_play_force(1);
				}
				if((key_det & INPUT_OK) || (key_det & INPUT_SHOT)) {
					snd_se_play_force(11);
					resident->shottype = shottype_menu_sel;
					resident->playchar_ascii = (playchar_menu_sel + '0');
					return playchar_menu_leave(false);
				}
				if(key_det & INPUT_CANCEL) {
					bgimage.free();
					break;
				}
				input_prev = key_det;
			} else {
				if(key_det == INPUT_NONE) {
					input_prev = INPUT_NONE;
				}
			}
			frame_delay(1);
		}
	}
}

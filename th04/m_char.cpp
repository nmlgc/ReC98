/* ReC98
 * -----
 * TH04 player character selection menu
 */

#pragma option -zCop_01_TEXT

extern "C" {
#include <stddef.h>
#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "th01/ranks.h"
#include "th02/hardware/frmdelay.h"
#include "th03/formats/pi.h"
#include "th04/common.h"
#include "th04/chars.h"
#include "th04/formats/scoredat.h"
#include "th04/resident.hpp"
#include "th04/hardware/input.h"
#include "th04/hardware/grppsafx.h"
#include "th04/formats/cdg.h"
#include "th04/snd/snd.h"
#include "th04/sprites/op_cdg.h"
#include "th04/op/op.h"

#include "th04/strings/m_char.c"

static const pixel_t PIC_W = 256;
static const pixel_t PIC_H = 244;

static const int COL_SELECTED = 15;
static const int COL_NOT_SELECTED = 3;
static const int COL_BOX = 2;
static const int COL_SHADOW = 1;

// Raised edge
// -----------

static const pixel_t RAISE_W = 8;
static const pixel_t RAISE_H = 8;

static const vram_byte_amount_t RAISE_BG_SIZE = (
	(((PIC_W * RAISE_H) + (RAISE_W * PIC_H)) / BYTE_DOTS) * PLANE_COUNT
);

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

static const screen_x_t REIMU_LEFT = 48;
static const vram_y_t REIMU_TOP = 52;

static const screen_x_t MARISA_LEFT = 336;
static const vram_y_t MARISA_TOP = 52;

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

unsigned char playchar_menu_sel;
unsigned char shottype_menu_sel;

// Stores the top and left edges of the background that would be covered by
// raising the pic of the given character. The top edge is stored first,
// followed by the left one.
// Actually a Planar<dots8_t>* (storing the 8 dots for all 4 planes before
// moving to the next byte), but used like a dots8_t* everywhere.
dots8_t *raise_bg[PLAYCHAR_COUNT];

bool selectable_with[PLAYCHAR_COUNT][SHOTTYPE_COUNT];
// -----

#define raise_bg_snap_and_advance(p, plane, vo_reimu, vo_marisa) \
	VRAM_SNAP( raise_bg[PLAYCHAR_REIMU][p], plane, vo_reimu,  8); \
	VRAM_SNAP(raise_bg[PLAYCHAR_MARISA][p], plane, vo_marisa, 8); \
	p++;

#define raise_bg_snap_and_advance_planar(p, vo_reimu, vo_marisa) \
	raise_bg_snap_and_advance(p, B, vo_reimu, vo_marisa); \
	raise_bg_snap_and_advance(p, R, vo_reimu, vo_marisa); \
	raise_bg_snap_and_advance(p, G, vo_reimu, vo_marisa); \
	raise_bg_snap_and_advance(p, E, vo_reimu, vo_marisa); \

#define raise_bg_put_and_advance_planar(vo, p) \
	VRAM_PUT(B, vo, *(p++), 8); \
	VRAM_PUT(R, vo, *(p++), 8); \
	VRAM_PUT(G, vo, *(p++), 8); \
	VRAM_PUT(E, vo, *(p++), 8);

void near raise_bg_allocate_and_snap(void)
{
	size_t raise_bg_p;
	vram_offset_t vo_reimu_row;
	pixel_t y;
	vram_byte_amount_t x;
	vram_offset_t vo_reimu;
	vram_offset_t vo_marisa_row;
	vram_offset_t vo_marisa;

	raise_bg[PLAYCHAR_REIMU] = HMem<dots8_t>::allocbyte(RAISE_BG_SIZE);
	raise_bg[PLAYCHAR_MARISA] = HMem<dots8_t>::allocbyte(RAISE_BG_SIZE);

	vo_reimu_row  = raise(vram_offset_shift(REIMU_LEFT,  REIMU_TOP));
	vo_marisa_row = raise(vram_offset_shift(MARISA_LEFT, MARISA_TOP));

	// Top edge
	y = 0;
	raise_bg_p = 0;
	while(y < RAISE_H) {
		x = 0;
		vo_reimu = vo_reimu_row;
		vo_marisa = vo_marisa_row;
		while(x < (PIC_W / BYTE_DOTS)) {
			raise_bg_snap_and_advance_planar(raise_bg_p, vo_reimu, vo_marisa);
			x++;
			vo_reimu++;
			vo_marisa++;
		}
		y++;
		vo_reimu_row  += ROW_SIZE;
		vo_marisa_row += ROW_SIZE;
	}

	// Left edge
	y = 0;
	while(y < PIC_H) {
		raise_bg_snap_and_advance_planar(
			raise_bg_p, vo_reimu_row, vo_marisa_row
		);
		y++;
		vo_reimu_row  += ROW_SIZE;
		vo_marisa_row += ROW_SIZE;
	}
}

void near pascal raise_bg_put(playchars_t playchar_lowered)
{
	vram_byte_amount_t x;
	pixel_t y;
	vram_offset_t vo_row;
	dots8_t *playchar_bg;
	vram_offset_t vo;

	if(playchar_lowered == PLAYCHAR_REIMU) {
		vo_row = raise(vram_offset_shift(REIMU_LEFT, REIMU_TOP));
		playchar_bg = raise_bg[PLAYCHAR_REIMU];
	} else {
		vo_row = raise(vram_offset_shift(MARISA_LEFT, MARISA_TOP));
		playchar_bg = raise_bg[PLAYCHAR_MARISA];
	}

	// Top edge
	for(y = 0; y < RAISE_H; y++, vo_row += ROW_SIZE) {
		x = 0;
		vo = vo_row;
		while(x < (PIC_W / BYTE_DOTS)) {
			raise_bg_put_and_advance_planar(vo, playchar_bg);
			x++;
			vo++;
		}
	}

	// Left edge
	for(y = 0; y < PIC_H; y++, vo_row += ROW_SIZE) {
		raise_bg_put_and_advance_planar(vo_row, playchar_bg);
	}
}

void near raise_bg_free(void)
{
	HMem<dots8_t>::free(raise_bg[PLAYCHAR_REIMU]);
	HMem<dots8_t>::free(raise_bg[PLAYCHAR_MARISA]);
}

#include "th04/op/darken.cpp"

void near pascal pic_darken(playchars_t playchar)
{
	vram_offset_t vo;
	vram_byte_amount_t x;
	pixel_t y;

	if(playchar == PLAYCHAR_REIMU) {
		vo = vram_offset_shift(REIMU_LEFT, REIMU_TOP);
	} else {
		vo = vram_offset_shift(MARISA_LEFT, MARISA_TOP);
	}
	darken(vo, x, y, PIC_W, PIC_H, 1);
}

#define playchar_title_left_for(left, playchar) \
	switch(playchar) { \
	case PLAYCHAR_REIMU:  left = playchar_title_left(REIMU_LEFT);  break; \
	case PLAYCHAR_MARISA: left = playchar_title_left(MARISA_LEFT); break; \
	}

void near pascal playchar_title_put(int playchar_sel)
{
	int playchar = playchar_sel;
	screen_x_t left;
	vram_y_t top;

	#define put(left, top, col, playchar) \
		graph_putsa_fx( \
			(left + BOX_ROUND), \
			(top + BOX_ROUND), \
			col, \
			PLAYCHAR_TITLE[playchar][0] \
		); \
		graph_putsa_fx( \
			(left + BOX_ROUND), \
			((top + BOX_ROUND) + (GLYPH_H * 2)), \
			col, \
			PLAYCHAR_TITLE[playchar][1] \
		);

	// Selected character
	playchar_title_left_for(left, playchar);
	top = PLAYCHAR_TITLE_TOP;
	put(left, top, COL_SELECTED, playchar);

	// Other character
	playchar = (PLAYCHAR_MARISA - playchar);
	playchar_title_left_for(left, playchar);
	put(left, top, COL_NOT_SELECTED, playchar);

	#undef put
}

void near pascal playchar_title_box_put(int playchar)
{
	screen_x_t left;
	vram_y_t top;

	playchar_title_left_for(left, playchar);
	top = PLAYCHAR_TITLE_TOP;

	grcg_setcolor(GC_RMW, COL_SHADOW);
	box_shadow_put(left, top, PLAYCHAR_TITLE_W, PLAYCHAR_TITLE_H, BOX_ROUND);
	grcg_setcolor(GC_RMW, COL_BOX);
	box_put(left, top, PLAYCHAR_TITLE_W, PLAYCHAR_TITLE_H, BOX_ROUND);
	grcg_off();
}

inline void pic_put_for(
	playchars_t playchar_sel,
	screen_x_t sel_left,
	vram_y_t sel_top,
	screen_x_t other_left,
	vram_y_t other_top
) {
	cdg_put_noalpha_8(
		(sel_left - RAISE_W), (sel_top - RAISE_H), (CDG_PIC + playchar_sel)
	);
	raise_bg_put(playchar_other(playchar_sel));
	cdg_put_noalpha_8(
		other_left, other_top, (CDG_PIC + playchar_other(playchar_sel))
	);
	pic_darken(playchar_other(playchar_sel));
	dropshadow_put((sel_left - RAISE_W), (sel_top - RAISE_H));
	playchar_title_put(playchar_sel);
}

void near pic_put(void)
{
	if(playchar_menu_sel == PLAYCHAR_REIMU) {
		pic_put_for(
			PLAYCHAR_REIMU, REIMU_LEFT, REIMU_TOP, MARISA_LEFT, MARISA_TOP
		);
	} else {
		pic_put_for(
			PLAYCHAR_MARISA, MARISA_LEFT, MARISA_TOP, REIMU_LEFT, REIMU_TOP
		);
	}
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

void near pascal shottype_title_put(int shottype_sel)
{
	vram_y_t top;
	int shottype = shottype_sel;
	screen_x_t left;
	int rank;
	uint8_t clearflag;

	rank = (resident->stage == STAGE_EXTRA)
		? static_cast<int>(RANK_EXTRA)
		: resident->rank;

	#define put(top, clearflag, rank, col) \
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
			SHOTTYPE_TITLE[playchar_menu_sel][shottype] \
		);

	// Selected shot type
	shottype_title_top_and_clearflag_for(top, clearflag, shottype);
	left = SHOTTYPE_TITLE_LEFT;
	put(top, clearflag, rank, COL_SELECTED);

	// Other shot type
	shottype = (SHOTTYPE_B - shottype);
	shottype_title_top_and_clearflag_for(top, clearflag, shottype);
	put(top, clearflag, rank, COL_NOT_SELECTED);

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
	shottype_title_put(shottype_menu_sel);
}

void near playchar_menu_put_initial(void)
{
	palette_black();
	pi_load(0, "slb1.pi");
	graph_accesspage(1);
	graph_showpage(0);
	pi_palette_apply(0);
	pi_put_8(0, 0, 0);
	raise_bg_allocate_and_snap();
	playchar_title_box_put(PLAYCHAR_REIMU);
	playchar_title_box_put(PLAYCHAR_MARISA);
	pic_put();
	graph_copy_page(0);
	palette_black_in(1);
}

inline bool16 near playchar_menu_leave(bool16 retval) {
	palette_black_out(1);
	raise_bg_free();
	pi_free(0);
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
				selectable_with[playchar][shottype] = (extra_unlocked) != false;

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
					playchar_menu_sel = (1 - playchar_menu_sel);
					if(
						!selectable_with[playchar_menu_sel][SHOTTYPE_A] &&
						!selectable_with[playchar_menu_sel][SHOTTYPE_B]
					) {
						playchar_menu_sel = (1 - playchar_menu_sel);
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
					palette_white();
					pi_put_8(0, 0, 0);
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
					shottype_title_put(shottype_menu_sel);
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
					raise_bg_free();
					pi_free(0);
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

}

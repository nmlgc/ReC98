/* ReC98
 * -----
 * TH05 player character selection menu
 */

#pragma codeseg op_01_TEXT

extern "C" {
#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "th01/ranks.h"
#include "th02/hardware/frmdelay.h"
#include "th04/formats/cdg.h"
#include "th04/bgimage.h"
#include "th04/score.h"
#include "th04/common.h"
#include "th05/chars.h"
#include "th05/resident.hpp"
#include "th05/op/op.h"
#include "th05/sprites/op_cdg.h"
#include "th05/snd/snd.h"
#include "th05/hardware/input.h"
#include "th05/formats/pi.h"

#pragma option -a2

static const pixel_t PIC_W = 224;
static const pixel_t PIC_H = 160;
static const pixel_t CLEARED_W = 64;
static const pixel_t CLEARED_H = 16;

static const pixel_t RAISE_W = 8;
static const pixel_t RAISE_H = 8;

static const screen_x_t REIMU_LEFT = 16;
static const vram_y_t REIMU_TOP = 48;

static const screen_x_t MARISA_LEFT = 272;
static const vram_y_t MARISA_TOP = 48;

static const screen_x_t MIMA_LEFT = 160;
static const vram_y_t MIMA_TOP = 224;

static const screen_x_t YUUKA_LEFT = 400;
static const vram_y_t YUUKA_TOP = 224;

unsigned char playchar_menu_sel;
static uint8_t unused_1;
unsigned char playchar_menu_rank;
static uint8_t unused_0[4];
bool extra_playable_with[PLAYCHAR_COUNT];
bool selectable_with[PLAYCHAR_COUNT];

#include "th04/op/darken.cpp"

void pascal near pic_darken(unsigned char playchar)
{
	vram_offset_t vram_offset;
	vram_byte_amount_t x;
	pixel_t y;

	switch(playchar) {
	case PLAYCHAR_REIMU:
		vram_offset = vram_offset_shift(REIMU_LEFT, REIMU_TOP);
		break;
	case PLAYCHAR_MARISA:
		vram_offset = vram_offset_shift(MARISA_LEFT, MARISA_TOP);
		break;
	case PLAYCHAR_MIMA:
		vram_offset = vram_offset_shift(MIMA_LEFT, MIMA_TOP);
		break;
	case PLAYCHAR_YUUKA:
		vram_offset = vram_offset_shift(YUUKA_LEFT, YUUKA_TOP);
		break;
	}
	darken(vram_offset, x, y, PIC_W, PIC_H, 1);
}

void pascal near pic_put(bool16 darkened)
{
	screen_x_t pic_left;
	vram_y_t pic_top;
	screen_x_t cleared_left;
	vram_y_t cleared_top;

	#define set_coords_for(playchar) \
		pic_left = playchar##_LEFT; \
		pic_top = playchar##_TOP; \
		cleared_left = (playchar##_LEFT + (PIC_W - CLEARED_W)); \
		cleared_top = (playchar##_TOP + (PIC_H - CLEARED_H));

	switch(playchar_menu_sel) {
	case PLAYCHAR_REIMU: 	set_coords_for(REIMU); 	break;
	case PLAYCHAR_MARISA:	set_coords_for(MARISA);	break;
	case PLAYCHAR_MIMA:  	set_coords_for(MIMA);  	break;
	case PLAYCHAR_YUUKA: 	set_coords_for(YUUKA); 	break;
	}

	#define pic_raised_left (pic_left - RAISE_W)
	#define pic_raised_top  (pic_top  - RAISE_H)

	if(!darkened) {
		// Pic
		if(selectable_with[playchar_menu_sel]) {
			cdg_put_noalpha_8(
				pic_raised_left, pic_raised_top, (CDG_PIC + playchar_menu_sel)
			);
		} else {
			cdg_put_noalpha_8(
				pic_raised_left, pic_raised_top, CDG_PIC_NOT_CLEARED
			);
		}

		// Drop shadow
		grcg_setcolor(GC_RMW, 1);
		grcg_boxfill_8(
			(pic_raised_left + PIC_W),
			pic_top,
			(pic_left + PIC_W - 1),
			(pic_raised_top + PIC_H - 1)
		);
		grcg_boxfill_8(
			pic_left,
			(pic_raised_top + PIC_H),
			(pic_left + PIC_W - 1),
			(pic_top + PIC_H - 1)
		);
		grcg_off();

		// "Cleared!!" sprite
		if(cleared_with[playchar_menu_sel][playchar_menu_rank]) {
			cdg_put_8(
				(cleared_left - RAISE_W), (cleared_top - RAISE_H), CDG_CLEARED
			);
		}
	} else {
		// Raised area of the highlighted pic
		bgimage_put_rect(pic_raised_left, pic_raised_top, PIC_W, RAISE_H);
		bgimage_put_rect(pic_raised_left, pic_top, RAISE_W, PIC_H);

		// Pic
		if(selectable_with[playchar_menu_sel]) {
			cdg_put_noalpha_8(pic_left, pic_top, (CDG_PIC + playchar_menu_sel));
		} else {
			cdg_put_noalpha_8(pic_left, pic_top, CDG_PIC_NOT_CLEARED);
		}

		// "Cleared!!" sprite
		if(cleared_with[playchar_menu_sel][playchar_menu_rank]) {
			cdg_put_8(cleared_left, cleared_top, CDG_CLEARED);
		}

		pic_darken(playchar_menu_sel);
	}

	#undef set_coords_for
	#undef pic_raised_top
	#undef pic_raised_left
}

void near playchar_menu_put_initial(void)
{
	int selected = playchar_menu_sel;

	palette_settone(0);
	graph_accesspage(1);
	pi_load_put_8_free(0, "slb1.pi");
	graph_copy_page(0);
	bgimage_snap();

	graph_accesspage(1);
	graph_showpage(0);

	int i = PLAYCHAR_REIMU;
	playchar_menu_sel = PLAYCHAR_REIMU;
	while(i < PLAYCHAR_COUNT) {
		pic_put(playchar_menu_sel != selected ? true : false);
		i++;
		playchar_menu_sel++;
	}
	playchar_menu_sel = selected;
	graph_copy_page(0);
	palette_black_in(1);
}

inline void near on_directional_input(uint8_t sel_xorval) {
	snd_se_play_force(1);

	graph_accesspage(1);
	pic_put(true);
	playchar_menu_sel ^= sel_xorval;
	pic_put(false);
	sync_pages_and_delay();
}

bool16 near playchar_menu(void)
{
	uint8_t input_prev;
	int i;

	for(i = PLAYCHAR_REIMU; i < PLAYCHAR_COUNT; i++) {
		selectable_with[i] = extra_playable_with[i];
	}

	if(resident->stage == STAGE_EXTRA) {
		playchar_menu_rank = RANK_EXTRA;
		playchar_menu_sel = 0xFF;
		for(i = PLAYCHAR_REIMU; i < PLAYCHAR_COUNT; i++) {
			if(playchar_menu_sel == 0xFF) {
				if(selectable_with[i]) {
					playchar_menu_sel = i;
				}
			}
		}
	} else {
		for(i = PLAYCHAR_REIMU; i < PLAYCHAR_COUNT; i++) {
			selectable_with[i] = true;
		}
		playchar_menu_rank = resident->rank;
		playchar_menu_sel = PLAYCHAR_REIMU;
	}

	playchar_menu_put_initial();

	while(1) {
		input_reset_sense_held();
		if(input_prev == INPUT_NONE) {
			if((key_det & INPUT_LEFT) || (key_det & INPUT_RIGHT)) {
				on_directional_input(1); // 0<->1, 2<->3
			}
			if((key_det & INPUT_UP) || (key_det & INPUT_DOWN)) {
				on_directional_input(2); // 0<->2, 1<->3
			}
			if((key_det & INPUT_OK) || (key_det & INPUT_SHOT)) {
				if(selectable_with[playchar_menu_sel]) {
					snd_se_play_force(11);
					resident->playchar = playchar_menu_sel;
					palette_black_out(1);
					bgimage_free();
					return false;
				}
			}
			if(key_det & INPUT_CANCEL) {
				palette_black_out(1);
				bgimage_free();
				return true;
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

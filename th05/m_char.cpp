/* ReC98
 * -----
 * TH05 player character selection menu
 */

#pragma option -zPop_01

#include "libs/master.lib/pc98_gfx.hpp"
#include "game/bgimage.hpp"
#include "th01/hardware/grcg.hpp"
#include "th02/hardware/frmdelay.h"
#include "th04/formats/cdg.h"
#include "th04/op/clear.hpp"
#include "th04/op/impl.hpp"
#include "th04/sprites/op_cdg.hpp"
#include "th05/resident.hpp"
#include "th05/op/op.hpp"
#include "th05/hardware/input.h"

#pragma option -a2

static const pixel_t PIC_W = 224;
static const pixel_t PIC_H = 160;
static const pixel_t CLEARED_W = 64;
static const pixel_t CLEARED_H = 16;

static const pixel_t RAISE_W = 8;
static const pixel_t RAISE_H = 8;

static const screen_point_t PLAYCHAR_TOPLEFT[PLAYCHAR_COUNT] = {
	{  16,  48 }, // Reimu
	{ 272,  48 }, // Marisa
	{ 160, 224 }, // Mima
	{ 400, 224 }, // Yuuka
};
unsigned char playchar_menu_sel;
unsigned char playchar_menu_rank;
bool extra_playable_with[PLAYCHAR_COUNT];
bool selectable_with[PLAYCHAR_COUNT];

#include "th04/op/darken.cpp"

void pascal near pic_darken(unsigned char playchar)
{
	const screen_point_t topleft = PLAYCHAR_TOPLEFT[playchar];
	vram_offset_t vram_offset = vram_offset_shift(topleft.x, topleft.y);
	darken(vram_offset, PIC_W, PIC_H, 1);
}

void pascal near pic_put(int sel, bool16 darkened)
{
	const screen_point_t pic_topleft = PLAYCHAR_TOPLEFT[sel];
	const screen_x_t cleared_left = (pic_topleft.x + PIC_W - CLEARED_W);
	const screen_y_t cleared_top  = (pic_topleft.y + PIC_H - CLEARED_H);
	const screen_x_t pic_raised_left = (pic_topleft.x - RAISE_W);
	const screen_y_t pic_raised_top  = (pic_topleft.y - RAISE_H);
	const int pic_slot = (selectable_with[sel]
		? (CDG_PIC + sel)
		: CDG_PIC_NOT_CLEARED
	);

	if(!darkened) {
		// Pic
		cdg_put_noalpha_8(pic_raised_left, pic_raised_top, pic_slot);

		// Drop shadow
		grcg_setcolor(GC_RMW, 1);
		grcg_boxfill_8(
			(pic_raised_left + PIC_W),
			pic_topleft.y,
			(pic_topleft.x + PIC_W - 1),
			(pic_raised_top + PIC_H - 1)
		);
		grcg_boxfill_8(
			pic_topleft.x,
			(pic_raised_top + PIC_H),
			(pic_topleft.x + PIC_W - 1),
			(pic_topleft.y + PIC_H - 1)
		);
		grcg_off();

		// "Cleared!!" sprite
		if(cleared_with[sel][playchar_menu_rank]) {
			cdg_put_8(
				(cleared_left - RAISE_W), (cleared_top - RAISE_H), CDG_CLEARED
			);
		}
	} else {
		// Raised area of the highlighted pic
		bgimage.write_bg_region(
			pic_raised_left, pic_raised_top, PIC_W, RAISE_H
		);
		bgimage.write_bg_region(pic_raised_left, pic_topleft.y, RAISE_W, PIC_H);

		// Pic
		cdg_put_noalpha_8(pic_topleft.x, pic_topleft.y, pic_slot);

		// "Cleared!!" sprite
		if(cleared_with[sel][playchar_menu_rank]) {
			cdg_put_8(cleared_left, cleared_top, CDG_CLEARED);
		}

		pic_darken(sel);
	}
}

void near playchar_menu_put_initial(void)
{
	palette_settone(0);
	graph_accesspage(1);
	graph_showpage(0);
	GrpSurface_LoadPI(bgimage, &Palettes, "slb1.pi");
	bgimage.write(0, 0);

	for(int i = PLAYCHAR_REIMU; i < PLAYCHAR_COUNT; i++) {
		pic_put(i, (i != playchar_menu_sel));
	}

	graph_copy_page(0);
	palette_black_in(1);
}

inline void near on_directional_input(uint8_t sel_xorval) {
	snd_se_play_force(1);

	graph_accesspage(1);
	pic_put(playchar_menu_sel, true);
	playchar_menu_sel ^= sel_xorval;
	pic_put(playchar_menu_sel, false);
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
					bgimage.free();
					return false;
				}
			}
			if(key_det & INPUT_CANCEL) {
				palette_black_out(1);
				bgimage.free();
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

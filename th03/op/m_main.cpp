// ZUN bloat: Only contains animations, the rest is in `op_01.cpp`.

#include "th03/op/m_main.hpp"
#include "th02/hardware/frmdelay.h"
#include "th02/formats/pi.h"
#include "th03/snd/snd.h"
#include "th03/op/m_select.hpp"
#include "th03/shiftjis/fns.hpp"
#include "libs/master.lib/master.hpp"
#include "game/bgimage.hpp"
#include "platform/x86real/pc98/page.hpp"
#include "platform/x86real/flags.hpp"
#include "platform/vblank.hpp"
#include "planar.h"

inline void title_load_opwin_and_bgm(void) {
	super_entry_bfnt("opwin.bft");
	snd_kaja_func(KAJA_SONG_STOP, 0);
	snd_load(BGM_MENU_MAIN_FN, SND_LOAD_SONG);
}

void near op_animate(void)
{
	enum {
		COL_SHADOW = 11, // Shadow behind the 東方夢時空 kanji. Faded to #888.
		COL_BG = 15, // Background
		SHIFT_DELTA = 2,
	};

	int i;
	int brightness = 0;
	page_t page = 0;

	title_load_opwin_and_bgm();
	pi_load(0, "TL01.PI");

	// TODO: Investigate whether this is a landmine once MAINL.EXE has reached
	// 100% RE and we know all possible VRAM and palette states at this point.
	palette_settone(0);

	graph_accesspage(1);
	pi_put_8(0, 0, 0);

	graph_accesspage(0);
	pi_palette_apply(0);
	pi_put_8(0, 0, 0);

	// Pre-shift only VRAM page 0 by 2 pixels. With this initial displacement,
	// each iteration of the page-flipped loop below only has to shift the
	// single respectively next page by a consistent 4 pixels to end up with an
	// animation at a smooth 2 pixels per frame.
	egc_shift_left_all(SHIFT_DELTA);

	Palettes[COL_BG].set(0x00, 0x00, 0x00);
	Palettes[COL_SHADOW].set(0x00, 0x00, 0x00);
	palette_show();
	pi_free(0);

	Palette8 bgimage_palette;
	GrpSurface_LoadPI(bgimage, &bgimage_palette, MENU_MAIN_BG_FN);
	graph_showpage(1);

	// Fade in and move. These values do actually represent the X position of
	// the 東方夢時空 kanji in TL01.PI (160) and TL02.PI, respectively. That 17
	// is still awkward though.
	for(i = 160; i > 17; i -= SHIFT_DELTA) {
		frame_delay(1);

		Palettes[COL_BG].c.r = brightness;
		Palettes[COL_BG].c.g = brightness;
		Palettes[COL_BG].c.b = brightness;
		if(brightness <= 0x80) {
			Palettes[COL_SHADOW].c.r = brightness;
			Palettes[COL_SHADOW].c.g = brightness;
			Palettes[COL_SHADOW].c.b = brightness;
		}
		palette_show();
		if(brightness <= 100) {
			palette_settone(brightness);
		}
		brightness += 2;
		graph_showpage(page);
		page = (1 - page);
		graph_accesspage(page);
		egc_shift_left_all(SHIFT_DELTA * 2);
	}

	// Complete fade-in
	while(brightness < 0xFF) {
		Palettes[COL_BG].c.r = brightness;
		Palettes[COL_BG].c.g = brightness;
		Palettes[COL_BG].c.b = brightness;
		palette_show();
		brightness += 2;
		frame_delay(1);
	}

	vsync_Count1 = 0;
	select_cdg_load_part3_of_4();
	while(vsync_Count1 < 16) {
	}

	// Flash
	for(i = 0; i < 8; i++) {
		palette_settone(200);
		frame_delay(1);
		palette_settone(100);
		frame_delay(1);
	}

	palette_settone(200);
	snd_kaja_func(KAJA_SONG_PLAY, 0);
	graph_showpage(0);
	graph_accesspage(0);
	Palettes = bgimage_palette;
	bgimage.write(0, 0);
	frame_delay(1);

	palette_settone(100);
	frame_delay(1);

	// Flash again
	for(i = 0; i < 8; i++) {
		palette_settone(200);
		frame_delay(1);
		palette_settone(100);
		frame_delay(1);
	}

	select_cdg_load_part1_of_4();
}

void near op_fadein_animate(void)
{
	PaletteTone = 0;
	vblank_run(palette_show);

	title_load_opwin_and_bgm();

	GrpSurface_LoadPI(bgimage, &Palettes, MENU_MAIN_BG_FN);
	graph_showpage(0);

	// This function is called either on startup (where we haven't loaded any
	// of these), or when leaving the character selection menu or the Music
	// Room (both of which free all .CDG sprites).
	select_cdg_load_part3_of_4();

	graph_accesspage(0);
	bgimage.write(0, 0);

	select_cdg_load_part1_of_4();

	snd_kaja_func(KAJA_SONG_PLAY, 0);
	frame_delay(1);
	for(int i = 4; i <= 100; i += 4) {
		palette_settone(i);
		frame_delay(1);
	}
}

void pascal near box_animate(pixel_t w_cur, pixel_t w_target)
{
	pixel_t step;
	pixel_t put_offset;

	if(w_target == w_cur) {
		return;
	} else if(w_target > w_cur) {
		step = +OPWIN_STEP_W;
		put_offset = 0;
	} else {
		step = -OPWIN_STEP_W;
		put_offset = -OPWIN_STEP_W;
	}
	screen_x_t right_left = (BOX_LEFT + w_cur - OPWIN_STEP_W);
	screen_x_t right_target = (BOX_LEFT + w_target - OPWIN_STEP_W + put_offset);

	while(right_left != right_target) {
		bgimage.write_bg_region(right_left, BOX_TOP, (OPWIN_STEP_W * 2), BOX_H);
		super_put((right_left + put_offset), BOX_TOP, OPWIN_RIGHT);
		frame_delay(1);
		right_left += step;
	}
}

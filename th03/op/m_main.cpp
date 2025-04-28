#include "th03/op/m_main.hpp"
#include "th02/hardware/frmdelay.h"
#include "th02/formats/pi.h"
#include "th03/snd/snd.h"
#include "th03/op/m_select.hpp"
#include "platform/x86real/pc98/page.hpp"
#include "platform/x86real/flags.hpp"
#include "planar.h"

#undef MENU_MAIN_BG_FN
extern const char MENU_MAIN_BG_FN[];

inline void title_load_opwin_and_bgm(void) {
	#undef BGM_MENU_MAIN_FN
	extern const char OPWIN_BFT[];
	extern const char BGM_MENU_MAIN_FN[];
	super_entry_bfnt(OPWIN_BFT);
	snd_kaja_func(KAJA_SONG_STOP, 0);
	snd_load(BGM_MENU_MAIN_FN, SND_LOAD_SONG);
}

void near op_fadein_animate(void)
{
	title_load_opwin_and_bgm();

	// ZUN landmine: Will cause tearing if we return from the Music Room, which
	// leaves with VRAM cleared to color 0 but still keeps its purple color in
	// palette slot 0.
	palette_settone(0);

	pi_load(0, MENU_MAIN_BG_FN);
	graph_showpage(0);

	// This function is called either on startup (where we haven't loaded any
	// of these), or when leaving the character selection menu or the Music
	// Room (both of which free all .CDG sprites).
	select_cdg_load_part3_of_4();

	graph_accesspage(1);
	pi_put_8(0, 0, 0);

	graph_accesspage(0);
	pi_palette_apply(0);
	pi_put_8(0, 0, 0);
	graph_accesspage(0); // ZUN bloat: Redundant
	pi_free(0);

	select_cdg_load_part1_of_4();

	snd_kaja_func(KAJA_SONG_PLAY, 0);
	for(int i = 0; i <= 100; i += 4) {
		// At least this one doesn't constitute an additional landmine because
		// the `palette_settone(0)` call on the first iteration matches the
		// call at the beginning of the function.
		palette_settone(i);
		frame_delay(1);
	}
}

void near box_main_to_submenu_animate(void)
{
	for(
		screen_x_t right_left = (BOX_MAIN_RIGHT - OPWIN_STEP_W);
		right_left < (BOX_SUBMENU_RIGHT - OPWIN_STEP_W);
		right_left += OPWIN_STEP_W
	) {
		box_column16_unput(right_left);
		super_put(right_left, BOX_TOP, OPWIN_RIGHT);
		frame_delay(1);
	}
}

void near box_submenu_to_main_animate(void)
{
	for(
		screen_x_t right_left = (BOX_SUBMENU_RIGHT - OPWIN_W);
		right_left >= (BOX_MAIN_RIGHT - OPWIN_W);
		right_left -= OPWIN_STEP_W
	) {
		box_column16_unput(right_left + OPWIN_STEP_W);
		super_put(right_left, BOX_TOP, OPWIN_RIGHT);
		frame_delay(1);
	}
}

void pascal near box_column16_unput(uscreen_x_t left)
{
	register dots16_t px_b;
	register dots16_t px_g;
	register dots16_t px_r;
	register dots16_t px_e;

	_AX = (left / BYTE_DOTS);
	_DI = vram_offset_shift(0, (BOX_BOTTOM - 1));
	_DI += _AX;
	_ES = vram_segment(B, 0, BOX_TOP);
	do {
		page_access(1);
		/*                              */	px_b = _peek_(_ES, _DI);
		_ES = vram_segment(R, 0, BOX_TOP);	px_r = _peek_(_ES, _DI);
		_ES = vram_segment(G, 0, BOX_TOP);	px_g = _peek_(_ES, _DI);
		_ES = vram_segment(E, 0, BOX_TOP);	px_e = _peek_(_ES, _DI);
		page_access(_AL ^= _AL);
		/*                              */	_poke_(_ES, _DI, px_e);
		_ES = vram_segment(G, 0, BOX_TOP);	_poke_(_ES, _DI, px_g);
		_ES = vram_segment(R, 0, BOX_TOP);	_poke_(_ES, _DI, px_r);
		_ES = vram_segment(B, 0, BOX_TOP);	_poke_(_ES, _DI, px_b);
		_DI -= ROW_SIZE;
	} while(!FLAGS_CARRY);
}

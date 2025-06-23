#include <dos.h>
#include "platform/vblank.hpp"
#include "shiftjis.hpp"
#include "libs/master.lib/master.hpp"
#include "libs/master.lib/pc98_gfx.hpp"
#include "th02/common.h"
#include "th02/hardware/frmdelay.h"
#include "th02/hardware/input.hpp"
#include "th02/core/globals.hpp"
#include "th02/formats/scoredat/scoredat.hpp"
#include "th02/gaiji/gaiji.h"
#include "th02/gaiji/score_p.hpp"
#include "th02/gaiji/str.hpp"
#include "th02/op/op.h"
#include "th02/shiftjis/hiscore.hpp"

#include "th02/score.c"

static const unsigned char gbcRANKS[4][8] = {
	g_chr_7(gb, _,E,A,S,Y,_,_), '\0',
	g_chr_7(gb, N,O,R,M,A,L,_), '\0',
	g_chr_7(gb, _,H,A,R,D,_,_), '\0',
	g_chr_7(gb, L,U,N,A,T,I,C), '\0',
};

const shiftjis_t *SHOTTYPES[SHOTTYPE_COUNT] = HISCORE_SHOTTYPES;
int logo_step = 0;
char need_op_h_bft = 1;

scoredat_section_t hi;
char extra_unlocked;
unsigned int score_duration;

#include "th02/formats/scoredat/load.cpp"

static void pascal near score_put(tram_y_t y, score_t score, tram_atrb2 atrb)
{
	#define on_digit(i, gaiji) { \
		gaiji_putca((26 + (i * GAIJI_TRAM_W)), y, gaiji, atrb); \
	}
	gaiji_score_put(score, on_digit, true);
	#undef on_digit
}

void pascal near shottype_put(tram_y_t y, int type, tram_atrb2 atrb)
{
	text_putsa(48, y, SHOTTYPES[type], atrb);
}

void int_to_string(char *str, int val, int chars)
{
	int divisor = 1;
	int c = 1;
	while(c < chars) {
		divisor *= 10;
		c++;
	}
	c = 0;
	while(c < chars) {
		int result = (val / divisor) % 10;
		str[c] = result + '0';
		divisor /= 10;
		c++;
	}
	str[c] = 0;
}

void pascal near scoredat_date_put(tram_y_t y, int place, tram_atrb2 atrb)
{
	char str[6];
	int_to_string(str, hi.score.date[place].da_year, 4);
	text_putsa(56, y, str, atrb);
	int_to_string(str, hi.score.date[place].da_mon, 2);
	text_putca(60, y, '/', atrb);
	text_putsa(61, y, str, atrb);
	int_to_string(str, hi.score.date[place].da_day, 2);
	text_putca(63, y, '/', atrb);
	text_putsa(64, y, str, atrb);
}

static void pascal near scores_put(int place_to_highlight)
{
	tram_atrb2 atrb = TX_WHITE;
	int i;
	gaiji_putsa(22, 2, gbHI_SCORE, TX_GREEN);
	gaiji_putsa(40, 2, gbcRANKS[rank], TX_GREEN);
	text_putsa(8, 4, HISCORE_HEADER, TX_GREEN);
	for(i = 0; i < SCOREDAT_PLACES; i++) {
		score_atrb_set(atrb, i, place_to_highlight);
		gaiji_putsa(12, 7+i, hi.score.g_name[i], atrb);
		score_put(7+i, hi.score.score[i], atrb);
		if(hi.score.stage[i] != STAGE_ALL) {
			gaiji_putca(44, 7+i, hi.score.stage[i] + gb_0, atrb);
		} else {
			gaiji_putca(44, 7+i, gs_ALL, atrb);
		}
		shottype_put(7+i, hi.score.shottype[i], atrb);
		scoredat_date_put(7+i, i, atrb);
	}
	for(i = 0; i < SCOREDAT_PLACES; i++) {
		score_atrb_set(atrb, i, place_to_highlight);
		if(i != 9) {
			gaiji_putca(9, (7 + i), (gb_1 + i), atrb);
		} else {
			gaiji_putca(8, 16, gb_1, atrb);
			gaiji_putca(10, 16, gb_0, atrb);
		}
	}
}

void pascal near logo_render(int step)
{
	grcg_setcolor(GC_RMW, 10);
	grcg_fill();
	grcg_off();

	// ZUN bug: The first defined frame only displays the purple background
	// without the 東方封魔録 label. See the `master` branch for more details.
	if(step == 0) {
		return;
	}

	for(int i = 0; i < 4; i++) {
		screen_y_t y = ((i * 100) - step);
		while(y < 0) {
			y += 400;
		}
		for(screen_x_t offset = 0; offset < RES_X; offset += (RES_X / 2)) {
			screen_x_t x = ((offset + step + (160 * i)) % RES_X);
			super_put_rect((x +  0), y, 0);
			super_put_rect((x + 64), y, 1);
		}
	}
}

void pascal score_menu(void)
{
	int input_allowed = 0;

	vblank_run(vblank_palette_black_and_tram_wipe);
	scoredat_load();

	if(need_op_h_bft) {
		need_op_h_bft = 0;

		// In super_entry_at(), master.lib insists on provisionally allocating
		// a 9,216-byte [super_buffer], just in case the user later wants to
		// perform any of the very few operations on the sprite that require
		// that amount of temporary memory. This allocation rips an unfortunate
		// 9,216-byte hole into our heap, which is smaller than most other
		// allocations we want to do on this branch, thus forceing us to boost
		// the memory limit to work around the ensuing heap fragmentation.
		// super_convert_tiny() is the only super_*() function in PC-98 Touhou
		// that needs this buffer, and we don't use it here. So let's
		// temporarily point [super_buffer] to some non-null address to prevent
		// the allocation, at least until we've replaced all of the super_*()
		// functions with our own...
		super_buffer = reinterpret_cast<void __seg *>(SEG_PLANE_B);
		super_entry_bfnt("op_h.bft");
		super_buffer = nullptr;
	}
	palette_entry_rgb("op_h.rgb");

	graph_accesspage(1);	graph_clear();
	graph_accesspage(0);	graph_clear();
	grc_setclip(128, 96, 512, 304);

	page_t page_shown = 1;
	logo_step = 0;
	do {
		input_reset_sense();
		if(!input_allowed && !key_det) {
			input_allowed = 1;
		} else if(input_allowed == 1 && key_det) {
			break;
		}
		logo_render(logo_step++);
		frame_delay(1);

		graph_accesspage(page_shown);
		graph_showpage(page_shown = (1 - page_shown));
		if(logo_step == 1) {
			palette_settone(100);
			scores_put(-1);
		}
		// Since we've merged the ZUN bug frame into this loop, we need to stay
		// here for one extra frame.
	} while(logo_step <= (score_duration + 1));
	key_det = 0;

	// Render the previously rendered frame to the now active page to ensure
	// that both VRAM pages are identical. This way, the call site can cleanly
	// transition to whatever it wants to draw on whatever page.
	vsync_Count1 = 0;
	logo_render(logo_step - 1);
	while(vsync_Count1 < 1) {
	}
	grc_setclip(0, 0, 639, 399);
}

inline char shottype_count() {
	return SHOTTYPE_COUNT;
}

int cleardata_load(void)
{
	int game_clear_constants[SHOTTYPE_COUNT] = GAME_CLEAR_CONSTANTS;
	unsigned char extra_clear_flags[SHOTTYPE_COUNT] = EXTRA_CLEAR_FLAGS;
	int extra_unlocked = 1;
	int shottype;

	for(rank = 0; rank < shottype_count(); rank++) {
		scoredat_load();
		if(hi.score.cleared != game_clear_constants[rank]) {
			cleared_game_with[rank] = 0;
			extra_unlocked = 0;
		} else {
			cleared_game_with[rank] = 1;
		}
	}
	rank = shottype_count();
	scoredat_load();
	for(shottype = 0; shottype < 3; shottype++) {
		if(hi.score.cleared & extra_clear_flags[shottype]) {
			cleared_extra_with[shottype] = 1;
		} else {
			cleared_extra_with[shottype] = 0;
		}
	}
	return extra_unlocked;
}

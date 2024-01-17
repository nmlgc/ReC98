/* ReC98
 * -----
 * Code segment #4 of TH02's OP.EXE
 */

#include <dos.h>
#include <mbctype.h>
#include <mbstring.h>
#include "platform.h"
#include "pc98.h"
#include "master.hpp"
#include "shiftjis.hpp"
#include "th01/rank.h"
#include "th02/common.h"
#include "th02/hardware/frmdelay.h"
extern "C" {
#include "th02/hardware/input.hpp"
}
#include "th02/core/globals.hpp"
#include "th02/formats/scoredat.hpp"
#include "th02/gaiji/gaiji.h"
#include "th02/op/op.h"

#include "th02/score.c"

const unsigned char gbcRANKS[4][8] = {
	gb_SP, gb_E_, gb_A_, gb_S_, gb_Y_, gb_SP, gb_SP, 0,
	gb_N_, gb_O_, gb_R_, gb_M_, gb_A_, gb_L_, gb_SP, 0,
	gb_SP, gb_H_, gb_A_, gb_R_, gb_D_, gb_SP, gb_SP, 0,
	gb_L_, gb_U_, gb_N_, gb_A_, gb_T_, gb_I_, gb_C_, 0,
};

const shiftjis_t *SHOTTYPES[] = {"高機動", "防御", "攻撃"};
int logo_step = 0;
char need_op_h_bft = 1;
int8_t need_op_h_bft_padding = 0;

scoredat_section_t hi;
char extra_unlocked;
int8_t extra_unlocked_padding;
unsigned int score_duration;

#include "th02/scorelod.c"

// Slightly differs from the same function in MAINE.EXE!
void pascal near score_put(unsigned y, long score, tram_atrb2 atrb)
{
	unsigned digit = gb_0_;
	long divisor = 10000000;
	long result;
	char putting = 0;
	int i;
	for(i = 0; i < 8; i++) {
		result = divisor ? ((score / divisor) % 10) : (score % 10);
		divisor /= 10;
		digit = result + gb_0_;
		if(result) {
			putting = 1;
		}
		if(putting) {
			gaiji_putca((i * 2) + 26, y, digit, atrb);
		}
	}
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

void pascal near scores_put(int place_to_highlight)
{
	tram_atrb2 atrb = TX_WHITE;
	int i;
	gaiji_putsa(22, 2, gbHI_SCORE, TX_GREEN);
	gaiji_putsa(40, 2, gbcRANKS[rank], TX_GREEN);
	text_putsa(
		8, 4,
		"      お名前　　　　　　得点　　　 STAGE  TYPE   日付",
		TX_GREEN
	);
	for(i = 0; i < SCOREDAT_PLACES; i++) {
		score_atrb_set(atrb, i, place_to_highlight);
		gaiji_putsa(12, 7+i, hi.score.g_name[i], atrb);
		score_put(7+i, hi.score.score[i], atrb);
		if(hi.score.stage[i] != STAGE_ALL) {
			gaiji_putca(44, 7+i, hi.score.stage[i] + gb_0_, atrb);
		} else {
			gaiji_putca(44, 7+i, gs_ALL, atrb);
		}
		shottype_put(7+i, hi.score.shottype[i], atrb);
		scoredat_date_put(7+i, i, atrb);
	}
	for(i = 0; i < SCOREDAT_PLACES; i++) {
		score_atrb_set(atrb, i, place_to_highlight);
		if(i != 9) {
			gaiji_putca(9, 7+i, gb_1_ + i, atrb);
		} else {
			gaiji_putca(8, 16, gb_1_, atrb);
			gaiji_putca(10, 16, gb_0_, atrb);
		}
	}
}

void pascal near logo_render(void)
{
	int i;
	grcg_setcolor(GC_RMW, 10);
	grcg_fill();
	grcg_off();
	logo_step++;
	#define render(i, offset) for(i = 0; i < 4; i++) { \
		screen_x_t x = logo_step + (160 * i) + offset; \
		x %= 640; \
		screen_y_t y = (i * 100) - logo_step; \
		while(1) { \
			if(y < 0) { \
				y += 400; \
			} else { \
				break; \
			} \
		} \
		super_put_rect(x, y, 0); \
		super_put_rect(x + 64, y, 1); \
	}
	render(i, 0);
	render(i, 320);
	#undef render
}

void pascal score_menu(void)
{
	int input_allowed = 0;
	char page = 0;

	scoredat_load();
	graph_accesspage(0);	graph_clear();
	graph_accesspage(1);	graph_clear();
	if(need_op_h_bft) {
		need_op_h_bft = 0;
		super_entry_bfnt("op_h.bft");
	}
	palette_entry_rgb_show("op_h.rgb");
	grc_setclip(128, 96, 512, 304);
	grcg_setcolor(GC_RMW, 10);
	grcg_fill();
	grcg_off();
	scores_put(-1);
	logo_step = 0;

	graph_accesspage(0);
	page = 1 - page;
	graph_showpage(1);

	do {
		input_sense();
		if(!input_allowed && !key_det) {
			input_allowed = 1;
		} else if(input_allowed == 1 && key_det) {
			break;
		}
		logo_render();
		frame_delay(1);
		graph_accesspage(page);
		graph_showpage(page = 1 - page);
	} while(logo_step <= score_duration);

	key_det = 0;
	frame_delay(20);
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

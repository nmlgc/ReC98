#pragma option -2 // ZUN bloat

#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "shiftjis.hpp"
#include "th01/math/clamp.hpp"
#include "th01/hardware/grppsafx.h"
#include "th02/v_colors.hpp"
#include "th02/common.h"
#include "th02/resident.hpp"
#include "th02/hardware/frmdelay.h"
#include "th02/hardware/grp_rect.h"
#include "th02/hardware/input.hpp"
#include "th02/formats/pi.h"

inline char sel_ring_end() {
	return SHOTTYPE_COUNT - 1;
}

char sel = 1;
int8_t sel_padding = 0;

const shiftjis_t *DESC[SHOTTYPE_COUNT][3] = {
	" 陰陽玉の力を使わない ",
	" 広範囲でかつ機動力に ",
	"　強い高機動力タイプ　",

	" 　靈撃が優れている 　",
	"　 バランスの取れた　 ",
	"　　防御重視タイプ　　",

	" 　陰陽玉の力で戦う   ",
	"　攻撃力が優れている　",
	"　　攻撃重視タイプ　　"
};
const shiftjis_t *CHOOSE = "靈夢の戦闘スタイルを、下の３つからえらんでね";
const shiftjis_t *EXTRA_NOTE[] = {
	"注）　エキストラステージでは、難易度、プレイヤー、ボム数は変更出来ません",
	"　　　それぞれ、難易度ＥＸＴＲＡ、プレイヤー３人、ボム１個となります    "
};
const shiftjis_t *CLEARED = "  ☆☆ＣＬＥＡＲＥＤ☆☆  ";

char cleared_game_with[SHOTTYPE_COUNT];
char cleared_extra_with[SHOTTYPE_COUNT];
long unused[2]; // ZUN bloat

void copy_pic_back(int sel, int highlight)
{
	screen_x_t x;
	screen_y_t y;
	if(!highlight) {
		switch(sel) {
			case 0: x =  16; y = 128; break;
			case 1: x = 224; y = 224; break;
			case 2: x = 432; y = 128; break;
		}
		graph_copy_rect_1_to_0_16(x, y, 16, 144);
		graph_copy_rect_1_to_0_16(x, y, 192, 10);
	} else {
		switch(sel) {
			case 0: x = 208; y = 136; break;
			case 1: x = 416; y = 232; break;
			case 2: x = 624; y = 136; break;
		}
		graph_copy_rect_1_to_0_16(x, y, 16, 144);
		switch(sel) {
			case 0: x =  24; y = 272; break;
			case 1: x = 232; y = 368; break;
			case 2: x = 440; y = 272; break;
		}
		graph_copy_rect_1_to_0_16(x, y, 192, 8);
	}
}

void darken_pic_at(screen_x_t x, screen_y_t y)
{
	vram_offset_t row_p = vram_offset_shift(x, y);
	pixel_t row;
	vram_byte_amount_t col;

	grcg_setcolor(GC_RMW, 0);
	for(row = 0; row < 144; row++, row_p += ROW_SIZE)  {
		for(col = 0; col < 192 / BYTE_DOTS; col += 2) {
			grcg_put(row_p + col, (row & 1 ? 0xAAAA : 0x5555), 16);
		}
	}
	grcg_off();
}

void draw_shottype_desc(int sel, vc2 color)
{
	screen_x_t x;
	screen_y_t y;
	switch(sel) {
		case 0: x =  16; y = 296; break;
		case 1: x = 224; y = 136; break;
		case 2: x = 432; y = 296; break;
	}
	grcg_setcolor(GC_RMW, color);
	grcg_round_boxfill(x + 8, y + 8, x + 200, y + 72, 8);
	grcg_setcolor(GC_RMW, 0);
	grcg_round_boxfill(x, y, x + 192, y + 64, 8);
	grcg_off();

	graph_putsa_fx(x + 8, y + 8 +  0, (color | FX_WEIGHT_BOLD), DESC[sel][0]);
	graph_putsa_fx(x + 8, y + 8 + 16, (color | FX_WEIGHT_BOLD), DESC[sel][1]);
	graph_putsa_fx(x + 8, y + 8 + 32, (color | FX_WEIGHT_BOLD), DESC[sel][2]);
}

void pascal draw_header(void)
{
	grcg_setcolor(GC_RMW, 12); grcg_round_boxfill(136, 24, 520, 56, 8);
	grcg_setcolor(GC_RMW, 0);  grcg_round_boxfill(128, 16, 512, 48, 8);
	grcg_off();

	graph_putsa_fx(144, 24, (12 | FX_WEIGHT_BOLD), CHOOSE);
	if(resident->stage == 5) {
		grcg_setcolor(GC_RMW, 12); grcg_round_boxfill(24, 56, 632, 104, 8);
		grcg_setcolor(GC_RMW, 0);  grcg_round_boxfill(16, 48, 624,  96, 8);
		grcg_off();

		graph_putsa_fx(32, 56, (V_WHITE | FX_WEIGHT_BOLD), EXTRA_NOTE[0]);
		graph_putsa_fx(32, 72, (V_WHITE | FX_WEIGHT_BOLD), EXTRA_NOTE[1]);
	}
}

void pascal shottype_menu_init(void)
{
	#define draw_cleared_for(cleared_mode_with) \
		if(cleared_mode_with[0]) { \
			graph_putsa_fx(16, 112, (V_WHITE | FX_WEIGHT_BOLD), CLEARED); \
		} \
		if(cleared_mode_with[1]) { \
			graph_putsa_fx(224, 112, (V_WHITE | FX_WEIGHT_BOLD), CLEARED); \
		} \
		if(cleared_mode_with[2]) { \
			graph_putsa_fx(432, 112, (V_WHITE | FX_WEIGHT_BOLD), CLEARED); \
		}

	palette_black();
	graph_accesspage(0);
	pi_fullres_load_palette_apply_put_free(3, "TSELECT.pi");
	graph_copy_page(1);
	graph_accesspage(0);
	if(resident->stage != 5) {
		draw_cleared_for(cleared_game_with);
	} else {
		draw_cleared_for(cleared_extra_with);
	}
	pi_put_8( 24, 136, 0);
	pi_put_8(224, 224, 1);
	pi_put_8(440, 136, 2);
	resident->shottype = 1;
	darken_pic_at( 24, 136);
	darken_pic_at(440, 136);

	draw_shottype_desc(0,  7);
	draw_shottype_desc(1, 12);
	draw_shottype_desc(2,  7);

	draw_header();
	palette_black_in(2);
}

inline void draw_new_sel(const screen_x_t pic_x[3], const screen_y_t pic_y[3]) {
	frame_delay(1);	copy_pic_back(sel, 1);
	frame_delay(1); draw_shottype_desc(sel, 12);
	frame_delay(1); pi_put_8(pic_x[sel], pic_y[sel], sel);
}

void pascal shottype_menu(void)
{
	int input_locked = 0;
	screen_x_t pic_x[] = { 16, 224, 432};
	screen_y_t pic_y[] = {128, 224, 128};
	unsigned int input_delay = 0;
	shottype_menu_init();

	do {
		input_reset_sense();
		if(!input_locked) {
			if(key_det & INPUT_LEFT) {
				draw_shottype_desc(sel, 7);
				frame_delay(1);
				copy_pic_back(sel, 0);
				frame_delay(1);
				pi_put_8(pic_x[sel] + 8, pic_y[sel] + 8, sel);
				frame_delay(1);
				darken_pic_at(pic_x[sel] + 8, pic_y[sel] + 8);

				ring_dec(sel, sel_ring_end());
				draw_new_sel(pic_x, pic_y);
			}
			if(key_det & INPUT_RIGHT) {
				copy_pic_back(sel, 0);
				frame_delay(1);
				pi_put_8(pic_x[sel] + 8, pic_y[sel] + 8, sel);
				frame_delay(1);
				draw_shottype_desc(sel, 7);
				frame_delay(1);
				darken_pic_at(pic_x[sel] + 8, pic_y[sel] + 8);

				ring_inc(sel, sel_ring_end());
				draw_new_sel(pic_x, pic_y);
			}
			if(key_det & INPUT_SHOT || key_det & INPUT_OK) {
				resident->shottype = sel;
				break;
			}
		}
		frame_delay(1);
		input_locked = key_det;
		if(input_locked) {
			input_delay++;
			if(input_delay > 30) {
				input_locked = 0;
			}
		} else {
			input_delay = 0;
		}
	} while(1);
	pi_free(0);
	pi_free(1);
	pi_free(2);
	palette_black_out(1);
}

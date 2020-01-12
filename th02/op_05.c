/* ReC98
 * -----
 * Code segment #5 of TH02's OP.EXE
 */

#include "th02\th02.h"
#include "th02/formats/pi.h"

char sel = 1;

const char *DESC[SHOTTYPE_COUNT][3] = {
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
const char *CHOOSE = "靈夢の戦闘スタイルを、下の３つからえらんでね";
const char *EXTRA_NOTE[] = {
	"注）　エキストラステージでは、難易度、プレイヤー、ボム数は変更出来ません",
	"　　　それぞれ、難易度ＥＸＴＲＡ、プレイヤー３人、ボム１個となります    "
};
const char *CLEARED = "  ☆☆ＣＬＥＡＲＥＤ☆☆  ";

char cleared_game_with[SHOTTYPE_COUNT];
char cleared_extra_with[SHOTTYPE_COUNT];
long unused[2];

void pascal graph_copy_rect_1_to_0(int x, int y, int w, int h);

void copy_pic_back(int sel, int highlight)
{
	int x, y;
	if(!highlight) {
		switch(sel) {
			case 0: x =  16; y = 128; break;
			case 1: x = 224; y = 224; break;
			case 2: x = 432; y = 128; break;
		}
		graph_copy_rect_1_to_0(x, y, 16, 144);
		graph_copy_rect_1_to_0(x, y, 192, 10);
	} else {
		switch(sel) {
			case 0: x = 208; y = 136; break;
			case 1: x = 416; y = 232; break;
			case 2: x = 624; y = 136; break;
		}
		graph_copy_rect_1_to_0(x, y, 16, 144);
		switch(sel) {
			case 0: x =  24; y = 272; break;
			case 1: x = 232; y = 368; break;
			case 2: x = 440; y = 272; break;
		}
		graph_copy_rect_1_to_0(x, y, 192, 8);
	}
}

void darken_pic_at(int x, int y)
{
	int row_p = VRAM_OFFSET(x, y);
	int row, col;

	grcg_setcolor(GC_RMW, 0);
	for(row = 0; row < 144; row++, row_p += 640 / 8)  {
		for(col = 0; col < 192 / 8; col += 2) {
			VRAM_PUT(B, row_p + col, (row & 1 ? 0xAAAA : 0x5555), 16);
		}
	}
	grcg_off();
}

void draw_shottype_desc(int sel, int color)
{
	int x, y;
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

	graph_putsa_fx(x + 8, y + 8 +  0, FX(color, 2, 0), DESC[sel][0]);
	graph_putsa_fx(x + 8, y + 8 + 16, FX(color, 2, 0), DESC[sel][1]);
	graph_putsa_fx(x + 8, y + 8 + 32, FX(color, 2, 0), DESC[sel][2]);
}

void pascal draw_header(void)
{
	grcg_setcolor(GC_RMW, 12); grcg_round_boxfill(136, 24, 520, 56, 8);
	grcg_setcolor(GC_RMW, 0);  grcg_round_boxfill(128, 16, 512, 48, 8);
	grcg_off();

	graph_putsa_fx(144, 24, FX(12, 2, 0), CHOOSE);
	if(resident->stage == 5) {
		grcg_setcolor(GC_RMW, 12); grcg_round_boxfill(24, 56, 632, 104, 8);
		grcg_setcolor(GC_RMW, 0);  grcg_round_boxfill(16, 48, 624,  96, 8);
		grcg_off();

		graph_putsa_fx(32, 56, FX(15, 2, 0), EXTRA_NOTE[0]);
		graph_putsa_fx(32, 72, FX(15, 2, 0), EXTRA_NOTE[1]);
	}
}

void pascal shottype_menu_init(void)
{
	#define DRAW_CLEARED_FOR(mode) \
		if(cleared_##mode##_with[0]) { \
			graph_putsa_fx(16, 112, FX(15, 2, 0), CLEARED); \
		} \
		if(cleared_##mode##_with[1]) { \
			graph_putsa_fx(224, 112, FX(15, 2, 0), CLEARED); \
		} \
		if(cleared_##mode##_with[2]) { \
			graph_putsa_fx(432, 112, FX(15, 2, 0), CLEARED); \
		}

	palette_black();
	graph_accesspage(0);
	pi_load_put_free(3, "TSELECT.pi");
	graph_copy_page(1);
	graph_accesspage(0);
	if(resident->stage != 5) {
		DRAW_CLEARED_FOR(game);
	} else {
		DRAW_CLEARED_FOR(extra);
	}
	pi_slot_put( 24, 136, 0);
	pi_slot_put(224, 224, 1);
	pi_slot_put(440, 136, 2);
	resident->shottype = 1;
	darken_pic_at( 24, 136);
	darken_pic_at(440, 136);

	draw_shottype_desc(0,  7);
	draw_shottype_desc(1, 12);
	draw_shottype_desc(2,  7);

	draw_header();
	palette_black_in(2);
}

void pascal shottype_menu(void)
{
	int input_locked = 0;
	int pic_x[] = { 16, 224, 432};
	int pic_y[] = {128, 224, 128};
	unsigned int input_delay = 0;
	shottype_menu_init();

	#define DRAW_NEW_SEL() \
		frame_delay(1);	copy_pic_back(sel, 1); \
		frame_delay(1); draw_shottype_desc(sel, 12); \
		frame_delay(1); pi_slot_put(pic_x[sel], pic_y[sel], sel);

	do {
		input_sense();
		if(!input_locked) {
			if(key_det & INPUT_LEFT) {
				draw_shottype_desc(sel, 7);
				frame_delay(1);
				copy_pic_back(sel, 0);
				frame_delay(1);
				pi_slot_put(pic_x[sel] + 8, pic_y[sel] + 8, sel);
				frame_delay(1);
				darken_pic_at(pic_x[sel] + 8, pic_y[sel] + 8);

				RING_DEC(sel, SHOTTYPE_COUNT - 1);
				DRAW_NEW_SEL();
			}
			if(key_det & INPUT_RIGHT) {
				copy_pic_back(sel, 0);
				frame_delay(1);
				pi_slot_put(pic_x[sel] + 8, pic_y[sel] + 8, sel);
				frame_delay(1);
				draw_shottype_desc(sel, 7);
				frame_delay(1);
				darken_pic_at(pic_x[sel] + 8, pic_y[sel] + 8);

				RING_INC(sel, SHOTTYPE_COUNT - 1);
				DRAW_NEW_SEL();
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
	graph_pi_free(&pi_slot_headers[0], pi_slot_buffers[0]);
	graph_pi_free(&pi_slot_headers[1], pi_slot_buffers[1]);
	graph_pi_free(&pi_slot_headers[2], pi_slot_buffers[2]);
	palette_black_out(1);
}

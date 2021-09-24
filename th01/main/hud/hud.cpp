#include <stddef.h>
#include "x86real.h"
#include "master.hpp"
#include "th01/common.h"
#include "th01/resident.hpp"
#include "th01/v_colors.hpp"
#include "th01/hardware/graph.h"
#include "th01/main/vars.hpp"
#include "th01/core/str_val.hpp"
#include "th01/formats/ptn.hpp"
#include "th01/formats/grf.hpp"
#include "th01/main/playfld.hpp"
#include "th01/main/player/player.hpp"
#include "th01/sprites/main_ptn.h"
#include "th01/main/hud/hud.hpp"

/// Constants
/// ---------
static const screen_x_t LIVES_LEFT = 128;
static const screen_y_t LIVES_TOP = 0;
static const int LIVES_PER_ROW = 6; // for all the cheaters?

static const screen_x_t BOMBS_LEFT = 128;
static const screen_y_t BOMBS_TOP = 16;

static const screen_x_t SCORE_LEFT = 256;
static const screen_y_t MAX_TOP = 0;
static const screen_y_t CUR_TOP = 16;

static const screen_x_t STAGE_LEFT = 608;
static const screen_y_t STAGE_TOP = 32;

static const int PTN_LIFE_QUARTER = 0;
static const int PTN_BOMB_QUARTER = 1;

static const int16_t MAX_FX = (V_WHITE | FX_WEIGHT_BOLD);
static const int16_t CUR_FX = (V_WHITE | FX_WEIGHT_BLACK);

#if (PTN_QUARTER_W < GLYPH_FULL_W)
	#error Original code assumes PTN_QUARTER_W >= GLYPH_FULL_W
#endif
#if (PTN_QUARTER_H < GLYPH_H)
	#error Original code assumes PTN_QUARTER_H >= GLYPH_H
#endif
static const pixel_t COL_W = PTN_QUARTER_W;
static const pixel_t ROW_H = PTN_QUARTER_H;

static const pixel_t SCORE_W = (SCORE_DIGITS * COL_W);

static const screen_x_t CARDCOMBO_LEFT = (
	SCORE_LEFT + ((SCORE_DIGITS + 2) * COL_W)
);
static const pixel_t CARDCOMBO_W = (CARDCOMBO_DIGITS * COL_W);
static const screen_x_t CARDCOMBO_RIGHT = (CARDCOMBO_LEFT + CARDCOMBO_W);

static const pixel_t SCORE_AND_CARDCOMBO_W = (CARDCOMBO_RIGHT - SCORE_LEFT);
/// ---------

/// Globals
/// -------
// Forces re-rendering of all full-width numbers on the HUD, even if they
// haven't changed since the last render call.
extern bool fwnum_force_rerender;

// extern uint8_t *hud_bg;
extern uint8_t hud_bg_rle_run_byte;
extern unsigned char hud_cardcombo_max; // Why a separate variable???
// size_t hud_bg_size;
/// -------

/// Functions
/// ---------
inline screen_x_t col_left(screen_x_t first_left, int col) {
	return (first_left + (col * COL_W));
}

#define bg_put(first_left, col, top, ptn_id, quarter) \
	ptn_put_quarter_noalpha_8(col_left(first_left, col), top, ptn_id, quarter)

#define bg_snap(first_left, col, top, ptn_id, quarter) \
	ptn_snap_quarter_8(col_left(first_left, col), top, ptn_id, quarter)

#define sprite_put(first_left, col, top, ptn_id, quarter) \
	ptn_put_quarter_8(col_left(first_left, col), top, ptn_id, quarter)

#define ptn_id_and_quarter_from_i(func, first_left, col, top, ptn_id_base, i) \
	func(first_left, col, top, (ptn_id_base + (i / 4)), (i % 4))

#define digit_changed(var, var_prev, divisor) \
	((var_prev / divisor) % 10) != ((var / divisor) % 10) || \
	(fwnum_force_rerender == true)

// Copies the (⌊[w]/16⌋*16)×[ROW_H] pixels starting at (⌊left/8⌋*8, top) from
// VRAM page 0 to VRAM page 1.
void graph_copy_hud_row_0_to_1_8(screen_x_t left, vram_y_t top, pixel_t w);
/// ---------
}

template <class T1, class T2> inline void fwnum_put(
	screen_x_t left,
	screen_y_t top,
	int fx,
	int digits,
	const T1 &val,
	const T2 &val_prev
) {
	graph_putfwnum_fx(
		left, top, fx, digits, val,
		(fwnum_force_rerender == true) ? 0 : val_prev, true
	);
}

#define score_bg(func, digit, top, ptn_id_base) \
	ptn_id_and_quarter_from_i(func, SCORE_LEFT, digit, top, ptn_id_base, digit)

#define score_max_bg(func, digit) \
	score_bg(func, digit, MAX_TOP, PTN_BG_MAX_SCORE)

inline void score_put(screen_y_t top, int fx, const long &prev) {
	fwnum_put(SCORE_LEFT, top, fx, SCORE_DIGITS, score, prev);
}

#define cardcombo_bg(func, digit, top, ptn_id) \
	func(CARDCOMBO_LEFT, digit, top, ptn_id, digit)

#define cardcombo_max_bg(func, digit) \
	cardcombo_bg(func, digit, MAX_TOP, PTN_BG_MAX_CARDCOMBO)

inline void cardcombo_put(screen_y_t top, int fx, const int &prev) {
	fwnum_put(CARDCOMBO_LEFT, top, fx, CARDCOMBO_DIGITS, cardcombo_cur, prev);
}

extern "C" {

void hiscore_update_and_render(void)
{
	// TODO: Should just be `static` once the variable can be declared here
	#define prev score_prev
	extern long prev;
	long divisor = 1000000; // Must match SCORE_DIGITS!
	unsigned long hiscore = resident->hiscore;

	if(hiscore >= score) {
		return;
	}
	for(int i = 0; i < SCORE_DIGITS; i++) {
		if(digit_changed(score, prev, divisor)) {
			graph_accesspage_func(1);	score_max_bg(bg_put, i);
			graph_accesspage_func(0);	score_max_bg(bg_put, i);
		}
		divisor /= 10;
	}
	graph_accesspage_func(1);	score_put(MAX_TOP, MAX_FX, prev);
	graph_accesspage_func(0);	score_put(MAX_TOP, MAX_FX, prev);

	prev = score;
	resident->hiscore = score;
	#undef prev
}

void cardcombo_max_render(void)
{
	// TODO: Should just be `static` once the variable can be declared here
	#define prev cardcombo_max_prev
	extern int prev;
	int divisor = 10; // Must match CARDCOMBO_DIGITS!

	for(int i = 0; i < CARDCOMBO_DIGITS; i++) {
		if(digit_changed(cardcombo_cur, prev, divisor)) {
			graph_accesspage_func(1);	cardcombo_max_bg(bg_put, i);
			graph_accesspage_func(0);	cardcombo_max_bg(bg_put, i);
		}
		divisor /= 10;
	}
	graph_accesspage_func(1);	cardcombo_put(MAX_TOP, MAX_FX, prev);
	graph_accesspage_func(0);	cardcombo_put(MAX_TOP, MAX_FX, prev);

	prev = cardcombo_cur;
	#undef prev
}

void hud_score_and_cardcombo_render(void)
{
	// TODO: Should just be `static` once the variable can be declared here
	#define score_prev score_cur_prev
	#define cardcombo_prev cardcombo_cur_prev
	extern long score_prev;
	extern int cardcombo_prev;

	int digit;
	int page;
	int cardcombo_divisor;
	long score_divisor;

	score_divisor = 1000000; // Must match SCORE_DIGITS!
	cardcombo_divisor = 10; // Must match CARDCOMBO_DIGITS!
	for(page = 1; page >= 0; page--) {
		graph_accesspage_func(page);
		score_divisor = 1000000; // Must match SCORE_DIGITS!
		cardcombo_divisor = 10; // Must match CARDCOMBO_DIGITS!

		for(digit = 0; digit < SCORE_DIGITS; digit++) {
			if(digit_changed(score, score_prev, score_divisor)) {
				score_bg(bg_put, digit, CUR_TOP, PTN_BG_CUR_SCORE);
			}
			score_divisor /= 10;
		}
		score_put(CUR_TOP, CUR_FX, score_prev);

		for(digit = 0; digit < CARDCOMBO_DIGITS; digit++) {
			if(digit_changed(cardcombo_cur, cardcombo_prev, cardcombo_divisor)) {
				cardcombo_bg(bg_put, digit, CUR_TOP, PTN_BG_CUR_CARDCOMBO);
			}
			cardcombo_divisor /= 10;
		}
		cardcombo_put(CUR_TOP, CUR_FX, cardcombo_prev);
	}

	score_prev = score;
	cardcombo_prev = cardcombo_cur;
	hiscore_update_and_render();
	if(hud_cardcombo_max < cardcombo_cur) {
		hud_cardcombo_max = cardcombo_cur;
		cardcombo_max_render();
	}
}

#define cardcombo_bg_loop(func, digit, top, ptn_id) \
	for(digit = 0; digit < CARDCOMBO_DIGITS; digit++) { \
		cardcombo_bg(func, digit, top, ptn_id); \
	} \

inline void cardcombo_put_initial(screen_y_t top, int fx) {
	graph_putfwnum_fx(CARDCOMBO_LEFT, top, fx, CARDCOMBO_DIGITS, 0, 99, true);
}

#define score_snap_bg_and_put(digit, top, ptn_id, fx, score) \
	graph_accesspage_func(1); \
	for(digit = 0; digit < SCORE_DIGITS; digit++) { \
		score_bg(bg_snap, digit, top, ptn_id); \
	} \
	graph_accesspage_func(0); \
	graph_putfwnum_fx(SCORE_LEFT, top, fx, SCORE_DIGITS, score, 0, true);

// Setting [first_run] to false will only reset the card combo display.
void score_and_cardcombo_put_initial(bool16 first_run)
{
	int digit;

	// Spot the difference… :(
	if(first_run) {
		score_snap_bg_and_put(digit, CUR_TOP, PTN_BG_CUR_SCORE, CUR_FX, score);
		graph_accesspage_func(1);
		cardcombo_bg_loop(bg_snap, digit, CUR_TOP, PTN_BG_CUR_CARDCOMBO);
	} else {
		cardcombo_bg_loop(bg_put, digit, CUR_TOP, PTN_BG_CUR_CARDCOMBO);
	}
	graph_accesspage_func(0);
	cardcombo_put_initial(CUR_TOP, CUR_FX);

	if(first_run) {
		score_snap_bg_and_put(
			digit, MAX_TOP, PTN_BG_MAX_SCORE, MAX_FX, resident->hiscore
		);
		graph_accesspage_func(1);
		cardcombo_bg_loop(bg_snap, digit, MAX_TOP, PTN_BG_MAX_CARDCOMBO);
		graph_accesspage_func(0);
	} else {
		cardcombo_bg_loop(bg_put, digit, MAX_TOP, PTN_BG_MAX_CARDCOMBO);
	}
	cardcombo_put_initial(MAX_TOP, MAX_FX);

	graph_copy_hud_row_0_to_1_8(SCORE_LEFT, MAX_TOP, SCORE_AND_CARDCOMBO_W);
	graph_copy_hud_row_0_to_1_8(SCORE_LEFT, CUR_TOP, SCORE_AND_CARDCOMBO_W);
	hud_cardcombo_max = 0;
}

/// Background
/// ----------
void hud_bg_put(void)
{
	register uint16_t vram_offset;
	uint16_t src_offset = 0;
	uint8_t byte;
	uint8_t runs;
	uint8_t rle_run_byte = hud_bg_rle_run_byte;

	disable();
	grcg_setcolor_rmw(V_RED);
	for(vram_offset = 0; vram_offset < (66 * ROW_SIZE); vram_offset++) {
		// Effectively the same algorithm as used for .GRX files, except for
		// • the customizable RLE run byte, and
		// • implicitly defining a run of 0x00 dots as a skip. (Which really
		//   is just an optimization here, since blitting a 0x00 byte with the
		//   GRCG won't blit anything after all.)
		byte = hud_bg[src_offset++];
		if(byte == rle_run_byte) {
			runs = hud_bg[src_offset++];
			if(runs) {
				byte = hud_bg[src_offset++];
				while(runs--) {
					if(byte != 0) {
						grcg_put(vram_offset, byte, 8);
					}
					vram_offset++;
				}
			}
		}
		// Yes, in case we just did a putting run, we are in fact putting
		// one more byte!
		if(byte != 0) {
			grcg_put(vram_offset, byte, 8);
		}
	}
	grcg_off();
	enable();
}

int hud_bg_load(const char *fn)
{
	int size;
	grf_header_t header;

	file_ropen(fn);
	file_read(&header, sizeof(header));

	hud_bg_rle_run_byte = header.rle_run_byte;
	size = header.rle_size.B;
	hud_bg_size = size;
	hud_bg = new uint8_t[size];

	file_read(hud_bg, size);
	file_close();
	return 0;
}
/// ----------

void graph_copy_hud_row_0_to_1_8(screen_x_t left, vram_y_t top, pixel_t w)
{
	vram_offset_t vram_offset;
	dots16_t dots;
	pixel_t y;
	vram_offset_t vram_offset_row = vram_offset_divmul(left, top);
	vram_word_amount_t x;

	vram_offset = vram_offset_row;
	for(y = 0; y < ROW_H; y++) {
		vram_offset = vram_offset_row;
		for(x = 0; x < (w / 16); x++) {
			#define copy_plane(plane) \
				outport(0xA6, 0);	VRAM_SNAP(dots, plane, vram_offset, 16); \
				outport(0xA6, 1);	VRAM_PUT(plane, vram_offset, dots, 16);
			copy_plane(B);
			copy_plane(R);
			copy_plane(G);
			copy_plane(E);
			vram_offset += static_cast<vram_offset_t>(sizeof(dots));
			#undef copy_plane
		}
		vram_offset_row += ROW_SIZE;
	}
	graph_accesspage_func(0);
}

/// Lives and bombs
/// ---------------
inline int lives_col(int i) {
	return (i % LIVES_PER_ROW);
}

inline screen_y_t lives_top(int i) {
	return (LIVES_TOP + ((i / LIVES_PER_ROW) * ROW_H));
}

#define lives_bg(func, left, i) \
	ptn_id_and_quarter_from_i( \
		func, left, lives_col(i), lives_top(i), PTN_BG_LIVES, i \
	)

#define lives_put(left, i) \
	sprite_put(left, lives_col(i), lives_top(i), PTN_HUD, PTN_LIFE_QUARTER)

#define bombs_bg(func, left, i) \
	ptn_id_and_quarter_from_i(func, left, i, BOMBS_TOP, PTN_BG_BOMBS, i)

#define bombs_put(left, i) \
	sprite_put(left, i, BOMBS_TOP, PTN_HUD, PTN_BOMB_QUARTER)

#define put_initial(left, top, func_bg, func_sprite, var) \
	for(int i = 0; i < var; i++) { \
		func_bg(bg_snap, left, i); \
		func_sprite(left, i); \
	} \
	/* Yet we don't accomodate cheaters here, and only copy a single row? */ \
	graph_copy_hud_row_0_to_1_8(left, top, var * COL_W);

#define put_change(left, top, func_bg, func_sprite, var_prev, var_new) \
	if(var_prev > var_new) { \
		for(int i = var_new; i < var_prev; i++) { \
			graph_accesspage_func(1);	func_bg(bg_put, left, i); \
			graph_accesspage_func(0);	func_bg(bg_put, left, i); \
		} \
	} else if(var_prev < var_new) { \
		for(int i = var_prev; i < var_new; i++) { \
			func_bg(bg_snap, left, i); \
			graph_accesspage_func(0); \
			func_sprite(left, i); \
		} \
		graph_copy_hud_row_0_to_1_8(left, top, var_new * COL_W); \
	} \

void lives_put_initial(void)
{
	put_initial(LIVES_LEFT, LIVES_TOP, lives_bg, lives_put, lives);
}

void hud_lives_put(int prev)
{
	put_change(LIVES_LEFT, LIVES_TOP, lives_bg, lives_put, prev, lives);
}

void bombs_put_initial(void)
{
	put_initial(BOMBS_LEFT, BOMBS_TOP, bombs_bg, bombs_put, bombs);
}

void hud_bombs_put(int prev)
{
	put_change(BOMBS_LEFT, BOMBS_TOP, bombs_bg, bombs_put, prev, bombs);
}

#undef put_initial
#undef put_change
/// ---------------

// Assumes page 0.
void stage_put_initial(void)
{
	char str[STAGE_DIGITS + 1];

	bg_snap(STAGE_LEFT, 0, STAGE_TOP, PTN_BG_STAGE, 0);
	str_right_aligned_from_uint16(str, stage_num, STAGE_DIGITS);
	graph_putsa_fx(STAGE_LEFT, STAGE_TOP, MAX_FX, str);
	graph_copy_hud_row_0_to_1_8(
		STAGE_LEFT, STAGE_TOP, STAGE_DIGITS * GLYPH_HALF_W
	);
}

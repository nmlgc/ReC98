#include <stddef.h>
#include "platform.h"
#include "x86real.h"
#include "decomp.hpp"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "shiftjis.hpp"
#include "th01/resident.hpp"
#include "th01/v_colors.hpp"
#include "th01/math/str_val.hpp"
#include "th01/hardware/egc.h"
#include "th01/hardware/graph.h"
#include "th01/hardware/grppsafx.h"
#include "th01/hardware/frmdelay.h"
#include "th01/hardware/tram_x16.hpp"
#include "th01/formats/ptn.hpp"
#include "th01/math/subpixel.hpp"
#include "th01/snd/mdrv2.h"
#include "th01/main/playfld.hpp"
#include "th01/main/bullet/pellet.hpp"
#include "th01/main/bullet/pellet_s.hpp"
#include "th01/main/stage/stages.hpp"
#include "th01/main/stage/timer.hpp"

unsigned int stage_timer;
static unsigned int frames_since_harryup;

// Function ordering fails
// -----------------------

void harryup_animate(void);
void pattern_harryup(void);
// -----------------------

/// Constants
/// ---------

static const screen_x_t TIMER_LEFT = 512;
static const screen_y_t TIMER_TOP = 0;
static const int16_t TIMER_COL_AND_FX = (FX_WEIGHT_BOLD | V_WHITE);

static const int TIMER_PTN_QUARTERS = (
	(TIMER_DIGITS * GLYPH_HALF_W) / PTN_QUARTER_W
);
/// ---------

/// Helper functions
/// ----------------

inline void unput(void) {
	// MODDERS: Loop over TIMER_PTN_QUARTERS instead.
	enum {
		LEFT_1 = (TIMER_LEFT + (0 * GLYPH_HALF_W)),
		LEFT_2 = (TIMER_LEFT + (2 * GLYPH_HALF_W)),
	};
	ptn_put_quarter_noalpha_8(LEFT_1, TIMER_TOP, PTN_BG_TIMER, 0);
	ptn_put_quarter_noalpha_8(LEFT_2, TIMER_TOP, PTN_BG_TIMER, 1);
}

#define put(tmp_str, col_and_fx) { \
	str_right_aligned_from_uint16(tmp_str, stage_timer, TIMER_DIGITS); \
	graph_putsa_fx(TIMER_LEFT, TIMER_TOP, col_and_fx, tmp_str); \
}
/// ----------------

void timer_init_for(int stage_id, int route)
{
	static unsigned int STAGE_TIMES[
		STAGES_OUTSIDE_ROUTE + (STAGES_ON_ROUTE * ROUTE_COUNT)
	] = {
		1000, 1000, 1000, 1000, 2000,	// Shrine
		// Makai
		1200, 1200, 1200, 1200, 3000,	// (06 - 10)
		1400, 1400, 1400, 1400, 4000,	// (11 - 15)
		1600, 1600, 1600,  600, 6000,	// (16 - 20)
		// Jigoku
		1200, 1200, 1200, 1200, 2000,	// (06 - 10)
		1400, 1400, 1400, 1400, 4000,	// (11 - 15)
		1600, 1800, 1800, 1600, 8000,	// (16 - 20)
	};

	if(stage_id < STAGES_OUTSIDE_ROUTE) {
		stage_timer = STAGE_TIMES[stage_id];
	} else {
		stage_timer = STAGE_TIMES[(route * STAGES_ON_ROUTE) + stage_id];
	}
	frames_since_harryup = 0;
}

void timer_bg_snap_and_put(void)
{
	char str[TIMER_DIGITS + 1];

	for(int i = 0; i < TIMER_PTN_QUARTERS; i++) {
		ptn_snap_quarter_8(TIMER_LEFT, TIMER_TOP, PTN_BG_TIMER, i);
	}

	str_right_aligned_from_uint16(str, stage_timer, TIMER_DIGITS);

	graph_accesspage_func(1);
	graph_putsa_fx(TIMER_LEFT, TIMER_TOP, TIMER_COL_AND_FX, str);
	graph_accesspage_func(0);
	graph_putsa_fx(TIMER_LEFT, TIMER_TOP, TIMER_COL_AND_FX, str);
}

void timer_put(void)
{
	int16_t col_and_fx = (stage_timer < 200)
		? (FX_WEIGHT_BOLD | V_RED)
		: TIMER_COL_AND_FX;
	char tmp_str[TIMER_DIGITS + 1];

	graph_accesspage_func(1); unput(); put(tmp_str, col_and_fx);
	graph_accesspage_func(0); unput(); put(tmp_str, col_and_fx);
}

void timer_tick_and_put(void)
{
	if(stage_timer > 0) {
		stage_timer -= TIMER_TICK;
		timer_put();
		if(stage_timer == 0) {
			pellet_speed_raise(0.05f);
			harryup_animate();
		}
	} else {
		pattern_harryup();
	}
}

void timer_extend_and_put(void)
{
	if(stage_timer != 0) {
		stage_timer += 200;
	} else {
		stage_timer += 1000;
	}
	timer_put();
	frames_since_harryup = 0;
}

// Largely copy-pasted from stage_num_animate()
void harryup_animate(void)
{
	TRAMCursor tram_cursor;
	REGS in;
	font_glyph_ank_8x16_t glyphs[7];

	mdrv2_se_play(17);

	fontrom_get(in, glyphs[0], 'H');
	fontrom_get(in, glyphs[1], 'A');
	fontrom_get(in, glyphs[2], 'R');
	fontrom_get(in, glyphs[3], 'R');
	fontrom_get(in, glyphs[4], 'Y');
	fontrom_get(in, glyphs[5], 'U');
	fontrom_get(in, glyphs[6], 'P');

	tram_cursor.rewind_to_topleft();
	tram_cursor.putkanji_for_5_rows(' ', TX_BLACK);

	{for(upixel_t glyph_y = 0; glyph_y < GLYPH_H; glyph_y++) {
		for(unsigned int i = 0; i < 5; i++) {
			tram_x16_row_put_red(
				tram_cursor, &glyphs[i].dots[glyph_y], GLYPH_HALF_H
			);
		}
		// 5 halfwidth glyphs scaled by a factor of 16 just happen to exactly
		// fit into one TRAM row, so we're already at the next one here.
	}}

	frame_delay(27);

	tram_cursor.rewind_to_topleft();
	tram_cursor.putkanji_for_5_rows(' ', TX_BLACK);

	{for(upixel_t glyph_y = 0; glyph_y < GLYPH_H; glyph_y++) {
		tram_x16_put_center_margin(tram_cursor, TX_BLACK);
		for(unsigned int i = 5; i < 7; i++) {
			tram_x16_row_put_red(
				tram_cursor, &glyphs[i].dots[glyph_y], GLYPH_HALF_H
			);
		}
		tram_x16_put_center_margin(tram_cursor, TX_BLACK);
	}}

	frame_delay(27);
	text_clear();
}

void pattern_harryup(void)
{
	static unsigned char harryup_cycle;

	frames_since_harryup++;
	harryup_cycle++;

	bool fire =
		(frames_since_harryup < 200) ? ((harryup_cycle % 5) == 0) :
		(frames_since_harryup < 300) ? ((harryup_cycle % 4) == 0) :
		(frames_since_harryup < 400) ? ((harryup_cycle % 3) == 0) :
		(frames_since_harryup < 500) ? ((harryup_cycle % 2) == 0) :
		/*                   >= 500 */ true;

	if(!fire) {
		return;
	}
	for(unsigned char i = 0; i <= rank; i++) {
		Pellets.add_group(
			playfield_rand_x(), PLAYFIELD_TOP, PG_1_RANDOM_WIDE, to_sp(3.0f)
		);
	}
}

/* ReC98
 * -----
 * Code segment #2 of TH01's FUUIN.EXE
 */

#pragma option -O- -1 -Z- -d-

static long unused_long = { 0 }; // ZUN bloat

#include <io.h>
#include <stdio.h>
#include <string.h>
#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "shiftjis.hpp"
#include "platform/x86real/pc98/keyboard.hpp"
#include "libs/master.lib/master.hpp"
#include "th01/rank.h"
#include "th01/resident.hpp"
#include "th01/hardware/graph.h"
#include "th01/hardware/grp_text.hpp"
#include "th01/hardware/input.hpp"
#include "th01/shiftjis/fns.hpp"
#include "th01/shiftjis/regist.hpp"
#include "th01/formats/scoredat.hpp"

#include "th01/hardware/grppfnfx.cpp"

// Input
// -----

void input_sense(bool16 reset_repeat)
{
	extern uint8_t input_prev[10];
	int group_1, group_2;

	if(reset_repeat == true) {
		input_prev[0] = 0;
		input_prev[1] = 0;
		input_prev[2] = 0;
		input_prev[3] = 0;
		input_prev[4] = 0;
		input_prev[5] = 0;
		input_prev[6] = 0;
		input_prev[7] = 0;
		input_prev[8] = 0;
		input_prev[9] = 0;
		return;
	}

	group_1 = key_sense(7);
	group_2 = key_sense(5);
	group_1 |= key_sense(7);
	group_2 |= key_sense(5);

	input_onchange_bool(0, input_up, (group_1 & K7_ARROW_UP));
	input_onchange_bool(1, input_down, (group_1 & K7_ARROW_DOWN));
	input_onchange_flag(2, input_lr, INPUT_LEFT, (group_1 & K7_ARROW_LEFT));
	input_onchange_flag(3, input_lr, INPUT_RIGHT, (group_1 & K7_ARROW_RIGHT));
	input_onchange_bool(4, input_shot, (group_2 & K5_Z));
	input_onchange_bool(5, input_strike, (group_2 & K5_X));

	input_pause_ok_sense(6, 7, group_1, group_2);
}

#include "th01/hardware/input_rs.cpp"
// -----

#define scoredat_declare() FILE *fp;
#define scoredat_cli() disable()
#define scoredat_sti() enable()
#define scoredat_error(str) printf(str)
#define scoredat_exist(fn) !access(fn, 0)
#define scoredat_create(fn) (fp = fopen(fn, "wb"))
#define scoredat_ropen(fn) (fp = fopen(fn, "rb"))
#define scoredat_read(buf, size) read(fileno(fp), buf, size)
#define scoredat_write(buf, size) write(fileno(fp), buf, size)
#define scoredat_close() fclose(fp)
#include "th01/hiscore/scorelod.cpp"

#include "th01/hiscore/score_nm.cpp"

#define graph_putkanji_fx_declare()
#define graph_putkanji_fx(left, top, fx, kanji) { \
	graph_printf_fx(left, top, fx, "%c%c", (kanji >> 8), (kanji & 0xFF)); \
}

#define graph_printf_s_fx(left, top, fx, str) \
	graph_printf_fx(left, top, fx, "%s", str);

#define regist_route_put(left, top, fx, char_1, char_2) \
	graph_printf_fx(left, top, fx, "%c%c", char_1, char_2);

#define regist_input_timeout_declare()
#define regist_input_timeout_reset()
#define regist_input_timeout_inc()
#define regist_input_timeout_if_reached(then)

inline void regist_bg_put(int16_t stage_num_or_scoredat_constant) {
}

#define regist_title_put( \
	left, stage_num_or_scoredat_constant, ranks, col_and_fx \
) { \
	graph_printf_fx( \
		left, TITLE_TOP, col_and_fx, REGIST_TITLE_WITH_SPACE "%s", ranks[rank] \
	); \
}

#include "th01/hiscore/regist.cpp"

// Global state that is defined here for some reason
// -------------------------------------------------

static int8_t unused; // ZUN bloat
static uint8_t input_prev[10];
// -------------------------------------------------

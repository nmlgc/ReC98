#if (GAME == 5)
	#include "th05/op/start.cpp"
#else
	#include "th04/op/start.cpp"
#endif

#include <string.h>
#include "x86real.h"
#include "shiftjis.hpp"
#include "th01/hardware/egc.h"
#include "th02/v_colors.hpp"
extern "C" {
#include "th04/hardware/grppsafx.h"
#include "th04/formats/cdg.h"
}
#include "th04/sprites/op_cdg.h"

#pragma option -a2

enum main_choice_t {
	MC_GAME,
	MC_EXTRA,
	MC_REGIST_VIEW,
	MC_MUSICROOM,
	MC_OPTION,
	MC_QUIT,
	MC_COUNT,
};

// Coordinates
// -----------
// Terminology:
// • Choice:  The set of selections in a menu.
// • Command: An option-less choice, displayed horizontally centered.
// • Cursor:  The sprites from CAR.CD2.
// • Label:   Any single sprite from SFT2.CD2.

static const pixel_t LABEL_W = 96;
static const pixel_t LABEL_H = 16;

static const pixel_t CURSOR_W = 32;

static const screen_y_t MENU_TOP = ((GAME == 5) ? 250 : 224);

static const screen_x_t COMMAND_LEFT = ((RES_X / 2) - (LABEL_W / 2));

static const pixel_t COMMAND_H = (LABEL_H + 4);
static const screen_x_t COMMAND_CURSOR_LEFT_LEFT = (
	COMMAND_LEFT - (CURSOR_W / 2)
);
static const screen_x_t COMMAND_CURSOR_RIGHT_LEFT = (
	(COMMAND_LEFT + LABEL_W) - (CURSOR_W / 2)
);

static const screen_x_t MENU_MAIN_LEFT = COMMAND_CURSOR_LEFT_LEFT;
static const pixel_t MENU_MAIN_W = (
	COMMAND_CURSOR_RIGHT_LEFT + CURSOR_W - MENU_MAIN_LEFT
);

inline screen_y_t main_choice_top(int sel /* ACTUAL TYPE: main_choice_t */) {
	return (MENU_TOP + (sel * COMMAND_H));
}

static const screen_y_t DESC_TOP = (RES_Y - GLYPH_H);
// -----------

// Colors
// ------

const vc2 COL_ACTIVE   = ((GAME == 5) ? 14 :  8);
const vc2 COL_LOCKED   = ((GAME == 5) ?  2 : 12);
const vc2 COL_DESC     = ((GAME == 5) ?  9 : V_WHITE);
// ------

extern const shiftjis_t* MENU_DESC[];

#define command_put(top, slot) { \
	cdg_put_nocolors_8(COMMAND_LEFT, top, slot); \
}

#define desc_unput_and_put(desc_id) { \
	egc_copy_rect_1_to_0_16(0, DESC_TOP, RES_X, GLYPH_H); \
	graph_putsa_fx_func = FX_WEIGHT_BOLD; \
	graph_putsa_fx( \
		(RES_X - GLYPH_FULL_W - (strlen(MENU_DESC[desc_id]) * GLYPH_HALF_W)), \
		DESC_TOP, \
		COL_DESC, \
		MENU_DESC[desc_id] \
	); \
}

void pascal near main_unput_and_put(int sel, vc2 col)
{
	screen_y_t top = main_choice_top(sel);
	egc_copy_rect_1_to_0_16(MENU_MAIN_LEFT, top, MENU_MAIN_W, LABEL_H);
	grcg_setcolor(GC_RMW, col);
	int desc_id = sel;

	// ZUN bloat: Could have been deduplicated.
	switch(sel) {
	case MC_GAME:
		command_put(main_choice_top(MC_GAME), CDG_MAIN_GAME);
		desc_id = (22 + resident->rank);
		break;
	case MC_EXTRA:
		if(!extra_unlocked) {
			grcg_setcolor(GC_RMW, COL_LOCKED);
		}
		command_put(main_choice_top(MC_EXTRA), CDG_MAIN_EXTRA);
		break;
	case MC_REGIST_VIEW:
		command_put(main_choice_top(MC_REGIST_VIEW), CDG_MAIN_REGIST_VIEW);
		break;
	case MC_MUSICROOM:
		command_put(main_choice_top(MC_MUSICROOM), CDG_MAIN_MUSICROOM);
		break;
	case MC_OPTION:
		command_put(main_choice_top(MC_OPTION), CDG_MAIN_OPTION);
		break;
	case MC_QUIT:
		command_put(main_choice_top(MC_QUIT), CDG_QUIT);
		break;
	}
	grcg_off();

	if(col == COL_ACTIVE) {
		cdg_put_8(COMMAND_CURSOR_LEFT_LEFT,  top, CDG_CURSOR_LEFT);
		cdg_put_8(COMMAND_CURSOR_RIGHT_LEFT, top, CDG_CURSOR_RIGHT);
		desc_unput_and_put(desc_id);
	}
}

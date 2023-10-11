/// Internal dialog code, shared between TH04 and TH05
/// --------------------------------------------------

#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "th04/main/playfld.hpp"
#include "th04/sprites/main_cdg.h"

// A silly TH05 micro-optimization. Could have been 8-bit variables then.
#if (GAME == 5)
	typedef tram_x_t dialog_x_t;
	typedef tram_y_t dialog_y_t;
#else
	typedef screen_x_t dialog_x_t;
	typedef screen_y_t dialog_y_t;
#endif

extern struct {
	dialog_x_t x;
	dialog_y_t y;
} dialog_cursor;

enum dialog_side_t {
	DIALOG_SIDE_PLAYCHAR = 0,
	DIALOG_SIDE_BOSS = 1,

	_dialog_side_t_FORCE_INT16 = 0x7FFF
};

extern dialog_side_t dialog_side;

// Metrics
// -------

#define DIALOG_BOX_W 320
#define DIALOG_BOX_H 48

static const pixel_t DIALOG_MARGIN = 16;
static const pixel_t DIALOG_LINE_W = (PLAYFIELD_W - DIALOG_MARGIN - FACE_W);

static const screen_x_t DIALOG_CURSOR_PLAYCHAR_LEFT = (
	PLAYFIELD_RIGHT - DIALOG_MARGIN - DIALOG_LINE_W
);
static const screen_y_t DIALOG_CURSOR_PLAYCHAR_TOP = (
	PLAYFIELD_BOTTOM - DIALOG_MARGIN - DIALOG_BOX_H
);

static const screen_x_t DIALOG_CURSOR_BOSS_LEFT = (
	PLAYFIELD_LEFT + DIALOG_MARGIN
);
static const screen_y_t DIALOG_CURSOR_BOSS_TOP = (
	DIALOG_CURSOR_PLAYCHAR_TOP - FACE_H
);
// -------

// Restores the [FACE_W]×[FACE_H] pixels starting at (⌊left/8⌋*8, top) on the
// currently active VRAM page with the same pixels from the other VRAM page.
void pascal near dialog_face_unput_8(uscreen_x_t left, uvram_y_t top);

void pascal near dialog_box_fade_in();

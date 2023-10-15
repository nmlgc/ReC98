/// Internal dialog code, shared between TH04 and TH05
/// --------------------------------------------------

#include <stddef.h>
#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "th01/math/subpixel.hpp"
#include "th02/hardware/egc.hpp"
extern "C" {
#include "th02/hardware/frmdelay.h"
#include "th02/hardware/pages.hpp"
#include "th02/formats/tile.hpp"
#include "th03/formats/cdg.h"
}
#include "th04/common.h"
#if (GAME == 4)
	#include "th04/playchar.h"
	#include "th04/formats/map.hpp"
	#include "th04/formats/std.hpp"
#endif
#include "th04/math/motion.hpp"
#include "th04/main/bg.hpp"
#include "th04/main/frames.h"
#include "th04/main/scroll.hpp"
#include "th04/main/phase.hpp"
#include "th04/main/playfld.hpp"
#include "th04/main/boss/boss.hpp"
#include "th04/main/hud/overlay.hpp"
#include "th04/main/stage/stage.hpp"
#include "th04/main/dialog/dialog.hpp"
#include "th04/sprites/main_cdg.h"

// A silly TH05 micro-optimization. Could have been 8-bit variables then.
#if (GAME == 5)
	typedef tram_x_t dialog_x_t;
	typedef tram_y_t dialog_y_t;
#else
	typedef screen_x_t dialog_x_t;
	typedef screen_y_t dialog_y_t;
#endif

inline dialog_x_t to_dialog_x(screen_x_t screen_x) {
	return ((GAME == 5) ? (screen_x / GLYPH_HALF_W) : screen_x);
}
inline dialog_y_t to_dialog_y(screen_y_t screen_y) {
	return ((GAME == 5) ? (screen_y / GLYPH_H) : screen_y);
}

extern struct {
	dialog_x_t x;
	dialog_y_t y;
} dialog_cursor;

enum dialog_side_t {
	SIDE_PLAYCHAR = 0,
	SIDE_BOSS = 1,

	_dialog_side_t_FORCE_INT16 = 0x7FFF
};

extern dialog_side_t dialog_side;

// Metrics
// -------

static const pixel_t BOX_W = 320;
static const pixel_t BOX_H = 48;

static const pixel_t MARGIN = 16;
static const pixel_t TEXT_W = (PLAYFIELD_W - MARGIN - FACE_W);

static const screen_x_t BOX_PLAYCHAR_LEFT = (PLAYFIELD_RIGHT - MARGIN - BOX_W);
static const screen_y_t BOX_PLAYCHAR_TOP = (PLAYFIELD_BOTTOM - MARGIN - BOX_H);
static const screen_x_t TEXT_PLAYCHAR_LEFT = (
	PLAYFIELD_RIGHT - MARGIN - TEXT_W
);
static const screen_y_t TEXT_PLAYCHAR_TOP = BOX_PLAYCHAR_TOP;

static const screen_x_t BOX_BOSS_LEFT = (PLAYFIELD_LEFT + MARGIN);
static const screen_y_t BOX_BOSS_TOP = (BOX_PLAYCHAR_TOP - FACE_H);
static const screen_x_t TEXT_BOSS_LEFT = BOX_BOSS_LEFT;
static const screen_y_t TEXT_BOSS_TOP = BOX_BOSS_TOP;
// -------

// ZUN bloat: Copying the entire playfield is strictly overkill here. Dialog
// sequences are single-buffered and only use the back page to keep the
// playfield/dialog box pixels behind the two faces for unblitting. Note how it
// also doesn't help with removing the dialog box pixels after the sequence,
// because this is called after those were blitted, so it's up to the tile or
// boss renderers to remove them.
void near playfield_copy_front_to_back(void);

// Restores the [FACE_W]×[FACE_H] pixels starting at (⌊left/8⌋*8, top) on the
// currently active VRAM page with the same pixels from the other VRAM page.
void pascal near dialog_face_unput_8(uscreen_x_t left, uvram_y_t top);

// Clears the text in the dialog box that starts at the given coordinate.
#if (GAME == 5)
	void pascal near dialog_box_wipe(dialog_x_t left, dialog_y_t top);
#endif

void near dialog_box_fade_in_animate();

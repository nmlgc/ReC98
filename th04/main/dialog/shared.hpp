/// Internal dialog code, shared between TH04 and TH05
/// --------------------------------------------------

#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "th01/math/subpixel.hpp"
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

static const screen_x_t TEXT_PLAYCHAR_LEFT = (
	PLAYFIELD_RIGHT - MARGIN - TEXT_W
);
static const screen_y_t TEXT_PLAYCHAR_TOP = (PLAYFIELD_BOTTOM - MARGIN - BOX_H);

static const screen_x_t TEXT_BOSS_LEFT = (PLAYFIELD_LEFT + MARGIN);
static const screen_y_t TEXT_BOSS_TOP = (TEXT_PLAYCHAR_TOP - FACE_H);
// -------

// Restores the [FACE_W]×[FACE_H] pixels starting at (⌊left/8⌋*8, top) on the
// currently active VRAM page with the same pixels from the other VRAM page.
void pascal near dialog_face_unput_8(uscreen_x_t left, uvram_y_t top);

void pascal near dialog_box_fade_in();

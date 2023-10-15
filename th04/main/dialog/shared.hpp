/// Internal dialog code, shared between TH04 and TH05
/// --------------------------------------------------

#include <stddef.h>
#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "shiftjis.hpp"
#include "libs/kaja/kaja.h"
#include "th01/math/subpixel.hpp"
#include "th02/hardware/egc.hpp"
extern "C" {
#include "th02/hardware/frmdelay.h"
#include "th02/hardware/pages.hpp"
#include "th02/formats/tile.hpp"
#include "th03/formats/cdg.h"
#if (GAME == 5)
	#include "th05/hardware/input.h"
#else
	#include "th04/hardware/input.h"
#endif
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
extern "C" {
#include "th04/snd/snd.h"
}

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
inline tram_x_t to_tram_x(dialog_x_t dialog_x) {
	return ((GAME == 5) ? dialog_x : (dialog_x / GLYPH_HALF_W));
}
inline tram_y_t to_tram_y(dialog_y_t dialog_y) {
	return ((GAME == 5) ? dialog_y : (dialog_y / GLYPH_H));
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
static const tram_cell_amount_t BOX_TRAM_H = (BOX_H / GLYPH_H);

static const pixel_t MARGIN = 16;
static const pixel_t TEXT_W = (PLAYFIELD_W - MARGIN - FACE_W);
static const tram_cell_amount_t TEXT_TRAM_W = (TEXT_W / GLYPH_HALF_W);

static const screen_x_t BOX_PLAYCHAR_LEFT = (PLAYFIELD_RIGHT - MARGIN - BOX_W);
static const screen_y_t BOX_PLAYCHAR_TOP = (PLAYFIELD_BOTTOM - MARGIN - BOX_H);
static const screen_x_t TEXT_PLAYCHAR_LEFT = (
	PLAYFIELD_RIGHT - MARGIN - TEXT_W
);
static const screen_y_t TEXT_PLAYCHAR_TOP = BOX_PLAYCHAR_TOP;
static const screen_x_t FACE_PLAYCHAR_LEFT = (TEXT_PLAYCHAR_LEFT - FACE_W);
static const screen_y_t FACE_PLAYCHAR_TOP = (
	PLAYFIELD_BOTTOM - MARGIN - FACE_H
);

static const screen_x_t BOX_BOSS_LEFT = (PLAYFIELD_LEFT + MARGIN);
static const screen_y_t BOX_BOSS_TOP = (BOX_PLAYCHAR_TOP - FACE_H);
static const screen_x_t TEXT_BOSS_LEFT = BOX_BOSS_LEFT;
static const screen_y_t TEXT_BOSS_TOP = BOX_BOSS_TOP;
static const screen_x_t FACE_BOSS_LEFT = (TEXT_BOSS_LEFT + TEXT_W);
static const screen_y_t FACE_BOSS_TOP = (FACE_PLAYCHAR_TOP - FACE_H);
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
#else
	#define dialog_box_wipe(left, top) { \
		/* ZUN bloat: Could have been calculated a single time. */ \
		tram_y_t y = to_tram_y(top); \
		while(y < (to_tram_y(top) + BOX_TRAM_H)) { \
			tram_x_t x = to_tram_x(left); \
			while(x < (to_tram_x(left) + TEXT_TRAM_W)) { \
				text_putca(x, y, ' ', TX_WHITE); \
				x++; \
			} \
			y++; \
		} \
	}
#endif

void near dialog_box_fade_in_animate();

inline void dialog_text_put(shiftjis_t* const& text) {
	// ZUN landmine: Since this function is supposed to be called with [text]
	// containing one fullwidth Shift-JIS codepoint followed by a terminating
	// \0, it would have been safer to just assume this format and use
	// text_putnsa() with a width of 2, or even to do a manual Shift-JIS➜JIS
	// conversion followed by a direct write to TRAM. master.lib's TRAM
	// functions follow the JIS X 0208:1997 standard of Shift-JIS that treats
	// 0xE0 to 0xFF inclusive as fullwidth characters, and 0xFF can easily
	// appear as the trail byte of an accidentally misaligned 2-byte pair when
	// modding text. With such a 0xFF interpreted as a lead byte, text_putsa()
	// will treat the terminating \0 as a trail byte, and end up printing a
	// much longer string up to the next properly aligned \0 byte.
	text_putsa(
		to_tram_x(dialog_cursor.x), to_tram_y(dialog_cursor.y), text, TX_WHITE
	);
	dialog_cursor.x += to_dialog_x(GLYPH_FULL_W);
}

#define dialog_delay(speedup_cycle) { \
	if(key_det == INPUT_NONE) { \
		frame_delay(2); \
	} else if(speedup_cycle & 1) { \
		frame_delay(1); \
	} \
}

// Script commands
// ---------------

template <class T> inline void dialog_op_gaiji(const T& c) {
	gaiji_putca(
		to_tram_x(dialog_cursor.x), to_tram_y(dialog_cursor.y), c, TX_WHITE
	);
	dialog_cursor.x += to_dialog_x(GAIJI_W);
}

inline void dialog_op_linebreak(void) {
	dialog_cursor.y += to_dialog_y(GLYPH_H);
	dialog_cursor.x = ((dialog_side == SIDE_PLAYCHAR)
		? to_dialog_x(TEXT_PLAYCHAR_LEFT)
		: to_dialog_x(TEXT_BOSS_LEFT)
	);
}

// ZUN landmine: Every dialog script must call this at some point; at the very
// latest before first blitting the boss sprite via the script itself. It's not
// only needed for freeing up space on the master.lib heap by deallocating any
// stage enemy and midboss, but also to reset [super_patnum] to PAT_STAGE,
// which ensures that the scripted super_entry_bfnt() calls end up writing
// their sprites to the patnums where the hardcoded boss rendering calls expect
// them to be. It should not be the responsibility of the dialog scripts to
// perform manual memory management just to ensure that bosses can render
// themselves with their intended sprites. This could have been done once at
// the beginning of each blocking dialog sequence, which would have eliminated
// the need for a script command.
//
// You might argue that letting scripts call this function allows them to blit
// stage-specific sprites before this call. However, the original games don't
// do that, probably because none of the two dialog interpreters features an
// unblitting command. And *even if they did*, it would have still been cleaner
// to expose the boss-specific super_clean() and super_entry_bfnt() calls as a
// single script command that can then also be called from game code if the
// script didn't do so. Calls like these just are a recipe for crashes,
// *especially* with a parser that processes on-screen text in fixed 2-byte
// chunks and where misaligned ASCII text can therefore easily cause these
// commands to be skipped.
#define dialog_op_super_clean_stage() { \
	super_clean(PAT_STAGE, (PAT_STAGE_last + 1)); \
}
// ---------------

/// Internal dialog code, shared between TH04 and TH05
/// --------------------------------------------------

#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "shiftjis.hpp"
#include "platform/x86real/flags.hpp"
#include "libs/master.lib/master.hpp"
#include "libs/master.lib/pc98_gfx.hpp"
#include "th01/math/subpixel.hpp"
#include "th01/hardware/grcg.hpp"
#include "th02/hardware/egc.hpp"
#include "th02/hardware/frmdelay.h"
#include "th02/hardware/pages.hpp"
#include "th02/formats/tile.hpp"
#include "th03/formats/cdg.h"
#if (GAME == 5)
	#include "th05/hardware/input.h"
#else
	#include "th04/hardware/input.h"
#endif
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
#include "th04/snd/snd.h"

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

#define BOX_TILE_W 16
#define BOX_TILE_H 4
#define BOX_TILE_COUNT 3

#define BOX_TILE_VRAM_W (BOX_TILE_W / BYTE_DOTS)
#define BOX_VRAM_W (BOX_W / BYTE_DOTS)
static const size_t BOX_TILE_SIZE = (BOX_TILE_VRAM_W * BOX_TILE_H);

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

inline void dialog_pre(void) {
	overlay_wipe();
	palette_settone(100);
	graph_accesspage(page_front);
	dialog_box_fade_in_animate();
	playfield_copy_front_to_back();
}

inline void dialog_post(void) {
	graph_accesspage(page_back);
	frame_delay(1);
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

extern const dot_rect_t(BOX_TILE_W, BOX_TILE_H) near BOX_TILES[BOX_TILE_COUNT];

bool near std_update_done(void)
{
	return false;
}

bool near std_update_frames_then_animate_dialog_and_activate_boss_if_done(void)
{
	if((scroll_speed == 0) && (page_back == 1)) {
		#if (GAME == 4)
			if((stage_id == 5) || (stage_id == STAGE_EXTRA)) {
				cdg_free(CDG_EYECATCH);
				std_free();
				map_free();
			}
		#endif

		dialog_animate();

		std_update = std_update_done;
		bg_render_not_bombing = boss_bg_render_func;
		boss_update = boss_update_func;
		boss_fg_render = boss_fg_render_func;
		#if (GAME == 4)
			bgm_title_id = (1 + (stage_id * 2) + 1);
			if((stage_id == 3) && (playchar != PLAYCHAR_REIMU)) {
				// TODO: Calculate as (sizeof(BGM_TITLES) - 1)
				bgm_title_id = 16;
			}
		#endif
		overlay1 = overlay_boss_bgm_update_and_render;
		return true;
	}
	total_std_frames++;
	return false;
}

void pascal near dialog_box_put(uscreen_x_t left, uvram_y_t top, int tile)
{
	#define rows_left	static_cast<pixel_t>(_DX)

	// ZUN bloat: A near pointer would have been much simpler...
	#define offset	static_cast<uint16_t>(_BX)

	grcg_setcolor(GC_RMW, 1);
	_ES = SEG_PLANE_B;
	_AX = left;
	_DX = top;
	_DI = vram_offset_shift_fast(_AX, _DX);

	static_assert(BOX_TILE_SIZE == 8);
	offset = tile;
	offset <<= 3;

	rows_left = BOX_H;

	do {
		static_assert(BOX_TILE_VRAM_W == 2);
		static_assert((BOX_VRAM_W & 1) == 0);
		_CX = (BOX_VRAM_W / 2);
		_AX = *reinterpret_cast<const dots_t(BOX_TILE_W) __ds *>(
			(reinterpret_cast<const uint8_t __ds *>(BOX_TILES) + offset)
		);
		asm { rep stosw };

		// A needlessly clever wraparound check that expects the box tile size
		// to be a power of two.
		static_assert((BOX_TILE_SIZE & (BOX_TILE_SIZE - 1)) == 0);
		offset += BOX_TILE_VRAM_W;

		// Turbo C++ is too smart to emit this instruction with
		// pseudo-registers, turning it into `TEST BL, 7`.
		asm { test bx, (BOX_TILE_SIZE - 1); }
		if(FLAGS_ZERO) {
			offset -= BOX_TILE_SIZE;
		}

		_DI += (ROW_SIZE - BOX_VRAM_W);
	} while(--rows_left);

	grcg_off();

	#undef offset
	#undef rows_left
}

#define egc_rect_interpage_16(bottom_p, w, src_page) { \
	_DX = 0xA6; /* PC-98 VRAM page access port */ \
	_AL = src_page; \
	\
	do { \
		_CX = (w / EGC_REGISTER_DOTS); \
		word_loop: { \
			outportb(_DX, _AL); _AL ^= 1; _BX = *bottom_p; \
			outportb(_DX, _AL); _AL ^= 1; *bottom_p = _BX; \
			bottom_p++; \
			asm { loop word_loop; } \
		} \
	} while(((int16_t)(bottom_p) -= ((RES_X + w) / BYTE_DOTS)) >= 0); \
}

void near playfield_copy_front_to_back(void)
{
	egc_start_copy_noframe();
	_ES = grcg_segment(0, PLAYFIELD_TOP);
	_DI = (((PLAYFIELD_H - 1) * ROW_SIZE) + PLAYFIELD_VRAM_LEFT);
	egc_rect_interpage_16(
		reinterpret_cast<egc_temp_t __es *>(_DI), PLAYFIELD_W, page_front
	);

	// The above call returns the VRAM page access port in DX, [page_front] in
	// AL, and ![page_front] as the accessed page. Since the caller expects to
	// access the other one, we should switch back here, and this single-byte
	// instruction is all it takes as a result.
	// (Technically, it's not necessary since the accessed page only matters
	// for face blitting and dialog_face_unput_8()'s back→front copy will
	// override the accessed page anyway, but it's still good form. Kudos to
	// ZUN for doing the correct thing for once!)
	outportb(_DX, _AL);

	egc_off();
}

void pascal near dialog_face_unput_8(uscreen_x_t left, uvram_y_t top)
{
	egc_start_copy_noframe();

	// ZUN bloat: _ES = grcg_segment(0, top);
	_AX = top;
	_BX = _AX;
	_ES = (SEG_PLANE_B + ((_AX * 4) + _BX));

	_DI = ((FACE_H - 1) * ROW_SIZE);
	_DI += (left / BYTE_DOTS);
	egc_rect_interpage_16(
		reinterpret_cast<egc_temp_t __es *>(_DI), FACE_W, page_back
	);
	egc_off();
}

#if (GAME == 5)
void pascal near dialog_box_wipe(dialog_x_t left, dialog_y_t top)
{
	for(dialog_y_t y = top; y < (top + to_dialog_y(BOX_H)); y++) {
		for(dialog_x_t x = left; x < (left + to_dialog_x(TEXT_W)); x++) {
			text_putca(x, y, ' ', TX_WHITE);
		}
	}
}
#endif

void near dialog_box_fade_in_animate(void)
{
	vsync_Count1 = 0; // ZUN bloat: Automatically done in frame_delay().
	for(int i = 0; i < BOX_TILE_COUNT; i++) {
		dialog_box_put(BOX_BOSS_LEFT, BOX_BOSS_TOP, i);
		dialog_box_put(BOX_PLAYCHAR_LEFT, BOX_PLAYCHAR_TOP, i);
		frame_delay(12);
	}
}

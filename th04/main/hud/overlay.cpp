#include <string.h>
#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "master.hpp"
#include "th04/score.h"
#include "th01/math/subpixel.hpp"
#include "th04/gaiji/gaiji.h"
extern "C" {
#include "th04/formats/bb.h"
#include "th04/hardware/grcg.h"
#include "th04/math/motion.hpp"
#include "th04/main/null.hpp"
#include "th04/main/playfld.hpp"
#include "th04/main/tile/tile.hpp"
#include "th04/main/scroll.hpp"
}
#include "th04/main/hud/hud.h"
#include "th04/main/hud/overlay.hpp"
#include "th04/main/stage/stage.hpp"

#if (GAME == 4)
	#include "th04/playchar.h"
#endif

// See tile.hpp for the reason this declaration is necessary
extern "C" void pascal near tiles_invalidate_around(
	subpixel_t center_y, subpixel_t center_x
);

#define gaiji_putsa(left, y, str, atrb) \
	gaiji_putsa(left, y, reinterpret_cast<const char *>(str), atrb);

// MODDERS: Keep this up-to-date!
static const unsigned int POPUP_STRING_MAX_LEN = 8;

extern const gaiji_th04_t* POPUP_STRINGS[];

extern const char* PLAYFIELD_BLANK_ROW;

/// Stage and BGM titles
/// --------------------

extern unsigned char boss_bgm_frame;
extern unsigned char titles_frame;
extern unsigned char dissolve_sprite;
extern int stage_title_len;
extern int stage_bgm_title_len;
extern int boss_bgm_title_len;
#if (GAME == 5)
	extern char *stage_title;
	extern char *stage_bgm_title;
	extern char *boss_bgm_title;
#else
	extern unsigned char stage_title_id;
	extern const char* BGM_TITLES[];
	extern const char* STAGE_TITLES[];
	#define stage_title (STAGE_TITLES[stage_title_id])
	#define stage_bgm_title (BGM_TITLES[bgm_title_id])
	#define boss_bgm_title stage_bgm_title
#endif
extern char gStage_1[8];
extern const char gFINAL_STAGE[12];
extern const char gEXTRA_STAGE[12];

#define STAGE_NUM_CENTER_Y 168
#define STAGE_TITLE_CENTER_Y 200
#define BGM_CENTER_Y 360
static const tram_y_t POPUP_TRAM_Y = (PLAYFIELD_TRAM_TOP + 1);

#define POPUP_FRAMES_UNTIL_OUT_DISSOLVE 192

#define vram_y_to_tram(y) (PLAYFIELD_TRAM_TOP + (y / GLYPH_H))

#define STAGE_NUM_W ((sizeof(gStage_1) - 1) * GAIJI_TRAM_W)
#define STAGE_NUM_FE_W ((sizeof(gFINAL_STAGE) - 1) * GAIJI_TRAM_W)
#define STAGE_NUM_TRAM_LEFT (PLAYFIELD_TRAM_CENTER_X - (STAGE_NUM_W / 2))
#define STAGE_NUM_FE_TRAM_LEFT (PLAYFIELD_TRAM_CENTER_X - (STAGE_NUM_FE_W / 2))

#define STAGE_NUM_TRAM_CENTER_Y (vram_y_to_tram(STAGE_NUM_CENTER_Y))
#define STAGE_TITLE_TRAM_CENTER_Y (vram_y_to_tram(STAGE_TITLE_CENTER_Y))
#define BGM_TRAM_Y (vram_y_to_tram(BGM_CENTER_Y))
#define BGM_TRAM_RIGHT (PLAYFIELD_TRAM_RIGHT - 1)

inline tram_x_t bgm_note_tram_left(int title_len)
{
	return ((BGM_TRAM_RIGHT - (GAIJI_TRAM_W + 1)) - title_len);
}
inline tram_x_t bgm_title_tram_left(int title_len)
{
	return (BGM_TRAM_RIGHT - title_len);
}

// Draws [dissolve_sprite] onto the graphics RAM along a row of text
// with the given halfwidth length, starting at the given text RAM X column
// and playfield-space Y position.
// Assumes that the GRCG is active, and set to the intended color.
void pascal near dissolve_put(tram_x_t tram_left, subpixel_t top, int ank_len)
{
	vram_x_t vram_left = tram_left;
	vram_x_t vram_right = ank_len;

	vram_left--;
	vram_right += vram_left;

	vram_right *= GLYPH_HALF_W;
	vram_left *= GLYPH_HALF_W;
	top = scroll_subpixel_y_to_vram_seg1(top);

	_ES = SEG_PLANE_B;
	while(vram_left < vram_right) {
		bb_txt_put_8(vram_left, top, dissolve_sprite);
		vram_left += GLYPH_FULL_W;
	}
}

void near overlay_titles_invalidate(void)
{
	unsigned char frames = (titles_frame + boss_bgm_frame);
	if(frames == 0) {
		return;
	}
	if(frames >= POPUP_FRAMES_UNTIL_OUT_DISSOLVE || frames <= 34) {
		tile_invalidate_box.x = PLAYFIELD_W;
		tile_invalidate_box.y = BB_TXT_H;
		tiles_invalidate_around_vram_xy(PLAYFIELD_W / 2, STAGE_NUM_CENTER_Y);
		tiles_invalidate_around_vram_xy(PLAYFIELD_W / 2, STAGE_TITLE_CENTER_Y);
		tiles_invalidate_around_vram_xy(PLAYFIELD_W / 2, BGM_CENTER_Y);
	}
}

inline void bgm_note_dissolve_put(const int& len)
{
	dissolve_put(bgm_note_tram_left(len), to_sp(BGM_CENTER_Y), GAIJI_TRAM_W);
}

inline void bgm_title_dissolve_put(const int& len)
{
	dissolve_put(bgm_title_tram_left(len), to_sp(BGM_CENTER_Y), len);
}

#define bgm_string_put(str, len) \
	gaiji_putca(bgm_note_tram_left(len), BGM_TRAM_Y, 3, TX_YELLOW); \
	text_putsa(bgm_title_tram_left(len), BGM_TRAM_Y, str, TX_WHITE);

inline void titles_dissolve_put(const int& bgm_len)
{
	grcg_setmode_rmw_seg1();

	grcg_setcolor_direct_seg1(11); // Yellow
	if(stage_id < 5) {
		dissolve_put(
			STAGE_NUM_TRAM_LEFT, to_sp(STAGE_NUM_CENTER_Y), STAGE_NUM_W
		);
	} else {
		dissolve_put(
			STAGE_NUM_FE_TRAM_LEFT, to_sp(STAGE_NUM_CENTER_Y), STAGE_NUM_FE_W
		);
	}
	bgm_note_dissolve_put(bgm_len);

	grcg_setcolor_direct_seg1(15); // White
	bgm_title_dissolve_put(bgm_len);
	dissolve_put(
		(PLAYFIELD_TRAM_CENTER_X - (stage_title_len / 2)),
		to_sp(STAGE_TITLE_CENTER_Y),
		stage_title_len
	);
	grcg_off();
}

#define titles_strings_put(bgm_str, bgm_len) \
	gStage_1[6] = static_cast<gaiji_th04_t>(gb_1_ + stage_id); \
	if(stage_id == 5) { \
		gaiji_putsa( \
			STAGE_NUM_FE_TRAM_LEFT, \
			STAGE_NUM_TRAM_CENTER_Y, \
			gFINAL_STAGE, \
			TX_YELLOW \
		); \
	} else if(stage_id == 6) { \
		gaiji_putsa( \
			STAGE_NUM_FE_TRAM_LEFT, \
			STAGE_NUM_TRAM_CENTER_Y, \
			gEXTRA_STAGE, \
			TX_YELLOW \
		); \
	} else { \
		gaiji_putsa( \
			STAGE_NUM_TRAM_LEFT, STAGE_NUM_TRAM_CENTER_Y, gStage_1, TX_YELLOW \
		); \
	} \
	text_putsa( \
		(PLAYFIELD_TRAM_CENTER_X - (stage_title_len / 2)), \
		STAGE_TITLE_TRAM_CENTER_Y, \
		stage_title, \
		TX_WHITE \
	); \
	bgm_string_put(bgm_str, bgm_len);

static inline void boss_bgm_dissolve_put(const int& bgm_len)
{
	grcg_setmode_rmw_seg1();

	grcg_setcolor_direct_seg1(11);	// Yellow
	bgm_note_dissolve_put(bgm_len);

	grcg_setcolor_direct_seg1(15);	// White
	bgm_title_dissolve_put(bgm_len);

	grcg_off();
}

#define dissolve_in_update(frame) \
	if((frame & 3) == 0) { \
		if(frame != 0) { \
			dissolve_sprite++; \
			if(dissolve_sprite >= (BB_TXT_IN_SPRITE + BB_TXT_IN_CELS)) { \
				dissolve_sprite = 0; \
			} \
		} \
	}

#define dissolve_out_update(frame) \
	if(frame == POPUP_FRAMES_UNTIL_OUT_DISSOLVE) { \
		playfield_tram_wipe(); \
		dissolve_sprite = BB_TXT_OUT_SPRITE; \
	} else { \
		if((frame & 1) == 0) { \
			dissolve_sprite++; \
		} \
	}

void pascal near overlay_titles_update_and_render(void)
{
	#define frames titles_frame
	if(frames >= POPUP_FRAMES_UNTIL_OUT_DISSOLVE) {
		dissolve_out_update(frames);
		if(dissolve_sprite >= (BB_TXT_OUT_SPRITE + BB_TXT_OUT_CELS)) {
			if(frames & 1) {
				overlay_text = nullfunc_near;
				frames = 0;
				dissolve_sprite = 0;
				return;
			}
		} else {
			titles_dissolve_put(stage_bgm_title_len);
		}
	} else {
		if(frames == 0) {
			dissolve_sprite = BB_TXT_IN_SPRITE;
			#if (GAME == 4)
				stage_title_id = (stage_id + 1);
				bgm_title_id = ((stage_id * 2) + 1);
				if(stage_id == 0 && playchar == PLAYCHAR_REIMU) {
					stage_title_id = 0;
					bgm_title_id = 0;
				}
			#endif
			stage_title_len = strlen(stage_title);
			stage_bgm_title_len = strlen(stage_bgm_title);
		}
		if(dissolve_sprite >= BB_TXT_IN_SPRITE) {
			if(dissolve_sprite == (BB_TXT_IN_SPRITE + 6)) {
				titles_strings_put(stage_bgm_title, stage_bgm_title_len);
			}
			titles_dissolve_put(stage_bgm_title_len);
			dissolve_in_update(frames);
		}
	}
	frames++;
	#undef frames
}

void pascal near overlay_boss_bgm_update_and_render(void)
{
	#define frames boss_bgm_frame
	if(frames >= POPUP_FRAMES_UNTIL_OUT_DISSOLVE) {
		dissolve_out_update(frames);
		if(dissolve_sprite >= (BB_TXT_OUT_SPRITE + BB_TXT_OUT_CELS)) {
			if(frames & 1) {
				overlay_text = nullfunc_near;
				frames = 0;
				return;
			}
		} else {
			boss_bgm_dissolve_put(boss_bgm_title_len);
		}
	} else {
		if(frames == 0) {
			dissolve_sprite = BB_TXT_IN_SPRITE;
			boss_bgm_title_len = strlen(boss_bgm_title);
		}
		if(dissolve_sprite >= BB_TXT_IN_SPRITE) {
			if(dissolve_sprite == (BB_TXT_IN_SPRITE + 6)) {
				bgm_string_put(boss_bgm_title, boss_bgm_title_len);
			}
			boss_bgm_dissolve_put(boss_bgm_title_len);
			dissolve_in_update(frames);
		}
	}
	frames++;
	#undef frames
}
/// --------------------

// Popup messages for common gameplay events, shown at the top of the playfield
// ----------------------------------------------------------------------------

const unsigned char POPUP_DURATION = 128;

inline void line_wipe(tram_y_t y) {
	text_putsa(PLAYFIELD_TRAM_LEFT, y, PLAYFIELD_BLANK_ROW, TX_WHITE);
}

inline void near popup_put_points(const unsigned long &points) {
	#if (GAME == 5)
		hud_points_put(PLAYFIELD_TRAM_CENTER_X, POPUP_TRAM_Y, points);
	#else
		void pascal near popup_put_points_th04(unsigned long points);
		popup_put_points_th04(points);
	#endif
}

void pascal near overlay_popup_update_and_render(void)
{
	#define frame	popup_frame
	#define gaiji_len	popup_gaiji_len
	#define id_cur	popup_id_cur
	#define dest_reached	popup_dest_reached
	#define shiftbuf	popup_shiftbuf
	#define cur_tram_left	popup_cur_tram_left
	#define dest_tram_left	popup_dest_tram_left

	#define cur_tram_right() \
		(cur_tram_left + (gaiji_len * GAIJI_TRAM_W))

	extern unsigned char frame;
	extern int gaiji_len;
	extern popup_id_t id_cur;
	extern bool dest_reached;

	// Buffer used for shifting in the popup text from the right of the
	// playfield. Only used while the text isn't fully visible.
	extern gaiji_th04_t shiftbuf[POPUP_STRING_MAX_LEN + 1];

	extern tram_x_t cur_tram_left;
	extern tram_x_t dest_tram_left;

	unsigned char i;

	// Make sure that the current popup is shown for at least 64 frames before
	// switching to a new one. Of course, it would have been cleaner to keep
	// popup events in a queue instead - with this approach, you only see the
	// last popup that happened within 64 frames, and any other potential
	// popups happening during that time are ignored.
	// Also note how the lack of a POPUP_NONE constant is the only reason why
	// this function has to be conditionally executed via the [popup] function
	// pointer...
	if((overlay_popup_id_new != id_cur) && (frame >= (POPUP_DURATION / 2))) {
		line_wipe(POPUP_TRAM_Y);
		line_wipe(BGM_TRAM_Y); // Why though?
		frame = 0; // Re-initialize
	}
	if(frame == 0) {
		id_cur = overlay_popup_id_new;
		for(i = 0; i < (sizeof(shiftbuf) - 1); i++) {
			shiftbuf[i] = g_EMPTY;
		}
		gaiji_len = strlen(
			reinterpret_cast<const char *>(POPUP_STRINGS[id_cur])
		);
		shiftbuf[gaiji_len] = g_NULL;
		cur_tram_left = (PLAYFIELD_TRAM_RIGHT - (gaiji_len * GAIJI_TRAM_W));
		if(overlay_popup_id_new != POPUP_ID_BONUS) {
			// Technically * (GAIJI_TRAM_W / 2), since the popup is centered.
			dest_tram_left = (PLAYFIELD_TRAM_CENTER_X - gaiji_len);
		} else {
			// This one is off-center anyway, though.
			dest_tram_left = (PLAYFIELD_TRAM_CENTER_X - 12);
		}
		dest_reached = false;
	}

	if(frame >= POPUP_DURATION) {
		line_wipe(POPUP_TRAM_Y);
		frame = 0;
		overlay_popup = nullfunc_near;
		return;
	}

	if(frame < (gaiji_len - 1)) {
		// Shift in a new gaiji
		for(i = 0; i < (gaiji_len - 1); i++) {
			shiftbuf[i] = shiftbuf[i + 1];
		}
		shiftbuf[gaiji_len - 1] = POPUP_STRINGS[id_cur][frame];
		gaiji_putsa(cur_tram_left, POPUP_TRAM_Y, shiftbuf, TX_WHITE);
	} else if(cur_tram_left > dest_tram_left) {
		// (Should really be !=, but whatever.) Use the full, unshifted string
		gaiji_putsa(
			cur_tram_left, POPUP_TRAM_Y, POPUP_STRINGS[id_cur], TX_WHITE
		);
		if(cur_tram_right() <= (PLAYFIELD_TRAM_RIGHT - GAIJI_TRAM_W)) {
			text_putca(cur_tram_right(), POPUP_TRAM_Y, '  ', TX_WHITE);
		}
		// "If I'd move at 1 TRAM column per frame, I'd have to clip the
		// overhanging second half of the last gaiji. Nah, let's just go twice
		// the speed :zunpet:"
		popup_cur_tram_left -= 2;
	} else {
		if(!dest_reached) {
			dest_reached = true;
			line_wipe(POPUP_TRAM_Y);
		}
		gaiji_putsa(
			dest_tram_left, POPUP_TRAM_Y, POPUP_STRINGS[id_cur], TX_WHITE
		);
		if(id_cur == POPUP_ID_BONUS) {
			popup_put_points(overlay_popup_bonus);
		}
	}
	frame++;

	#undef cur_tram_right
	#undef dest_tram_left
	#undef cur_tram_left
	#undef shiftbuf
	#undef dest_reached
	#undef id_cur
	#undef gaiji_len
	#undef frame
}

#if (GAME == 4)
	void pascal near popup_put_points_th04(unsigned long points)
	{
		int i;
		bool16 past_leading_zeroes;
		gaiji_th04_t buf[SCORE_DIGITS + 1];
		unsigned long divisor = 1000000; // Must match SCORE_DIGITS!
		unsigned long digit;

		i = 0;
		past_leading_zeroes = false;
		while(divisor > 1) {
			digit = (points / divisor);
			points = (points % divisor);
			past_leading_zeroes |= digit;
			if(past_leading_zeroes) {
				buf[i] = static_cast<gaiji_th04_t>(gb_0_ + digit);
			} else {
				buf[i] = g_EMPTY;
			}
			divisor /= 10;
			i++;
		}
		// (ones)
		buf[SCORE_DIGITS - 2] = static_cast<gaiji_th04_t>(gb_0_ + points);
		buf[SCORE_DIGITS - 1] = gb_0_;  // ("continues used" digit)
		buf[SCORE_DIGITS - 0] = g_NULL; // (null terminator)

		gaiji_putsa(PLAYFIELD_TRAM_CENTER_X, POPUP_TRAM_Y, buf, TX_WHITE);
	}
#endif
// ----------------------------------------------------------------------------

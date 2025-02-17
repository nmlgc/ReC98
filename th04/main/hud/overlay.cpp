#pragma option -zPmain_01

#include <string.h>
#include "shiftjis.hpp"
#include "libs/master.lib/pc98_gfx.hpp"
#include "th01/hardware/grcg.hpp"
#include "th02/v_colors.hpp"
#include "th04/hardware/grcg.hpp"
#include "th04/formats/bb.h"
#include "th04/main/null.hpp"
#include "th04/main/playfld.hpp"
#include "th04/main/tile/tile.hpp"
#include "th04/main/scroll.hpp"
#include "th04/main/hud/hud.hpp"
#include "th04/main/hud/overlay.hpp"
#include "th04/main/stage/stage.hpp"

#if (GAME == 5)
	#include "th05/resident.hpp"
#else
	#include "th04/playchar.h"
	#include "th04/resident.hpp"
#endif

// See tile.hpp for the reason why this declaration is necessary
extern "C" void pascal near tiles_invalidate_around(
	subpixel_t center_y, subpixel_t center_x
);

#define gaiji_putsa(left, y, str, atrb) \
	gaiji_putsa(left, y, reinterpret_cast<const char *>(str), atrb);

// String constants and state
// --------------------------

extern union {
	unsigned char in_frames;
	unsigned char out_time;
} overlay_fade; // = 0
extern unsigned char boss_bgm_frame; // = 0
extern unsigned char popup_frame; // = 0

extern gaiji_th04_t gStage_1[8];
extern const gaiji_th04_t gFINAL_STAGE[12];
extern const gaiji_th04_t gEXTRA_STAGE[12];
extern const gaiji_th04_t gpHISCORE_ENTRY[];
extern const gaiji_th04_t gpEXTEND[];
extern const gaiji_th04_t gpBONUS[];
extern const gaiji_th04_t gpFULL_POWERUP[];
#if (GAME == 5)
	extern const gaiji_th04_t gpDREAMBONUS_MAX[];
#endif

// MODDERS: Keep this up-to-date!
static const ushiftjis_kanji_amount_t POPUP_STRING_MAX_LEN = 8;
extern const gaiji_th04_t* POPUP_STRINGS[];

extern unsigned char dissolve_sprite; // = 0

extern int stage_title_len;
extern int stage_bgm_title_len;
#if (GAME == 4)
	extern unsigned char stage_title_id;
#endif

// Pre-declarations, since we want some of the data to be function-static, but
// still need to preserve the original order
extern unsigned char titles_frame;
#if (GAME == 4)
	extern const shiftjis_t* BGM_TITLES[];
	extern const shiftjis_t* STAGE_TITLES[];
	#define stage_title (STAGE_TITLES[stage_title_id])
	#define stage_bgm_title (BGM_TITLES[bgm_title_id])
	#define boss_bgm_title stage_bgm_title
#endif
// --------------------------

// Coordinates
// -----------

const subpixel_t STAGE_NUM_CENTER_Y = TO_SP((PLAYFIELD_H / 2) - GLYPH_H);
const subpixel_t STAGE_TITLE_CENTER_Y = TO_SP((PLAYFIELD_H / 2) + GLYPH_H);
const subpixel_t BGM_CENTER_Y = TO_SP(PLAYFIELD_H - (GLYPH_H / 2));
const tram_y_t POPUP_TRAM_Y = (PLAYFIELD_TRAM_TOP + 1);

const int POPUP_FRAMES_UNTIL_OUT_DISSOLVE = 192;

#define vram_y_to_tram(y) (PLAYFIELD_TRAM_TOP + (TO_PIXEL(y) / GLYPH_H))

const shiftjis_kanji_amount_t STAGE_NUM_W = (
	(sizeof(gStage_1) - 1) * GAIJI_TRAM_W
);
const shiftjis_kanji_amount_t STAGE_NUM_FE_W = (
	(sizeof(gFINAL_STAGE) - 1) * GAIJI_TRAM_W
);
const tram_x_t STAGE_NUM_TRAM_LEFT = (
	PLAYFIELD_TRAM_CENTER_X - (STAGE_NUM_W / 2)
);
const tram_x_t STAGE_NUM_FE_TRAM_LEFT = (
	PLAYFIELD_TRAM_CENTER_X - (STAGE_NUM_FE_W / 2)
);

const tram_y_t STAGE_NUM_TRAM_CENTER_Y = vram_y_to_tram(STAGE_NUM_CENTER_Y);
const tram_y_t STAGE_TITLE_TRAM_CENTER_Y = vram_y_to_tram(STAGE_TITLE_CENTER_Y);
const tram_y_t BGM_TRAM_Y = vram_y_to_tram(BGM_CENTER_Y);
const tram_x_t BGM_TRAM_RIGHT = (PLAYFIELD_TRAM_RIGHT - 1);
// -----------

// Overlay fills
// -------------

void near overlay_wipe(void)
{
	overlay_fill(TX_WHITE);
}

void near overlay_black(void)
{
	overlay_fill(TX_BLACK | TX_REVERSE);
}
// -------------

// Stage transitions
// -----------------

#define overlay_fade_put(frames) { \
	if((frames % OVERLAY_FADE_INTERVAL) == 0) { \
		unsigned char cel_num = (frames / OVERLAY_FADE_INTERVAL); \
		if(cel_num != 0) { \
			tram_y_t y = PLAYFIELD_TRAM_TOP; \
			while(y < PLAYFIELD_TRAM_BOTTOM) { \
				tram_y_t x = PLAYFIELD_TRAM_LEFT; \
				while(x < PLAYFIELD_TRAM_RIGHT) { \
					gaiji_putca( \
						x, y, ((g_OVERLAY_FADE_last + 1) - cel_num), TX_BLACK \
					); \
					x += GAIJI_TRAM_W; \
				} \
				y++; \
			} \
		} \
	} \
}

void pascal near overlay_stage_enter_update_and_render(void)
{
	if(overlay_fade.in_frames >= OVERLAY_FADE_DURATION) {
		overlay_wipe();
		if(
			(resident->demo_num == 0) ||
			((GAME == 5) && (resident->demo_num == 5))
		) {
			overlay1 = overlay_titles_update_and_render;
		} else {
			extern const gaiji_th04_t gDEMO_PLAY[10];
			overlay1 = nullfunc_near;
			gaiji_putsa(
				// Off-center...
				((PLAYFIELD_TRAM_CENTER_X - 1) - (sizeof(gDEMO_PLAY) - 1)),
				PLAYFIELD_TRAM_CENTER_Y,
				gDEMO_PLAY,
				(TX_YELLOW | TX_BLINK)
			);
		}
		titles_frame = 0;
		return;
	}
	overlay_fade_put(overlay_fade.in_frames);
	overlay_fade.in_frames++;
}

void pascal near overlay_stage_leave_update_and_render(void)
{
	if(overlay_fade.out_time == 0) {
		overlay_black();
		overlay1 = nullfunc_near;
		return;
	}
	overlay_fade.out_time--;
	overlay_fade_put(overlay_fade.out_time);
}
// -----------------

// Stage and BGM titles
// --------------------

inline tram_x_t bgm_note_tram_left(int title_len) {
	return ((BGM_TRAM_RIGHT - (GAIJI_TRAM_W + 1)) - title_len);
}
inline tram_x_t bgm_title_tram_left(int title_len) {
	return (BGM_TRAM_RIGHT - title_len);
}

// Draws [dissolve_sprite] onto the graphics RAM along a row of text
// with the given halfwidth length, starting at the given text RAM X column
// and playfield-space Y position.
// Assumes that the GRCG is active, and set to the intended color.
void pascal near dissolve_put(
	tram_x_t tram_left, subpixel_t top, shiftjis_ank_amount_t ank_len
)
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
		tiles_invalidate_around_xy(to_sp(PLAYFIELD_W / 2), STAGE_NUM_CENTER_Y);
		tiles_invalidate_around_xy(
			to_sp(PLAYFIELD_W / 2), STAGE_TITLE_CENTER_Y
		);
		tiles_invalidate_around_xy(to_sp(PLAYFIELD_W / 2), BGM_CENTER_Y);
	}
}

inline void bgm_note_dissolve_put(const int& len) {
	dissolve_put(bgm_note_tram_left(len), BGM_CENTER_Y, GAIJI_TRAM_W);
}
inline void bgm_title_dissolve_put(const int& len) {
	dissolve_put(bgm_title_tram_left(len), BGM_CENTER_Y, len);
}

#define bgm_string_put(str, len) \
	gaiji_putca(bgm_note_tram_left(len), BGM_TRAM_Y, 3, TX_YELLOW); \
	text_putsa(bgm_title_tram_left(len), BGM_TRAM_Y, str, TX_WHITE);

inline void titles_dissolve_put(const int& bgm_len) {
	grcg_setmode_rmw();

	grcg_setcolor_direct(11); // Yellow
	if(stage_id < 5) {
		dissolve_put(STAGE_NUM_TRAM_LEFT, STAGE_NUM_CENTER_Y, STAGE_NUM_W);
	} else {
		dissolve_put(
			STAGE_NUM_FE_TRAM_LEFT, STAGE_NUM_CENTER_Y, STAGE_NUM_FE_W
		);
	}
	bgm_note_dissolve_put(bgm_len);

	grcg_setcolor_direct(V_WHITE);
	bgm_title_dissolve_put(bgm_len);
	dissolve_put(
		(PLAYFIELD_TRAM_CENTER_X - (stage_title_len / 2)),
		STAGE_TITLE_CENTER_Y,
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

inline void boss_bgm_dissolve_put(const int& bgm_len) {
	grcg_setmode_rmw();

	grcg_setcolor_direct(11);	// Yellow
	bgm_note_dissolve_put(bgm_len);

	grcg_setcolor_direct(V_WHITE);
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
		overlay_wipe(); \
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
				overlay1 = nullfunc_near;
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
	extern int boss_bgm_title_len;

	#define frames boss_bgm_frame
	if(frames >= POPUP_FRAMES_UNTIL_OUT_DISSOLVE) {
		dissolve_out_update(frames);
		if(dissolve_sprite >= (BB_TXT_OUT_SPRITE + BB_TXT_OUT_CELS)) {
			if(frames & 1) {
				overlay1 = nullfunc_near;
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
// --------------------

// Popup messages for common gameplay events, shown at the top of the playfield
// ----------------------------------------------------------------------------

const unsigned char POPUP_DURATION = 128;

inline void line_wipe(tram_y_t y) {
	overlay_line_fill(y, TX_WHITE);
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
	#define gaiji_len	popup_gaiji_len
	#define id_cur	popup_id_cur
	#define dest_reached	popup_dest_reached
	#define shiftbuf	popup_shiftbuf
	#define cur_tram_left	popup_cur_tram_left
	#define dest_tram_left	popup_dest_tram_left

	#define cur_tram_right() \
		(cur_tram_left + (gaiji_len * GAIJI_TRAM_W))

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
	if(
		(overlay_popup_id_new != id_cur) &&
		(popup_frame >= (POPUP_DURATION / 2))
	) {
		line_wipe(POPUP_TRAM_Y);
		line_wipe(BGM_TRAM_Y); // Why though?
		popup_frame = 0; // Re-initialize
	}
	if(popup_frame == 0) {
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

	if(popup_frame >= POPUP_DURATION) {
		line_wipe(POPUP_TRAM_Y);
		popup_frame = 0;
		overlay2 = nullfunc_near;
		return;
	}

	if(popup_frame < (gaiji_len - 1)) {
		// Shift in a new gaiji
		for(i = 0; i < (gaiji_len - 1); i++) {
			shiftbuf[i] = shiftbuf[i + 1];
		}
		shiftbuf[gaiji_len - 1] = POPUP_STRINGS[id_cur][popup_frame];
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
		cur_tram_left -= GAIJI_TRAM_W;
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
	popup_frame++;

	#undef cur_tram_right
	#undef dest_tram_left
	#undef cur_tram_left
	#undef shiftbuf
	#undef dest_reached
	#undef id_cur
	#undef gaiji_len
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

// TODO: These need to be turned into definitions once we can.
extern unsigned char bgm_title_id;
extern popup_id_t overlay_popup_id_new;
extern nearfunc_t_near overlay1;
extern nearfunc_t_near overlay2;
extern unsigned char titles_frame;
extern unsigned long overlay_popup_bonus;
#if (GAME == 5)
	extern shiftjis_t *stage_title;
	extern shiftjis_t *stage_bgm_title;
	extern shiftjis_t *boss_bgm_title;
#endif

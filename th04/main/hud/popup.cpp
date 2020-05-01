#include "ReC98.h"
#include "th03/math/subpixel.hpp"
#include "th04/gaiji/gaiji.h"
#include "th04/formats/bb.h"
#include "th04/hardware/grcg.h"
#include "th04/math/motion.hpp"
#include "th04/main/null.hpp"
#include "th04/main/playfld.h"
#include "th04/main/tile.hpp"
#include "th04/main/scroll.hpp"
#include "th04/main/hud/popup.hpp"
#include "th04/main/stage/stage.hpp"
#include "th04/main/item/items.hpp"

#if (GAME == 4)
	#include "th04/chars.h"
#endif

// See tile.hpp for the reason this declaration is necessary
void pascal near tiles_invalidate_around(
	subpixel_t center_y, subpixel_t center_x
);

/// Stage and BGM titles
/// --------------------
extern unsigned char popup_dissolve_sprite;
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

#define POPUP_FRAMES_UNTIL_OUT_DISSOLVE 192

#define vram_y_to_tram(y) (PLAYFIELD_TRAM_Y + (y / GLYPH_H))

#define STAGE_NUM_W ((sizeof(gStage_1) - 1) * GAIJI_TRAM_W)
#define STAGE_NUM_FE_W ((sizeof(gFINAL_STAGE) - 1) * GAIJI_TRAM_W)
#define STAGE_NUM_TRAM_LEFT (PLAYFIELD_TRAM_CENTER_X - (STAGE_NUM_W / 2))
#define STAGE_NUM_FE_TRAM_LEFT (PLAYFIELD_TRAM_CENTER_X - (STAGE_NUM_FE_W / 2))

#define STAGE_NUM_TRAM_CENTER_Y (vram_y_to_tram(STAGE_NUM_CENTER_Y))
#define STAGE_TITLE_TRAM_CENTER_Y (vram_y_to_tram(STAGE_TITLE_CENTER_Y))
#define BGM_TRAM_CENTER_Y (vram_y_to_tram(BGM_CENTER_Y))
#define BGM_TRAM_RIGHT (PLAYFIELD_TRAM_RIGHT - 1)

inline int bgm_note_tram_left(int title_len)
{
	return ((BGM_TRAM_RIGHT - (GAIJI_TRAM_W + 1)) - title_len);
}
inline int bgm_title_tram_left(int title_len)
{
	return (BGM_TRAM_RIGHT - title_len);
}

// Draws [popup_dissolve_sprite] onto the graphics RAM along a row of text
// with the given halfwidth length, starting at the given text RAM X column
// and playfield-space Y position.
// Assumes that the GRCG is active, and set to the intended color.
void pascal near popup_dissolve_put(int tram_left, subpixel_t top, int ank_len)
{
	int vram_left = tram_left;
	int vram_right = ank_len;

	vram_left--;
	vram_right += vram_left;

	vram_right *= GLYPH_HALF_W;
	vram_left *= GLYPH_HALF_W;
	top = scroll_subpixel_y_to_vram_seg1(top);

	_ES = SEG_PLANE_B;
	while(vram_left < vram_right) {
		bb_txt_put_8(vram_left, top, popup_dissolve_sprite);
		vram_left += GLYPH_FULL_W;
	}
}

void pascal near popup_titles_invalidate(void)
{
	unsigned char frames = (popup_titles_frame + popup_boss_bgm_frame);
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
	popup_dissolve_put(
		bgm_note_tram_left(len), to_sp(BGM_CENTER_Y), GAIJI_TRAM_W
	);
}

inline void bgm_title_dissolve_put(const int& len)
{
	popup_dissolve_put(bgm_title_tram_left(len), to_sp(BGM_CENTER_Y), len);
}

#define bgm_string_put(str, len) \
	gaiji_putca(bgm_note_tram_left(len), BGM_TRAM_CENTER_Y, 3, TX_YELLOW); \
	text_putsa(bgm_title_tram_left(len), BGM_TRAM_CENTER_Y, str, TX_WHITE);

inline void titles_dissolve_put(const int& bgm_len)
{
	grcg_setmode_rmw_seg1();

	grcg_setcolor_direct_seg1(11); // Yellow
	if(stage_id < 5) {
		popup_dissolve_put(
			STAGE_NUM_TRAM_LEFT, to_sp(STAGE_NUM_CENTER_Y), STAGE_NUM_W
		);
	} else {
		popup_dissolve_put(
			STAGE_NUM_FE_TRAM_LEFT, to_sp(STAGE_NUM_CENTER_Y), STAGE_NUM_FE_W
		);
	}
	bgm_note_dissolve_put(bgm_len);

	grcg_setcolor_direct_seg1(15); // White
	bgm_title_dissolve_put(bgm_len);
	popup_dissolve_put(
		(PLAYFIELD_TRAM_CENTER_X - (stage_title_len / 2)),
		to_sp(STAGE_TITLE_CENTER_Y),
		stage_title_len
	);
	grcg_off();
}

#define titles_strings_put(bgm_str, bgm_len) \
	gStage_1[6] = (gb_1_ + stage_id); \
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
			popup_dissolve_sprite++; \
			if(popup_dissolve_sprite >= (BB_TXT_IN_SPRITE + BB_TXT_IN_CELS)) { \
				popup_dissolve_sprite = 0; \
			} \
		} \
	}

#define dissolve_out_update(frame) \
	if(frame == POPUP_FRAMES_UNTIL_OUT_DISSOLVE) { \
		playfield_tram_wipe(); \
		popup_dissolve_sprite = BB_TXT_OUT_SPRITE; \
	} else { \
		if((frame & 1) == 0) { \
			popup_dissolve_sprite++; \
		} \
	}

void pascal near popup_titles_update_and_render(void)
{
	#define frames popup_titles_frame
	if(frames >= POPUP_FRAMES_UNTIL_OUT_DISSOLVE) {
		dissolve_out_update(frames);
		if(popup_dissolve_sprite >= (BB_TXT_OUT_SPRITE + BB_TXT_OUT_CELS)) {
			if(frames & 1) {
				overlay_text = nullfunc_near;
				frames = 0;
				popup_dissolve_sprite = 0;
				return;
			}
		} else {
			titles_dissolve_put(stage_bgm_title_len);
		}
	} else {
		if(frames == 0) {
			popup_dissolve_sprite = BB_TXT_IN_SPRITE;
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
		if(popup_dissolve_sprite >= BB_TXT_IN_SPRITE) {
			if(popup_dissolve_sprite == (BB_TXT_IN_SPRITE + 6)) {
				titles_strings_put(stage_bgm_title, stage_bgm_title_len);
			}
			titles_dissolve_put(stage_bgm_title_len);
			dissolve_in_update(frames);
		}
	}
	frames++;
	#undef frames
}

void pascal near popup_boss_bgm_update_and_render(void)
{
	#define frames popup_boss_bgm_frame
	if(frames >= POPUP_FRAMES_UNTIL_OUT_DISSOLVE) {
		dissolve_out_update(frames);
		if(popup_dissolve_sprite >= (BB_TXT_OUT_SPRITE + BB_TXT_OUT_CELS)) {
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
			popup_dissolve_sprite = BB_TXT_IN_SPRITE;
			boss_bgm_title_len = strlen(boss_bgm_title);
		}
		if(popup_dissolve_sprite >= BB_TXT_IN_SPRITE) {
			if(popup_dissolve_sprite == (BB_TXT_IN_SPRITE + 6)) {
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

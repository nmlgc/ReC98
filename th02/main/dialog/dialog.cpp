#include <stddef.h>
#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "shiftjis.hpp"
#include "master.hpp"
#include "platform/array.hpp"
#include "th02/common.h"
#include "th02/resident.hpp"
extern "C" {
#include "th02/hardware/frmdelay.h"
#include "th02/hardware/input.hpp"
}
#include "th02/hardware/pages.hpp"
#include "th02/formats/dialog.hpp"
#include "th02/formats/tile.hpp"
#include "th02/formats/mpn.hpp"
#include "th02/main/playfld.hpp"
#include "th02/main/score.hpp"
#include "th02/main/scroll.hpp"
#include "th02/main/dialog/dialog.hpp"
#include "th02/main/hud/overlay.hpp"
#include "th02/main/stage/stage.hpp"
#include "th02/main/player/player.hpp"
#include "th02/main/tile/tile.hpp"
#include "th02/sprites/main_pat.h"
#include "th02/sprites/face.hpp"

// Coordinates
// -----------

static const pixel_t BOX_W = PLAYFIELD_W;
static const pixel_t BOX_H = (
	(DIALOG_BOX_PART_H / 2) +
	(DIALOG_BOX_LINES * GLYPH_H) +
	(DIALOG_BOX_PART_H / 2)
);
static const screen_x_t BOX_LEFT = PLAYFIELD_LEFT;
static const screen_y_t BOX_TOP = (PLAYFIELD_BOTTOM - BOX_H);

static const pixel_t BOX_MIDDLE_W = (
	BOX_W - DIALOG_BOX_LEFT_W - DIALOG_BOX_PART_W
);

static const pixel_t BOX_SLIDE_SPEED = (PLAYFIELD_W / 24);

static const screen_x_t FACE_LEFT = (BOX_LEFT + 8);
static const screen_y_t FACE_TOP = (BOX_TOP + 8);
static const tram_x_t TEXT_TRAM_LEFT = (
	(BOX_LEFT + DIALOG_BOX_LEFT_W - (DIALOG_BOX_PART_W / 2)) / GLYPH_HALF_W
);
static const tram_x_t TEXT_TRAM_TOP = (
	(BOX_TOP + (BOX_H / 2) - ((DIALOG_BOX_LINES * GLYPH_H) / 2)) / GLYPH_H
);
// -----------

// State
// -----

extern shiftjis_t dialog_text[64][DIALOG_BOX_LINES][DIALOG_LINE_SIZE];
extern bool restore_tile_mode_none_at_post;
// -----

// Core system
// -----------

void dialog_load_and_init(void)
{
	extern char dialog_fn[];
	char* fn = dialog_fn;
	fn[5] = ('0' + stage_id);

	file_ropen(fn);

	// ZUN landmine: No check to ensure that the size is ≤ sizeof(dialog_text).
	size_t size = file_size();
	file_read(dialog_text, size);

	file_close();
	dialog_box_cur = 0;
}

// ZUN bloat: Turn into a single global inline function.
#define egc_start_copy	static near egc_start_copy
#include "th01/hardware/egcstart.cpp"
#undef egc_start_copy

void near dialog_put_player(void)
{
	// A function that shouldn't exist, and it contains no less than 3 bugs!
	//
	// • ZUN bug: This function is supposed to blit the player with an enforced
	//   PAT_PLAYCHAR_STILL sprite and keep this sprite visible under the text
	//   box during the slide-in animation. However, every sprite blitting call
	//   must be preceded by a matching invalidation to clear the sprite from
	//   its previous position in VRAM, which is missing from both call sites.
	//   The only area that is sure to be cleared when we get here is the text
	//   box area from (32, 320) to (416, 400) exclusive, so this only won't
	//   overlap a previously blitted PAT_PLAYCHAR_LEFT or PAT_PLAYCHAR_RIGHT
	//   sprite if it happens to be located entirely within that area.
	//
	// • ZUN bug: Also, this function is exclusively called within the very
	//   first function that runs after flipping hardware pages, long before
	//   any coordinates are updated. Therefore, [page_front] would have been
	//   the correct index into the option position array; [page_back] points
	//   to the previous position of the option.
	//
	// • ZUN bug: It also blits the option sprite for the A shot type,
	//   regardless of which one the player is actually using. This should
	//   really be done in a common function inside the player module, which
	//   can then refer to [player_patnum].
	//
	// (You could also count the bug that shifts up all sprites blitted in the
	// last frame before the dialog by one pixel because the three here draw
	// even more attention towards that one, but the fix for that one needs to
	// be somewhere else.)

	#define option_left_topleft player_option_left_topleft

	vram_y_t top;

	top = scroll_screen_y_to_vram(top, player_topleft.y);
	super_roll_put(player_topleft.x, top, PAT_PLAYCHAR_STILL);

	top = scroll_screen_y_to_vram(top, option_left_topleft[page_back].y);
	super_roll_put_tiny(option_left_topleft[page_back].x, top, PAT_OPTION_A);
	super_roll_put_tiny(
		(option_left_topleft[page_back].x + PLAYER_OPTION_TO_OPTION_DISTANCE),
		top,
		PAT_OPTION_A
	);

	#undef option_left_topleft
}

void pascal near dialog_box_put_top_and_bottom_part(
	screen_x_t& left,
	vram_y_t top_top,
	vram_y_t bottom_top,
	int top_patnum // ACTUAL TYPE: main_patnum_t
)
{
	enum {
		PATNUM_TO_BOTTOM = (
			PAT_DIALOG_BOX_LEFT_BOTTOM - PAT_DIALOG_BOX_LEFT_TOP
		),
	};

	// Assuming the constant slide speed, these are the last coordinates where
	// the box part wouldn't be fully covered by black TRAM cells.
	// ZUN bloat: Using the playfield_clip_left*() and playfield_clip_right*()
	// functions would have been cleaner and more consistent.
	static_assert(BOX_SLIDE_SPEED == (DIALOG_BOX_PART_W / 2));
	if(
		(left >= (PLAYFIELD_LEFT -  BOX_SLIDE_SPEED)) &&
		(left <= (PLAYFIELD_RIGHT - BOX_SLIDE_SPEED))
	) {
		static_assert(BOX_H == (DIALOG_BOX_PART_H * 2));
		static_assert(
			(PAT_DIALOG_BOX_MIDDLE_BOTTOM - PAT_DIALOG_BOX_MIDDLE_TOP) ==
			PATNUM_TO_BOTTOM
		);
		static_assert(
			(PAT_DIALOG_BOX_RIGHT_BOTTOM - PAT_DIALOG_BOX_RIGHT_TOP) ==
			PATNUM_TO_BOTTOM
		);
		super_roll_put(left,    top_top, (top_patnum + 0));
		super_roll_put(left, bottom_top, (top_patnum + PATNUM_TO_BOTTOM));
	}
	left += DIALOG_BOX_PART_W;
}

// ZUN bloat: Passing [left] by reference made sense in the function above, but
// here it doesn't.
void pascal near dialog_box_put(
	screen_x_t& left, vram_y_t top_top, vram_y_t bottom_top
)
{
	int i;

	for(i = PAT_DIALOG_BOX_LEFT_TOP; i < PAT_DIALOG_BOX_MIDDLE_TOP; i++) {
		dialog_box_put_top_and_bottom_part(left, top_top, bottom_top, i);
	}
	for(i = 0; i < (BOX_MIDDLE_W / DIALOG_BOX_PART_W); i++) {
		dialog_box_put_top_and_bottom_part(
			left, top_top, bottom_top, PAT_DIALOG_BOX_MIDDLE_TOP
		);
	}
	dialog_box_put_top_and_bottom_part(
		left, top_top, bottom_top, PAT_DIALOG_BOX_RIGHT_TOP
	);
}

// ZUN bloat: Turn this and the function below into a single
// dialog_box_slide_animate() function.
#define dialog_box_slide_init(left, top_top, bottom_top, left_start) { \
	top_top = scroll_screen_y_to_vram(top_top, BOX_TOP); \
	scroll_add_scrolled(bottom_top, top_top, 0); \
	left = left_start; \
}

#define dialog_box_slide_update_and_render( \
	left, temp_left_mut, top_top, bottom_top \
) { \
	left -= BOX_SLIDE_SPEED; \
	temp_left_mut = left; \
	frame_delay(1); \
	\
	egc_start_copy(); \
	\
	/* \
	 * ZUN bloat: Why not [BOX_H]? Reblitting the bottom margin of the \
	 * playfield has no effect. \
	 */ \
	tiles_invalidate_rect(BOX_LEFT, BOX_TOP, BOX_W, (RES_Y - BOX_TOP)); \
	\
	tiles_egc_render(); \
	egc_off(); \
	\
	dialog_put_player(); \
	dialog_box_put(temp_left_mut, top_top, bottom_top); \
}

void near dialog_pre(void)
{
	// ZUN bloat: Deduplicate and move into dialog_box_slide_animate().
	vram_y_t top_top;
	vram_y_t bottom_top = DIALOG_BOX_PART_H;

	overlay_wipe();

	// ZUN quirk: The game doesn't reset [score_delta] before the next proper
	// game frame calls score_update_and_render(), thus retaining the inherent
	// quirk of this function.
	score_grant_current_delta_as_bonus();

	graph_scrollup(scroll_line);
	palette_100();
	graph_accesspage(page_front);

	// ZUN bloat: Already did this above. TRAM is not double-buffered :P
	overlay_wipe();

	screen_x_t left_mut;
	screen_x_t left;
	dialog_box_slide_init(
		left, top_top, bottom_top, (PLAYFIELD_RIGHT - BOX_SLIDE_SPEED)
	);

	// If we don't render any tiles, tiles_egc_render() should behave like a
	// flood fill with hardware color 0 in order to actually unblit anything.
	// ZUN bug: It would have been more robust to just snap the entire original
	// [BOX_W]×[BOX_H] area and re-blit that to VRAM on every frame.
	if(tile_mode == TM_NONE) {
		restore_tile_mode_none_at_post = true;
		tile_mode = TM_COL_0;
	} else {
		restore_tile_mode_none_at_post = false;
	}

	while(left > PLAYFIELD_LEFT) {
		dialog_box_slide_update_and_render(left, left_mut, top_top, bottom_top);
	}
}

void near dialog_post(void)
{
	// ZUN bloat: Deduplicate and move into dialog_box_slide_animate().
	vram_y_t top_top;
	vram_y_t bottom_top = DIALOG_BOX_PART_H;

	overlay_wipe();

	screen_x_t left_mut;
	screen_x_t left;
	dialog_box_slide_init(left, top_top, bottom_top, PLAYFIELD_LEFT);

	do {
		dialog_box_slide_update_and_render(left, left_mut, top_top, bottom_top);
	} while(left_mut >= (PLAYFIELD_LEFT + BOX_SLIDE_SPEED));

	if(restore_tile_mode_none_at_post == true) {
		restore_tile_mode_none_at_post = false;
		tile_mode = TM_NONE;
	}

	graph_accesspage(page_back);
}

void pascal near dialog_face_put(
	int topleft_id // ACTUAL TYPE: face_topleft_id_t
)
{
	static_assert(FACE_TILES_X == 3);
	static_assert(FACE_TILES_Y == 3);

	vram_y_t top1;
	vram_y_t top2 = 0;
	vram_y_t top3 = 0;

	top1 = scroll_screen_y_to_vram(top1, FACE_TOP);
	scroll_add_scrolled(top2, top1, TILE_H);
	scroll_add_scrolled(top3, top2, TILE_H);

	if(topleft_id == FACE_COL_0) {
		grcg_setcolor(GC_RMW, 0);
		grcg_boxfill(
			FACE_LEFT, top1, (FACE_LEFT + FACE_W - 1), (top1 + FACE_H - 1)
		);
		grcg_off();
		return;
	}

	mpn_put_8((FACE_LEFT + (0 * TILE_W)), top1, face_tile_id(topleft_id, 0, 0));
	mpn_put_8((FACE_LEFT + (1 * TILE_W)), top1, face_tile_id(topleft_id, 1, 0));
	mpn_put_8((FACE_LEFT + (2 * TILE_W)), top1, face_tile_id(topleft_id, 2, 0));
	mpn_put_8((FACE_LEFT + (0 * TILE_W)), top2, face_tile_id(topleft_id, 0, 1));
	mpn_put_8((FACE_LEFT + (1 * TILE_W)), top2, face_tile_id(topleft_id, 1, 1));
	mpn_put_8((FACE_LEFT + (2 * TILE_W)), top2, face_tile_id(topleft_id, 2, 1));
	mpn_put_8((FACE_LEFT + (0 * TILE_W)), top3, face_tile_id(topleft_id, 0, 2));
	mpn_put_8((FACE_LEFT + (1 * TILE_W)), top3, face_tile_id(topleft_id, 1, 2));
	mpn_put_8((FACE_LEFT + (2 * TILE_W)), top3, face_tile_id(topleft_id, 2, 2));
}

void pascal near dialog_text_put(
	tram_cell_amount_t line, const shiftjis_t* str, uint16_t atrb, int n
)
{
	// ZUN landmine: master.lib has text_putnsa() for this purpose, which works
	// without copying the string and risking a buffer overflow in the process,
	// or wasting 40 bytes of conventional RAM on \0 bytes.
	extern const Array<shiftjis_t, DIALOG_LINE_SIZE> clear_bytes;
	Array<shiftjis_t, DIALOG_LINE_SIZE> buf = clear_bytes;
	for(int i = 0; i < n; i++) {
		buf[i] = str[i];
	}

	text_putsa(TEXT_TRAM_LEFT, (TEXT_TRAM_TOP + line), buf.data(), atrb);
}

inline void near dialog_box_wipe(void) {
	extern const char near* LINE_BLANK;

	static_assert(DIALOG_BOX_LINES == 2);
	text_putsa(TEXT_TRAM_LEFT, (TEXT_TRAM_TOP + 0), LINE_BLANK, TX_WHITE);
	text_putsa(TEXT_TRAM_LEFT, (TEXT_TRAM_TOP + 1), LINE_BLANK, TX_WHITE);
}

// Shows a single dialog box in a blocking way, then advances [box_cur].
void pascal near dialog_box_animate_and_advance(
	int face_topleft_id // ACTUAL TYPE: face_topleft_id_t
)
{
	dialog_box_wipe();

	// ZUN quirk: Assumes that the box starts with a 6-byte character name and
	// colon, and prints that all at once in the first frame. This assumption
	// breaks with "魔梨沙：" in Stage 3, which is 8 bytes.
	shiftjis_ank_amount_t box_cursor = 6;

	int loop_count = 0;
	int delay_per_kanji;
	int box = dialog_box_cur;
	while(box_cursor <= ((DIALOG_BOX_LINES * DIALOG_LINE_LENGTH) + 8)) {
		input_sense();
		dialog_face_put(face_topleft_id); // ZUN bloat: Every frame?

		static_assert(DIALOG_BOX_LINES == 2);
		if(box_cursor <= (DIALOG_LINE_LENGTH * 1)) {
			dialog_text_put(
				0,
				dialog_text[box][0],
				TX_WHITE,
				(box_cursor - (DIALOG_LINE_LENGTH * 0))
			);
		} else if(box_cursor <= (DIALOG_LINE_LENGTH * 2)) {
			dialog_text_put(
				1,
				dialog_text[box][1],
				TX_WHITE,
				(box_cursor - (DIALOG_LINE_LENGTH * 1))
			);
		}

		loop_count++;
		if(key_det) {
			delay_per_kanji = 1;
		} else {
			delay_per_kanji = 3;
			frame_delay(1);
		}
		if((loop_count % delay_per_kanji) == 0) {
			box_cursor += static_cast<int>(sizeof(shiftjis_kanji_t));
		}
	}
	key_delay();
	dialog_box_cur++;
}
// -----------

// Stage-specific hardcoded "scripts"
// ----------------------------------
// ZUN bloat: All face ID arrays in this section should have been `static
// const` to avoid the useless copy.

#define boxes_animate(face_id_array) { \
	for(int i = 0; i < face_id_array.count(); i++) { \
		dialog_box_animate_and_advance(face_id_array[i]); \
	} \
}

void pascal near dialog_script_generic_part_animate(dialog_sequence_t sequence)
{
	enum {
		STAGE_SEQUENCE_COUNT = (TOTAL_STAGE_COUNT * DS_COUNT),
	};
	extern const uint8_t GENERIC_BOX_COUNTS[TOTAL_STAGE_COUNT][DS_COUNT];
	extern const face_tile_topleft_t GENERIC_FACES[STAGE_SEQUENCE_COUNT][22];

	int stage_and_sequence = ((stage_id * DS_COUNT) + sequence);
	for(int i = 0; i < GENERIC_BOX_COUNTS[stage_id][sequence]; i++) {
		dialog_box_animate_and_advance(GENERIC_FACES[stage_and_sequence][i]);
	}
}

void near dialog_script_stage2_pre_intro_animate(void)
{
	dialog_box_animate_and_advance(FACE_REIMU_NEUTRAL);
	dialog_box_animate_and_advance(FACE_GENJII);
}

void near dialog_script_stage4_pre_intro_animate(void)
{
	typedef Array<face_tile_topleft_t, 8> T1;
	extern const T1 STAGE4_PREBOSS_INTRO_FACES;
	const T1 FACES = STAGE4_PREBOSS_INTRO_FACES;
	boxes_animate(FACES);
}

void near dialog_script_stage4_pre_marisa_animate(void)
{
	typedef Array<face_tile_topleft_t, 11> T1;
	extern const T1 STAGE4_PREBOSS_MARISA_FACES;
	const T1 FACES = STAGE4_PREBOSS_MARISA_FACES;
	boxes_animate(FACES);
	dialog_box_wipe();
}

void near dialog_script_stage4_post_animate(void)
{
	typedef Array<shiftjis_t near*, 10> T1;
	typedef Array<int /* ACTUAL TYPE: face_tile_topleft_t */, 3> T2;
	typedef Array<int /* ACTUAL TYPE: face_tile_topleft_t */, 5> T3;

	extern const T1 STAGE4_POSTBOSS_CONTINUED_NUMERALS;
	extern const T2 STAGE4_POSTBOSS_CONTINUED_BEFORE_FACES;
	extern const T3 STAGE4_POSTBOSS_CONTINUED_AFTER_FACES;
	extern const T3 STAGE4_POSTBOSS_NOTCONTINUED_FACES;

	const T1 CONTINUED_NUMERALS = STAGE4_POSTBOSS_CONTINUED_NUMERALS;
	const T2 CONTINUED_BEFORE_BOX_FACE = STAGE4_POSTBOSS_CONTINUED_BEFORE_FACES;
	const T3 CONTINUED_AFTER_BOX_FACE = STAGE4_POSTBOSS_CONTINUED_AFTER_FACES;
	const T3 NOTCONTINUED_BOX_FACE = STAGE4_POSTBOSS_NOTCONTINUED_FACES;

	dialog_script_generic_part_animate(DS_POSTBOSS);
	if(resident->continues_used) {
		boxes_animate(CONTINUED_BEFORE_BOX_FACE);

		// Insert number of continues into the next dialog box
		int digit = (resident->continues_used / 10);
		if(digit) {
			dialog_text[dialog_box_cur][0][8] = CONTINUED_NUMERALS[digit][0];
			dialog_text[dialog_box_cur][0][9] = CONTINUED_NUMERALS[digit][1];
		}
		digit = (resident->continues_used % 10);
		dialog_text[dialog_box_cur][0][10] = CONTINUED_NUMERALS[digit][0];
		dialog_text[dialog_box_cur][0][11] = CONTINUED_NUMERALS[digit][1];

		// ZUN bloat: Same as boxes_animate().
		for(digit = 0; digit < CONTINUED_AFTER_BOX_FACE.count(); digit++) {
			dialog_box_animate_and_advance(CONTINUED_AFTER_BOX_FACE[digit]);
		}
	} else {
		dialog_box_cur += (
			CONTINUED_BEFORE_BOX_FACE.count() +
			CONTINUED_AFTER_BOX_FACE.count()
		);
		boxes_animate(NOTCONTINUED_BOX_FACE);
	}
}
// ----------------------------------

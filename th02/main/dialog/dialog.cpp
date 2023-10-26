#include <stddef.h>
#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "shiftjis.hpp"
#include "master.hpp"
extern "C" {
#include "th02/hardware/frmdelay.h"
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
// -----------

// State
// -----

extern shiftjis_t dialog_text[64][DIALOG_BOX_LINES][DIALOG_LINE_SIZE];
extern bool restore_tile_mode_none_at_post;
// -----

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

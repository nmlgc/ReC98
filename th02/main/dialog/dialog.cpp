#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "shiftjis.hpp"
#include "master.hpp"
#include "th02/hardware/pages.hpp"
#include "th02/formats/dialog.hpp"
#include "th02/main/playfld.hpp"
#include "th02/main/scroll.hpp"
#include "th02/main/dialog/dialog.hpp"
#include "th02/main/stage/stage.hpp"
#include "th02/main/player/player.hpp"
#include "th02/sprites/main_pat.h"

// Coordinates
// -----------

static const pixel_t BOX_W = PLAYFIELD_W;
static const pixel_t BOX_H = (
	(DIALOG_BOX_PART_H / 2) +
	(DIALOG_BOX_LINES * GLYPH_H) +
	(DIALOG_BOX_PART_H / 2)
);

static const pixel_t BOX_MIDDLE_W = (
	BOX_W - DIALOG_BOX_LEFT_W - DIALOG_BOX_PART_W
);

static const pixel_t BOX_SLIDE_SPEED = (PLAYFIELD_W / 24);
// -----------

// State
// -----

extern shiftjis_t dialog_text[64][DIALOG_BOX_LINES][DIALOG_LINE_SIZE];
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
#define egc_start_copy	near egc_start_copy_2
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

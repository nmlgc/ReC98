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

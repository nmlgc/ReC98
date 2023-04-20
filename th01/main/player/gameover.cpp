#include "th01/main/player/gameover.hpp"

void player_gameover_animate(void)
{
	enum {
		EFFECT_COUNT = 5, // ordered clockwise from left to right
		EFFECT_SPEED = 8,
	};

	int i;
	int j;
	screen_x_t left[EFFECT_COUNT];
	screen_y_t top[EFFECT_COUNT];
	bool16 clipped[EFFECT_COUNT] = { false };

	#define frame j

	items_reset();
	player_miss_put(); // ZUN bug: Missing an unblitting call.

	// ZUN quirk: Not centered, even though the effects are clearly meant to
	// expand from the center?
	for(j = 0; j < EFFECT_COUNT; j++) {
		left[j] = player_left;
		top[j] = player_top;
	}

	// Make sure we don't unblit the miss sprite. Kind of wasteful
	// to copy the whole page, but who cares.
	graph_accesspage_func(0);
	graph_copy_accessed_page_to_other();
	graph_accesspage_func(0);

	for(frame = 0; frame < 16; frame++) {
		z_vsync_wait_and_scrollup(RES_Y - ((j % 2) * 8));
		for(i = 0; i < EFFECT_COUNT; i++) {
			// ZUN bug: Indexing [clipped] with [frame] rather than [i],
			// leading to a out-of-bounds read from frame 5 on. In the original
			// game, this ends up accessing [top] and [left], whose positions
			// can never be 0.
			if(!clipped[frame]) {
				// ZUN quirk: Sloppy unblitting is actually a good choice here,
				// since Reimu's sprite has also been blitted to VRAM page 1
				// above, and we're inside a blocking animation anyway. But
				// this ends up unblitting a rectangle around Reimu with a
				// constant height of 32 pixels and only growing on the X
				// axis... Then again, it probably wasn't meant to "correctly"
				// unblit each effect sprite as you would usually expect, as
				// that would look rather wimpy in comparison.
				ptn_sloppy_unput_16(left[i], player_top);
			}
		}

		// ZUN quirk: This is a correct attempt to accurately calculate a
		// trigonometric velocity for a 45° angle, multiplying the speed with
		// ±cos(45°) = ±sin(45°) = √½. However, ZUN gets the execution entirely
		// wrong, using
		// 1) master.lib's *integer* square root function, which can only
		//    truncate √2 to 1,
		// 2) integer divisions,
		// 3) and pixel coordinates.
		// Why not just use the perfectly appropriate polar_*() functions?!
		left[0] -= EFFECT_SPEED;
		left[1] -= (EFFECT_SPEED / isqrt(2));
		left[3] += (EFFECT_SPEED / isqrt(2));
		left[4] += EFFECT_SPEED;

		top[1] -= (EFFECT_SPEED / isqrt(2));
		top[3] -= (EFFECT_SPEED / isqrt(2));
		top[2] -= EFFECT_SPEED;

		for(i = 0; i < EFFECT_COUNT; i++) {
			if(
				(left[i] >= (PLAYFIELD_RIGHT - PTN_W)) ||
				(left[i] < PLAYFIELD_LEFT)
			) {
				clipped[i] = true;
			}
			if(!clipped[i]) {
				ptn_put_8(left[i], top[i], (PTN_MISS_EFFECT + (frame % 2)));
			}
		}
		frame_delay(frame / 6);
	}

	z_vsync_wait_and_scrollup(0);

	// ZUN bug: Both should have been set to [credit_bombs] from REIIDEN.CFG.
	// That file is never read in REIIDEN.EXE though, nor is the value
	// preserved in the resident structure. In the end it makes no difference,
	// as [credit_bombs] is a constant 1 in the original game.
	rem_bombs = 1;
	resident->rem_bombs = 1;

	#undef frame
}

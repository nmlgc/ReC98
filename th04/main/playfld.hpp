#include "th04/main/scroll.hpp"
#include "th04/math/motion.hpp"
#include "th02/main/playfld.hpp"

struct PlayfieldPoint : public SPPoint {
	screen_x_t to_screen_left(pixel_t sprite_w_if_centered = 0) const {
		return playfield_to_screen_left(x, sprite_w_if_centered);
	}

	screen_y_t to_screen_top(pixel_t sprite_h_if_centered = 0) const {
		return playfield_to_screen_top(y, sprite_h_if_centered);
	}

	vram_y_t to_vram_top_scrolled_seg1(pixel_t sprite_h_if_centered) const {
		return scroll_subpixel_y_to_vram_seg1(
			y + (PLAYFIELD_TOP - (sprite_h_if_centered / 2))
		);
	}

	vram_y_t to_vram_top_scrolled_seg3(pixel_t sprite_h_if_centered) const {
		return scroll_subpixel_y_to_vram_seg3(
			y + (PLAYFIELD_TOP - (sprite_h_if_centered / 2))
		);
	}
};

struct PlayfieldMotion : public MotionBase<PlayfieldPoint> {
	// Moves by one step, and returns the new current position.
	// The _seg1() and _seg3() variants are provided for near calls within
	// code segment #1 (rendering) and code segment #3 (update),
	// respectively.
	// Note that some calls to these functions directly access the returned
	// value through the AX (X) and DX (Y) registers.
	PlayfieldPoint pascal near update_seg1();
	PlayfieldPoint pascal near update_seg3();
};

/// Shaking
/// -------

// Shake amount for the current frame; resets to 0 after calling
// playfield_shake_update_and_render(). Can also be manually controlled while
// [playfield_shake_anim_time] is 0.
extern pixel_t playfield_shake_x;
extern pixel_t playfield_shake_y;

// Frames left in the 4-direction shake animation.
extern int playfield_shake_anim_time;

// Shifts the playfield on the current VRAM page by [playfield_shake], or runs
// the 4-direction shake animation if it's active. After the playfield was
// shifted, all tiles are invalidated for the next two frames, forcing a
// redraw of the unshifted playfield on both VRAM pages.
void near playfield_shake_update_and_render(void);
/// -------

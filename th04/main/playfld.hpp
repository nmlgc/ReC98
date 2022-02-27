#include "th02/main/playfld.hpp"

#if defined(SUBPIXEL_HPP) && defined(MOTION_HPP)
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
#endif

// Fills the playfield area on the text RAM with transparent spaces.
void near playfield_tram_wipe(void);
// Fills the playfield area on the text RAM with black, effectively hiding the
// playfield in the process.
void near playfield_tram_black(void);

#define playfield_bg_put(left, top, cdg_slot) \
	cdg_put_noalpha_8((PLAYFIELD_LEFT + left), (PLAYFIELD_TOP + top), cdg_slot)

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

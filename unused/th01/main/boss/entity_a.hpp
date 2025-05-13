/// Entities
/// --------

#include "pc98.h"

class CBossEntity {
	/// Blitting
	/// --------

	// Precisely restores pixels according to the alpha mask of [image] from
	// VRAM page 1, starting at (⌊left/8⌋*8, top).
	// Additionally clips at the top and bottom edges of VRAM.
	void unput_8(screen_x_t left, vram_y_t top, int image) const;

	// Like wave_put(), but calls unput_and_put_1line() for each line instead.
	void wave_unput_and_put(int image, int len, pixel_t amp, int phase) const;

	// Tries to unblit the two sprites at (left_1, top) and (left_2, top) that
	// were previously blitted with the given wave function using the EGC, but
	// fails.
	void egc_sloppy_wave_unput_double_broken(
		screen_x_t left_1, vram_y_t top, int unused,
		int len_1, pixel_t amp_1, int phase_1,
		screen_x_t left_2,
		int len_2, pixel_t amp_2, int phase_2
	) const;

	// Blits the 16×8 pixels of [bos_image] in [bos_slot] starting at
	// (bos_left, bos_top), relative to the top-left corner of the sprite, to
	//	((⌊cur_left/8⌋ + bos_left/8⌋) * 8, (cur_top + bos_top))
	// after precisely restoring pixels according to the alpha mask of the
	// pixels to be blitted from VRAM page 1.
	// Additionally clips at the top and bottom edges of VRAM.
	void unput_and_put_16x8_8(pixel_t bos_left, pixel_t bos_top) const;

	// Restores the pixels inside the entire ([vram_w]*8)×[h] rectangle
	// starting at (cur_left, cur_top) from VRAM page 1.
	void sloppy_unput(void) const;
	/// --------
};
/// --------

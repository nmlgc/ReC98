#include "th03/formats/cdg.h"


// Displays only the alpha plane of the CDG image in the given [slot] at
// (⌊left/8⌋*8, top).
extern "C" {
void pascal cdg_put_nocolors_8(screen_x_t left, vram_y_t top, int slot);
}

#if (GAME == 4)
// Displays the given [plane] of the CDG image in the given [slot] at
// (left, top). (Unlike other CDG displaying functions, this one actually
// accepts any value for [left].) Assumes the GRCG to be set to monochrome
// mode.
//
// This is used for the "dissolution effect" in the staff roll. It actually
// doesn't apply any sort of effect on the pixel data though, and relies on the
// individual planes being pre-dissolved.)
extern "C" {
void pascal cdg_put_plane(
	screen_x_t left, vram_y_t top, int slot, int plane
);
}

// ORs a single plane of the CDG image in the given [slot] into the given VRAM
// destination plane at (⌊left/8⌋*8, top), wrapped vertically.
void pascal cdg_put_plane_roll_8(
	screen_x_t left,
	vram_y_t top,
	int slot,
	vram_plane_t plane_src_id,
	dots8_t __seg *plane_dst
);
#endif


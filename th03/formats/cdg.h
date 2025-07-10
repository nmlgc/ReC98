/// Uncompressed, monochrome / 16-color / 16-color + alpha, 32w×h sprite format
/// ---------------------------------------------------------------------------

#ifndef TH03_FORMATS_CDG_H
#define TH03_FORMATS_CDG_H

#include "planar.h"

// Number of planes per image.
typedef enum {
#if (GAME >= 4)
	CDG_COLORS = 0,          	// 4 planes per image
	CDG_COLORS_AND_ALPHA = 1,	// 5 planes per image
	CDG_ALPHA = 2,           	// 1 plane per image
#else
	CDG_COLORS_AND_ALPHA = 0,	// 5 planes per image
#endif
} cdg_plane_layout_t;

// Doubles as both the file format header (describing all images in a file)
// and the internal slot structure (describing a single image).
struct CDG {
	// Size of a single bitplane.
	uint16_t bitplane_size;

	// Only used by custom functions that apply effects on the image. The core
	// CDG functions mainly use the two pre-calculated values
	// [offset_at_bottom_left] and [vram_dword_w] instead.
	int16_t pixel_w;
	int16_t pixel_h;

	// vram_byte_amount_t, equal to (ROW_SIZE * ([pixel_h - 1])).
	int16_t offset_at_bottom_left;

	// vram_dword_amount_t, equal to [pixel_w / 32].
	uint16_t vram_dword_w;

	// In TH03, this can also be 0 for single-image files.
	uint8_t image_count;

	// See cdg_plane_layout_t.
	int8_t plane_layout;

	// Memory segments of the loaded data. Must be 0 in the file header!
	dots8_t __seg *seg[2];

	dots8_t __seg*& seg_alpha() {
		return seg[0];
	}

	dots8_t __seg*& seg_colors() {
		return seg[1];
	}
};

static const int CDG_SLOT_COUNT = ((GAME >= 4) ? 64 : 32);

extern CDG cdg_slots[CDG_SLOT_COUNT];

extern "C" {

// Loading and freeing
// -------------------

// Loads all images of the CDG file [fn], starting at [slot_first] and
// incrementing the slot number for every further image.
void pascal cdg_load_all(int slot_first, const char *fn);

// Like cdg_load_all(), but not loading any alpha planes.
void pascal cdg_load_all_noalpha(int slot_first, const char *fn);

// Loads the [n]th image of the CDG file [fn] into [slot].
void pascal cdg_load_single(int slot, const char *fn, int n);

// Like cdg_load_single(), but not loading any alpha planes.
void pascal cdg_load_single_noalpha(int slot, const char *fn, int n);

// Frees the CDG image in the given [slot], but retains the metadata.
void pascal cdg_free(int slot);

// Frees the CDG images in all slots.
void pascal cdg_free_all(void);
// -------------------

// Blitting
// --------

// Displays the CDG image in the given [slot] at (⌊left/8⌋*8, top).
void pascal cdg_put_8(screen_x_t left, vram_y_t top, int slot);

// Displays the CDG image in the given [slot] at (⌊left/8⌋*8, top),
// disregarding its alpha plane.
void pascal cdg_put_noalpha_8(screen_x_t left, vram_y_t top, int slot);

#if (GAME == 3)
// Displays the CDG image in the given [slot] at (⌊left/8⌋*8, top), flipped
// horizontally using the [hflip_lut].
void pascal cdg_put_hflip_8(screen_x_t left, vram_y_t top, int slot);

// Displays the CDG image in the given [slot] centered at
// (⌊center_x/8⌋*8, center_y), then applies a dissolve effect with the given
// [strength] (mod 8, 0 = none, 7 = full) on the E bitplane.
void pascal cdg_put_dissolve_e_8(
	screen_x_t center_x, vram_y_t center_y, int slot, int strength
);

// Assuming that the CDG image in the given [slot] was previously displayed
// centered at (⌊center_x/8⌋*8, center_y), this function clears the two lines
// at the bottom of that image, as well as the one line immediately below, from
// the VRAM's E plane.
void cdg_unput_for_upwards_motion_e_8(
	screen_x_t center_x, vram_y_t center_y, int slot
);
#endif
// --------

}
#endif /* TH03_FORMATS_CDG_H */
/// ---------------------------------------------------------------------------

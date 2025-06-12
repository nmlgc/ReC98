/// PC-98 sprite and image management
/// ---------------------------------

#include "game/coords.hpp"
#include "planar.h"

// Surface classes
// ---------------
// Blit functions can only guarantee support for X values that are multiples of
// 8.

struct GrpSurface {
	uvram_byte_amount_t w;
	upixel_t h;
};

// Surfaces allocated in memory, with each bitplane stored sequentially in a
// single allocation.
struct GrpSurface_M : public GrpSurface {
	seg_t plane_B; // Segment pointer to the first bitplane.
	uint16_t plane_paras; // Paragraph size of a single bitplane.

	void pascal free(void);
};

// 4×1bpp surface
struct GrpSurface_M4 : public GrpSurface_M {
	void pascal write(
		screen_x_t left,
		screen_y_t top,
		const LTWH<upixel_t> near *region = nullptr
	);
};
// ---------------

enum pi_flag_t {
	PIF_NONE = 0,

	// Skips odd-numbered lines. Required for 4 sets of images in TH03.
	PIF_LINESKIP = 1,
};

// Loads the given PI file into the given sprite sheet and optionally returns
// its palette.
int pascal GrpSurface_LoadPI(
	GrpSurface_M4& surf,
	Palette8 *palette,
	const char *fn,
	pi_flag_t flags = PIF_NONE
);

// Directly blits the given PI file to the top-left corner of VRAM and
// optionally returns its palette.
int pascal GrpSurface_BlitBackgroundPI(Palette8 *palette, const char *fn);

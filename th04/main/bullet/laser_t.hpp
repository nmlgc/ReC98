/// Thick lasers
/// ------------

#include "th01/math/subpixel.hpp"

#define THICKLASER_COUNT 2

enum thicklaser_flag_t {
	TF_FREE = 0,
	TF_LINE = 1,
	TF_GROW = 2,
	TF_STATIC = 3,
	TF_SHRINK = 4,
};

struct thicklaser_t {
	thicklaser_flag_t flag;
	/* ------------------------- */ int8_t unused_1;
	SPPoint origin;
	/* ------------------------- */ int8_t unused_2;
	int cur_flag_frames;

	// Frames to spend in TF_LINE before transitioning to TF_GROW.
	int line_frames;

	// Frames to spend in TF_STATIC before transitioning to TF_SHRINK.
	int static_frames;

	// Hardware palette color of the outermost layer of the laser. The second
	// layer is rendered with the hardware palette color at this index + 1.
	vc_t col_outline;

	/* ------------------------- */ int8_t unused_3;

	// Target radius during TF_GROW, and fixed radius during TF_STATIC.
	pixel_t radius_max;

	pixel_t radius_cur;

	// Per-frame radius delta during both TF_GROW and TF_SHRINK.
	pixel_t radius_speed;
};

extern thicklaser_t thicklaser_template;
extern thicklaser_t thicklasers[THICKLASER_COUNT];

#include "pc98.h"

static const pixel_t OPWIN_W = 16;
static const pixel_t OPWIN_H = 128;

// The right half of [OPWIN_LEFT] is assumed to be identical to the left half
// of [OPWIN_RIGHT].
static const pixel_t OPWIN_STEP_W = (OPWIN_W / 2);

// OPWIN.BFT sprites
enum op_window_patnum_t {
	OPWIN_LEFT,

	// Unused due to the assumption described in [OPWIN_STEP_W]'s comment
	OPWIN_MIDDLE,

	OPWIN_RIGHT,
};

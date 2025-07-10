#include "pc98.h"
#include "shiftjis.hpp"
#include "defconv.h"

// Font weights
// ------------

// As stored in font ROM
#define WEIGHT_NORMAL 0

// Naively adds one pixel of boldness, to the left
#define WEIGHT_HEAVY 1

// Adds one pixel of boldness to the left, but preserves holes inbetween
// strokes.
#define WEIGHT_BOLD 2

// Adding another pixel of boldness, to the left, on top of WEIGHT_BOLD.
// (Very thicc!)
#define WEIGHT_BLACK 3

#define WEIGHT_COUNT 4
// ------------

#if (GAME <= 3)
#define FX_WEIGHT_NORMAL (WEIGHT_NORMAL << 4)
#define FX_WEIGHT_HEAVY  (WEIGHT_HEAVY << 4)
#define FX_WEIGHT_BOLD   (WEIGHT_BOLD << 4)
#define FX_WEIGHT_BLACK  (WEIGHT_BLACK << 4)

// Not used in any of the three games that support the feature.
#define FX_SPACING(spacing) \
	((spacing & 7) << 6)

// Puts the given [str] onto the graphics RAM at the given position, with the
// given graphics color and effect.
#if (GAME != 1)
// Needed to provide an implicit overload for a non-`const` [str] parameter for
// a single call in TH02's verdict screen.
extern "C"
#endif
void DEFCONV graph_putsa_fx(
	screen_x_t left, vram_y_t top, int16_t col_and_fx, const shiftjis_t *str
);
#endif

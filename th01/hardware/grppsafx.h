#ifndef TH01_HARDWARE_GRPPSAFX_H
#define TH01_HARDWARE_GRPPSAFX_H

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

#if (GAME == 1)
// TH01-exclusive effects
// ----------------------

// Puts a black background behind the text. Useful if the text is rendered
// onto the back page and should then be 2× scaled onto the front page.
static const int16_t FX_CLEAR_BG  = 0x200;

static const int16_t FX_UNDERLINE = 0x400;
static const int16_t FX_REVERSE   = 0x800;
static const int16_t FX_8X8       = 0x1000; // Use the 8×8 font
// ----------------------
#endif

// Not used in any of the three games that support the feature.
#define FX_SPACING(spacing) \
	((spacing & 7) << 6)

#if (GAME == 1)
// Calculates the width of [str], displayed with the given [fx].
int text_extent_fx(int16_t fx, const shiftjis_t *str);
#endif

// Puts the given [str] onto the graphics RAM at the given position, with the
// given graphics color and effect.
#if (GAME == 2)
// Needed to provide an implicit overload for a non-`const` [str] parameter for
// a single call in TH02's verdict screen.
extern "C"
#endif
void DEFCONV graph_putsa_fx(
	screen_x_t left, vram_y_t top, int16_t col_and_fx, const shiftjis_t *str
);
#endif

#endif /* TH01_HARDWARE_GRPPSAFX_H */

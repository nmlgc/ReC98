/// Font ROM glyphs in VRAM
/// -----------------------
/// TH01-exclusive extensions to the graph_putsa_fx() function.

#include "th01/hardware/grppsafx.h"

// TH01-exclusive effects
// ----------------------

// Puts a black background behind the text. Useful if the text is rendered
// onto the back page and should then be 2× scaled onto the front page.
static const int16_t FX_CLEAR_BG  = 0x200;

static const int16_t FX_UNDERLINE = 0x400;
static const int16_t FX_REVERSE   = 0x800;
// ----------------------

// Calculates the width of [str], displayed with the given [fx].
int text_extent_fx(int16_t fx, const shiftjis_t *str);

// Variadic version of graph_putsa_fx().
void graph_printf_fx(
	screen_x_t left,
	vram_y_t top,
	int16_t col_and_fx,
	const shiftjis_t *fmt,
	...
);

// Puts the rightmost N [digits] of [num] onto the graphics RAM, using
// full-width digits, and applying the given effect. (Consequently, the units
// place will appear at x = [left] + (([digits] - 1) * GLYPH_FULL_W).)
// Each digit is blitted separately; if [num_prev] is nonzero, the function
// only blits the digits of [num] that differ from those in [num_prev].
// Will put nothing if [put_leading_zeroes] is false and [num] is 0.
void graph_putfwnum_fx(
	screen_x_t left, vram_y_t top, int16_t col_and_fx, int digits,
	long num, long num_prev, bool16 put_leading_zeroes
);
/// -----------------------

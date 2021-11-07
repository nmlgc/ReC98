/// BIOS
/// ----
// Enables the graphics layer in 640x400 mode, applies z_Palettes, and clears
// page 0.
void z_graph_init(void);
// Resets all hardware colors to black and clears page 0.
void z_graph_exit(void);

void z_graph_show(void);
void z_graph_hide(void);
/// ----

/// Pages
/// -----
void graph_showpage_func(page_t page);
void graph_accesspage_func(int page);

// Fills the entire active page with hardware color 0 or the given [col].
void z_graph_clear(void);
void z_graph_clear_col(uint4_t col);

// Fills page #0 with hardware color 0.
void z_graph_clear_0(void);

// Copies the content of the VRAM page that was previously set as the accessed
// one via a call to graph_accesspage_func() to the opposite one.
void graph_copy_accessed_page_to_other(void);
/// -----

/// GRCG
/// ----
void grcg_setcolor_rmw(int col);
void grcg_setcolor_tdw(int col);
void grcg_off_func(void);
#undef grcg_off
#define grcg_off grcg_off_func

void z_grcg_boxfill(
	screen_x_t left, vram_y_t top, screen_x_t right, vram_y_t bottom, int col
);
/// ----

/// Points
/// ------
void z_grcg_pset(screen_x_t x, vram_y_t y, int col);
// Returns the color value at the given point on the current VRAM page.
int z_graph_readdot(screen_x_t x, vram_y_t y);
/// ------

/// Restorable line drawing
/// -----------------------
// Draws straight horizontal or vertical lines.
void graph_r_hline(screen_x_t left, screen_x_t right, vram_y_t y, int col);
void graph_r_vline(screen_x_t x, vram_y_t top, vram_y_t bottom, int col);

// Draws a line with an arbitrary angle between the two points.
void graph_r_line(
	screen_x_t left, vram_y_t top, screen_x_t right, vram_y_t bottom, int col
);

// Draws a line with an arbitrary angle and an arbitrary 16-pixel pattern
// between the two points.
void graph_r_line_patterned(
	screen_x_t left,
	vram_y_t top,
	screen_x_t right,
	vram_y_t bottom,
	int col,
	dots16_t pattern
);

// Recovers the pixels on the given arbitrary-angle line from page 1.
void graph_r_line_unput(
	screen_x_t left, vram_y_t top, screen_x_t right, vram_y_t bottom
);

// Draws the outline of a rectangle.
void graph_r_box(
	screen_x_t left, vram_y_t top, screen_x_t right, vram_y_t bottom, int col
);

// Draws lines in the given [col] from each of the given X/Y points to the
// next one, and then back from the last point to the first one.
void graph_r_lineloop_put(
	const screen_x_t x[], const vram_y_t y[], int point_count, int col
);

// Like graph_r_lineloop_put(), but recovering the pixels along the given
// lines from VRAM page 1 instead.
void graph_r_lineloop_unput(
	const screen_x_t x[], const vram_y_t y[], int point_count
);
/// -----------------------

/// Text
/// ----
// Calculates the width of [str], displayed with the given [fx].
int text_extent_fx(int fx, const unsigned char *str);

#include "th01/hardware/grppsafx.h"

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
/// ----

/// Blitting
/// --------
// Copies the given rectangle on the current from
//     (⌊left/8⌋*8, top)
// to
//     (⌊left/8⌋*8 + ⌊(right-left)/8⌋*8, bottom)
// from the VRAM page that was previously set as the accessed one via a call
// to  graph_accesspage_func() to the same position on the opposite page.
void graph_copy_byterect_from_accessed_page_to_other(
	screen_x_t left, vram_y_t top, screen_x_t right, vram_y_t bottom
);

// Moves the given source rectangle from
//     (⌊left/8⌋*8, top)
// on the [src] page to
//     (⌊left/8⌋*8 + ⌊(right-left)/8⌋*8, bottom)
// on the [dst] page. Already assumes [src] to be the currently accessed page.
void graph_move_byterect_interpage(
	screen_x_t src_left,
	vram_y_t src_top,
	screen_x_t src_right,
	vram_y_t src_bottom,
	screen_x_t dst_left,
	vram_y_t dst_top,
	int src, int dst
);

// Recovers the dots set in the given [mask] from (⌊left/8⌋*8, top) to
// (⌊(left/8) + w⌋*8, top) from VRAM page 1.
void graph_hline_unput_masked_8(
	screen_x_t left, vram_y_t top, dots8_t *mask, vram_byte_amount_t vram_w
);
/// --------

/// BIOS
/// ----

#include "planar.h"

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

// Fills the entire active page with hardware color 0 or the given [col].
void z_graph_clear(void);
void z_graph_clear_col(svc_t col);

// Fills page #0 with hardware color 0.
void z_graph_clear_0(void);

// Copies the contents of the given VRAM page to the other one. Returns with
// the other one (= ![src]) as the accessed VRAM page.
void graph_copy_page_to_other(page_t src);
/// -----

/// GRCG
/// ----

void grcg_setcolor_rmw(vc2 col);

// Enters TCR (Tile Compare Read / "color extraction") mode. VRAM reads will
// return 1 for any dot whose corresponding pixel has the given [col], and 0
// otherwise.
void grcg_setcolor_tcr(vc2 col);

void grcg_off_func(void);

void z_grcg_boxfill(
	screen_x_t left, vram_y_t top, screen_x_t right, vram_y_t bottom, vc2 col
);
/// ----

/// Points
/// ------

void z_grcg_pset(screen_x_t x, vram_y_t y, vc2 col);
// Returns the color value at the given point on the current VRAM page.
int z_graph_readdot(screen_x_t x, vram_y_t y);
/// ------

/// Restorable line drawing
/// -----------------------

// Draws straight horizontal lines.
void graph_r_hline(screen_x_t left, screen_x_t right, vram_y_t y, vc2 col);

// Draws straight vertical lines.
void graph_r_vline(screen_x_t x, vram_y_t top, vram_y_t bottom, vc2 col);

// Draws a line with an arbitrary angle between the two points.
void graph_r_line(
	screen_x_t left, vram_y_t top, screen_x_t right, vram_y_t bottom, vc2 col
);

// Draws a line with an arbitrary angle and an arbitrary 16-pixel pattern
// between the two points.
void graph_r_line_patterned(
	screen_x_t left,
	vram_y_t top,
	screen_x_t right,
	vram_y_t bottom,
	vc2 col,
	dots16_t pattern
);

// Recovers horizontal 32-pixel chunks along on the given arbitrary-angled line
// from page 1. The [right] and [bottom] points are included in the line.
//
// ZUN bug: Will raise a General Protection Fault if it ever writes to the
// topmost byte of VRAM, corresponding to the pixel coordinates from (0, 0) to
// (0, 7) inclusive. Thanks to an off-by-one error, this also happens for any
// lines ending at ((RES_X - 1), 0).
void graph_r_line_unput(
	screen_x_t left, vram_y_t top, screen_x_t right, vram_y_t bottom
);

// Draws the outline of a rectangle.
void graph_r_box(
	screen_x_t left, vram_y_t top, screen_x_t right, vram_y_t bottom, vc2 col
);

// Draws lines in the given [col] from each of the given points to the next
// one, and then back from the last point to the first one.
void graph_r_lineloop_put(const screen_point_t point[], int count, vc_t col);

// Like graph_r_lineloop_put(), but recovering the pixels along the given
// lines from VRAM page 1 instead.
void graph_r_lineloop_unput(const screen_point_t point[], int count);
/// -----------------------

/// Blitting
/// --------

// Moves the given source rectangle from
//     (⌊left/8⌋*8, top)
// on the [src] page to
//     (⌊left/8⌋*8 + ⌊(right-left)/8⌋*8, bottom)
// on the other page. Returns with the other one (= ![src]) as the accessed
// VRAM page.
void graph_move_byterect_interpage(
	screen_x_t src_left,
	vram_y_t src_top,
	screen_x_t src_right,
	vram_y_t src_bottom,
	screen_x_t dst_left,
	vram_y_t dst_top,
	page_t src
);
/// --------

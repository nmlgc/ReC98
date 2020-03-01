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

// Also updates [page_back].
void graph_accesspage_func(int page);

// Fills the entire active page with hardware color 0 or the given [col].
void z_graph_clear(void);
void z_graph_clear_col(uint4_t col);

// Fills page #0 with hardware color 0.
void z_graph_clear_0(void);

void graph_copy_page_front_to_back(void);
/// -----

/// GRCG
/// ----
void grcg_setcolor_rmw(int col);
void grcg_setcolor_tdw(int col);
void grcg_off_func(void);
#undef grcg_off
#define grcg_off grcg_off_func

void z_grcg_boxfill(int left, int top, int right, int bottom, int col);
/// ----

/// Points
/// ------
void z_grcg_pset(int x, int y, int col);
// Returns the color value at the given point on the current VRAM page.
int z_col_at(int x, int y);
/// ------

/// Restorable line drawing
/// -----------------------
// Draws straight horizontal or vertical lines.
void graph_r_hline(int left, int right, int y, int col);
void graph_r_vline(int x, int top, int bottom, int col);

// Draws a line with an arbitrary angle between the two points.
void graph_r_line(int left, int top, int right, int bottom, int col);

// Draws a line with an arbitrary angle and an arbitrary 16-pixel pattern
// between the two points.
void graph_r_line_patterned(
	int left, int top, int right, int bottom, int col, planar16_t pattern
);

// Recovers the pixels on the given arbitrary-angle line from page 1.
void graph_r_line_from_1(int left, int top, int right, int bottom);

// Draws the outline of a rectangle.
void graph_r_box(int left, int top, int right, int bottom, int col);
/// -----------------------

/// Text
/// ----
// Calculates the width of [str], displayed with the given [fx]
int text_extent_fx(int fx, const unsigned char *str);

// TH01-exclusive effects
// ----------------------
// Puts a black background behind the text. Useful if the text is rendered
// onto the back page and should then 2✕ scaled onto the front page.
#define FX_CLEAR_BG 	0x200

#define FX_UNDERLINE 	0x400
#define FX_REVERSE  	0x800
// ----------------------
#include "th01/hardware/grppsafx.h"
void graph_printf_fx(int left, int top, int fx, const char *fmt, ...);
/// ----

/// Blitting
/// --------
// Copies the given rectangle from
//     (⌊left/8⌋*8, top)
// to
//     (⌊left/8⌋*8 + ⌊(right-left)/8⌋*8, bottom)
// on the current back page to the same position on the current front page.
void graph_copy_byterect_back_to_front(
	int left, int top, int right, int bottom
);

// Moves the given source rectangle from
//     (⌊left/8⌋*8, top)
// to
//     (⌊left/8⌋*8 + ⌊(right-left)/8⌋*8, bottom)
// on the [src] page to the given position
// in the [dst] page. Already assumes [src] to be the currently accessed page.
void graph_move_byterect_interpage(
	int src_left, int src_top, int src_right, int src_bottom,
	int dst_left, int dst_top,
	page_t src, page_t dst
);
/// --------

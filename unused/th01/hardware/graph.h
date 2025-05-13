#include "pc98.h"

void graph_400line_access_and_show_0();

// Fills the entire active page with the given [col].
void z_graph_clear_col(svc_t col);

void z_palette_white(void);
void z_palette_white_out(void);
void z_palette_show(void);

void z_grcg_pset(screen_x_t x, vram_y_t y, vc2 col);

// Returns the color value at the given point on the current VRAM page.
int z_graph_readdot(screen_x_t x, vram_y_t y);

// Draws the outline of a rectangle.
void graph_r_box(
	screen_x_t left, vram_y_t top, screen_x_t right, vram_y_t bottom, vc2 col
);

// Fades each hardware palette color from the given RGB value to its respective
// value in z_Palettes, blocking [step_ms] milliseconds at each of the 16 fade
// steps. If [keep] is nonzero for a specific color number, that color is
// excluded from the fade calculation and will stay at its z_Palettes value
// throughout the function.
void z_palette_fade_from(
	svc_comp_t from_r,
	svc_comp_t from_g,
	svc_comp_t from_b,
	vc2 keep[COLOR_COUNT],
	unsigned int step_ms
);

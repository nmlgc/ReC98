#include "platform.h"
#include "pc98.h"
#include "master.hpp"
#include "th01/hardware/egc.h"

// MSWIN.BFT sprites
enum setup_window_patnum_t {
	MSWIN_INSIDE,
	MSWIN_MIDDLE_TOP,
	MSWIN_MIDDLE_LEFT,
	MSWIN_MIDDLE_BOTTOM,
	MSWIN_MIDDLE_RIGHT,
	MSWIN_LEFT_TOP,
	MSWIN_LEFT_BOTTOM,
	MSWIN_RIGHT_BOTTOM,
	MSWIN_RIGHT_TOP,
};

// Coordinates
// -----------

static const pixel_t MSWIN_BORDER_H = 8;
static const pixel_t MSWIN_W = 16;
static const pixel_t MSWIN_H = 16;

static const pixel_t DROP_SPEED = (MSWIN_H / 2);
// -----------

typedef int mswin_tile_amount_t;

#define window window_tiles
static Palette8 palette_unused; // ZUN bloat
struct {
	mswin_tile_amount_t w;
	mswin_tile_amount_t h;

	pixel_t pixel_w(void) const {
		return (w * MSWIN_W);
	}
} window;

// Blits ([DROP_SPEED] + [MSWIN_H]) pixels in the Y direction.
void pascal near window_dropdown_put(
	screen_x_t left, screen_y_t bottom_tile_top
)
{
	egc_copy_rect_1_to_0_16(left, bottom_tile_top, window.pixel_w(), MSWIN_H);

	super_put(left, bottom_tile_top, MSWIN_MIDDLE_LEFT);
	super_put(left, (bottom_tile_top + DROP_SPEED), MSWIN_LEFT_BOTTOM);
	left += MSWIN_W;
	for(mswin_tile_amount_t x = 1; x < (window.w - 1); (x++, left += MSWIN_W)) {
		super_put(left, bottom_tile_top, MSWIN_INSIDE);
		super_put(left, (bottom_tile_top + DROP_SPEED), MSWIN_MIDDLE_BOTTOM);
	}
	super_put(left, bottom_tile_top, MSWIN_MIDDLE_RIGHT);
	super_put(left, (bottom_tile_top + DROP_SPEED), MSWIN_RIGHT_BOTTOM);
}

void pascal near window_rollup_put(screen_x_t left, screen_y_t bottom_tile_top)
{
	egc_copy_rect_1_to_0_16(
		left, (bottom_tile_top + DROP_SPEED), window.pixel_w(), MSWIN_H
	);

	super_put(left, bottom_tile_top, MSWIN_LEFT_BOTTOM);
	left += MSWIN_W;
	for(mswin_tile_amount_t x = 1; x < (window.w - 1); (x++, left += MSWIN_W)) {
		super_put(left, bottom_tile_top, MSWIN_MIDDLE_BOTTOM);
	}
	super_put(left, bottom_tile_top, MSWIN_RIGHT_BOTTOM);
}

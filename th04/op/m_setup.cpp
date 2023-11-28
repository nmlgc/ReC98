#include "platform.h"
#include "pc98.h"
#include "master.hpp"
#include "th01/hardware/egc.h"
extern "C" {
#include "th02/hardware/frmdelay.h"
}

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
static const int DROP_FRAMES_PER_TILE = (MSWIN_H / DROP_SPEED);
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
	pixel_t pixel_h(void) const {
		return (h * MSWIN_H);
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

void pascal near dropdown(screen_x_t left, screen_y_t top_)
{
	mswin_tile_amount_t i;
	screen_x_t tile_left = left;
	screen_y_t top = top_; // ZUN bloat

	super_put(tile_left, top, MSWIN_LEFT_TOP);
	tile_left += MSWIN_W;
	for(i = 1; i < (window.w - 1); (i++, tile_left += MSWIN_W)) {
		super_put(tile_left, top, MSWIN_MIDDLE_TOP);
	}
	super_put(tile_left, top, MSWIN_RIGHT_TOP);

	top += MSWIN_H;
	i = 1;
	while(i < ((window.h * DROP_FRAMES_PER_TILE) - DROP_FRAMES_PER_TILE - 1)) {
		window_dropdown_put(left, top);
		frame_delay(1);
		i++;
		top += DROP_SPEED;
	}
}

void pascal near singleline(screen_x_t left, screen_y_t top)
{
	egc_copy_rect_1_to_0_16(left, top, window.pixel_w(), (MSWIN_H * 2));

	super_put(left, (top + (0 * MSWIN_H)), MSWIN_LEFT_TOP);
	super_put(left, (top + (1 * MSWIN_H)), MSWIN_LEFT_BOTTOM);
	left += MSWIN_W;
	for(mswin_tile_amount_t x = 1; x < (window.w - 1); (x++, left += MSWIN_W)) {
		super_put(left, (top + (0 * MSWIN_H)), MSWIN_MIDDLE_TOP);
		super_put(left, (top + (1 * MSWIN_H)), MSWIN_MIDDLE_BOTTOM);
	}
	super_put(left, (top + (0 * MSWIN_H)), MSWIN_RIGHT_TOP);
	super_put(left, (top + (1 * MSWIN_H)), MSWIN_RIGHT_BOTTOM);
}

void pascal near rollup(screen_x_t left, screen_y_t top)
{
	screen_y_t bottom_tile_top = top;
	bottom_tile_top += (window.pixel_h() - MSWIN_H);

	mswin_tile_amount_t i = 1;
	while(i < ((window.h * DROP_FRAMES_PER_TILE) - DROP_FRAMES_PER_TILE)) {
		window_rollup_put(left, bottom_tile_top);
		frame_delay(1);
		i++;
		bottom_tile_top -= DROP_SPEED;
	}
}

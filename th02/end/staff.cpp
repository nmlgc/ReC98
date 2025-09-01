#include "planar.h"
#include "libs/master.lib/pc98_gfx.hpp"
#include "th01/math/polar.hpp"
#include "th02/v_colors.hpp"
#include "th02/math/vector.hpp"
#include "th02/hardware/frmdelay.h"
#include "th02/end/staff.hpp"

static const screen_x_t ROTRECT_CENTER_X = (
	STAFFROLL_PIC_LEFT + (CUTSCENE_PIC_W / 2)
);
static const screen_y_t ROTRECT_CENTER_Y = (
	STAFFROLL_PIC_TOP + (CUTSCENE_PIC_H / 2)
);

void pascal near rotrect_put(pixel_t rad, unsigned char angle)
{
	screen_x_t x[4];
	screen_y_t y[4];
	int i;
	for(i = 0; i < 4; i++) {
		x[i] = polar_x_fast(ROTRECT_CENTER_X, rad, angle);
		y[i] = polar_y_fast(ROTRECT_CENTER_Y, rad, angle);
		if(i & 1) {
			angle += 0x51;
		} else {
			angle += 0x2F;
		}
	}
	grcg_line(x[0], y[0], x[1], y[1]);
	grcg_line(x[1], y[1], x[2], y[2]);
	grcg_line(x[2], y[2], x[3], y[3]);
	grcg_line(x[3], y[3], x[0], y[0]);
}

#define page_access graph_accesspage
#include "th01/hardware/egcrect.cpp"

void pascal staffroll_rotrect_animate(
	unsigned char angle_speed, unsigned char angle_start
)
{
	enum {
		RECT_COUNT = 5,
		PADDING = 4,
		R_LEFT   = (STAFFROLL_PIC_LEFT - PADDING),
		R_TOP    = (STAFFROLL_PIC_TOP - PADDING),
		R_RIGHT  = (STAFFROLL_PIC_RIGHT + PADDING),
		R_BOTTOM = (STAFFROLL_PIC_TOP + CUTSCENE_PIC_H + PADDING),
		AREA_RIGHT = (STAFFROLL_PIC_LEFT + CUTSCENE_PIC_W + STAFFROLL_PIC_LEFT),

		SHRINK_FRAMES = 16,
		RADIUS_SHRINK_SPEED = 4,

		// The circumscribed circle of a rectangle with size w×h has the radius
		//
		// 	(√(w² + h²) / 2)
		//
		// which comes out to 188.68 for the 320×200 cutscene pic, or 194.20
		// for the padded 328×208 rectangle, so 192 is a decent approximation.
		// (See https://www.desmos.com/calculator/pvom3bvxb2)
		RAD_TARGET = 192,
		RAD_INITIAL = (RAD_TARGET + (RADIUS_SHRINK_SPEED * SHRINK_FRAMES)),
	};

	pixel_t rads[RECT_COUNT] = {
		RAD_INITIAL, RAD_INITIAL, RAD_INITIAL, RAD_INITIAL, RAD_INITIAL
	};

	// ZUN bloat: Redundant initialization with unused constants.
	unsigned char angles[RECT_COUNT] = { 0x29, 0x29, 0x29, 0x29, 0x29 };

	int i, j;
	for(i = 0; i < RECT_COUNT; i++) {
		angles[i] = angle_start;
	}
	grcg_setcolor(GC_RMW, 0);
	grcg_boxfill(0, 0, AREA_RIGHT, (RES_Y - 1));
	for(i = 0; i < (SHRINK_FRAMES + (RECT_COUNT - 1)); i++) {
		grcg_setcolor(GC_RMW, 0);

		// ZUN bug: This is supposed to unblit the rectangle that is about to
		// be removed from the screen. However, since the largest possible X
		// coordinate for a rectangle corner ([ROTRECT_CENTER_X + RAD_INITIAL])
		// (= 448) is larger than [AREA_RIGHT] (= 384), this will always touch
		// pixels outside of the area designated for this animation and set
		// them to black. With the Staff Roll starting at 416 pixels and never
		// being reblitted, this will cut black holes into the glyphs at
		// certain angles.
		rotrect_put(rads[0], angles[0]);

		angles[0] = angles[1];
		rads[0] = rads[1];
		grcg_setcolor(GC_RMW, 4);
		for(j = 1; j < (RECT_COUNT - 1); j++) {
			rotrect_put(rads[j], angles[j]);
			angles[j] = angles[j+1];
			rads[j] = rads[j+1];
		}
		grcg_setcolor(GC_RMW, V_WHITE);
		if(i < SHRINK_FRAMES) {
			rads[RECT_COUNT - 1] -= RADIUS_SHRINK_SPEED;
			angles[RECT_COUNT - 1] += angle_speed;
		}
		rotrect_put(rads[RECT_COUNT - 1], angles[RECT_COUNT - 1]);
		frame_delay(1);
	}
	grcg_setcolor(GC_RMW, 0);
	grcg_boxfill(0, 0, AREA_RIGHT, (RES_Y - 1));

	grcg_setcolor(GC_RMW, V_WHITE);
	grcg_line(R_RIGHT, R_TOP,    R_RIGHT, R_BOTTOM);
	grcg_line(R_RIGHT, R_BOTTOM, R_LEFT,  R_BOTTOM);
	grcg_line(R_LEFT,  R_BOTTOM, R_LEFT,  R_TOP);
	grcg_line(R_LEFT,  R_TOP,    R_RIGHT, R_TOP);
	grcg_off();

	palette_settone(200);
}

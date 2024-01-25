/* ReC98
 * -----
 * Code segment #5 of TH02's MAINE.EXE
 */

#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "th01/math/polar.hpp"
#include "th02/v_colors.hpp"
#include "th02/math/vector.hpp"
extern "C" {
#include "th02/hardware/frmdelay.h"
}

void pascal near rotrect_draw(int rad, unsigned char angle)
{
	screen_x_t x[4];
	screen_y_t y[4];
	int i;
	for(i = 0; i < 4; i++) {
		x[i] = polar_x_fast(192, rad, angle);
		y[i] = polar_y_fast(200, rad, angle);
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

#define graph_accesspage_func graph_accesspage
#include "th01/hardware/egcrect.cpp"

void pascal rotrect_animate(char rot_speed, char start_angle)
{
	int rads[] = {256, 256, 256, 256, 256};
	char angles[] = {0x29, 0x29, 0x29, 0x29, 0x29};
	int i, j;
	for(i = 0; i < 5; i++) {
		angles[i] = start_angle;
	}
	grcg_setcolor(GC_RMW, 0);
	grcg_boxfill(0, 0, 384, 399);
	for(i = 0; i < 20; i++) {
		grcg_setcolor(GC_RMW, 0);
		rotrect_draw(rads[0], angles[0]);
		angles[0] = angles[1];
		rads[0] = rads[1];
		grcg_setcolor(GC_RMW, 4);
		for(j = 1; j < 4; j++) {
			rotrect_draw(rads[j], angles[j]);
			angles[j] = angles[j+1];
			rads[j] = rads[j+1];
		}
		grcg_setcolor(GC_RMW, V_WHITE);
		if(i < 16) {
			rads[4] -= 4;
			angles[4] += rot_speed;
		}
		rotrect_draw(rads[4], angles[4]);
		frame_delay(1);
	}
	grcg_setcolor(GC_RMW, 0);
	grcg_boxfill(0, 0, 384, 399);
	grcg_setcolor(GC_RMW, V_WHITE);
	grcg_line(356,  96, 356, 304);
	grcg_line(356, 304,  28, 304);
	grcg_line( 28, 304,  28,  96);
	grcg_line( 28,  96, 356,  96);
	grcg_off();
	palette_white();
}

#pragma option -zCSHARED -3

extern "C" {
#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "th03/formats/pi.h"

void pascal pi_put_quarter_8(
	screen_x_t left, vram_y_t top, int slot, int quarter
)
{
	pi_buffer_p_t row_p;

	pi_buffer_p_init(row_p, slot);
	if(quarter == 1) {
		pi_buffer_p_offset(row_p, PI_QUARTER_W, 0);
	} else if(quarter == 2) {
		pi_buffer_p_offset(row_p, 0, PI_QUARTER_H);
	} else if(quarter == 3) {
		pi_buffer_p_offset(row_p, PI_QUARTER_W, PI_QUARTER_H);
	}
	pi_buffer_p_normalize(row_p);

	for(pixel_t y_in_quarter = 0; y_in_quarter < PI_QUARTER_H; y_in_quarter++) {
		graph_pack_put_8(left, top, row_p, PI_QUARTER_W);
		top++;
		if(top >= RES_Y) {
			top -= RES_Y;
		}
		pi_buffer_p_offset(row_p, PI_W, 0);
		pi_buffer_p_normalize(row_p);
	}
}

}

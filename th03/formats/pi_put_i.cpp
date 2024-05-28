#pragma option -zCSHARED

#include "th03/formats/pi.hpp"

void pascal pi_put_interlace_8(screen_x_t left, vram_y_t top, int slot)
{
	pi_buffer_p_t row_p;
	pixel_t y;

	pi_buffer_p_init(row_p, slot);
	for(y = 0; y < pi_headers[slot].ysize; y += 2) {
		graph_pack_put_8(left, top, row_p, pi_headers[slot].xsize);
		top++;
		if(top >= RES_Y) {
			top -= RES_Y;
		}
		row_p += pi_headers[slot].xsize; // = pi_buffer_p_next_row(), twice
		pi_buffer_p_normalize(row_p);
	}
}

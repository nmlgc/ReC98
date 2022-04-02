#pragma option -zCSHARED -3

#include <mem.h>
#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "master.hpp"
extern "C" {
#include "th02/formats/pi.h"

void DEFCONV pi_palette_apply(int slot)
{
	palette_set_all(pi_headers[slot].palette);
	palette_show();
}

void DEFCONV pi_put_8(screen_x_t left, vram_y_t top, int slot)
{
	pi_buffer_p_t row_p;
	pixel_t y;

	pi_buffer_p_init(row_p, slot);
	for(y = 0; y < pi_headers[slot].ysize; y++) {
		graph_pack_put_8(left, top, row_p, pi_headers[slot].xsize);
		top++;
		if(top >= RES_Y) {
			top -= RES_Y;
		}
		pi_buffer_p_next_row(row_p, slot);
		pi_buffer_p_normalize(row_p);
	}
}

}

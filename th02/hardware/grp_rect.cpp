#pragma option -zCSHARED -3

#include "planar.h"
#include "libs/master.lib/pc98_gfx.hpp"
#include "th02/hardware/grp_rect.h"

void pascal graph_copy_rect_1_to_0_16(
	screen_x_t left, vram_y_t top, pixel_t w, pixel_t h
)
{
	vram_offset_t row_p = vram_offset_shift(left, top);
	pixel_t row;
	for(row = 0; row < h; row++) {
		vram_word_amount_t col;
		int p;
		for(col = 0, p = row_p; col < (w >> 4); col++, p += 2) {
			if(row_p >= 0) {
				Planar<dots16_t> p16;
				graph_accesspage(1);	VRAM_SNAP_PLANAR(p16, p, 16);
				graph_accesspage(0);	VRAM_PUT_PLANAR(p, p16, 16);
			}
		}
		row_p += ROW_SIZE;
	}
}

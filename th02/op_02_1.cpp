/* ReC98
 * -----
 * 1st part of code segment #2 of TH02's OP.EXE
 */

#pragma codeseg SHARED
#pragma option -3

extern "C" {
#include "th02/th02.h"
#include "th02/formats/pi.h"

resident_t *resident;
char unused_op_2_3;
char lives;
char bombs;
long unused_4;
long unused_5;

#include "th01/hardware/vplanset.c"
#include "th02/formats/pi_load.c"

void pascal graph_copy_rect_1_to_0(
	screen_x_t x, vram_y_t y, pixel_t w, pixel_t h
)
{
	vram_offset_t row_p = vram_offset_shift(x, y);
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

}

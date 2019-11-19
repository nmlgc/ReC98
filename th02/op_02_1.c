/* ReC98
 * -----
 * 1st part of code segment #2 of TH02's OP.EXE
 */

#include "th02/th02.h"
#include "th02/initexit.h"

#pragma codeseg op_02_TEXT
#pragma option -3

#include "th02/exit_dos.c"
#include "th02/zunerror.c"
#include "th02/hardware/grppsafx.c"
#include "th01/hardware/vplanset.c"
#include "th02/formats/pi_load.c"

void pascal graph_copy_rect_1_to_0(int x, int y, int w, int h)
{
	int row_p = VRAM_OFFSET(x, y);
	int row;
	for(row = 0; row < h; row++) {
		int col;
		int p;
		for(col = 0, p = row_p; col < (w >> 4); col++, p += 2) {
			if(row_p >= 0) {
				vram_planar_16_pixels_t p16;
				graph_accesspage(1);
				p16.B = *(int*)(VRAM_PLANE_B + p);
				p16.R = *(int*)(VRAM_PLANE_R + p);
				p16.G = *(int*)(VRAM_PLANE_G + p);
				p16.E = *(int*)(VRAM_PLANE_E + p);
				graph_accesspage(0);
				*(int*)(VRAM_PLANE_B + p) = p16.B;
				*(int*)(VRAM_PLANE_R + p) = p16.R;
				*(int*)(VRAM_PLANE_G + p) = p16.G;
				*(int*)(VRAM_PLANE_E + p) = p16.E;
			}
		}
		row_p += ROW_SIZE;
	}
}

#include "th02/hardware/frmdely2.c"

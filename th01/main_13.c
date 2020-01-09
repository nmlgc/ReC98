/* ReC98
 * -----
 * Code segment #13 of TH01's REIIDEN.EXE
 */

#include "th01/th01.h"

#pragma option -2
#pragma option -O-
#pragma option -Z-

#include "th01/grps2xsc.c"

void egc_copy_wave_1_to_0(int x, int y, int len, int amp, int ph, int w, int h)
{
	int row;
	int t = ph;
	for(row = 0; row < h; row++) {
		int x_wave = (((long)amp * Sin8(t)) / 256) + x;
		t += 256 / len;
		egc_copy_rect_1_to_0(x_wave, y + row, w, 1);
	}
}

void graph_copy_hline_mask_1_to_0(int x, int y, char *mask, int w)
{
	vram_planar_8_pixels_t px8;
	int col;
	register int p = VRAM_OFFSET(x, y);
	for(col = 0; col < w; col++, p++) {
		if(mask[col]) {
			graph_accesspage_func(1);
			px8.B = mask[col] & VRAM_PLANE_B[p];
			px8.R = mask[col] & VRAM_PLANE_R[p];
			px8.G = mask[col] & VRAM_PLANE_G[p];
			px8.E = mask[col] & VRAM_PLANE_E[p];
			graph_accesspage_func(0);
			grcg_setcolor_rmw(0);
			VRAM_PLANE_B[p] = mask[col];
			grcg_off();
			VRAM_PLANE_B[p] |= px8.B;
			VRAM_PLANE_R[p] |= px8.R;
			VRAM_PLANE_G[p] |= px8.G;
			VRAM_PLANE_E[p] |= px8.E;
		}
	}
}

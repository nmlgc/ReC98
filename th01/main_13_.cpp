/* ReC98
 * -----
 * 2nd part of code segment #13 of TH01's REIIDEN.EXE
 */

extern "C" {
#include "th01/th01.h"

#pragma option -2
#pragma option -O-
#pragma option -Z-

#include "th01/hardware/grp2xscs.c"

void egc_wave_unput(int left, int top, int len, int amp, int ph, int w, int h)
{
	int t = ph;
	for(int y = 0; y < h; y++) {
		int x = (((long)amp * Sin8(t)) / 256) + left;
		t += 256 / len;
		egc_copy_rect_1_to_0(x, top + y, w, 1);
	}
}

void graph_hline_unput_masked(int left, int top, dots8_t *mask, int w)
{
	planar8_t px8;
	register uint16_t p = vram_offset_shift(left, top);
	for(int x = 0; x < w; x++, p++) {
		if(mask[x]) {
			graph_accesspage_func(1);
			px8.B = mask[x] & VRAM_PLANE_B[p];
			px8.R = mask[x] & VRAM_PLANE_R[p];
			px8.G = mask[x] & VRAM_PLANE_G[p];
			px8.E = mask[x] & VRAM_PLANE_E[p];
			graph_accesspage_func(0);
			grcg_setcolor_rmw(0);
			VRAM_PLANE_B[p] = mask[x];
			grcg_off();
			VRAM_PLANE_B[p] |= px8.B;
			VRAM_PLANE_R[p] |= px8.R;
			VRAM_PLANE_G[p] |= px8.G;
			VRAM_PLANE_E[p] |= px8.E;
		}
	}
}

}

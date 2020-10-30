/* ReC98
 * -----
 * 2nd part of code segment #13 of TH01's REIIDEN.EXE
 */

#pragma codeseg main_13_TEXT
#pragma option -2 -O- -Z-

extern "C" {
#include "th01/th01.h"
#include "th01/math/wave.hpp"
#include "th01/hardware/planar.h"

#include "th01/hardware/grp2xscs.cpp"

void egc_wave_unput(
	screen_x_t left,
	vram_y_t top,
	int len,
	pixel_t amp,
	int ph,
	pixel_t w,
	pixel_t h
)
{
	int t = ph;
	for(pixel_t y = 0; y < h; y++) {
		screen_x_t x = (wave_x(amp, t) + left);
		t += (0x100 / len);
		egc_copy_rect_1_to_0_16(x, top + y, w, 1);
	}
}

void graph_hline_unput_masked_8(
	screen_x_t left, vram_y_t top, dots8_t *mask, vram_byte_amount_t vram_w
)
{
	Planar<dots8_t> px8;
	register vram_offset_t p = vram_offset_shift(left, top);
	for(vram_byte_amount_t x = 0; x < vram_w; x++, p++) {
		if(mask[x]) {
			graph_accesspage_func(1);
			px8.B = mask[x] & VRAM_PLANE_B[p];
			px8.R = mask[x] & VRAM_PLANE_R[p];
			px8.G = mask[x] & VRAM_PLANE_G[p];
			px8.E = mask[x] & VRAM_PLANE_E[p];
			graph_accesspage_func(0);
			vram_erase(p, mask[x], 8);
			VRAM_PLANE_B[p] |= px8.B;
			VRAM_PLANE_R[p] |= px8.R;
			VRAM_PLANE_G[p] |= px8.G;
			VRAM_PLANE_E[p] |= px8.E;
		}
	}
}

}

#pragma option -zCGRAPH_EX_TEXT -2 -O- -Z-

#include "platform.h"
#include "pc98.h"
#include "planar.h"
extern "C" {
#include "th01/hardware/graph.h"
}
#include "th01/hardware/planar.h"
#include "th01/hardware/grph1to0.hpp"

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

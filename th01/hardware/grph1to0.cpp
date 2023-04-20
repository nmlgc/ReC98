#pragma option -zCGRAPH_EX_TEXT

#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "platform/x86real/pc98/page.hpp"
#include "th01/hardware/graph.h"
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
			page_access(1);
			px8.B = mask[x] & VRAM_CHUNK(B, p, 8);
			px8.R = mask[x] & VRAM_CHUNK(R, p, 8);
			px8.G = mask[x] & VRAM_CHUNK(G, p, 8);
			px8.E = mask[x] & VRAM_CHUNK(E, p, 8);
			page_access(0);
			vram_erase(p, mask[x], 8);
			VRAM_CHUNK(B, p, 8) |= px8.B;
			VRAM_CHUNK(R, p, 8) |= px8.R;
			VRAM_CHUNK(G, p, 8) |= px8.G;
			VRAM_CHUNK(E, p, 8) |= px8.E;
		}
	}
}

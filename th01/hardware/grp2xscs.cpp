#pragma option -zCGRAPH_EX_TEXT

#include <stdlib.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "shiftjis.hpp"
#include "th01/hardware/graph.h"
#include "th01/hardware/grp_text.hpp"
#include "th01/hardware/grp2xscs.hpp"

void scale_2x(dots32_t &dst32, sdots16_t src16)
{
	dots32_t mask = 1;
	dots32_t srcex = 0;
	dots32_t dst_local;
	int i;

	srcex = src16;
	dst_local = 0;
	dst32 = 0;
	for(i = 0; i < 16; i++) {
		dst_local |= _lrotl(srcex & mask, ((i * 2) + 0) - i);
		dst_local |= _lrotl(srcex & mask, ((i * 2) + 1) - i);
		mask = _lrotl(mask, 1);
	}
	mask = 0x00FF00FF;	dst32 |= _lrotl(dst_local & mask, 8);
	mask = 0xFF00FF00;	dst32 |= _lrotr(dst_local & mask, 8);
}

void graph_2xscale_byterect_1_to_0_slow(
	screen_x_t left_0, vram_y_t top_0,
	screen_x_t left_1, vram_y_t top_1, pixel_t w_1, pixel_t h_1
)
{
	vram_offset_t row_p1 = vram_offset_divmul(left_1, top_1);
	vram_offset_t row_p0 = vram_offset_divmul(left_0, top_0);
	vram_word_amount_t col16;
	pixel_t row;
	Planar<dots16_t> px16;
	dots16_t px16_nonzero;

	for(row = 0; row < h_1; row++) {
		vram_offset_t p0 = row_p0;
		vram_offset_t p1 = row_p1;
		for(col16 = 0; col16 < w_1 / 16; col16++) {
			vram_byte_amount_t scale_p;
			graph_accesspage_func(1);
			VRAM_SNAP_PLANAR(px16, p1, 16);
			px16_nonzero = (px16.B | px16.R | px16.G | px16.E);
			for(scale_p = 0; scale_p < (ROW_SIZE * 2); scale_p += ROW_SIZE) {
				dots32_t dst32;
				dots32_t px32_nonzero;

				// Parentheses omitted for code generation reasons.
				graph_accesspage_func(0);
				scale_2x(px32_nonzero, px16_nonzero);
				grcg_setcolor_rmw(0);
				grcg_put(p0 + scale_p, px32_nonzero, 32);
				grcg_off_func();

				scale_2x(dst32, px16.B);
				VRAM_CHUNK(B, p0 + scale_p, 32) |= dst32;

				scale_2x(dst32, px16.R);
				VRAM_CHUNK(R, p0 + scale_p, 32) |= dst32;

				scale_2x(dst32, px16.G);
				VRAM_CHUNK(G, p0 + scale_p, 32) |= dst32;

				scale_2x(dst32, px16.E);
				VRAM_CHUNK(E, p0 + scale_p, 32) |= dst32;
			}
			p1 += static_cast<vram_byte_amount_t>(sizeof(dots16_t));
			p0 += static_cast<vram_byte_amount_t>(sizeof(dots32_t));
		}
		row_p0 += (ROW_SIZE * 2);
		row_p1 += ROW_SIZE;
	}
}

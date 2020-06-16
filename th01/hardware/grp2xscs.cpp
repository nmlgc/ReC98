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
	int left_0, int top_0,
	int left_1, int top_1, int w_1, int h_1
)
{
	int row_p1 = vram_offset_divmul(left_1, top_1);
	int row_p0 = vram_offset_divmul(left_0, top_0);
	int col16;
	int row;
	Planar<dots16_t> px16;
	dots16_t px16_nonzero;

	for(row = 0; row < h_1; row++) {
		int p0 = row_p0;
		int p1 = row_p1;
		for(col16 = 0; col16 < w_1 / 16; col16++) {
			int scale_p;
			graph_accesspage_func(1);
			VRAM_SNAP_PLANAR(px16, p1, 16);
			px16_nonzero = px16.B | px16.R | px16.G | px16.E;
			for(scale_p = 0; scale_p < ROW_SIZE * 2; scale_p += ROW_SIZE) {
				dots32_t dst32;
				dots32_t px32_nonzero;

				graph_accesspage_func(0);
				scale_2x(px32_nonzero, px16_nonzero);
				grcg_setcolor_rmw(0);
				*(dots32_t*)(VRAM_PLANE_B + p0 + scale_p) = px32_nonzero;
				grcg_off();

				scale_2x(dst32, px16.B);
				*(dots32_t*)(VRAM_PLANE_B + p0 + scale_p) |= dst32;

				scale_2x(dst32, px16.R);
				*(dots32_t*)(VRAM_PLANE_R + p0 + scale_p) |= dst32;

				scale_2x(dst32, px16.G);
				*(dots32_t*)(VRAM_PLANE_G + p0 + scale_p) |= dst32;

				scale_2x(dst32, px16.E);
				*(dots32_t*)(VRAM_PLANE_E + p0 + scale_p) |= dst32;
			}
			p1 += 2;
			p0 += 4;
		}
		row_p0 += ROW_SIZE * 2;
		row_p1 += ROW_SIZE;
	}
}

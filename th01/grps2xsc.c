void scale_2x(planar32_t *dst32, splanar16_t src16)
{
	planar32_t mask = 1;
	planar32_t srcex = 0;
	planar32_t dst_local;
	int i;

	srcex = src16;
	dst_local = 0;
	*dst32 = 0;
	for(i = 0; i < 16; i++) {
		dst_local |= _lrotl(srcex & mask, ((i * 2) + 0) - i);
		dst_local |= _lrotl(srcex & mask, ((i * 2) + 1) - i);
		mask = _lrotl(mask, 1);
	}
	mask = 0x00FF00FF;	*dst32 |= _lrotl(dst_local & mask, 8);
	mask = 0xFF00FF00;	*dst32 |= _lrotr(dst_local & mask, 8);
}

void graph_slow_2xscale_rect_1_to_0(int x0, int y0, int x1, int y1, int w1, int h1)
{
	int row_p1 = (x1 / 8) + (y1 * ROW_SIZE);
	int row_p0 = (x0 / 8) + (y0 * ROW_SIZE);
	int col16;
	int row;
	vram_planar_16_pixels_t px16;
	planar16_t px16_nonzero;

	for(row = 0; row < h1; row++) {
		int p0 = row_p0;
		int p1 = row_p1;
		for(col16 = 0; col16 < w1 / 16; col16++) {
			int scale_p;
			graph_accesspage_func(1);
			VRAM_SNAP_4(px16, p1, 16);
			px16_nonzero = px16.B | px16.R | px16.G | px16.E;
			for(scale_p = 0; scale_p < ROW_SIZE * 2; scale_p += ROW_SIZE) {
				planar32_t dst32;
				planar32_t px32_nonzero;

				graph_accesspage_func(0);
				scale_2x(&px32_nonzero, px16_nonzero);
				grcg_setcolor_rmw(0);
				*(planar32_t*)(VRAM_PLANE_B + p0 + scale_p) = px32_nonzero;
				grcg_off();

				scale_2x(&dst32, px16.B);
				*(planar32_t*)(VRAM_PLANE_B + p0 + scale_p) |= dst32;

				scale_2x(&dst32, px16.R);
				*(planar32_t*)(VRAM_PLANE_R + p0 + scale_p) |= dst32;

				scale_2x(&dst32, px16.G);
				*(planar32_t*)(VRAM_PLANE_G + p0 + scale_p) |= dst32;

				scale_2x(&dst32, px16.E);
				*(planar32_t*)(VRAM_PLANE_E + p0 + scale_p) |= dst32;
			}
			p1 += 2;
			p0 += 4;
		}
		row_p0 += ROW_SIZE * 2;
		row_p1 += ROW_SIZE;
	}
}

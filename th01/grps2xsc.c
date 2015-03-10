void scale_2x(unsigned long *dst32, int src16)
{
	unsigned long mask = 1;
	unsigned long srcex = 0;
	unsigned long dst_local;
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
	int px16_nonzero;

	for(row = 0; row < h1; row++) {
		int p0 = row_p0;
		int p1 = row_p1;
		for(col16 = 0; col16 < w1 / 16; col16++) {
			int scale_p;
			graph_accesspage(1);
			px16.B = *(int*)(VRAM_PLANE_B + p1);
			px16.R = *(int*)(VRAM_PLANE_R + p1);
			px16.G = *(int*)(VRAM_PLANE_G + p1);
			px16.E = *(int*)(VRAM_PLANE_E + p1);
			px16_nonzero = px16.B | px16.R | px16.G | px16.E;
			for(scale_p = 0; scale_p < ROW_SIZE * 2; scale_p += ROW_SIZE) {
				unsigned long dst32;
				unsigned long px32_nonzero;

				graph_accesspage(0);
				scale_2x(&px32_nonzero, px16_nonzero);
				grcg_setcolor_rmw(0);
				*(long*)(VRAM_PLANE_B + p0 + scale_p) = px32_nonzero;
				grcg_off();

				scale_2x(&dst32, px16.B);  
				*(long*)(VRAM_PLANE_B + p0 + scale_p) |= dst32;

				scale_2x(&dst32, px16.R);
				*(long*)(VRAM_PLANE_R + p0 + scale_p) |= dst32;

				scale_2x(&dst32, px16.G);
				*(long*)(VRAM_PLANE_G + p0 + scale_p) |= dst32;

				scale_2x(&dst32, px16.E);
				*(long*)(VRAM_PLANE_E + p0 + scale_p) |= dst32;
			}
			p1 += 2;
			p0 += 4;
		}
		row_p0 += ROW_SIZE * 2;
		row_p1 += ROW_SIZE;
	}
}

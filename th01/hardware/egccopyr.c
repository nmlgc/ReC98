#include "th01/hardware/egcscopy.c"

void egc_copy_rect_1_to_0(int x, int y, int w, int h)
{
	register int x_end = x;
	register int x_floor = x_end;
	int row;
	int col;
	int row_p;
	dots16_t dots;
	int p;

	x_end += w;
	x_floor &= 0xFFF0;
	row_p = VRAM_OFFSET(x_floor, y);
	egc_start_copy();
	for(row = 0; row < h; row++) {
		for(col = x_floor, p = row_p; col < x_end; p += 2, col += 16) {
			graph_accesspage_func(1); VRAM_SNAP(dots, B, p, 16);
			graph_accesspage_func(0); VRAM_PUT(B, p, dots, 16);
		}
		row_p += 640 / 8;
	}
	egc_off();
}

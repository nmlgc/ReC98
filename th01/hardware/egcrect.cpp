#include "th01/hardware/egcstart.cpp"

void egc_copy_rect_1_to_0_16(screen_x_t x, vram_y_t y, pixel_t w, pixel_t h)
{
	register screen_x_t x_end = x;
	register screen_x_t x_floor = x_end;
	pixel_t row;
	screen_x_t col;
	vram_offset_t row_p;
	dots16_t dots;
	vram_offset_t p;

	x_end += w;
	x_floor &= 0xFFF0;
	row_p = vram_offset_shift(x_floor, y);
	egc_start_copy();
	for(row = 0; row < h; row++) {
		for(col = x_floor, p = row_p; col < x_end; p += 2, col += 16) {
			graph_accesspage_func(1); egc_snap(dots, p, 16);
			graph_accesspage_func(0); egc_put(p, dots, 16);
		}
		row_p += ROW_SIZE;
	}
	egc_off();
}

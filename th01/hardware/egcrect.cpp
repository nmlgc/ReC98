#include "th01/hardware/egcstart.cpp"

void egc_copy_rect_1_to_0_16(screen_x_t x, vram_y_t y, pixel_t w, pixel_t h)
{
	register screen_x_t x_end = x;
	register screen_x_t x_floor = x_end;
	pixel_t row;
	screen_x_t column;
	vram_offset_t vo_row;
	egc_temp_t tmp;
	vram_offset_t vo;

	x_end += w;
	x_floor &= 0xFFF0;
	vo_row = vram_offset_shift(x_floor, y);
	egc_start_copy();
	for(row = 0; row < h; row++) {
		for(
			(column = x_floor, vo = vo_row);
			column < x_end;
			(vo += EGC_REGISTER_SIZE, column += EGC_REGISTER_DOTS)
		) {
			graph_accesspage_func(1);	tmp = egc_chunk(vo);
			graph_accesspage_func(0);	egc_chunk(vo) = tmp;
		}
		vo_row += ROW_SIZE;
	}
	egc_off();
}

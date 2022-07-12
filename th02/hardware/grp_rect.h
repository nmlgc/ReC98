// Blits the rectangle from
// 	(⌊left/8⌋*8, top)
// to
// 	(((⌊left/8⌋*8) + (⌊w/16⌋*16)), (top + h))
// from VRAM page 1 to the same position on VRAM page 0.
void pascal graph_copy_rect_1_to_0_16(
	screen_x_t left, vram_y_t top, pixel_t w, pixel_t h
);

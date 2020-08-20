// Performs a very slow, unoptimized, 2× nearest-neighbor scale of the
// rectangle from
//     (⌊left_1/8⌋*8, top_1) - (⌊left_1/8⌋*8 + ⌊w_1/16⌋*16, top_1 + h_1)
// on plane #1 to
//     (⌊left_0/8⌋*8, top_0) - (⌊left_1/8⌋*8 + ⌊w_1/16⌋*32, top_1 + h_1*2)
// on plane #0.
void graph_2xscale_byterect_1_to_0_slow(
	screen_x_t left_0, vram_y_t top_0,
	screen_x_t left_1, vram_y_t top_1, int w_1, int h_1
);

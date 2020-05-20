// Performs a very slow, unoptimized, 2× nearest-neighbor scale of the
// rectangle from
//     (⌊left_1/8⌋*8, top_1) - (⌊left_1/8⌋*8 + ⌊w_1/16⌋*16, top_1 + h_1)
// on plane #1 to
//     (⌊left_0/8⌋*8, top_0) - (⌊left_1/8⌋*8 + ⌊w_1/16⌋*32, top_1 + h_1*2)
// on plane #0.
void graph_2xscale_byterect_1_to_0_slow(
	int left_0, int top_0,
	int left_1, int top_1, int w_1, int h_1
);

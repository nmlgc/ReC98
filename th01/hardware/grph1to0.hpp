// Recovers the dots set in the given [mask] from (⌊left/8⌋*8, top) to
// (⌊(left/8) + w⌋*8, top) from VRAM page 1.
void graph_hline_unput_masked_8(
	screen_x_t left, vram_y_t top, dots8_t *mask, vram_byte_amount_t vram_w
);

// Performs a very slow, unoptimized, 2× nearest-neighbor scale of the
// rectangle from
//     (⌊left_1/8⌋*8, top_1) - (⌊left_1/8⌋*8 + ⌊w_1/16⌋*16, top_1 + h_1)
// on plane #1 to
//     (⌊left_0/8⌋*8, top_0) - (⌊left_1/8⌋*8 + ⌊w_1/16⌋*32, top_1 + h_1*2)
// on plane #0.
void graph_2xscale_byterect_1_to_0_slow(
	screen_x_t left_0, vram_y_t top_0,
	screen_x_t left_1, vram_y_t top_1, pixel_t w_1, pixel_t h_1
);

// Convenience function for blitting and scaling rows of glyphs
// ------------------------------------------------------------
// (Which are the only things that this 2× scale is performed on anyway.)

// Blits [str] to the given glyph [row] with the given color and effects, for
// a later 2× scale of the
inline void graph_glyphrow_put(int row, int col_and_fx, const char *str) {
	graph_putsa_fx(0, (GLYPH_H * row), (FX_CLEAR_BG | col_and_fx), str);
}

// Performs a 2× nearest-neighbor scale of the first [w_1x] pixels from the
// given glyph [row] on VRAM page 1 to (⌊left_0/8⌋*8, top_0) on VRAM page 0.
inline void graph_glyphrow_2xscale_1_to_0(
	screen_x_t left_0, vram_y_t top_0, int row, pixel_t w_1x
) {
	graph_2xscale_byterect_1_to_0_slow(
		left_0, top_0, 0, (GLYPH_H * row), w_1x, GLYPH_H
	);
}
// ------------------------------------------------------------

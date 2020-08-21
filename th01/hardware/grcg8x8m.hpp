// Blits the given monochrome 8×8 [sprite] to the VRAM position indicated by
// [vram_offset_topleft] and [first_bit], in the given [col] via the GRCG.
void grcg_put_8x8_mono(
	vram_offset_t vram_offset_topleft,
	char first_bit,
	const dots8_t sprite[8],
	int col
);

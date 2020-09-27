#include "th01/sprites/ileave_m.h"

// Combines the pixels from both VRAM pages in the 8×8 square starting at
// (⌊left/8⌋*8, top), using one of the interlace masks. The resulting square
// is blitted to VRAM page 0.
void graph_interleave_pages_8x8_8(screen_x_t left, vram_y_t top, int mask_id)
{
	const interleave_masks_t masks = sINTERLEAVE_MASKS;

	vram_offset_t vram_offset = vram_offset_divmul(left, top);
	dots8_t dots;
	for(char y = 0; y < INTERLEAVE_W; y++) {
		#define mask masks.dots[mask_id][y]

		#define snap(plane, vram_offset) \
			VRAM_CHUNK(plane, vram_offset, 8)

		#define interleave(plane, vram_offset) \
			graph_accesspage_func(1); dots = ~mask & snap(plane, vram_offset); \
			graph_accesspage_func(0); dots |= mask & snap(plane, vram_offset); \
			graph_accesspage_func(0); VRAM_PUT(plane, vram_offset, dots, 8);

		interleave(B, vram_offset);
		interleave(R, vram_offset);
		interleave(G, vram_offset);
		interleave(E, vram_offset);
		vram_offset += ROW_SIZE;

		#undef interleave
		#undef snap
		#undef mask
	}
}

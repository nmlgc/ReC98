#include "th01/hardware/grcg8x8m.hpp"

void grcg_put_8x8_mono(
	vram_offset_t vram_offset_topleft,
	char first_bit,
	const dot_rect_t(8, 8)& sprite,
	int col
)
{
	grcg_setcolor_rmw(col);
	for(pixel_t y = 0; y < sprite.h(); y++) {
		dots16_t d = (
			(sprite[y] >> first_bit) + (sprite[y] << (16 - first_bit))
		);
		grcg_put(vram_offset_topleft, d, 16);
		vram_offset_topleft += ROW_SIZE;
		if(vram_offset_topleft >= PLANE_SIZE) {
			break;
		}
	}
	grcg_off();
}

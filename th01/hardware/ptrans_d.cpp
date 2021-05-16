#include "th01/sprites/ileave_m.hpp"
#include "th01/hardware/palette.h"
#include "th01/hardware/ptrans.hpp"

// Combines the pixels from both VRAM pages in the 8×8 square starting at
// (⌊left/8⌋*8, top), using one of the interlace masks. The resulting square
// is blitted to VRAM page 0.
void graph_interleave_pages_8x8_8(screen_x_t left, vram_y_t top, int mask_id)
{
	const interleave_masks_t masks = sINTERLEAVE_MASKS;

	vram_offset_t vram_offset = vram_offset_divmul(left, top);
	dots8_t dots;
	for(char y = 0; y < INTERLEAVE_H; y++) {
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

void pagetrans_diagonal_8x8(unsigned int step_ms)
{
	pagetrans_diagonal_8x8_with_palette(step_ms, z_Palettes, z_Palettes);
}

static const int FRAME_COUNT = (
	(RES_X / INTERLEAVE_W) + (RES_Y / INTERLEAVE_H)
);

void pagetrans_diagonal_8x8_with_palette(
	unsigned int step_ms, Palette4 &pal_cur, const Palette4 &pal_target
)
{
	int comp;
	int col;
	screen_x_t from_topleft_left = 0;
	vram_y_t from_topleft_top = 0;
	screen_x_t from_bottomright_left = (RES_X - INTERLEAVE_W);
	vram_y_t from_bottomright_top = (RES_Y - INTERLEAVE_H);
	screen_x_t tip_left;
	vram_y_t tip_top;

	for(int frame = 0; frame < FRAME_COUNT; frame++) {
		tip_left = from_topleft_left;
		tip_top = from_topleft_top;
		while((from_topleft_left >= 0) && (from_topleft_top <= (RES_Y - 1))) {
			graph_interleave_pages_8x8_8(
				from_topleft_left, from_topleft_top, 1
			);
			from_topleft_left -= INTERLEAVE_W;
			from_topleft_top += INTERLEAVE_H;
		}

		from_topleft_left = (tip_left < (RES_X - INTERLEAVE_W))
			? (tip_left + INTERLEAVE_W)
			: tip_left;
		from_topleft_top = (tip_left < (RES_X - INTERLEAVE_W))
			? 0
			: (tip_top + INTERLEAVE_H);

		if((frame % (FRAME_COUNT / COLOR_COUNT)) == 0) {
			for(col = 0; col < COLOR_COUNT; col++) {
				// Not identical to the ramping loop in z_palette_fade_from()!
				for(comp = 0; comp < COMPONENT_COUNT; comp++) {
					if(pal_cur[col].v[comp] != pal_target[col].v[comp]) {
						pal_cur.colors[col].v[comp] +=
							(pal_cur[col].v[comp] > pal_target[col].v[comp])
							? -1
							:  1;
					}
				}
			}
			z_palette_set_all_show(pal_cur);
		}

		tip_left = from_bottomright_left;
		tip_top = from_bottomright_top;
		while(
			(from_bottomright_left >= 0) &&
			(from_bottomright_top <= (RES_Y - 1))
		) {
			graph_interleave_pages_8x8_8(
				from_bottomright_left, from_bottomright_top, 2
			);
			from_bottomright_left -= INTERLEAVE_W;
			from_bottomright_top += INTERLEAVE_H;
		}

		from_bottomright_left = (tip_top > 0)
			? (RES_X - INTERLEAVE_W)
			: (tip_left - INTERLEAVE_W);
		from_bottomright_top = (tip_top > 0)
			? (tip_top - INTERLEAVE_H)
			: tip_top;

		delay(step_ms);
	}
}

#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "decomp.hpp"
#include "shiftjis.hpp"
#include "master.hpp"
#include "th03/cutscene/cutscene.hpp"

typedef enum {
	BOX_MASK_0,
	BOX_MASK_1,
	BOX_MASK_2,
	BOX_MASK_3,
	BOX_MASK_COPY,
	BOX_MASK_COUNT,

	_box_mask_t_FORCE_UINT16 = 0xFFFF
} box_mask_t;

// Copies the text box area from VRAM page 1 to VRAM page 0, applying the
// given [mask]. Assumes that the EGC is active, and initialized for a copy.
void pascal near box_1_to_0_masked(box_mask_t mask)
{
	extern const dot_rect_t(16, 4) BOX_MASKS[BOX_MASK_COUNT];
	egc_temp_t tmp;

	for(screen_y_t y = BOX_TOP; y < BOX_BOTTOM; y++) {
		outport2(EGC_READPLANEREG, 0x00ff);
		// EGC_COMPAREREAD | EGC_WS_PATREG | EGC_RL_MEMREAD
		outport2(EGC_MODE_ROP_REG, 0x3100);
		outport2(EGC_BITLENGTHREG, 0xF);
		outport(EGC_MASKREG, BOX_MASKS[mask][y & 3]);

		vram_offset_t vram_offset = vram_offset_shift(BOX_LEFT, y);
		pixel_t x = 0;
		while(x < BOX_W) {
			graph_accesspage(1);	tmp = egc_chunk(vram_offset);
			graph_accesspage(0);	egc_chunk(vram_offset) = tmp;
			x += EGC_REGISTER_DOTS;
			vram_offset += EGC_REGISTER_SIZE;
		}
	}
}

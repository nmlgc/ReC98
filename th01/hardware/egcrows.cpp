#pragma option -zCGRAPH_EX_TEXT -2 -Z-

#include "platform.h"
#include "decomp.hpp"
#include "pc98.h"
#include "planar.h"
#include "libs/master.lib/master.hpp"
#include "th01/hardware/graph.h"
#include "th01/hardware/egc.h"
#include "th01/hardware/egcrows.hpp"

void egc_copy_rows_1_to_0(vram_y_t top, pixel_t h)
{
	vram_offset_t vram_offset = vram_offset_muldiv(0, top);
	egc_on();
	egc_setup_copy();

	for(pixel_t y = 0; y < h; y++) {
		vram_word_amount_t x = 0;
		while(x < (ROW_SIZE / EGC_REGISTER_SIZE)) {
			egc_temp_t tmp;
			graph_accesspage_func(1);	tmp = egc_chunk(vram_offset);
			graph_accesspage_func(0);	egc_chunk(vram_offset) = tmp;
			x++;
			vram_offset += EGC_REGISTER_SIZE;
		}
	}
	egc_off();
}

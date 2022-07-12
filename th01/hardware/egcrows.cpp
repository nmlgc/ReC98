#pragma option -zCGRAPH_EX_TEXT -2 -Z-

#include "platform.h"
#include "decomp.hpp"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
extern "C" {
#include "th01/hardware/graph.h"
}
#include "th01/hardware/egc.h"
#include "th01/hardware/egcrows.hpp"

void egc_copy_rows_1_to_0(vram_y_t top, pixel_t h)
{
	vram_offset_t vram_offset = vram_offset_muldiv(0, top);
	egc_on();
	egc_setup_copy();

	for(pixel_t y = 0; y < h; y++) {
		vram_word_amount_t x = 0;
		while(x < (ROW_SIZE / 2)) {
			dots16_t page1;
			graph_accesspage_func(1);	egc_snap(page1, vram_offset, 16);
			graph_accesspage_func(0);	egc_put(vram_offset, page1, 16);
			x++;
			vram_offset += static_cast<vram_offset_t>(sizeof(page1));
		}
	}
	egc_off();
}

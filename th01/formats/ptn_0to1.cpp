#pragma option -zCSHARED

#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "th01/hardware/graph.h"
#include "th01/formats/ptn.hpp"

void ptn_copy_8_0_to_1(screen_x_t left, vram_y_t top)
{
	Planar<dots_t(PTN_W)> row;
	vram_offset_t vram_offset = vram_offset_shift(left, top);
	for(pixel_t y = 0; y < PTN_H; y++) {
		graph_accesspage_func(0);	VRAM_SNAP_PLANAR(row, vram_offset, PTN_W);
		graph_accesspage_func(1);	VRAM_PUT_PLANAR(vram_offset, row, PTN_W);
		vram_offset += ROW_SIZE;
	}
	graph_accesspage_func(0);
}

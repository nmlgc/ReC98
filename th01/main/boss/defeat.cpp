extern "C" {
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "th01/v_colors.hpp"
#include "th01/hardware/graph.h"
}

void grcg_whiteline(screen_y_t y)
{
	vram_offset_t vo = vram_offset_muldiv(0, y);
	grcg_setcolor_rmw(V_WHITE);
	for(vram_word_amount_t x = 0; x < (ROW_SIZE / sizeof(dots16_t)); x++) {
		grcg_put(vo, 0xFFFF, 16);
		vo += static_cast<vram_offset_t>(sizeof(dots16_t));
	}
	grcg_off();
}

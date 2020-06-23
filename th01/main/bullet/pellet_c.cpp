#pragma option -1

extern "C" {

#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "th01/hardware/graph.h"
#include "th01/main/bullet/pellet_c.hpp"
#include "th01/sprites/pellet_c.h"

void pellet_cloud_put_8(int left, int top, int col, int cel)
{
	uint16_t vram_offset = vram_offset_shift(left, top);

	grcg_setcolor_rmw(col);

	int y = 0;
	while(y < PELLET_CLOUD_H) {
		if(sPELLET_CLOUD[cel][y]) {
			VRAM_PUT(B, vram_offset, sPELLET_CLOUD[cel][y], PELLET_CLOUD_W);
		}
		y++;
		vram_offset += ROW_SIZE;
	}
	grcg_off();
}

void pellet_cloud_unput_8(int left, int top, int cel)
{
	planar_t(PELLET_CLOUD_W) page1;
	uint16_t vram_offset = vram_offset_shift(left, top);

	pellet_cloud_put_8(left, top, 0, cel);

	int y = 0;
	while(y < PELLET_CLOUD_H) {
		if(sPELLET_CLOUD[cel][y]) {
			graph_accesspage_func(1);
			vram_snap_planar_masked(
				page1, vram_offset, PELLET_CLOUD_W, sPELLET_CLOUD[cel][y]
			);

			graph_accesspage_func(0);
			vram_or_planar_emptyopt(vram_offset, page1, PELLET_CLOUD_W);
		}
		y++;
		vram_offset += ROW_SIZE;
	}
}

}

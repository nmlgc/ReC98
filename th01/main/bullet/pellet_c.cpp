#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "platform/x86real/pc98/page.hpp"
#include "th01/hardware/graph.h"
#include "th01/main/bullet/pellet_c.hpp"
#include "th01/sprites/pellet_c.hpp"

#include "th01/sprites/pellet_c.csp"

void pellet_cloud_put_8(screen_x_t left, vram_y_t top, vc2 col, int cel)
{
	vram_offset_t vram_offset = vram_offset_shift(left, top);

	grcg_setcolor_rmw(col);

	pixel_t y = 0;
	while(y < PELLET_CLOUD_H) {
		if(sPELLET_CLOUD[cel][y]) {
			grcg_put(vram_offset, sPELLET_CLOUD[cel][y], PELLET_CLOUD_W);
		}
		y++;
		vram_offset += ROW_SIZE;
	}
	grcg_off();
}

void pellet_cloud_unput_8(screen_x_t left, vram_y_t top, int cel)
{
	Planar<dots_t(PELLET_CLOUD_W)> page1;
	vram_offset_t vram_offset = vram_offset_shift(left, top);

	pellet_cloud_put_8(left, top, 0, cel);

	pixel_t y = 0;
	while(y < PELLET_CLOUD_H) {
		if(sPELLET_CLOUD[cel][y]) {
			page_access(1);
			vram_snap_planar_masked(
				page1, vram_offset, PELLET_CLOUD_W, sPELLET_CLOUD[cel][y]
			);

			page_access(0);
			vram_or_planar_emptyopt(vram_offset, page1, PELLET_CLOUD_W);
		}
		y++;
		vram_offset += ROW_SIZE;
	}
}

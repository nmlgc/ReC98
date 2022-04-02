#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "th01/math/subpixel.hpp"
#include "th04/math/motion.hpp"
extern "C" {
#include "th04/math/vector.hpp"
#include "th04/hardware/grcg.h"
#include "th04/main/scroll.hpp"
#include "th04/main/playfld.hpp"
#include "th04/main/drawp.hpp"
#include "th04/main/bullet/bullet.hpp"
#include "th04/main/gather.hpp"

bool near gather_point_on_playfield()
{
	return playfield_encloses_point(drawpoint, GATHER_POINT_W, GATHER_POINT_H);
}

void gather_render(void)
{
	_ES = SEG_PLANE_B;

	gather_t near *gather;
	int circle_i;
	unsigned char angle;
	uint4_t col_cur;

	col_cur = -1;
	gather = gather_circles;

	for(circle_i = 0; circle_i < GATHER_CAP; circle_i++, gather++) {
		if(gather->flag != 1) {
			continue;
		}
		if(gather->col != col_cur) {
			col_cur = gather->col;
			grcg_setcolor_direct_seg3(col_cur);
		}
		for(int point_i = 0; gather->ring_points > point_i; point_i++) {
			angle = (
				((point_i * 0x100) / gather->ring_points) + gather->angle_cur
			);
			vector2_at(
				drawpoint,
				gather->center.cur.x,
				gather->center.cur.y,
				gather->radius_cur,
				angle
			);
			if(!gather_point_on_playfield()) {
				continue;
			}
			_DX = drawpoint.to_vram_top_scrolled_seg3(GATHER_POINT_H);
			_AX = drawpoint.to_screen_left(GATHER_POINT_W);
			gather_point_render(_AX, _DX);
		}
	}
}

}

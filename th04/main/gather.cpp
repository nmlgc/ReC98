#include <stddef.h>
#include <mem.h>
#include "platform.h"
#include "x86real.h"
#include "decomp.hpp"
#include "pc98.h"
#include "th01/math/subpixel.hpp"
#include "th04/hardware/grcg.hpp"
#include "th04/math/motion.hpp"
extern "C" {
#include "th04/math/vector.hpp"
#include "th04/main/scroll.hpp"
#include "th04/main/playfld.hpp"
#include "th04/main/drawp.hpp"
#include "th04/main/bullet/bullet.hpp"
}
#include "th04/main/gather.hpp"

void pascal near set_bullet_template_to_gather_template(gather_t near &gather)
{
	// MODDERS: bullet_template = gather.bullet_template;
	copy_near_struct_member(bullet_template, gather, gather_t, bullet_template);
}

void gather_update(void)
{
	gather_t near *gather;
	int i;
	for((gather = gather_circles, i = 0); i < GATHER_CAP; (i++, gather++)) {
		if(gather->flag == F_FREE) {
			continue;
		} else if(gather->flag >= F_REMOVE) {
			gather->flag = F_FREE;
			continue;
		}
		gather->center.update_seg3();
		gather->radius_prev = gather->radius_cur;
		gather->radius_cur.v -= gather->radius_delta.v;
		gather->angle_cur += gather->angle_delta;
		if(gather->radius_cur.v < GATHER_RADIUS_END) {
			gather->flag = F_REMOVE;
			if(gather->bullet_template.spawn_type != BST_GATHER_ONLY) {
				set_bullet_template_to_gather_template(*gather);
				bullet_template.origin.x = gather->center.cur.x;
				bullet_template.origin.y = gather->center.cur.y;
				#if (GAME == 5)
					if(
						bullet_template.spawn_type <
						BST_GATHER_NORMAL_SPECIAL_MOVE
					) {
						bullets_add_regular();
					} else {
						bullet_template.spawn_type = BST_NORMAL;
						bullets_add_special();
					}
				#else
					bullets_add_regular();
				#endif
			}
		}
	}
}

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
		if(gather->flag != F_ALIVE) {
			continue;
		}
		if(gather->col != col_cur) {
			col_cur = gather->col;
			_AH = col_cur;
			// MODDERS: Replace with grcg_setcolor_direct_inlined(), and remove
			// the translation unit that defines this function.
			grcg_setcolor_direct_seg3_raw();
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

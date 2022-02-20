#pragma option -G

#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "th01/math/overlap.hpp"
#include "th01/math/subpixel.hpp"
#include "th04/math/motion.hpp"
extern "C" {
#include "th04/math/vector.hpp"
#include "th04/main/playfld.hpp"
#include "th04/main/frames.h"
#include "th04/main/bullet/bullet.hpp"
#include "th05/main/player/player.hpp"
}
#include "th05/main/custom.h"
#include "th05/main/bullet/curve.hpp"

static const subpixel_t TRAIL_KILLBOX_W = TO_SP(12);
static const subpixel_t TRAIL_KILLBOX_H = TO_SP(12);
static const subpixel_t HEAD_KILLBOX_W = TO_SP(16);
static const subpixel_t HEAD_KILLBOX_H = TO_SP(16);

static const int TRAIL_NODE_LAST = (CURVEBULLET_TRAIL_NODE_COUNT - 1);

void near curvebullets_update(void)
{
	curvebullet_head_t near *head_p;
	curvebullet_trail_t near *trail_p;
	int b_i;
	int node_i;
	unsigned char angle_delta;
	unsigned char unused_friction_factor;

	for(
		(head_p = curvebullet_heads, trail_p = curvebullet_trails, b_i = 1);
		(b_i < (1 + CURVEBULLET_COUNT));
		(b_i++, head_p++, trail_p++)
	 ) {
		if(trail_p->flag == CBF_FREE) {
			continue;
		}
		head_p->age++;

		for(node_i = TRAIL_NODE_LAST; node_i > 0; node_i--) {
			trail_p->node_pos[node_i] = trail_p->node_pos[node_i - 1];

			if(overlap_points_wh_fast(
				trail_p->node_pos[node_i],
				player_pos.cur,
				TRAIL_KILLBOX_W,
				TRAIL_KILLBOX_H
			)) {
				player_is_hit = true;
			}

			trail_p->node_sprite[node_i] = trail_p->node_sprite[node_i - 1];
		}
		trail_p->node_pos[0] = head_p->pos.cur;
		trail_p->node_sprite[0] = head_p->sprite;
		if(!playfield_encloses_point(
			trail_p->node_pos[TRAIL_NODE_LAST], CURVEBULLET_W, CURVEBULLET_H
		)) {
			trail_p->flag = CBF_FREE;
			head_p->flag = CBF_FREE;
			continue;
		}

		/* DX:AX = */ head_p->pos.update_seg3();
		_AX -= player_pos.cur.x.v;
		_DX -= player_pos.cur.y.v;
		if(overlap_wh_inplace_fast(_AX, _DX, HEAD_KILLBOX_W, HEAD_KILLBOX_H)) {
			player_is_hit = true;
		}

		if(trail_p->flag == CBF_SLOWDOWN) {
			head_p->speed.v--; // -= to_sp(1 / 16.0f)
			if(head_p->speed.v <= to_sp8(0.25f)) {
				static_cast<unsigned char>(trail_p->flag)++;
			}
			unused_friction_factor = 0x10;
		} else /* if(trail_p->flag == CBF_SPEEDUP) */ {
			head_p->speed.v += (stage_frame_mod2 + to_sp(0.0625f));
			unused_friction_factor = (head_p->speed.v + 0x20);
		}

		angle_delta = (head_p->angle - player_angle_from(
			head_p->pos.cur.x, head_p->pos.cur.y
		));

		enum {
			ANGLE_DELTA_SNAP = 0x02,
		};

		// What follows is a whole lot of code that can be simplified to:
		//
		// 	if(
		// 		(angle_delta > ANGLE_DELTA_SNAP) &&
		// 		(angle_delta < static_cast<unsigned char>(-ANGLE_DELTA_SNAP))
		// 	) {
		// 		angle_delta = (angle_delta >= 0x80) ? -0x01 : 0x01;
		// 	}
		//	head_p->angle -= angle_delta;
		// ---------------------------------------------------------------
		if(angle_delta >= 0x80) {
			// Player in clockwise direction
			if(angle_delta < static_cast<unsigned char>(-ANGLE_DELTA_SNAP)) {
				angle_delta = ((0x100 - angle_delta) / unused_friction_factor);
				// Always true!
				if(angle_delta < unused_friction_factor) {
					angle_delta = 0x01;
				}
				head_p->angle += angle_delta;
			} else {
				head_p->angle = player_angle_from(
					head_p->pos.cur.x, head_p->pos.cur.y
				);
			}
		} else {
			// Player in counterclockwise direction
			if(angle_delta <= ANGLE_DELTA_SNAP) {
				head_p->angle = player_angle_from(
					head_p->pos.cur.x, head_p->pos.cur.y
				);
			} else {
				angle_delta = (angle_delta / unused_friction_factor);
				// Always true!
				if(angle_delta < unused_friction_factor) {
					angle_delta = 0x01;
				}
				head_p->angle -= angle_delta;
			}
		}
		// ---------------------------------------------------------------
		vector2_near(head_p->pos.velocity, head_p->angle, head_p->speed);
		head_p->sprite = bullet_patnum_for_angle(0, head_p->angle);
	}
}

extern "C" {
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "th01/sprites/laser_s.h"
#include "th01/hardware/egc.h"
#include "th01/hardware/graph.h"
#include "th01/hardware/input.hpp"
#include "th01/main/playfld.hpp"
#include "th01/main/player/player.hpp"
#include "th01/main/bullet/laser_s.hpp"
}

void CShootoutLaser::spawn(
	screen_x_t _origin_left,
	vram_y_t _origin_y,
	screen_x_t _target_left,
	vram_y_t _target_y,
	int speed_multiplied_by_8,
	int _col,
	int _moveout_at_age,
	int w
)
{
	if(alive) {
		return;
	}
	origin_left.v = to_laser_pixel(_origin_left);
	origin_y.v = to_laser_pixel(_origin_y);
	ray_start_left.v = origin_left.v;
	ray_start_y.v = origin_y.v;
	target_left = _target_left;
	target_y = _target_y;
	unknown = -256;

	unsigned char angle = iatan2(
		(_target_y - _origin_y), (_target_left - _origin_left)
	);
	step_x.v = Cos8(angle);
	step_y.v = Sin8(angle);
	velocity_x.v = ((speed_multiplied_by_8 * step_x.v) >> 3);
	velocity_y.v = ((speed_multiplied_by_8 * step_y.v) >> 3);
	ray_extend_speed = (speed_multiplied_by_8 / 8);

	w--;
	width_cel = w;
	alive = true;
	damaging = true;
	moveout_at_age = _moveout_at_age;
	age = 0;
	col = _col;
	ray_moveout_speed = ray_extend_speed;
	ray_length = 0;
}

void CShootoutLaser::hittest_and_render(void)
{
	screen_x_t left = ray_i_left.to_pixel();
	vram_y_t y = ray_i_y.to_pixel();
	unsigned int i;
	vram_offset_t vram_offset;
	int preshift = (width_cel * PRESHIFT);
	dots16_t dots = 0;
	unsigned int pixel_count;

	if(put_flag) {
		pixel_count = ray_length;
		grcg_setcolor_rmw(col);
	} else {
		pixel_count = ray_moveout_speed;
	}

	for(i = 0; i < pixel_count; i++) {
		if(
			((left >> 3) != ray_i_left.to_vram_byte_amount()) ||
			(y != ray_i_y.to_pixel())
		) {
			if(put_flag) {
				vram_offset = vram_offset_shift(left, y);
				grcg_put(vram_offset, dots, 16);
				dots = 0;

				if(!player_invincible && damaging) {
					if(
						(y > (player_top + 8)) &&
						((player_left + ((PLAYER_W / 8) * 1)) <= left) &&
						((player_left + ((PLAYER_W / 8) * 6)) >  left)
					) {
						done = true;
					}
				}
			}
			left = ray_i_left.to_pixel();
			y = ray_i_y.to_pixel();
			if(
				(left > (PLAYFIELD_RIGHT - 2)) ||
				(left < PLAYFIELD_LEFT) ||
				(y < PLAYFIELD_TOP) ||
				(y > (PLAYFIELD_BOTTOM - 1))
			) {
				break;
			}
		}

		// MODDERS: Should just be
		// 	sSHOOTOUT_LASER[preshift][(ray_i_left.to_pixel()...)].
		// (Or actually, how about throwing away that sprite altogether?)
		dots |= sSHOOTOUT_LASER[0][
			preshift + (ray_i_left.to_pixel() & BYTE_MASK)
		];

		if(put_flag == SL_RAY_UNPUT) {
			egc_copy_rect_1_to_0_16(
				ray_i_left.to_pixel(),
				ray_i_y.to_pixel(),
				(sizeof(dots) * BYTE_DOTS),
				1
			);
		}
		ray_i_left.v += step_x.v;
		ray_i_y.v += step_y.v;
	}

	if(put_flag) {
		grcg_off_func();
	}
}

void CShootoutLaser::update_hittest_and_render(void)
{
	if(!alive) {
		return;
	}
	if(age >= moveout_at_age) {
		ray_i_left.v = ray_start_left.v;
		ray_i_y.v = ray_start_y.v;

		put_flag = SL_RAY_UNPUT;
		hittest_and_render();

		// hittest_and_render() has conveniently advanced [ray_i_*] by
		// [ray_moveout_speed]...
		ray_start_left.v = ray_i_left.v;
		ray_start_y.v = ray_i_y.v;
		if(
			(ray_start_left.v >= to_laser_pixel(PLAYFIELD_RIGHT)) ||
			(ray_start_left.v <  to_laser_pixel(PLAYFIELD_LEFT)) ||
			(ray_start_y.v <  to_laser_pixel(PLAYFIELD_TOP)) ||
			(ray_start_y.v >= to_laser_pixel(PLAYFIELD_BOTTOM))
		) {
			alive = false;
			return;
		}
	} else {
		ray_length += ray_extend_speed;
	}
	age++;
	ray_i_left.v = ray_start_left.v;
	ray_i_y.v = ray_start_y.v;

	put_flag = SL_RAY_PUT;
	hittest_and_render();
}

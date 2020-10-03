#include "libs/master.lib/master.h"
#include "platform.h"
#include "pc98.h"
#include "th01/main/bullet/laser_s.hpp"

void CShootoutLaser::spawn(
	screen_x_t _origin_left,
	vram_y_t _origin_y,
	screen_x_t _target_left,
	vram_y_t _target_y,
	int speed_multiplied_by_8,
	unsigned char _col,
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

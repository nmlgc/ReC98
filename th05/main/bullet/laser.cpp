#pragma option -G

#include "platform.h"
#include "pc98.h"
#include "master.hpp"
#include "th01/math/subpixel.hpp"
extern "C" {
#include "th04/math/vector.hpp"
#include "th04/snd/snd.h"
#include "th04/main/playfld.hpp"
#include "th05/main/playperf.hpp"
}
#include "th05/main/bullet/laser.hpp"

// Segment 3 (as allocated in the header)
// ---------

void near lasers_shootout_add(void)
{
	Laser near *laser;
	int i;
	subpixel_t speed = playperf_speedtune(laser_template.shootout_speed.v);

	for((laser = lasers, i = 0); i < LASER_COUNT; (i++, laser++)) {
		if(laser->flag != LF_FREE) {
			continue;
		}
		laser->flag = LF_SHOOTOUT;
		laser->coords.starts_at_distance.set(LASER_DISTANCE_MIN);
		laser->coords.ends_at_distance.set(LASER_DISTANCE_MIN);
		laser->age = 0;
		laser->active_at_age = laser_template.active_at_age;
		laser->col = laser_template.col;
		laser->shootout_speed.v = speed;
		laser->grow_to_width = 6;
		laser->coords.width = 6;
		laser->coords.angle = laser_template.coords.angle;
		vector2_at(
			laser->coords.origin,
			laser_template.coords.origin.x.v,
			laser_template.coords.origin.y.v,
			to_sp(LASER_DISTANCE_MIN / 2.0f),
			laser_template.coords.angle
		);
		snd_se_play(5);
		return;
	}
}

void pascal near laser_fixed_spawn(int slot)
{
	Laser near &laser = lasers[slot];
	if(laser.flag != LF_FREE) {
		return;
	}
	laser.fixed_init(laser_template.coords.origin);
	laser.active_at_age.grow = laser_template.active_at_age.grow;
	laser.shrink_at_age = laser_template.shrink_at_age;
	laser.col = laser_template.col;
	laser.grow_to_width = laser_template.coords.width;
	laser.coords.width = 1;
	laser.coords.angle = laser_template.coords.angle;
	snd_se_play(5);
}

void pascal near laser_manual_fixed_spawn(int slot)
{
	Laser near &laser = lasers[slot];
	if(laser.flag != LF_FREE) {
		return;
	}
	laser.fixed_init(laser_template.coords.origin);
	laser.active_at_age.grow = -1;
	laser.shrink_at_age = -1;
	laser.col = laser_template.col;
	laser.coords.width = 1;
	laser.grow_to_width = laser_template.coords.width;
	laser.coords.angle = laser_template.coords.angle;
	snd_se_play(5);
}

void pascal near laser_manual_grow(int slot)
{
	if(lasers[slot].flag != LF_FIXED_WAIT_TO_GROW) {
		return;
	}
	lasers[slot].flag = LF_FIXED_GROW;
	snd_se_play(6);
}

void pascal near laser_stop(int slot)
{
	if(lasers[slot].flag == LF_FIXED_ACTIVE) {
		lasers[slot].flag = LF_FIXED_SHRINK;
	} else if (lasers[slot].flag == LF_SHOOTOUT) {
		lasers[slot].flag = LF_DECAY;
	} else if (
		(lasers[slot].flag != LF_FIXED_SHRINK) &&
		(lasers[slot].flag != LF_DECAY)
	) {
		lasers[slot].flag = LF_FREE;
	}
}
// ---------

#pragma option -G

#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "master.hpp"
#include "th01/math/subpixel.hpp"
#include "th02/v_colors.hpp"
extern "C" {
#include "th04/math/vector.hpp"
}
#include "th04/hardware/grcg.hpp"
extern "C" {
#include "th04/snd/snd.h"
#include "th04/main/playfld.hpp"
#include "th04/main/bullet/clearzap.hpp"
#include "th04/main/drawp.hpp"
#include "th05/main/playperf.hpp"
}
#include "th05/main/bullet/laser.hpp"

// Segment 1 (as allocated in the header)
// ---------

// ZUN bloat: Needed to circumvent 16-bit promotion in comparisons.
inline int8_t laser_width_min(void) {
	return 1;
}

void near lasers_update(void)
{
	#define shootout_update(laser) { \
		if(laser->coords.starts_at_distance < LASER_DISTANCE_MAX) { \
			laser->coords.ends_at_distance.v += laser->shootout_speed.v; \
		} \
		if(laser->age >= laser->active_at_age.moveout) { \
			laser->coords.starts_at_distance.v += laser->shootout_speed.v; \
		} \
	}

	Laser near *laser;
	int i;
	for((laser = lasers, i = 0); i < LASER_COUNT; (i++, laser++)) {
		if(laser->flag == LF_FREE) {
			continue;
		}

		if(bullet_clear_time || bullet_zap.active) {
			if(laser->flag == LF_SHOOTOUT) {
				laser->flag = LF_SHOOTOUT_DECAY;
				laser->shootout_speed.v /= 2;
			}
		}

		switch(laser->flag) {
		case LF_SHOOTOUT:
			shootout_update(laser);
			laser_hittest(*laser);
			break;

		case LF_FIXED_WAIT_TO_GROW:
			if(laser->active_at_age.grow > 0) {
				if(laser->age >= laser->active_at_age.grow) {
					// laser->flag = LF_FIXED_GROW;
					static_cast<uint8_t>(laser->flag)++;
					snd_se_play(6);
				}
			}
			break;

		case LF_FIXED_GROW:
			if(laser->age & 1) {
				laser->coords.width.nonshrink += 2;
			}
			if(laser->coords.width.nonshrink >= laser->grow_to_width) {
				// laser->flag = LF_FIXED_ACTIVE;
				static_cast<uint8_t>(laser->flag)++;
			}
			break;

		case LF_FIXED_ACTIVE:
			laser_hittest(*laser);
			if(laser->shrink_at_age > 0) {
				if(laser->age >= laser->shrink_at_age) {
					// laser->flag = LF_FIXED_SHRINK;
					static_cast<uint8_t>(laser->flag)++;
				}
			}
			break;

		case LF_FIXED_SHRINK:
			if(laser->age & 1) {
				// MODDERS: The necessary clamp to 0 here is caught by the
				// signed comparison below.
				laser->coords.width.shrink -= 2;
			}
			if(laser->coords.width.shrink < laser_width_min()) {
				laser->flag = LF_FREE;
			}
			break;

		case LF_FIXED_SHRINK_AND_WAIT_TO_GROW:
			if(laser->age & 1) {
				// MODDERS: See above… except that the signed comparison
				// wouldn't even have been needed here, as the condition is
				// `true` for both 1 and 0.
				laser->coords.width.shrink -= 2;
			}
			if(laser->coords.width.shrink <= laser_width_min()) {
				laser->flag = LF_FIXED_WAIT_TO_GROW;
				laser->age = 0;
			}
			break;

		case LF_SHOOTOUT_DECAY:
			shootout_update(laser);
			laser->coords.width.nonshrink += 2;
			if(
				laser->coords.width.nonshrink >=
				LASER_SHOOTOUT_DECAY_WIDTH_MAX
			) {
				laser->flag = LF_FREE;
			}
			break;
		}
		laser->age++;
	}

	#undef shootout_update
}

inline void laser_line_put(PlayfieldPoint& start, PlayfieldPoint& end) {
	start.x.v = start.to_screen_left();
	start.y.v = start.to_screen_top();
	end.x.v = end.to_screen_left();
	end.y.v = end.to_screen_top();
	grcg_line(start.x, start.y, end.x, end.y);
}

void near lasers_render(void)
{
	extern PlayfieldPoint laser_line_endpoint;

	Laser near *laser;
	int i;
	for((laser = lasers, i = 0); i < LASER_COUNT; (i++, laser++)) {
		if(laser->flag == LF_FREE) {
			continue;
		}
		screen_x_t circle_center_x;
		screen_x_t circle_center_y;
		Subpixel end_distance_orig;

		// ZUN bloat: Only needed because we mutate [coords] for rendering the
		// inner ray.
		pixel_length_8_t width_orig = laser->coords.width.nonshrink;

		pixel_length_8_t radius = laser->coords.width.nonshrink;

		vector2_at(
			drawpoint,
			laser->coords.origin.x,
			laser->coords.origin.y,
			LASER_DISTANCE_MIN,
			laser->coords.angle
		);
		circle_center_x = drawpoint.to_screen_left();
		circle_center_y = drawpoint.to_screen_top();

		if(laser->flag != LF_SHOOTOUT_DECAY) {
			if(radius < 2) {
				radius = 2;
			}
			if(laser->coords.width.nonshrink >= 3) {
				// Outer circle
				grcg_setcolor_direct(laser->col);
				if(laser->coords.starts_at_distance.v <= LASER_DISTANCE_MIN) {
					grcg_circlefill(circle_center_x, circle_center_y, radius);
					radius -= 2; // Preparing for the inner circle already...
				}
				if(laser->coords.ends_at_distance.v > to_sp(2.0f)) {
					// Outer ray
					end_distance_orig = laser->coords.ends_at_distance;
					laser->coords.ends_at_distance -= 2.0f;
					laser_render_ray(laser->coords);
					laser->coords.ends_at_distance = end_distance_orig;
				}

				// Inner circle and ray
				laser->coords.width.nonshrink = (
					(laser->coords.width.nonshrink >= 5)
						? (laser->coords.width.nonshrink - 4)
						: (laser->coords.width.nonshrink - 2)
				);
			}
			grcg_setcolor_direct(V_WHITE);
			if(laser->coords.starts_at_distance.v <= LASER_DISTANCE_MIN) {
				grcg_circlefill(circle_center_x, circle_center_y, radius);
			}
			if(laser->coords.width.nonshrink <= 1) {
				// Laser is a single 1-pixel line
				vector2_at(
					drawpoint,
					laser->coords.origin.x,
					laser->coords.origin.y,
					laser->coords.starts_at_distance,
					laser->coords.angle
				);
				vector2_at(
					laser_line_endpoint,
					laser->coords.origin.x,
					laser->coords.origin.y,
					laser->coords.ends_at_distance,
					laser->coords.angle
				);
				laser_line_put(drawpoint, laser_line_endpoint);
			} else {
				if(laser_render_ray(laser->coords)) {
					laser->flag = LF_FREE;
				}
			}
		} else {
			grcg_setcolor_direct(V_WHITE);

			// Same transformation as in laser_render_ray(). Note that we only
			// get here for widths < LASER_SHOOTOUT_DECAY_WIDTH_MAX, so this
			// 8-bit shift doesn't reduce the number of possible widths for
			// other types.
			radius <<= (SUBPIXEL_BITS - 1);

			// ZUN bloat: Would have made more sense inside the loop...
			vector2_at(
				drawpoint,
				laser->coords.origin.x,
				laser->coords.origin.y,
				radius,
				(laser->coords.angle + 0x40)
			);
			for(int decay_line = 0; decay_line < 2; decay_line++) {
				vector2_at(
					laser_line_endpoint,
					drawpoint.x,
					drawpoint.y,
					laser->coords.ends_at_distance,
					laser->coords.angle
				);
				vector2_at(
					drawpoint,
					drawpoint.x,
					drawpoint.y,
					laser->coords.starts_at_distance,
					laser->coords.angle
				);
				laser_line_put(drawpoint, laser_line_endpoint);

				// ZUN bloat: ...replacing this one.
				vector2_at(
					drawpoint,
					laser->coords.origin.x,
					laser->coords.origin.y,
					radius,
					(laser->coords.angle - 0x40)
				);
			}
		}
		laser->coords.width.nonshrink = width_orig;
	}
}
// ---------

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
		laser->coords.starts_at_distance.v = LASER_DISTANCE_MIN;
		laser->coords.ends_at_distance.v = LASER_DISTANCE_MIN;
		laser->age = 0;
		laser->active_at_age = laser_template.active_at_age;
		laser->col = laser_template.col;
		laser->shootout_speed.v = speed;
		laser->grow_to_width = 6;
		laser->coords.width.nonshrink = 6;
		laser->coords.angle = laser_template.coords.angle;
		vector2_at(
			laser->coords.origin,
			laser_template.coords.origin.x.v,
			laser_template.coords.origin.y.v,
			(LASER_DISTANCE_MIN / 2),
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
	laser.grow_to_width = laser_template.coords.width.nonshrink;
	laser.coords.width.nonshrink = 1;
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
	laser.coords.width.nonshrink = 1;
	laser.grow_to_width = laser_template.coords.width.nonshrink;
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
		lasers[slot].flag = LF_SHOOTOUT_DECAY;
	} else if (
		(lasers[slot].flag != LF_FIXED_SHRINK) &&
		(lasers[slot].flag != LF_SHOOTOUT_DECAY)
	) {
		lasers[slot].flag = LF_FREE;
	}
}
// ---------

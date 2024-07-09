#include "th01/math/overlap.hpp"
#include "th01/sprites/pellet.h"

bool16 unused_boss_stage_flag = false; // ZUN bloat

static const pixel_t SHOT_SPRITE_MARGIN = 2;
static const int SHOT_DECAY_FRAMES = 7;

void CShots::add(screen_x_t new_left, screen_y_t new_top)
{
	if(new_left < PLAYFIELD_LEFT || new_left > (PLAYFIELD_RIGHT - 1)) {
		return;
	}
	for(int i = 0; i < SHOT_COUNT; i++) {
		if(moving[i] == true) {
			continue;
		}
		if(decay_frame[i] != 0) {
			continue;
		}
		left[i] = new_left;
		top[i] = new_top;
		moving[i] = true;
		mdrv2_se_play(1);
		decay_frame[i] = 0;
		return;
	}
}

void CShots::unput_and_reset(void)
{
	for(int i = 0; i < SHOT_COUNT; i++) {
		if(moving[i]) {
			ptn_sloppy_unput_quarter_16(left[i], top[i]);
			moving[i] = false;
		} else if(decay_frame[i]) {
			ptn_sloppy_unput_quarter_16(left[i], top[i]);
			decay_frame[i] = false;
		}
	}
}

inline int decay_quarter(int frame) {
	return ((frame / 4) + 1);
}

void CShots::unput_update_render(void)
{
	for(int i = 0; i < SHOT_COUNT; i++) {
		if(moving[i] == true) {
			ptn_sloppy_unput_quarter_16(left[i], top[i]);
			top[i] -= 12;

			if(!orb_in_portal) {
				if(hittest_orb(i, orb_cur_left, orb_cur_top) == true) {
					continue;
				}
			}
			if(top[i] >= PLAYFIELD_TOP) {
				ptn_put_quarter_8(left[i], top[i], PTN_SHOT, 0);
			} else {
				moving[i] = false;
			}
		} else if(decay_frame[i]) {
			ptn_unput_quarter_8(
				left[i], top[i], PTN_SHOT, decay_quarter(decay_frame[i])
			);
			decay_frame[i]++;
			if(decay_frame[i] > SHOT_DECAY_FRAMES) {
				decay_frame[i] = 0;
				moving[i] = false;
			} else {
				ptn_put_quarter_8(
					left[i], top[i], PTN_SHOT, decay_quarter(decay_frame[i])
				);
			}
		}
	}
}

bool16 CShots::hittest_orb(int i, screen_x_t orb_left, screen_y_t orb_top)
{
	if(moving[i] == false) {
		return false;
	}
	if(overlap_xywh_xywh_lt_gt(
		left[i], top[i], SHOT_W, SHOT_H,
		orb_left, orb_top, ORB_W, ORB_H
	)) {
		if((left[i] - orb_left) > (SHOT_W / 2)) {
			orb_velocity_x = OVX_4_LEFT;
		} else if((left[i] - orb_left) == (SHOT_W / 2)) {
			orb_velocity_x = OVX_0;
		} else if((left[i] - orb_left) > (-SHOT_W)) {
			orb_velocity_x = OVX_4_RIGHT;
		}
		orb_force_new(0, OF_SHOT);
		moving[i] = false;

		// Yup, an extra orb update... *Very* sloppy!
		orb_move_x(orb_velocity_x);
		orb_cur_top += orb_velocity_y_update();
		return true;
	}
	return false;
}

#define on_hit(i) \
	ptn_sloppy_unput_quarter_16(left[i], top[i]); \
	moving[i] = false; \
	decay_frame[i] = 1; \
	mdrv2_se_play(16);

bool16 CShots::hittest_pellet(screen_x_t pellet_left, screen_y_t pellet_top)
{
	for(int i = 0; i < SHOT_COUNT; i++) {
		if(moving[i] == false) {
			continue;
		}
		if(decay_frame[i] == 1) {
			continue;
		}
		if(overlap_xywh_xywh_le_ge(
			left[i],
			top[i],
			(SHOT_W - SHOT_SPRITE_MARGIN),
			(SHOT_H - SHOT_SPRITE_MARGIN),
			pellet_left,
			pellet_top,
			(PELLET_W - SHOT_SPRITE_MARGIN),
			(PELLET_H - SHOT_SPRITE_MARGIN)
		)) {
			on_hit(i);
			return true;
		}
	}
	return false;
}

bool16 CShots::hittest_boss(
	screen_x_t hitbox_left,
	screen_y_t hitbox_top,
	pixel_t hitbox_w_minus_shot_w,
	pixel_t hitbox_h_minus_shot_h
)
{
	for(int i = 0; i < SHOT_COUNT; i++) {
		if(moving[i] == false) {
			continue;
		}
		if(overlap_xy_xywh_le_ge(
			left[i],
			top[i],
			hitbox_left,
			hitbox_top,
			hitbox_w_minus_shot_w,
			hitbox_h_minus_shot_h
		)) {
			on_hit(i);
			return true;
		}
	}
	return false;
}

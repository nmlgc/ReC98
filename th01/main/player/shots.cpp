#include "th01/snd/mdrv2.h"
#include "th01/formats/ptn.hpp"
#include "th01/hardware/egc.h"
#include "th01/main/playfld.hpp"
#include "th01/main/player/player.hpp"
#include "th01/main/player/orb.hpp"
#include "th01/main/player/shots.hpp"

static const int SHOT_SPRITE_MARGIN = 2;
static const int SHOT_DECAY_FRAMES = 7;

#define sloppy_unput(i) \
	egc_copy_rect_1_to_0(left[i], top[i], SHOT_W, SHOT_H);

#define PTN_SHOT \
	1, 0

#define PTN_SHOT_DECAY(frame) \
	1, (frame / 4) + 1

void CShots::add(int new_left, int new_top)
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

void CShots::unput_and_reset_all(void)
{
	for(int i = 0; i < SHOT_COUNT; i++) {
		if(moving[i]) {
			sloppy_unput(i);
			moving[i] = false;
		} else if(decay_frame[i]) {
			sloppy_unput(i);
			decay_frame[i] = false;
		}
	}
}

void CShots::unput_update_render(void)
{
	for(int i = 0; i < SHOT_COUNT; i++) {
		if(moving[i] == true) {
			sloppy_unput(i);
			top[i] -= 12;

			if(!orb_in_portal) {
				if(hittest_orb(i, orb_cur_left, orb_cur_top) == true) {
					continue;
				}
			}
			if(top[i] >= PLAYFIELD_TOP) {
				ptn_put_quarter_8(left[i], top[i], PTN_SHOT);
			} else {
				moving[i] = false;
			}
		} else if(decay_frame[i]) {
			ptn_unput_quarter_8(
				left[i], top[i], PTN_SHOT_DECAY(decay_frame[i])
			);
			decay_frame[i]++;
			if(decay_frame[i] > SHOT_DECAY_FRAMES) {
				decay_frame[i] = 0;
				moving[i] = false;
			} else {
				ptn_put_quarter_8(
					left[i], top[i], PTN_SHOT_DECAY(decay_frame[i])
				);
			}
		}
	}
}

bool16 CShots::hittest_orb(int i, int orb_left, int orb_top)
{
	if(moving[i] == false) {
		return false;
	}
	if(overlap_lt_gt(
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
	sloppy_unput(i); \
	moving[i] = false; \
	decay_frame[i] = 1; \
	mdrv2_se_play(16);

bool16 CShots::hittest_pellet(int pellet_left, int pellet_top)
{
	for(int i = 0; i < SHOT_COUNT; i++) {
		if(moving[i] == false) {
			continue;
		}
		if(decay_frame[i] == 1) {
			continue;
		}
		if(overlap_le_ge(
			left[i], top[i],
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
	int hitbox_left, int hitbox_top, int hitbox_w, int hitbox_h
)
{
	for(int i = 0; i < SHOT_COUNT; i++) {
		if(moving[i] == false) {
			continue;
		}
		if(overlap_point_le_ge_wh(
			left[i], top[i], hitbox_left, hitbox_top, hitbox_w, hitbox_h
		)) {
			on_hit(i);
			return true;
		}
	}
	return false;
}

#undef sloppy_unput

#include "th01/hardware/egc.h"
#include "th01/main/bullet/missile.hpp"
#include "th01/main/player/player.hpp"

CMissiles Missiles;

void CMissiles::add(
	screen_x_t left, screen_x_t top, double velocity_x, double velocity_y,
	int8_t unknown
)
{
	for(int i = 0; i < MISSILE_COUNT; i++) {
		if(flag[i] != MF_FREE) {
			continue;
		}
		this->cur_left[i].v = TO_SP(left);
		this->cur_top[i].v = TO_SP(top);
		this->prev_left[i].v = MISSILE_NEW;
		this->velocity_x[i].v = (velocity_x * SUBPIXEL_FACTOR);
		this->velocity_y[i].v = (velocity_y * SUBPIXEL_FACTOR);
		this->unknown[i] = unknown;
		this->flag[i] = MF_MOVING;
		return;
	}
}

void CMissiles::ptn_cel_for(int i, main_ptn_id_t& ptn_id, int& quarter) const
{
	enum {
		ANGLE_PER_PTN = (0x100 / MISSILE_PTNS),
		ANGLE_PER_CEL = (0x100 / MISSILE_CELS),
	};

	// ZUN bloat: I have no words. Every further line in this function is bad.
	// A sane version:
	//
	// 	unsigned char angle = iatan2(velocity_y[i], velocity_x[i]);
	// 	ptn_id = (ptn_id_base + (angle / ANGLE_PER_PTN));
	// 	quarter = (angle % ANGLE_PER_CEL);
	//
	// Due to the overhead from mutating references, that should also just be a
	// part of unput_update_render(), rather than its own function.

	double angle = iatan2(velocity_y[i], velocity_x[i]);

	ptn_id = static_cast<main_ptn_id_t>(
		(angle < (ANGLE_PER_PTN * 1)) ? 0 :
		(angle < (ANGLE_PER_PTN * 2)) ? 1 :
		(angle < (ANGLE_PER_PTN * 3)) ? 2 :
		(angle < (ANGLE_PER_PTN * 4)) ? 3 : 0
	);
	reinterpret_cast<int &>(ptn_id) += ptn_id_base;
	quarter = (
		(angle < ((ANGLE_PER_PTN * 0) + (ANGLE_PER_CEL * 1))) ? 0 :
		(angle < ((ANGLE_PER_PTN * 0) + (ANGLE_PER_CEL * 2))) ? 1 :
		(angle < ((ANGLE_PER_PTN * 0) + (ANGLE_PER_CEL * 3))) ? 2 :
		(angle < ((ANGLE_PER_PTN * 0) + (ANGLE_PER_CEL * 4))) ? 3 :
		(angle < ((ANGLE_PER_PTN * 1) + (ANGLE_PER_CEL * 1))) ? 0 :
		(angle < ((ANGLE_PER_PTN * 1) + (ANGLE_PER_CEL * 2))) ? 1 :
		(angle < ((ANGLE_PER_PTN * 1) + (ANGLE_PER_CEL * 3))) ? 2 :
		(angle < ((ANGLE_PER_PTN * 1) + (ANGLE_PER_CEL * 4))) ? 3 :
		(angle < ((ANGLE_PER_PTN * 2) + (ANGLE_PER_CEL * 1))) ? 0 :
		(angle < ((ANGLE_PER_PTN * 2) + (ANGLE_PER_CEL * 2))) ? 1 :
		(angle < ((ANGLE_PER_PTN * 2) + (ANGLE_PER_CEL * 3))) ? 2 :
		(angle < ((ANGLE_PER_PTN * 2) + (ANGLE_PER_CEL * 4))) ? 3 :
		(angle < ((ANGLE_PER_PTN * 3) + (ANGLE_PER_CEL * 1))) ? 0 :
		(angle < ((ANGLE_PER_PTN * 3) + (ANGLE_PER_CEL * 2))) ? 1 :
		(angle < ((ANGLE_PER_PTN * 3) + (ANGLE_PER_CEL * 3))) ? 2 :
		(angle < ((ANGLE_PER_PTN * 3) + (ANGLE_PER_CEL * 4))) ? 3 : 0
	);
}

void CMissiles::reset(void)
{
	for(int i = 0; i < MISSILE_COUNT; i++) {
		flag[i] = MF_FREE;
	}
}

// Missiles are blitted to unaligned X positions (and are, in fact, the only
// 16×16 .PTN entity where this is the case), so a missile sprite is likely
// to cover two 16-pixel words. Since the left coordinate is rounded down to
// the previous multiple of 16, the unblitting width therefore has to be
// doubled.
// … Except that it doesn't have to, because egc_copy_rect_1_to_0_16() already
// ceils the unblitted width to the next multiple of 16. Which makes this
// addition just as unnecessary as the _word_w() wrapper.
#define sloppy_unput(missiles, i) { \
	egc_copy_rect_1_to_0_16_word_w( \
		(missiles).prev_left[i].to_pixel(), \
		(missiles).prev_top[i].to_pixel(), \
		(15 + MISSILE_W), \
		MISSILE_H \
	); \
}

#define in_current_interlace_field(i) \
	((i % 2) == (frame_rand & 1))

void CMissiles::unput_update_render(void)
{
	int i;

	// Unput/update/explode
	for(i = 0; i < MISSILE_COUNT; i++) {
		if(flag[i] == MF_FREE) {
			continue;
		}
		if(in_current_interlace_field(i) && (prev_left[i].v != MISSILE_NEW)) {
			sloppy_unput(*this, i);
		}
		if(flag[i] == MF_MOVING) {
			cur_left[i].v += velocity_x[i].v;
			cur_top[i].v += velocity_y[i].v;

			if(!overlap_xy_lrtb_le_ge(
				cur_left[i].to_pixel(),
				cur_top[i].to_pixel(),
				MISSILE_LEFT_MIN,
				MISSILE_TOP_MIN,
				MISSILE_LEFT_MAX,
				MISSILE_TOP_MAX
			)) {
				flag[i] = MF_HIT;
				sloppy_unput(*this, i);

				if(cur_left[i].to_pixel() < MISSILE_LEFT_MIN) {
					prev_left[i].v = to_sp(MISSILE_LEFT_MIN);
				} else if(cur_left[i].to_pixel() > MISSILE_LEFT_MAX) {
					prev_left[i].v = to_sp(MISSILE_LEFT_MAX);
				}
				if(cur_top[i].to_pixel() < MISSILE_TOP_MIN) {
					prev_top[i].v = to_sp(MISSILE_TOP_MIN);
				} else if(cur_top[i].to_pixel() > MISSILE_TOP_MAX) {
					prev_top[i].v = to_sp(PLAYFIELD_BOTTOM - (MISSILE_H / 2));
				}
			}
		} else {
			if(in_current_interlace_field(i)) {
				static_cast<int8_t>(flag[i])++;
			}
			if(flag[i] > MF_HIT_last) {
				flag[i] = MF_FREE;
				sloppy_unput(*this, i);
				mdrv2_se_play(7);
			}
		}
	}

	// Render
	for(i = 0; i < MISSILE_COUNT; i++) {
		if((flag[i] == MF_FREE) || !in_current_interlace_field(i)) {
			continue;
		} else if(flag[i] == MF_MOVING) {
			main_ptn_id_t ptn_id;
			int quarter;

			ptn_cel_for(i, ptn_id, quarter);
			ptn_put_quarter(
				cur_left[i].to_pixel(), cur_top[i].to_pixel(), ptn_id, quarter
			);
			prev_left[i] = cur_left[i];
			prev_top[i] = cur_top[i];
		} else { // >= MF_HIT
			ptn_put_quarter(
				prev_left[i].to_pixel(),
				prev_top[i].to_pixel(),
				(ptn_id_base + MISSILE_HIT_IMAGE),
				(flag[i] - MF_HIT)
			);
		}
	}

	// Collision detection
	if(player_invincible) {
		return;
	}
	for(i = 0; i < MISSILE_COUNT; i++) {
		if(flag[i] == MF_FREE) {
			continue;
		}

		// 46×46 pixels around the player's center point
		enum {
			HITBOX_OFFSET_LEFT = (-(MISSILE_W / 2)),
			HITBOX_OFFSET_RIGHT = ((PLAYER_W / 2) + (MISSILE_W / 2)),
			HITBOX_OFFSET_TOP = (-(MISSILE_H / 2)),
			HITBOX_OFFSET_BOTTOM = (PLAYER_H)
		};
		if(
			(cur_left[i].to_pixel() > (player_left + HITBOX_OFFSET_LEFT)) &&
			(cur_left[i].to_pixel() < (player_left + HITBOX_OFFSET_RIGHT)) &&
			(cur_top[i].to_pixel() < (player_top + HITBOX_OFFSET_BOTTOM)) &&
			(cur_top[i].to_pixel() > (player_top + HITBOX_OFFSET_TOP))
		) {
			player_is_hit = true;
			return;
		}
	}
}

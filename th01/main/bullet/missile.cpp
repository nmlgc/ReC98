extern "C" {
#include "planar.h"
#include "th01/math/overlap.hpp"
#include "th01/hardware/egc.h"
#include "th01/hardware/input.hpp"
#include "th01/snd/mdrv2.h"
#include "th01/formats/ptn.hpp"
}
#include "th01/main/vars.hpp"
#include "th01/main/bullet/missile.hpp"

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

// Calculates the current [ptn_id] and [quarter] for the missile at the given
// index.
// TODO: Should be turned into a class method once it can be part of this
// translation unit.
void ptn_cel_for(CMissiles& that, int i, main_ptn_id_t& ptn_id, int& quarter);

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

			/* TODO: Replace with the decompiled calls
			 * 	ptn_cel_for(i, ptn_id, quarter);
			 * 	ptn_put_quarter(
			 * 		cur_left[i].to_pixel(), cur_top[i].to_pixel(), ptn_id, quarter
			 * 	);
			 * once ptn_cel_for() is part of this translation unit */
			_asm {
				push	ss;
				lea 	ax, quarter;
				push	ax
				push	ss;
				lea 	ax, ptn_id;
				push	ax
				db  	0x56;	// PUSH SI
				db  	0x66, 0xFF, 0x76, 0x06;	// PUSH LARGE [this]
				push	cs;
				call	near ptr ptn_cel_for;
				push	quarter;
				push 	ptn_id;
			}
			_AX = cur_top[i].to_pixel();
			_asm {
				push	ax;
			}
			_AX = ((Subpixel *)(
				(uint8_t  __seg *)(_ES) +
				(uint8_t __near *)(_BX) +
				(uint16_t)&(((CMissiles __near *)0)->cur_left)
			))->to_pixel();
			_asm {
				push	ax;
				call	far ptr ptn_put_quarter
				add 	sp, 22
			}
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
			done = true;
			return;
		}
	}
}

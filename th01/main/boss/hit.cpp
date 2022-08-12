#include "th01/hardware/palette.h"
#include "th01/main/player/bomb.hpp"
#include "th01/main/player/orb.hpp"
#include "th01/main/player/shot.hpp"

#define z_palette_flash_colors(colors, colors_count, i) \
	for(i = 0; colors_count > i; i++) { \
		z_palette_set_show(colors[i], RGB4::max(), RGB4::max(), RGB4::max()); \
	}

void boss_hit_update_and_render(
	int &invincibility_frame,
	bool16 &is_invincible,
	int &hp,
	const unsigned char invincibility_flash_colors[],
	unsigned char invincibility_flash_colors_count,
	int hit_score,
	farfunc_t_far hit_callback,
	bool colliding_with_orb,
	screen_x_t shot_hitbox_left,
	screen_y_t shot_hitbox_top,
	pixel_t shot_hitbox_w,
	pixel_t shot_hitbox_h
)
{
	int i;

	if(test_damage == true) {
		hp--;
		test_damage = false;
		hud_hp_decrement(hp);
	}

	// Sure, why not? This function didn't have enough parameters already,
	// after all!
	Shots.hittest_boss(
		shot_hitbox_left, shot_hitbox_top, shot_hitbox_w, shot_hitbox_h
	);

	if(
		((colliding_with_orb == true) && (is_invincible == false)) ||
		(bomb_deals_damage(frame_rand) == true)
	) {
		invincibility_frame = 0;
		z_palette_flash_colors(
			invincibility_flash_colors, invincibility_flash_colors_count, i
		);
		hp--;
		is_invincible = true;

		if(orb_is_moving_left()) {
			orb_velocity_x = OVX_4_RIGHT;
		} else if(orb_is_moving_right()) {
			orb_velocity_x = OVX_4_LEFT;
		} else if(orb_velocity_x == OVX_0) {
			if(orb_cur_left < (PLAYFIELD_CENTER_X - (ORB_W / 2))) {
				orb_velocity_x = OVX_4_RIGHT;
			} else {
				orb_velocity_x = OVX_4_LEFT;
			}
		}
		score += hit_score;
		hud_score_and_cardcombo_render();
		mdrv2_se_play(3);
		hit_callback();
		hud_hp_decrement(hp);
	}

	if(
		(is_invincible == true) &&
		(invincibility_frame < BOSS_HIT_INVINCIBILITY_FRAMES)
	) {
		if((invincibility_frame % 4) == 2) {
			z_palette_flash_colors(
				invincibility_flash_colors, invincibility_flash_colors_count, i
			);
		} else if((invincibility_frame % 4) == 0) {
			boss_palette_show();
		}
	} else if(invincibility_frame > BOSS_HIT_INVINCIBILITY_FRAMES) {
		// ZUN bug: This is done even if [is_invincible] is false. Since all
		// callers of this function increment [invincibility_frame] on every
		// frame, this palette reset ends up happening periodically, completely
		// unrelated to the boss getting hit and defying common sense. At best,
		// this call acts as a safety net against wild mutation of the hardware
		// palette during boss fights, but you're way more likely to perceive
		// *this* as a wild unexpected palette change from out of nowhere.
		//
		// (For examples, see Mima's pattern_hop_and_fire_chase_pellets(), and
		// Konngara's konngara_load_and_entrance())
		boss_palette_show();

		invincibility_frame = 0;
		is_invincible = false;
	}
}

#undef z_palette_flash_colors

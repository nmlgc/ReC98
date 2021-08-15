bool16 is_bomb_damage_frame(unsigned long frame);

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
	screen_x_t hitbox_left,
	screen_y_t hitbox_top,
	pixel_t hitbox_w,
	pixel_t hitbox_h
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
	Shots.hittest_boss(hitbox_left, hitbox_top, hitbox_w, hitbox_h);

	/* TODO: Replace with the decompiled expression
	 * 	if(
	 * 		((colliding_with_orb == true) && (is_invincible == false)) ||
	  *		(is_bomb_damage_frame(frame_rand) == true)
	 * 	)
	 * once that function is part of this translation unit */
	if((colliding_with_orb == true) && (is_invincible == false)) {
		goto got_hit;
	}
	_asm {
		db  	0x66, 0xFF, 0x36;	// PUSH LARGE [m32]
		dw  	offset frame_rand;
		nop;
		push	cs;
		call	near ptr is_bomb_damage_frame;
		add 	sp, 4;
	}
	if(_AX != 1) {
		goto still_invincible;
	}
got_hit:
	{
		invincibility_frame = 0;
		z_palette_flash_colors(
			invincibility_flash_colors, invincibility_flash_colors_count, i
		);
		hp--;
		is_invincible = true;

		if(
			(orb_velocity_x == OVX_4_LEFT) || (orb_velocity_x == OVX_8_LEFT)
		) {
			orb_velocity_x = OVX_4_RIGHT;
		} else if(
			(orb_velocity_x == OVX_4_RIGHT) || (orb_velocity_x == OVX_8_RIGHT)
		) {
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

still_invincible:
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
		boss_palette_show();
		invincibility_frame = 0;
		is_invincible = false;
	}
}

#undef z_palette_flash_colors

#pragma option -G

#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "libs/master.lib/master.hpp"
#include "th01/math/overlap.hpp"
#include "th01/math/subpixel.hpp"
#include "th04/math/vector.hpp"
#include "th04/main/frames.h"
#include "th04/main/scroll.hpp"
#include "th04/main/drawp.hpp"
#include "th04/main/playperf.hpp"
#include "th04/main/score.hpp"
#include "th04/main/slowdown.hpp"
#include "th04/main/bullet/pellet_r.hpp"
#include "th04/main/bullet/clearzap.hpp"
#include "th04/main/player/player.hpp"
#include "th04/main/spark.hpp"
#include "th04/main/hud/hud.hpp"
#include "th04/main/hud/overlay.hpp"
#include "th04/main/pointnum/pointnum.hpp"

#if (GAME == 5)
	#include "th04/main/item/item.hpp"
	#include "th05/sprites/main_pat.h"

	static const int SLOWDOWN_BULLET_THRESHOLD_UNUSED = 32;

	// Updates [bullet]'s patnum based on its current angle.
	void pascal near bullet_update_patnum(bullet_t near &bullet)
	{
		unsigned char patnum_base; // main_patnum_t, obviously

		if(bullet.patnum < PAT_BULLET16_D) {
			return;
		}
		if(bullet.patnum < (PAT_BULLET16_D_BLUE_last + 1)) {
			patnum_base = PAT_BULLET16_D_BLUE;
		} else if(bullet.patnum < (PAT_BULLET16_D_GREEN_last + 1)) {
			patnum_base = PAT_BULLET16_D_GREEN;
		} else if(bullet.patnum < (PAT_BULLET16_V_RED_last + 1)) {
			patnum_base = PAT_BULLET16_V_RED;
		} else {
			patnum_base = PAT_BULLET16_V_BLUE;
		}
		bullet.patnum = bullet_patnum_for_angle(patnum_base, bullet.angle);
	}
#else
	#include "th04/sprites/main_pat.h"

	static const int SLOWDOWN_BULLET_THRESHOLD_UNUSED = 24;

	inline void bullet_update_patnum(bullet_t near &bullet) {
	}
#endif

#pragma option -a2

#define bullet_velocity_set_from_angle_and_speed(bullet) \
	vector2_near(bullet.pos.velocity, bullet.angle, bullet.speed_cur)

void pascal near bullet_turn_x(bullet_t near &bullet)
{
	bullet.u1.turns_done++;
	bullet.angle = (0x80 - bullet.angle);
	if(bullet.u1.turns_done >= bullet_special_motion.turns_max) {
		bullet.move_state = BMS_REGULAR;
	}
	bullet_velocity_set_from_angle_and_speed(bullet);
	bullet_update_patnum(bullet);
}

void pascal near bullet_turn_y(bullet_t near &bullet)
{
	bullet.u1.turns_done++;
	bullet.angle = (/* 0x00 */ - bullet.angle);
	if(bullet.u1.turns_done >= bullet_special_motion.turns_max) {
		bullet.move_state = BMS_REGULAR;
	}
	bullet_velocity_set_from_angle_and_speed(bullet);
	bullet_update_patnum(bullet);
}

#define bullet_turn_complete(bullet) \
	bullet_update_patnum(bullet); \
	bullet.speed_cur = bullet.speed_final; \
	if(bullet.u1.turns_done >= bullet_special_motion.turns_max) { \
		bullet.move_state = BMS_REGULAR; \
	} \
	bullet_velocity_set_from_angle_and_speed(bullet);

enum bullet_bounce_edge_t {
	BBE_LEFT = (1 << 0),
	BBE_RIGHT = (1 << 1),
	BBE_TOP = (1 << 2),
	BBE_BOTTOM = (1 << 3),
};

#define bullet_bounce(bullet, edges) \
	if( \
		((edges & BBE_LEFT) && (bullet.pos.cur.x.v <= to_sp(0.0f))) || \
		((edges & BBE_RIGHT) && (bullet.pos.cur.x.v >= to_sp(PLAYFIELD_W))) \
	) { \
		bullet_turn_x(bullet); \
	} \
	if(\
		((edges & BBE_TOP) && (bullet.pos.cur.y.v <= to_sp(0.0f))) || \
		((edges & BBE_BOTTOM) && (bullet.pos.cur.y.v >= to_sp(PLAYFIELD_H))) \
	) { \
		bullet_turn_y(bullet); \
	}

// Calculates [bullet.velocity] for the special motion types.
void pascal near bullet_update_special(bullet_t near &bullet)
{
	switch(bullet.special_motion) {
	case BSM_SLOWDOWN_THEN_TURN_AIMED:
		if(bullet.speed_cur.v != to_sp(0.0f)) {
			bullet_velocity_set_from_angle_and_speed(bullet);
			bullet.speed_cur.v--; // -= to_sp(1 / 16.0f)
		} else {
			bullet.u1.turns_done++;
			bullet.angle = iatan2(
				(player_pos.cur.y.v - bullet.pos.cur.y.v),
				(player_pos.cur.x.v - bullet.pos.cur.x.v)
			);
			bullet_turn_complete(bullet);
		}
		break;

	case BSM_SLOWDOWN_THEN_TURN:
		if(bullet.speed_cur.v != to_sp(0.0f)) {
			bullet_velocity_set_from_angle_and_speed(bullet);
			bullet.speed_cur.v--; // -= to_sp(1 / 16.0f)
		} else {
			bullet.u1.turns_done++;
			bullet.angle += bullet.u2.angle.turn_by;
			bullet_turn_complete(bullet);
		}
		break;

	case BSM_SPEEDUP:
		bullet_velocity_set_from_angle_and_speed(bullet);
		bullet.speed_cur.v += bullet_special_motion.speed_delta.v;
		break;

	case BSM_SLOWDOWN_TO_ANGLE:
		if(bullet.speed_cur.v != to_sp(0.0f)) {
			bullet_velocity_set_from_angle_and_speed(bullet);
			// >= to_sp(2 / 16.0f) would have been cleaner
			if(bullet.speed_cur.v > to_sp8(1 / 16.0f)) {
				bullet.speed_cur.v += to_sp(-2 / 16.0f);
			} else {
				bullet.speed_cur.set(0.0f);
			}
			if(bullet.speed_cur.v < to_sp8(2.0f)) {
				bullet.angle += (static_cast<int8_t>(
					bullet.u2.angle.target - bullet.angle
				) / 4);
			}
		} else {
			bullet.angle = bullet.u2.angle.target;
			bullet.speed_cur.v = bullet.speed_final.v;
			bullet.move_state = BMS_REGULAR;
			bullet_velocity_set_from_angle_and_speed(bullet);
		}
		break;

	case BSM_BOUNCE_LEFT_RIGHT:
		bullet_bounce(bullet, (BBE_LEFT | BBE_RIGHT));
		break;

	case BSM_BOUNCE_TOP_BOTTOM:
		bullet_bounce(bullet, (BBE_TOP | BBE_BOTTOM));
		break;

	case BSM_BOUNCE_LEFT_RIGHT_TOP_BOTTOM:
		bullet_bounce(bullet, (BBE_LEFT | BBE_RIGHT | BBE_TOP | BBE_BOTTOM));
		break;

	case BSM_BOUNCE_LEFT_RIGHT_TOP:
		bullet_bounce(bullet, (BBE_LEFT | BBE_RIGHT | BBE_TOP));
		break;

	case BSM_GRAVITY:
		if(stage_frame_mod2) {
			bullet.pos.velocity.y.v += bullet_special_motion.speed_delta;
		}
		break;

	#if (GAME == 5)
		case BSM_EXACT_LINEAR:
			bullet.distance.v += bullet.speed_cur.v;
			vector2_at(
				drawpoint,
				bullet.origin.x.v,
				bullet.origin.y.v,
				bullet.distance.v,
				bullet.angle
			);
			bullet.pos.velocity.x.v = (drawpoint.x.v - bullet.pos.cur.x.v);
			bullet.pos.velocity.y.v = (drawpoint.y.v - bullet.pos.cur.y.v);
			break;
	#endif
	}
}

void bullets_update(void)
{
	int i;
	int bullets_seen = 0;
	#if (GAME == 5)
		pellet_clouds_render_count = 0;
	#endif
	pellets_render_count = 0;
	bullet_t near *bullet = &bullets[BULLET_COUNT - 1];

	// Since we iterate over the bullet array backwards, we encounter the 16×16
	// bullets first.
	#define is_bullet16(i) \
		(i < BULLET16_COUNT)

	#define is_pellet(i) \
		!is_bullet16(i)

	if(bullet_zap.active == false) {
		for(i = 0; i < BULLET_COUNT; i++, bullet--) {
			if(bullet->flag == F_FREE) {
				continue;
			}
			if(bullet->flag == F_REMOVE) {
				bullet->flag = F_FREE;
				continue;
			}
			bullets_seen++;
			if(bullet_clear_time) {
				if(bullet->move_state < BMS_DECAY) {
					bullet->move_state = BMS_DECAY;
					bullet->patnum = is_bullet16(i)
						? PAT_DECAY_BULLET16
						: PAT_DECAY_PELLET;

					if(bullet->age != 0) {
						score_delta += 100;
					} else {
						score_delta += 10;
					}
				} else {
					reinterpret_cast<unsigned char &>(bullet->move_state)++;
					if(bullet->move_state >= BMS_DECAY_END) {
						bullet->pos.update_seg3();
						bullet->flag = F_REMOVE;
						continue;
					}
					if((bullet->move_state % BMS_DECAY_FRAMES_PER_CEL) == 0) {
						bullet->patnum++;
					}
				}
			}
			bullet->age++;
			if(bullet->spawn_state >= BSS_ACTIVE) {
				if(bullet->spawn_state == BSS_ACTIVE) {
					bullet->spawn_state = BSS_GRAZEABLE;
				} else {
					// In delay cloud state
					if(bullet->spawn_state == BSS_CLOUD_BACKWARDS) {
						bullet->pos.prev = bullet->pos.cur;
						bullet->pos.cur.x.v -= (bullet->pos.velocity.x.v << 3);
						bullet->pos.cur.y.v -= (bullet->pos.velocity.y.v << 3);
						bullet->spawn_state = BSS_CLOUD_FORWARDS;
					} else if(bullet->spawn_state == BSS_CLOUD_FORWARDS) {
						bullet->pos.update_seg3();
					} else {
						bullet->pos.prev = bullet->pos.cur;
						bullet->pos.cur.x.v += (bullet->pos.velocity.x.v / 3);
						bullet->pos.cur.y.v += (bullet->pos.velocity.y.v / 3);
					}
					reinterpret_cast<unsigned char &>(bullet->spawn_state)++;
					if(bullet->spawn_state >= BSS_CLOUD_END) {
						#if (GAME == 5)
							if(!playfield_encloses_yx_lt_ge(
								bullet->pos.cur.x,
								bullet->pos.cur.y,
								BULLET16_W,
								BULLET16_H
							)) {
								bullet->flag = F_REMOVE;
								continue;
							}
						#endif
						bullet->spawn_state = BSS_ACTIVE;
					}
					#if (GAME == 5)
						else if(is_pellet(i)) {
							pellet_clouds_render[pellet_clouds_render_count++] =
								bullet;
						}
					#endif
					continue;
				}
			}
			if(bullet->move_state == BMS_SPECIAL) {
				bullet_update_special(*bullet);
			} else if(bullet->move_state == BMS_SLOWDOWN) {
				bullet->u1.slowdown_time--;
				bullet->speed_cur.v = (bullet->speed_final.v + ((
					bullet->u1.slowdown_time * bullet->u2.slowdown_speed_delta.v
				) / BMS_SLOWDOWN_FRAMES));
				if(bullet->u1.slowdown_time == 0) {
					bullet->speed_cur = bullet->speed_final;
					bullet->move_state = BMS_REGULAR;
				}
				bullet_velocity_set_from_angle_and_speed((*bullet));
			}

			/* DX:AX = */ bullet->pos.update_seg3();
			if(!playfield_encloses(_AX, _DX, BULLET16_W, BULLET16_H)) {
				bullet->flag = F_REMOVE;
				continue;
			}

			if(bullet_clear_time != 0) {
				continue;
			}
			_AX -= player_pos.cur.x.v;
			_DX -= player_pos.cur.y.v;
			if(player_invincibility_time == 0) {
				// Yup, a bullet must have been grazed in a previous frame
				// before it can be collided with.
				if(bullet->spawn_state != BSS_GRAZEABLE) {
					if(overlap_wh_inplace_fast(
						_AX, _DX, BULLET_KILLBOX_W, BULLET_KILLBOX_H
					)) {
						bullet->flag = F_REMOVE;
						player_is_hit = true;
						continue;
					}
				} else {
					// Yes, the graze box is biased to the right, and taller
					// than wide.
					if(overlap_offcenter_inplace_fast(
						_AX, _DX,
						to_sp(16.0f), to_sp(22.0f), to_sp(20.0f), to_sp(22.0f)
					)) {
						/* TODO: Replace with the decompiled call
						 * 	sparks_add_random(bullet->pos.cur.x, bullet->pos.cur.y, to_sp(2.0f), 2);
						 * once that function is part of the same segment */
						_asm {
							db  	0xFF, 0x74, 0x02;
							db  	0xFF, 0x74, 0x04;
							db  	0x66, 0x68, 2, 0x00, (2 * 16), 0x00;
							nop;
							push	cs;
							call	near ptr sparks_add_random;
						}
						bullet->spawn_state = BSS_GRAZED;
						if(stage_graze < STAGE_GRAZE_CAP) {
							stage_graze++;
							hud_graze_put();
							score_delta += graze_score;
						}
					}
				}
			}

			if(is_pellet(i)) {
				pellets_render[pellets_render_count].top.left = (
					bullet->pos.cur.to_screen_left(PELLET_W)
				);
				pellets_render[pellets_render_count].top.top = (
					bullet->pos.cur.to_vram_top_scrolled_seg3(PELLET_H)
				);
				pellets_render_count++;
			}
		}
		if(turbo_mode == false) {
			#if (GAME == 5)
				slowdown_caused_by_bullets = false;
				i = 42;
			#else
				i = 24;
				i += playperf;
			#endif
			i += (rank * 8);
			if(bullets_seen >= i) {
				if(!stage_frame_mod2) {
					slowdown_factor = 2;
					#if (GAME == 5)
						slowdown_caused_by_bullets = true;
					#endif
				}
			} else if(bullets_seen >= (i + SLOWDOWN_BULLET_THRESHOLD_UNUSED)) {
				// Yes, never executed, as the first condition would then have
				// been true as well
				slowdown_factor = 2;
				#if (GAME == 5)
					slowdown_caused_by_bullets = true;
				#endif
			}
		}
	} else {
		// A bit wasteful to run all of this every frame, since no new bullets
		// are spawned while [bullet_zap] is active; the bullet spawn wrapper
		// functions prevent that. Then again, this means that the code here
		// does kind of rely on bullets not being spawned through other methods.

		unsigned int score_per_bullet;
		unsigned int score_step;

		// Without this cap, the [popup_bonus] formula would be
		// 	0.5n³ - n² + 1.5n
		// with n = [bullets_seen].
		unsigned int score_per_bullet_cap;
		unsigned char patnum;

		patnum =
			(PAT_BULLET_ZAP + (bullet_zap.frames / BULLET_ZAP_FRAMES_PER_CEL)
		);
		score_per_bullet = 1;
		score_step = 1;
		#if (GAME == 5)
			// ZUN quirk: All code below uses TH04's patnum for that sprite.
			// This causes the decay animation to never actually play in TH05.
			#define PAT_BULLET_ZAP 72

			score_per_bullet_cap = (rank == RANK_EXTRA)
				? 1600
				: select_for_rank(960, 1280, 1280, 1280);
		#else
			switch(rank) {
			case RANK_EASY:
				score_per_bullet_cap = 1000;
				break;
			case RANK_NORMAL:
			case RANK_HARD:
			case RANK_LUNATIC:
				score_per_bullet_cap = 1600;
				break;
			case RANK_EXTRA:
				score_per_bullet_cap = 2000;
				break;
			}
		#endif

		overlay_popup_bonus = 0;
		for(i = 0; i < BULLET_COUNT; i++, bullet--) {
			if(bullet->flag != F_ALIVE) {
				continue;
			}
			bullet->pos.velocity.set(0.0f, 0.0f);
			bullet->pos.update_seg3();

			// ZUN quirk: Always false in TH05, see above
			if(patnum < (PAT_BULLET_ZAP + BULLET_DECAY_CELS)) {
				bullet->patnum = patnum;
				#if (GAME == 5)
					bullets_seen++;
				#endif
				continue;
			}
			overlay_popup_bonus += score_per_bullet;
			score_delta += score_per_bullet;
			pointnums_add_white(
				bullet->pos.cur.x, bullet->pos.cur.y, score_per_bullet
			);

			score_per_bullet += score_step;
			score_step += 3;
			if(score_per_bullet > score_per_bullet_cap) {
				score_per_bullet = score_per_bullet_cap;
			}

			bullet->flag = F_REMOVE;
			#if (GAME == 5)
				if(bullet_zap_drop_point_items && ((bullets_seen % 4) == 0)) {
					items_add(bullet->pos.cur.x, bullet->pos.cur.y, IT_POINT);
				}
				bullets_seen++;
			#endif
		}
		// Note that this would show only one popup even *if* bullets could
		// spawn during the zap frames: Popups can be changed at least every
		// 64 frames, and BULLET_ZAP_FRAMES is smaller.
		if(overlay_popup_bonus) {
			overlay_popup_show(POPUP_ID_BONUS);
		}
		bullet_zap.frames++;

		// ZUN quirk: Always true in TH05, see above
		if(patnum >= (PAT_BULLET_ZAP + BULLET_ZAP_CELS)) {
			bullet_zap.active = false;
		}
	}
	if(bullet_clear_time) {
		bullet_clear_time--;
	}
}

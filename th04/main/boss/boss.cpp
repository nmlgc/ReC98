#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "libs/kaja/kaja.h"
#include "th01/math/overlap.hpp"
#include "th01/math/subpixel.hpp"
extern "C" {
#include "th02/hardware/frmdelay.h"
}
#include "th03/hardware/palette.hpp"
#include "th04/common.h"
#include "th04/gaiji/gaiji.h"
#include "th04/math/motion.hpp"
extern "C" {
#include "th04/snd/snd.h"
}
#include "th04/sprites/main_pat.h"
#include "th04/main/bg.hpp"
#include "th04/main/end.hpp"
#include "th04/main/frames.h"
#include "th04/main/homing.hpp"
extern "C" {
#include "th04/main/null.hpp"
#include "th04/main/phase.h"
#include "th04/main/playfld.hpp"
#include "th04/main/rank.hpp"
#include "th04/main/quit.hpp"
#include "th04/main/score.hpp"
}
#include "th04/main/slowdown.hpp"
#include "th04/main/hud/overlay.hpp"
#include "th04/main/stage/stage.hpp"
extern "C" {
#include "th04/main/tile/tile.hpp"
}
#include "th04/main/dialog/dialog.hpp"
#include "th04/main/bullet/clearzap.hpp"
#include "th04/main/player/player.hpp"
#include "th04/main/player/bomb.hpp"
#if (GAME == 5)
	#include "th01/math/area.hpp"
	#include "th05/resident.hpp"
	#include "th05/main/boss/boss.hpp"
#else
	extern "C" {
	#include "th03/formats/cdg.h"
	}
	#include "th04/resident.hpp"
	#include "th04/formats/bb.h"
	#include "th04/formats/dialog.hpp"
	#include "th04/sprites/main_cdg.h"
	#include "th04/main/boss/boss.hpp"
	extern "C" {
	#include "th04/main/boss/bosses.hpp"
	}
	#include "th04/shiftjis/fns.hpp"
#endif

inline void optimization_barrier(void) {}

#if (GAME == 5)
	// Processes any collision between the player and boss sprites.
	void near boss_hittest_player(void);
#else
	// Moving on top of the boss doesn't kill the player in TH04.
	inline void boss_hittest_player(void) {
	}
#endif

void pascal near boss_phase_next(
	explosion_type_t explosion_type, int next_end_hp
)
{
	if(explosion_type != ET_NONE) {
		boss_explode_small(explosion_type);
		if(!boss_phase_timed_out) {
			bullets_clear();
			boss_items_drop();
		}
	}
	boss_phase_timed_out = true;
	boss.phase++;
	boss.phase_frame = 0;
	boss.mode = 0;
	boss.mode_change = 0;
	boss.hp = boss.phase_end_hp;
	boss.phase_end_hp = next_end_hp;
}

#if (GAME == 5)
	void pascal near boss_defeat_update(unsigned int bonus_units)
#else
	// Temporarily declaring these here for alignment reasons.
	char st06bk_cdg[] = BOSS_BG_MUGETSU_FN;
	char st06_bb[] = BOSS_BB_MUGETSU_FN;

	void near boss_defeat_update(void)
#endif
{
	#if (GAME == 5)
		if(boss.phase == PHASE_BOSS_EXPLODE_SMALL) {
			if(boss.phase_frame == BDF_SMALL_1) {
				boss.damage_this_frame = 0;
				boss_explode_small(ET_CIRCLE);
				snd_se_play(13);
			}
			if(boss.phase_frame == BDF_SMALL_2) {
				boss_explode_small(ET_VERTICAL);
			}
			if(boss.phase_frame == BDF_BIG) {
				boss_defeat_explode_big(ET_CIRCLE, bonus_units);
				player_invincibility_time = BOSS_DEFEAT_INVINCIBILITY_FRAMES;
			}
			homing_target.x.v = Subpixel::None();
			homing_target.y.v = Subpixel::None();
			return;
		} else if(boss.phase == PHASE_BOSS_EXPLODE_BIG) {
	#else
		if(boss.phase == PHASE_EXPLODE_BIG) {
	#endif
		if(boss.phase_frame < 12) {
			playfield_shake_x = (stage_frame_mod2 == 0) ? -4 : +4;
			playfield_shake_y = (stage_frame_mod4 <= 1) ? -4 : +4;
		}
		bg_render_bombing_func = tiles_render_all;
		slowdown_factor = 2;
		#if (GAME == 4)
			boss.phase_frame++;
		#endif
		if((boss.phase_frame % 8) == 0) {
			boss.sprite++;
			if(boss.sprite >= (PAT_ENEMY_KILL_last + 1)) {
				boss.phase++; // = PHASE_NONE
				boss.phase_frame = 0;
				bombing_disabled = true;
				#if (GAME == 5)
					boss_fg_render = nullfunc_near;
				#endif
			}
		}
		return;
	} // else if(boss.phase == PHASE_NONE) {
	palette_settone_deferred(60);
	if(boss.phase_frame == BDF_DIALOG) {
		resident->graze += stage_graze;
		if(stage_id != (MAIN_STAGE_COUNT - 1)) {
			#if (GAME == 5)
				dialog_animate();
				if(stage_id != STAGE_EXTRA) {
					stage_clear_bonus();
				} else {
					stage_allclear_bonus();
					optimization_barrier();
				}
			#elif (GAME == 4)
				if((stage_id == 4) && (
					(score.continues_used != 0) || (rank == RANK_EASY)
				)) {
					dialog_load_yuuka5_defeat_bad();
					dialog_animate();
					end_game_bad();
				}
				if(stage_id == STAGE_EXTRA) {
					#define gengetsu_started static_cast<bool>( \
						boss_statebyte[0] \
					)

					super_clean(PAT_STAGE, (PAT_STAGE_last + 1));
					dialog_animate();

					if(!gengetsu_started) {
						gengetsu_started = true;
						boss_reset();
						boss.pos.init(
							(PLAYFIELD_W / 2), (playfield_fraction_y(6 / 23.0f))
						);
						bg_render_not_bombing = mugetsu_gengetsu_bg_render;
						boss_update = gengetsu_update;
						boss_fg_render = gengetsu_fg_render;
						boss.sprite = PAT_GENGETSU_TIPPING;
						boss_hitbox_radius.set(
							(GENGETSU_W / 4), (GENGETSU_H / 2)
						);
						bgm_title_id = 15;
						overlay1 = overlay_boss_bgm_update_and_render;
						cdg_free(CDG_BG_BOSS);

						/* TODO: Replace with the decompiled call
						 * 	bb_boss_free();
						 * once that function is part of this translation
						 * unit */
						_asm { push cs; call near ptr bb_boss_free; }

						cdg_load_single_noalpha(
							CDG_BG_BOSS, BOSS_BG_GENGETSU_FN, 0
						);
						bb_boss_load(BOSS_BB_GENGETSU_FN);
						bombing_disabled = false;
					} else {
						stage_allclear_bonus();
						boss.phase_frame++;
					}
					return;

					#undef gengetsu_started
				}
				dialog_animate();
				stage_clear_bonus();
			#endif
		} else {
			stage_allclear_bonus();
		}
	} else if(boss.phase_frame == BDF_FADEOUT) {
		#if (GAME == 5)
			// ZUN bug: TH04 doesn't do this. It's not a problem in stages 1
			// to 5 because the remaining score delta will carry over into the
			// next stage and be added to the score there. During the final and
			// Extra Stage though, the lack of this call causes the Clear Bonus
			// to effectively be capped to
			//
			// 	((BDF_FADEOUT - BDF_DIALOG) * SCORE_DELTA_FRAME_LIMIT)
			//
			// points, as we immediately launch into MAINE.EXE while ignoring
			// the rest of the delta.
			score_delta_commit();

			if(stage_id < STAGE_EXTRA) {
				for(int i = 0; i < SCORE_DIGITS; i++) {
					resident->stage_score[stage_id].digits[i] = score.digits[i];
				}
			}
		#endif
		if(stage_id == (MAIN_STAGE_COUNT - 1)) {
			end_game();
		} else if(stage_id == STAGE_EXTRA) {
			end_extra();
		}
		overlay_stage_leave();
		snd_kaja_func(KAJA_SONG_FADE, 10);
	} else if(boss.phase_frame == BDF_NEXT_STAGE) {
		resident->stage++;
		#if (GAME == 4)
			resident->stage_ascii++;
		#endif
		quit = Q_NEXT_STAGE;
		frame_delay(1);
	}
	#if (GAME == 4)
		boss.phase_frame++;
	#endif
	homing_target.x.v = Subpixel::None();
	homing_target.y.v = Subpixel::None();
}

#if (GAME == 5)
	void near boss_hittest_player(void)
	{
		#define delta_x	static_cast<subpixel_t>(_AX)
		#define delta_y	static_cast<subpixel_t>(_DX)

		delta_x = boss.pos.cur.x.v;
		delta_y = boss.pos.cur.y.v;
		delta_x -= player_pos.cur.x.v;
		delta_y -= player_pos.cur.y.v;

		// You probably wouldn't swap X and Y in sane code.
		if(overlap_wh_inplace_fast(
			delta_y, delta_x, to_sp(BOSS_H / 2), to_sp(BOSS_W / 2)
		)) {
			player_is_hit = true;
		}

		#undef delta_y
		#undef delta_x
	}
#endif

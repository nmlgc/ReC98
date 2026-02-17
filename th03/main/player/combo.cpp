#include "th03/main/player/chain.hpp"
#include "th03/main/player/combo.hpp"
#include "th03/main/player/gba.hpp"
#include "th03/main/player/stuff.hpp"
#include "th03/main/enemy/efe.hpp"
#include "th03/main/enemy/expl.hpp"
#include "th03/main/hud/dynamic.hpp"
#include "th03/main/hud/warning.hpp"
#include "th03/main/difficul.hpp"
#include "th03/main/round.hpp"
#include "th03/main/score.hpp"
#include "th03/main/v_colors.hpp"
#include "th03/gaiji/gaiji.h"
#include "libs/master.lib/pc98_gfx.hpp"

/// Constants
/// ---------

static const int COMBO_DIGITS = 2;
/// ---------

/// Coordinates
/// -----------

// These are in playfield space.
static const pixel_t BOX_LEFT = 16;
static const pixel_t SCORE_LEFT = (BOX_LEFT + 8);

// ZUN bloat: Wouldn't have been needed if the respective coordinates were
// calculated relative to [PLAYFIELD_LEFT].
inline tram_x_t playfield_border_tram_x(const pid2& pid) {
	return (
		PLAYFIELD1_CLIP_LEFT + (pid * (PLAYFIELD_W_BORDERED / GLYPH_HALF_W))
	);
}
inline tram_x_t box_tram_x(tram_x_t playfield_border_left) {
	return (
		playfield_border_left + ((PLAYFIELD_BORDER + BOX_LEFT) / GLYPH_HALF_W)
	);
}
/// -----------

extern const char near gsHIT[];
extern const char near gBONUS_BOX[];
extern const char near aBONUS_BOX_SPACES[];

void combos_update_and_render(void)
{
	enum {
		SCORE_TOP = (PLAYFIELD_TOP + 32),
		SCORE_TRAM_Y = (SCORE_TOP / GLYPH_H),
		SCORE_VRAM_TOP = (SCORE_TOP / 2),
		HITS_TRAM_Y = (SCORE_TRAM_Y - 1),
	};
	combo_t near *p = combos;
	tram_x_t left;
	int pid;
	uint8_t col;
	for(pid = 0; pid < PLAYER_COUNT; (pid++, p++)) {
		if(p->time == 0) {
			continue;
		}
		if(p->time == COMBO_FRAMES) {
			left = playfield_border_tram_x(pid);
			gaiji_putsa(
				(box_tram_x(left) + (COMBO_DIGITS * GAIJI_TRAM_W)),
				HITS_TRAM_Y,
				gsHIT,
				TX_WHITE
			);
			gaiji_putsa(box_tram_x(left), SCORE_TRAM_Y, gBONUS_BOX, TX_WHITE);

			// ZUN bloat: This digit rendering code didn't need to write to the
			// unrelated [col] variable.
			uint8_t hit_val_rem = p->hits_highest;
			if(hit_val_rem >= 10) {
				col = static_cast<gaiji_th03_t>(gb_0 + (hit_val_rem / 10));
				gaiji_putca(box_tram_x(left), HITS_TRAM_Y, col, TX_WHITE);
				hit_val_rem %= 10;
			} else {
				gaiji_putca(box_tram_x(left), HITS_TRAM_Y, g_SP, TX_WHITE);
			}
			col = static_cast<gaiji_th03_t>(gb_0 + hit_val_rem);
			gaiji_putca(
				(box_tram_x(left) + GAIJI_TRAM_W), HITS_TRAM_Y, col, TX_WHITE
			);
		}
		p->time--;
		{
			// ZUN bloat: Could have been a separate variable...
			#define left static_cast<screen_x_t>(left)

			static_assert(PLAYER_COUNT == 2);
			if(pid == 0) {
				left = playfield_x(0, SCORE_LEFT);
			} else {
				left = playfield_x(1, SCORE_LEFT);
			}
			col = V_YELLOW_BRIGHT;

			// ZUN bloat: `&&` instead of `&` would have been more readable,
			// and would have created shorter code.
			if(
				(p->time < COMBO_HIT_RESET_FRAMES) &
				((round_or_result_frame & 3) < 2)
			) {
				col = 8;
			}
			hud_dynamic_5_digit_points_put(
				left, SCORE_VRAM_TOP, p->bonus_total, col
			);

			#undef left
		}
		if(p->time == 0) {
			// ZUN quirk: This will remove the bonus frame and hit label on the
			// last combo frame while leaving the score visible. Should have
			// maybe been done at the beginning of the next frame.
			left = playfield_border_tram_x(pid);
			text_puts(box_tram_x(left), HITS_TRAM_Y, aBONUS_BOX_SPACES);
			text_puts(box_tram_x(left), SCORE_TRAM_Y, aBONUS_BOX_SPACES);

			p->hits_highest = 0;
			score_add(p->bonus_total, pid);
			p->bonus_total = 0;
		}
	}
}

// ZUN bloat: Should be in some other translation unit. Probably the fireball
// one, or a dedicated one for chains?
void pascal near explosion_collision_chain_slot_fire_charged_fireball(
	pid_t pid, efe_t near *efe
)
{
	if(
		chains.charge_fireball[pid][explosion_collision_chain_slot] >=
		(12 - (round_speed / to_sp(1.0f)))
	) {
		chains.charge_fireball[pid][explosion_collision_chain_slot] = 0;

		// ZUN bloat: If only fireballs_add() took a parameter!
		efe_t near *efe_p_prev = efe_p.efe;
		efe_p.efe = efe;

		/* TODO: Replace with the decompiled call
		 * 	fireballs_add();
		 * once that function is part of the same segment */
		_asm { nop; push cs; call near ptr fireballs_add; }

		efe_p.efe = efe_p_prev;
	}
}

// ZUN bloat: On Turbo C++ 4.OJ, using an 8-bit index in subscript-heavy code
// generates a redundant conversion to 16 bits every time.
void pascal near fire_point_based_boss_attack_or_panic(
	uint16_t points, pid_t pid
)
{
	extern bool boss_panic_fired_in_current_combo[PLAYER_COUNT];

	if(points >= combo_points_for_boss_attack) {
		if(warning_flag[pid] != WF_NONE) {
			return;
		}
		if(gba_boss_launched_by != pid) {
			if(gba_flag_active[pid] == GBAF_BOSS) {
				return;
			}
			gba_flag_next[pid] = GBAF_BOSS;
			warning_flag[pid] = WF_PORTRAIT;

			// This would be the regular [chain_slot] parameter if this was
			// merged into combo_add()...
			chains.pellet_and_fireball_value[pid][
				explosion_collision_chain_slot
			] = 0;
			chains.charge_fireball[pid][explosion_collision_chain_slot] = 0;
			chains.charge_exatt[pid][explosion_collision_chain_slot] = 0;

			combo_points_for_boss_attack += 5120;
			if(gba_boss_level < GBA_BOSS_LEVEL_MAX) {
				gba_boss_level++;
			}
			if(gba_boss_launched_by == PID_NONE) {
				players[pid].boss_attacks_fired++;
			} else {
				players[pid].boss_attacks_reversed++;
			}
		} else if(points >= 30000) {
			if(
				boss_panic_fired_in_current_combo[pid] ||
				(gba_flag_active[pid] != GBAF_NONE)
			) {
				return;
			}
			gba_flag_next[pid] = GBAF_GAUGE_BULLET_INIT;
			warning_flag[pid] = WF_PORTRAIT;
			boss_panic_fired_in_current_combo[pid] = true;
			gba_gauge_level[pid] += 3;
			if(gba_gauge_level[pid] > GBA_GAUGE_LEVEL_MAX) {
				gba_gauge_level[pid] = GBA_GAUGE_LEVEL_MAX;
			}
			players[pid].boss_panics_fired++;
		}
	} else {
		boss_panic_fired_in_current_combo[pid] = false;
	}
}

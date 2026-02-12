#pragma option -zCE_EXPL_TEXT

#include "th03/main/player/chain.hpp"
#include "th03/main/player/combo.hpp"
#include "th03/main/player/gba.hpp"
#include "th03/main/player/stuff.hpp"
#include "th03/main/enemy/efe.hpp"
#include "th03/main/enemy/expl.hpp"
#include "th03/main/hud/warning.hpp"
#include "th03/main/difficul.hpp"

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

#pragma option -zCE_EXPL_TEXT

#include "th03/main/player/chain.hpp"
#include "th03/main/enemy/efe.hpp"
#include "th03/main/enemy/expl.hpp"
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

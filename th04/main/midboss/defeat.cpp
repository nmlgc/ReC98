#include "platform.h"
#include "pc98.h"
#include "th01/math/subpixel.hpp"
#include "th04/math/motion.hpp"
#include "th04/sprites/main_pat.h"
#include "th04/main/phase.h"
extern "C" {
#include "th04/main/playfld.hpp"
}
#include "th04/main/midboss/midboss.hpp"

void near midboss_defeat_update(void)
{
	if(midboss.phase == PHASE_EXPLODE_BIG) {
		if(midboss.phase_frame == ((GAME == 5) ? 1 : 0)) {
			playfield_shake_anim_time = ((GAME == 5) ? 10 : 12);
			#if (GAME == 5)
				// Deferred to midboss_reset() in TH04.
				midboss_active = false;
			#endif
		}

		#if (GAME == 4)
			midboss.phase_frame++;
		#endif

		if((midboss.phase_frame % 16) == 0) {
			midboss.sprite++;
			if(midboss.sprite >= (PAT_ENEMY_KILL_last + 1)) {
				midboss.phase = PHASE_NONE;
			}
		}
	} else {
		/* TODO: Replace with the decompiled call
		 * 	midboss_reset();
		 * if we ever decide to put that function into the same translation
		 * unit */
		_asm { push cs; call near ptr midboss_reset; }
	}
}

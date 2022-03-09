#include "platform.h"
#include "pc98.h"
#include "th01/math/overlap.hpp"
#include "th01/math/subpixel.hpp"
#include "th04/math/motion.hpp"
extern "C" {
#include "th04/main/playfld.hpp"
}
#include "th04/main/boss/boss.hpp"
#include "th04/main/player/player.hpp"

#if (GAME == 5)
	// Processes any collision between the player and boss sprites.
	void near boss_hittest_player(void);
#else
	// Moving on top of the boss doesn't kill the player in TH04.
	inline void boss_hittest_player(void) {
	}
#endif

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

#pragma option -G

#include "th03/main/hitbox.hpp"
#include "th03/main/defeat.hpp"
#include "th03/main/hitcirc.hpp"
#include "th03/main/round.hpp"
#include "th03/main/enemy/efe.hpp"
#include "th03/main/enemy/expl.hpp"
#include "th03/main/player/bomb.hpp"
#include "th03/main/player/ch_shot.hpp"
#include "th03/main/player/shot.hpp"

uint8_t hitbox_hittest(void)
{
	shotpair_t near *p;
	playfield_subpixel_t center_x;
	int i;
	playfield_subpixel_t center_y;
	uint8_t damage = 0;

	if(hitbox.origin.center.y.v < to_sp(0.0f) || (defeat_flag == DF_BANNER)) {
		return 0;
	}

	// Shot pairs
	// ----------

	ef_onehit = false;
	p = shotpairs;
	hitbox.right.v  = (hitbox.origin.center.x.v + hitbox.radius.x.v);
	hitbox.bottom.v = (hitbox.origin.center.y.v + hitbox.radius.y.v);
	hitbox.origin.topleft.x.v = (hitbox.origin.center.x.v - hitbox.radius.x.v);
	hitbox.origin.topleft.y.v = (hitbox.origin.center.y.v - hitbox.radius.y.v);
	hitcircles_enemy_add_do_not_randomly_center_within_hitbox = true;
	for(i = 0; i < SHOTPAIR_COUNT; (i++, p++)) {
		if((p->alive != true) || (p->pid != hitbox.pid)) {
			continue;
		}
		center_x = (p->topleft.x.v + to_sp(SHOTPAIR_W / 2));
		center_y = (p->topleft.y.v + to_sp(SHOTPAIR_H / 2));
		if(
			((center_x - to_sp(SHOTPAIR_W / 2)) > hitbox.right.v) ||
			((center_x + to_sp(SHOTPAIR_W / 2)) < hitbox.origin.topleft.x.v) ||
			(center_y < hitbox.origin.topleft.y.v) ||
			(center_y > hitbox.bottom.v)
		) {
			continue;
		}
		p->alive = false;
		damage += 2;
		hitcircles_enemy_add(center_x, center_y, hitbox.pid);
	}
	hitcircles_enemy_add_do_not_randomly_center_within_hitbox = false;
	// ----------

	if(!hitbox_hittest_skip_explosions) {
		/* TODO: Replace with the decompiled call
		 * 	damage += explosions_hittest();
		 * once the segmentation allows us to, if ever */
		asm { nop; push cs; call near ptr explosions_hittest; }
		damage += _AL;
	}

	// ZUN bloat: `damage += chargeshot_hittest[hitbox.pid]();`
	static_assert(PLAYER_COUNT == 2);
	if(hitbox.pid == 0) {
		damage += chargeshot_hittest[0]();
	} else {
		damage += chargeshot_hittest[1]();
	}

	// This code never runs for fireballs, because they're always removed in
	// fireballs_update().
	if(
		(bomb_flag[hitbox.pid] != BF_INACTIVE) &&
		((round_or_result_frame & 1) == 0)
	) {
		damage++;
	}
	return damage;
}

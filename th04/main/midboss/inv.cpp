#include "platform.h"
#include "pc98.h"
#include "th04/main/phase.hpp"
#include "th04/main/enemy/size.hpp"
#include "th04/main/midboss/midboss.hpp"
#include "th04/main/tile/tile.hpp"

// See tile.hpp for the reason why this declaration is necessary
extern "C" void pascal near tiles_invalidate_around(const SPPoint center);

void pascal near midboss_invalidate_func(void)
{
	if(midboss.phase < PHASE_EXPLODE_BIG) {
		tile_invalidate_box.x = MIDBOSS_W_MAX;
		tile_invalidate_box.y = MIDBOSS_H_MAX;
		tiles_invalidate_around(midboss.pos.prev);
	} else {
		tile_invalidate_box.x = (ENEMY_KILL_W * 4);
		tile_invalidate_box.y = (ENEMY_KILL_H * 4);
		tiles_invalidate_around(midboss.pos.cur);
	}
}

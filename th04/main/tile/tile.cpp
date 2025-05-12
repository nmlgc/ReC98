#pragma option -zPmain_01

#include "th04/main/bg.hpp"
#include "th04/main/enemy/enemy.hpp"
#include "th04/main/hud/overlay.hpp"
#include "th04/main/midboss/midboss.hpp"
#include "th04/main/player/shot.hpp"
#include "th04/main/pointnum/pointnum.hpp"
#include "th04/main/stage/stage.hpp"
#include "th04/main/tile/tile.hpp"
#include "th04/main/spark.hpp"
#include "decomp.hpp"

#define render_all_time tile_render_all_time
extern uint8_t render_all_time;

inline void tiles_invalidate_set_all(uint32_t value)
{
	// ZUN bloat: memset(halftiles_dirty, value, sizeof(halftiles_dirty));
	// ZUN landmine: Should clear the direction flag to ensure that `REP STOSD`
	// actually overwrites [halftiles_dirty] instead of the 1,600 bytes before.
	_ES = FP_SEG(halftiles_dirty);
	_DI = FP_OFF(halftiles_dirty);
	_EAX = (value | (value << 8) | (value << 16) | (value << 24));
	_CX = (sizeof(halftiles_dirty) / sizeof(uint32_t));
	REP STOSD;
}

void near tiles_invalidate_reset(void)
{
	tiles_invalidate_set_all(false);
}

void near tiles_invalidate_all(void)
{
	tiles_invalidate_set_all(true);
}

void pascal near tiles_render(void)
{
	overlay_titles_invalidate();
	player_invalidate();
	shots_invalidate();
	enemies_invalidate();
	bullets_and_gather_invalidate();
	items_invalidate();
	sparks_invalidate();
	pointnums_invalidate();
	midboss_invalidate();
	stage_invalidate();

	tiles_redraw_invalidated();
}

static void pascal near tiles_render_all_timed(void)
{
	tiles_render_all();
	render_all_time--;
	if(render_all_time == 0) {
		bg_render_not_bombing = tiles_render;
	}
}

void tiles_activate(void)
{
	bg_render_not_bombing = tiles_render;
}

void pascal tiles_activate_and_render_all_for_next_N_frames(uint8_t n)
{
	render_all_time = n;
	bg_render_not_bombing = tiles_render_all_timed;
}

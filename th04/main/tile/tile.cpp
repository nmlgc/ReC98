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

#define render_all_time tile_render_all_time
extern uint8_t render_all_time;

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

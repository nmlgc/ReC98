#pragma option -zPmain_01

#include "platform.h"
#include "pc98.h"
#include "th04/main/bg.hpp"
#include "th04/main/tile/tile.hpp"

#define render_all_time tile_render_all_time
extern uint8_t render_all_time;

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

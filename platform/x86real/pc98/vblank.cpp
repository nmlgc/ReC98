#pragma option -zCPLATFORM_TEXT

#include "platform/x86real/pc98/vblank.hpp"
#include "libs/master.lib/master.hpp"
#include "libs/master.lib/pc98_gfx.hpp"
#include "x86real.h"

func_t vblank_pending;

static void pascal vblank_run_pending(void)
{
	vblank_pending();
	vblank_flush_func_queue();
}

bool vblank_in(void)
{
	return ((_inportb_(0xA0) & 0x20) ? true : false);
}

void vblank_run(func_t func)
{
	if(inportb(0xA0) & 0x20) {
		func();
		return;
	}

	// Sanity check, since we currently only support a single pending function
	while(vblank_pending != nullptr) {
	}

	vblank_pending = func;
	vsync_proc_set(vblank_run_pending);
}

void vblank_flush_func_queue(void)
{
	vblank_pending = nullptr;
	vsync_proc_reset();
}

void vblank_palette_black_and_tram_wipe(void)
{
	palette_settone(0);
	text_clear();
}

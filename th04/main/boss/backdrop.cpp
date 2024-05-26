#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "th01/hardware/grcg.hpp"
#include "th03/formats/cdg.h"
#include "th04/hardware/grcg.hpp"
#include "th04/main/boss/backdrop.hpp"
#include "th04/sprites/main_cdg.h"

void pascal near boss_backdrop_render(screen_x_t left, vram_y_t top, vc_t col)
{
	cdg_put_noalpha_8(left, top, CDG_BG_BOSS);
	grcg_setmode_tdw();
	grcg_setcolor_direct(col);
	boss_backdrop_colorfill();
	grcg_off();
}

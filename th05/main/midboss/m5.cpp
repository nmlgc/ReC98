/// Stage 5 midboss
/// ---------------

#pragma option -zCmain_0_TEXT

#include "platform.h"
#include "libs/master.lib/pc98_gfx.hpp"
#include "th02/v_colors.hpp"
#include "th01/math/subpixel.hpp"
#include "th04/main/phase.hpp"
#include "th04/main/scroll.hpp"
#include "th04/main/midboss/midboss.hpp"

// Constants
// ---------

static const pixel_t MIDBOSS5_W = 64;
static const pixel_t MIDBOSS5_H = 64;
// ---------

// Rendering
// ---------

void pascal near midboss5_render(void)
{
	if(midboss.phase < PHASE_EXPLODE_BIG) {
		if(playfield_clip_center_top_large_roll(
			midboss.pos.cur.y, MIDBOSS5_H
		)) {
			return;
		}
		screen_x_t left = midboss.pos.cur.to_screen_left(MIDBOSS5_W);
		vram_y_t top = midboss.pos.cur.to_vram_top_scrolled_seg1(MIDBOSS5_H);
		midboss_put_generic(left, top, midboss.sprite);
	} else if(midboss.phase == PHASE_BOSS_EXPLODE_BIG) {
		midboss_defeat_render();
	}
}
// ---------

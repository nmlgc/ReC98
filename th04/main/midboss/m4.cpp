/// Stage 4 midboss
/// ---------------

#pragma option -zCM4_RENDER_TEXT -zPmain_01

#include "platform.h"
#include "libs/master.lib/pc98_gfx.hpp"
#include "th01/math/subpixel.hpp"
#include "th02/v_colors.hpp"
#include "th04/main/scroll.hpp"
#include "th04/main/phase.hpp"
#include "th04/main/midboss/midboss.hpp"
#include "th04/main/hud/hud.hpp"
#include "th04/sprites/main_pat.h"

// Constants
// ---------

static const pixel_t MIDBOSS4_W = 64;
static const pixel_t MIDBOSS4_H = 64;
// ---------

void pascal near midboss4_render(void)
{
	// ZUN bug: Should use the large variant instead.
	if(playfield_clip_point_yx_small_roll(
		midboss.pos.cur, MIDBOSS4_W, MIDBOSS4_H
	)) {
		return;
	}
	screen_x_t left = midboss.pos.cur.x.to_pixel();
	vram_y_t top = midboss.pos.cur.to_vram_top_scrolled_seg1(MIDBOSS4_H);
	if(midboss.phase <= 2) {
		int patnum = (PAT_MIDBOSS4_STILL_LEFT + midboss.sprite);
		if(midboss.pos.cur.x.v >= to_sp(PLAYFIELD_W / 2)) {
			patnum += M4C_CELS;
		}
		midboss_put_generic(left, top, patnum);
	} else if(midboss.phase == PHASE_EXPLODE_BIG) {
		midboss_defeat_render();
	}
}

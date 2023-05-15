#pragma option -3 -Z

#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "th01/math/subpixel.hpp"
#include "th04/math/motion.hpp"
#include "th04/formats/cdg.h"
#include "th04/main/playfld.hpp"
#include "th04/main/phase.hpp"
#include "th04/main/scroll.hpp"
#include "th04/main/boss/boss.hpp"
#include "th04/main/stage/stages.hpp"
#include "th04/main/tile/tile.hpp"
#include "th04/sprites/main_cdg.h"

// See tile.hpp for the reason why this declaration is necessary
extern "C" void pascal near tiles_invalidate_around(
	subpixel_t center_y, subpixel_t center_x
);

/// Stage 5
/// -------

#define star_center_y	stage5_star_center_y
#define STAR_COUNT  	STAGE5_STAR_COUNT

static const pixel_t STAR_W = 96;
static const pixel_t STAR_H = 80;
static const pixel_t STAR_VELOCITY_Y = 4;
static const pixel_t STAR_MARGIN = (
	((PLAYFIELD_W - (STAR_W * STAR_COUNT)) / STAR_COUNT) / 2
);

static const pixel_t STAR_MARGIN_W = (STAR_MARGIN + STAR_W + STAR_MARGIN);

void pascal near stage5_render(void)
{
	if(
		(boss.phase >= PHASE_BOSS_ENTRANCE_BB) &&
		(boss.phase < PHASE_EXPLODE_BIG)
	) {
		return;
	}
	for(int i = 0; i < STAR_COUNT; i++) {
		star_center_y[i].v += to_sp(STAR_VELOCITY_Y);
		if(star_center_y[i].v >= to_sp(RES_Y)) {
			star_center_y[i].v -= to_sp(RES_Y);
		}

		vram_y_t top = scroll_subpixel_y_to_vram_seg1(
			star_center_y[i].v + to_sp(PLAYFIELD_TOP - (STAR_H / 2))
		);
		cdg_put_plane_roll_8(
			(PLAYFIELD_LEFT + STAR_MARGIN + (i * STAR_MARGIN_W)),
			top,
			CDG_BG_2,
			PL_B,
			reinterpret_cast<dots8_t __seg *>(SEG_PLANE_E)
		);
	}
}

void pascal near stage5_invalidate(void)
{
	tile_invalidate_box.x = STAR_W;
	tile_invalidate_box.y = STAR_H;
	for(int i = 0; i < STAR_COUNT; i++) {
		tiles_invalidate_around_xy(
			(to_sp(STAR_MARGIN + (STAR_W / 2)) + (i * to_sp(STAR_MARGIN_W))),
			(star_center_y[i].v - to_sp(STAR_VELOCITY_Y))
		);
	}
}

#undef STAR_COUNT
#undef star_center_y
/// -------

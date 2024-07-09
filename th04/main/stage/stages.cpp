#pragma option -3 -Z

#include "x86real.h"
#include "th04/formats/cdg.h"
#include "th04/main/frames.h"
#include "th04/main/null.hpp"
#include "th04/main/scroll.hpp"
#include "th04/main/boss/boss.hpp"
#include "th04/main/stage/stage.hpp"
#include "th04/main/stage/stages.hpp"
#include "th04/main/tile/tile.hpp"
#include "th04/sprites/main_cdg.h"

// See tile.hpp for the reason why this declaration is necessary
extern "C" void pascal near tiles_invalidate_around(
	subpixel_t center_y, subpixel_t center_x
);

/// Stage 4 (Mugenkan corridor carpet lighting animation)
/// -------
/// Replaces the initially dark set of carpet tiles with two brighter versions
/// in an outwards "barn door" animation, from the center of the map to the
/// edges.

static const uint8_t CARPET_LIGHT_LEVELS = 3;
static const uint8_t CARPET_LIGHTING_CELS = 8;

extern vram_offset_t CARPET_TILE_IMAGE_VOS[CARPET_LIGHT_LEVELS][TILES_X];

// Defines what to do to each tile on a row on every frame of the lighting
// animation.
//
// 	2: Tile hasn't been touched by the animation to the next light level; leave
// 	   it at the current one
//	1: Actively replace this tile with its counterpart on the next light level
//	0: Tile has been touched by a previous frame of the current animation
//
// (Not using an enum because any more than one character per column would hurt
// readability way too much.)
extern uint8_t CARPET_LIGHTING_ANIM[CARPET_LIGHTING_CELS][TILES_X];

// Takes a [cel] of the lighting animation and changes any 1 tiles in every row
// of the playfield to the respective tiles of the [target_level]. Must be
// called during every frame of the lighting animation even if each [cel] takes
// longer than one frame, to ensure that newly scrolled-in tiles are replaced as
// well.
void pascal near carpet_lighting_put_new(int cel, unsigned int target_level)
{
	#define _SI               	reinterpret_cast<uint8_t near *>(_SI)
	#define tile_image_vos    	reinterpret_cast<vram_offset_t __ds *>(_BX)
	#define tile_ring_bytewise	reinterpret_cast<uint8_t __ds*>(tile_ring)

	// ZUN bloat: We don't use ES here?
	asm {
		push	ds;
		pop 	es;
	}

	// ZUN bloat: _SI = CARPET_LIGHTING_ANIM[cel];
	_BX = TILES_X;
	_AX = cel;
	asm { mul bx; }
	_SI = reinterpret_cast<uint8_t near *>(_AX);
	_SI += FP_OFF(CARPET_LIGHTING_ANIM);

	// ZUN bloat: tile_image_vos = CARPET_TILE_IMAGE_VOS[target_level];
	_AX = target_level;
	static_assert(
		sizeof(CARPET_TILE_IMAGE_VOS[0][0]) ==
		(2 * sizeof(CARPET_LIGHTING_ANIM[0][0]))
	);
	_BX += _BX;
	asm { mul bx; }
	_AX += FP_OFF(CARPET_TILE_IMAGE_VOS);
	tile_image_vos = reinterpret_cast<vram_offset_t near *>(_AX);

	int tile_x = 0;
	_CX = TILES_X;
	column_loop: {
		asm { lodsb; }
		if(_AL == 1) {
			/// Set all tiles in the current column...
			/// --------------------------------------

			_DI = tile_x;
			static_assert(sizeof(tile_ring[0][0]) == 2);

			// Turbo C++ is too smart to emit this instruction for either
			// variables or pseudo-registers.
			asm { shl	di, 1; }

			_AX = *tile_image_vos;
			do {
				*reinterpret_cast<vram_offset_t near *>(
					&tile_ring_bytewise[_DI]
				) = _AX;
				_DI += sizeof(tile_ring[0]);
			} while(_DI < sizeof(tile_ring));
			/// ---------------------------------------

			/// …  and mark them for redrawing.
			/// -------------------------------

			_DI = tile_x;
			static_assert(sizeof(halftiles_dirty[0][0]) == 1);

			do {
				halftiles_dirty[0][_DI] = true;
				_DI += sizeof(halftiles_dirty[0]);
			} while(_DI < sizeof(halftiles_dirty));
			/// -------------------------------
		}
		tile_x++;
		tile_image_vos++;
		asm { loop column_loop; }
	}

	#undef tile_ring_bytewise
	#undef tile_image_vos
	#undef _SI
}

#define carpet_lighting_update_and_render(cel, level_cur, level_target) { \
	carpet_lighting_put_new(cel, level_target); \
	if(stage_frame_mod4 == 0) { \
		cel++; \
		if(cel > (CARPET_LIGHTING_CELS - 1)) { \
			level_cur++; \
			cel = 0; \
		} \
	} \
}

void pascal near stage4_render(void)
{
	#define lighting_cel	carpet_lighting_cel
	#define light_level 	carpet_light_level

	extern int lighting_cel;
	extern uint8_t light_level;

	int x;
	int y;

	// ST03.MAP only defines the Stage 4 tile sections in terms of fully-lit
	// carpet tiles. On lower light levels, we therefore need to override any
	// tiles that were newly scrolled in at the end of the last frame.
	//
	// ZUN landmine: However, this function is only called *after* the game
	// rendered the regular tiles for this frame – both if it rendered all of
	// them (on the first frame of the stage) or just the invalidated ones. If
	// the game scrolled in new tiles at the end of the previous frame, their
	// first lines were therefore already rendered to VRAM in their fully-lit
	// form. And thanks to page flipping, any invalidations we do here won't
	// even apply to the same VRAM page, leaving these lines in VRAM until
	// they're hopefully invalidated in the frame after the next one- This can
	// only ever not glitch because newly scrolled-in lines are covered by the
	// opaque black TRAM cells above the playfield during their first two
	// frames on the playfield…
	//
	// ZUN landmine: …and if the height of the invalidation box is at least
	// three times the [scroll_speed], covering the current frame plus the last
	// two. While a hardcoded box height of 2 pixels works for the 0.25-pixel
	// scroll speed that ST03 defines for the length of this animation, the box
	// should really be derived from the [scroll_speed]. To simplify the
	// arithmetic in the necessary calculations, we jump back 4 frames rather
	// than the required three. For the Y position, negating [scroll_speed] and
	// multiplying it by 2 then gets us into the middle of the four sets of
	// lines. For the size, we need to round up the Q12.4 [scroll_speed] to the
	// next integer pixel.
	// The correct box calculation would therefore be:
	//
	// 	tile_invalidate_box.y = ((scroll_speed.to_pixel() + 1) * 4);
	// 	tiles_invalidate_around_xy(to_sp(PLAYFIELD_W / 2), -(scroll_speed * 2));
	//
	// But really, it would have been much simpler to just directly manipulate
	// the tiles inside the loaded .MAP. That would have removed the need for
	// this tile invalidation call and the loop below. The required [tile_ring]
	// manipulation of rendered tiles during the first frame and the animation
	// could have even been replaced with calls to tiles_fill_initial() and
	// tiles_invalidate_all(). Nothing about this would have introduced any
	// drawback, since the entire effect expects that Stage 4's initial tile
	// sections restrict themselves to a single repeating row of tiles anyway.
	tile_invalidate_box.x = PLAYFIELD_W;
	tile_invalidate_box.y = 2;
	tiles_invalidate_around_xy(to_sp(PLAYFIELD_W / 2), 0);

	y = (scroll_line / TILE_H);
	for(x = 0; x < TILES_X; x++) {
		// Override any tiles that have not yet been touched by the animation
		// (= 2) towards the next light level with the respective image on the
		// current light level.
		// ZUN landmine: This should really also override the tiles that *have*
		// been animated (= 0) with the image from the *next* light level.
		// Otherwise, these tiles would wrongly appear fully lit even on light
		// level 1. This only doesn't matter in the original game because
		// 1) the [scroll_speed] is slow enough, and
		// 2) the animation onto the final light level 2 follows directly after
		//    the level 1 animation, making wrong tiles not stick out as much
		//    during the few frames they would be visible.
		if(CARPET_LIGHTING_ANIM[lighting_cel][x] == 2) {
			tile_ring[y][x] = (CARPET_TILE_IMAGE_VOS[light_level][x]);
		}
	}

	if(stage_frame <= 1) {
		for(y = 0; y < TILES_Y; y++) {
			for(x = 0; x < TILES_X; x++) {
				tile_ring[y][x] = CARPET_TILE_IMAGE_VOS[0][x];
			}
		}
		tiles_invalidate_all();
		light_level = 0;
	} else if(light_level == 0) {
		if(stage_frame >= 1664) { // 29.5 seconds into the stage
			carpet_lighting_update_and_render(lighting_cel, light_level, 1);
		}
	} else if(light_level == 1) {
		carpet_lighting_update_and_render(lighting_cel, light_level, 2);
	} else {
		stage_render = nullfunc_near;
	}

	#undef light_level
	#undef lighting_cel
}

/// -------

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

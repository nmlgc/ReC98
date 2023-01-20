#pragma option -zC_TEXT

#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "th02/main/playfld.hpp"
#include "th02/main/tile/tile.hpp"

// Terminology:
// • Line: [TILE_W]×1 stripe within a tile
// • Row: [TILES_X]×[TILE_H] stripe within the full tile map or a tile section

typedef dots_t(TILE_W) tile_line_dots_t;

// State
// -----

extern int8_t tile_line_at_top;
extern vram_offset_t tile_image_vos[TILE_IMAGE_COUNT];
extern pixel_t tile_copy_lines_top;
extern pixel_t tile_copy_lines_h;
extern bool tile_dirty[TILES_X][TILES_Y];

// Optimization to skip checking all vertical tiles for clean columns.
extern bool tile_column_dirty[TILES_X];
// -----

void pascal near tile_egc_copy_lines_8(vram_offset_t vo_dst, int image)
;
void pascal near tile_egc_copy_8(vram_offset_t vo_topleft, int image)
;

// Overwrites the tile starting at [vo_topleft] with the contents of the GRCG
// tile register. Assumes that the GRCG is set to RMW or TDW mode.
void pascal near tile_grcg_clear_8(vram_offset_t vo_topleft)
;

void pascal tile_egc_roll_copy_8(screen_x_t left, vram_y_t top, int image)
{
	#define vo_src	static_cast<vram_offset_t>(_BX)

	_ES = SEG_PLANE_E;
	_CX = _CX; // ZUN bloat: Just blocks this register from being used.

	vram_offset_t vo_dst = vram_offset_shift_fast(left, top);
	vo_src = tile_image_vos[image];
	for(register pixel_t line = 0; line < TILE_H; line++) {
		*reinterpret_cast<tile_line_dots_t __es *>(vo_dst) = (
			*reinterpret_cast<tile_line_dots_t __es *>(vo_src)
		);
		vo_dst += ROW_SIZE;
		vo_src += ROW_SIZE;
		if(vo_dst > PLANE_SIZE) {
			vo_dst -= PLANE_SIZE;
		}
	}

	#undef vo_src
}

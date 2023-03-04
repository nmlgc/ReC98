#pragma option -zC_TEXT -G

#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "th02/hardware/egc.hpp"
#include "th02/hardware/pages.hpp"
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

void pascal tile_ring_set_and_put_both_8(
	screen_x_t left_, vram_y_t y_, int image
)
{
	static_assert((1 << TILE_BITS_W) == TILE_W);
	static_assert((1 << TILE_BITS_H) == TILE_H);

	_ES = SEG_PLANE_B;

	screen_x_t left = left_;
	vram_y_t top = y_;
	int tile_y = (top >> TILE_BITS_H);
	int tile_x = ((left - PLAYFIELD_LEFT) >> TILE_BITS_W);

	tile_copy_lines_top = 0;
	tile_copy_lines_h = TILE_H;
	tile_ring[tile_y][tile_x] = image;

	/* TODO: Replace with the decompiled call
	 * 	egc_start_copy_noframe();
	 * once that function is part of this translation unit */
	_asm { push cs; call near ptr egc_start_copy_noframe; }

	graph_accesspage(page_front);

	top = (tile_y * TILE_H);

	// Should really also be calculated from [tile_x]...
	vram_offset_t vo = vram_offset_shift_fast(left, top);

	tile_egc_copy_lines_8(vo, image);
	graph_accesspage(page_back);
	tile_egc_copy_lines_8(vo, image);
	egc_off();
}
#pragma codestring "\x90"

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

#pragma option -zC_TEXT -G -2

#include "platform.h"
#include "x86real.h"
#include "decomp.hpp"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "th02/hardware/egc.hpp"
#include "th02/hardware/pages.hpp"
#include "th02/main/playfld.hpp"
#include "th02/main/scroll.hpp"
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

#define tile_grcg_clear_8_func(vo_topleft, unused) { \
	tile_grcg_clear_8(vo_topleft); \
}

#define tiles_egc_render_loop(func) { \
	for(register int tile_x = 0; tile_x < TILES_X; tile_x++) { \
		if((tiles_egc_render_all == true) || tile_column_dirty[tile_x]) { \
			vram_offset_t vo = ( \
				vram_offset_shift(PLAYFIELD_LEFT, 0) + (tile_x * TILE_VRAM_W) \
			); \
			register int tile_y = 0; \
			while(tile_y < TILES_Y) { \
				if( \
					(tiles_egc_render_all == true) || \
					tile_dirty[tile_x][tile_y] \
				) { \
					func(vo, tile_ring[tile_y][tile_x]); \
				} \
				tile_y++; \
				vo += (TILE_H * ROW_SIZE); \
			} \
		} \
	} \
}

void pascal tiles_invalidate_rect(
	screen_x_t left, vram_y_t top, pixel_t w, pixel_t h
)
{
	static_assert(sizeof(tile_dirty[0]) == (RES_Y / TILE_H));

	#define screen_top  	static_cast<int>(_AX)
	#define array_offset	static_cast<int>(_AX)
	#define tile_left   	left
	#define screen_right	w
	#define tile_right  	w

	register pixel_t y;
	register pixel_t y_tmp;
	register vram_y_t bottom;
	register int tile_x;

	if(tile_mode == TM_NONE) {
		return;
	}

	// Round down to the closest tile so that we don't unnecessarily invalidate
	// an additional tile to the right if e.g. ([left] % TILE_W) is 0 and [w]
	// is TILE_W.
	w--;

	/// ZUN bloat: The comments indicate the semantic flow of data, which
	/// couldn't be retained for code generation reasons.
	/* screen_right = left; */
	screen_right += left;
	/* tile_right = screen_right; */
	tile_right >>= TILE_BITS_W;
	/* tile_left = left; */
	tile_left >>= TILE_BITS_W;

	tile_left -= (PLAYFIELD_LEFT / TILE_W);
	tile_right -= (PLAYFIELD_LEFT / TILE_W);

	screen_top = (top + scroll_line);
	if(screen_top >= RES_Y) {
		screen_top -= RES_Y;
	} else if(screen_top < keep_0(0u)) {
		// ZUN bug: Since the comparison above is unsigned, it can never be
		// true, and this branch can therefore never execute. Even Turbo C++
		// 4.0J would have warned about this if ZUN had just written idiomatic
		// C here… As a result, the array writes below can leave their bounds
		// if this function is ever called with a negative [top] value. This
		// doesn't seem to happen all that easily in this game though, but
		// let's still classify this as a bug until we can prove it to be a
		// landmine.
		screen_top += RES_Y;
	}

	bottom = h;
	bottom--; // Same rounding we saw above.
	bottom += screen_top;
	top = (screen_top & ~(TILE_H - 1));

	tile_x = tile_left;
	array_offset = (tile_x * TILES_Y);
	while(tile_x <= tile_right) {
		// Could have been clamped outside, but eh, fine.
		if((tile_x >= 0) && (tile_x < TILES_X)) {
			y = top;
			do {
				y_tmp = y;
				if(y_tmp >= RES_Y) {
					y_tmp -= RES_Y;
				}
				y_tmp >>= TILE_BITS_H;
				tile_dirty[0][array_offset + y_tmp] = true;
				y += TILE_H;
			} while(y <= bottom);
			tile_column_dirty[tile_x] = true;
		}
		tile_x++;
		array_offset += TILES_Y;
	}

	#undef tile_right
	#undef screen_right
	#undef tile_left
	#undef array_offset
	#undef screen_top
}

void tiles_egc_render(void)
{
	_ES = SEG_PLANE_E;
	if(tile_mode == TM_TILES) {
		tiles_egc_render_loop(tile_egc_copy_8);
	} else if(tile_mode == TM_COL_0) {
		grcg_setcolor(GC_RMW, 0);
		tiles_egc_render_loop(tile_grcg_clear_8_func);
		grcg_off();
	}

	// ZUN bloat: memset()ting the two arrays would have been actually fast...
	_BX = 0;
	_CX = (TILES_X * TILES_Y);
	dirty_reset_loop: {
		tile_dirty[0][_BX++] = false;
		asm { loop dirty_reset_loop; }
	}
	_BX = 0;
	_CX = TILES_X;
	dirty_column_reset_loop: {
		tile_column_dirty[_BX++] = false;
		asm { loop dirty_column_reset_loop; }
	}

	tiles_egc_render_all = false;
}

#pragma codestring "\x90"

void tiles_render_all(void)
{
	_ES = SEG_PLANE_B;
	tile_copy_lines_top = 0;
	tile_copy_lines_h = TILE_H;

	/* TODO: Replace with the decompiled call
	 * 	egc_start_copy_noframe();
	 * once that function is part of this translation unit */
	_asm { push cs; call near ptr egc_start_copy_noframe; }

	if(tile_mode == TM_TILES) {
		int tile_y = 0;
		int image;
		vram_offset_t vo_row = vram_offset_shift(PLAYFIELD_LEFT, 0);
		while(tile_y < TILES_Y) {
			int tile_x = 0;
			vram_offset_t vo_col = vo_row;
			while(tile_x < TILES_X) {
				image = tile_ring[tile_y][tile_x];

				// ZUN bloat: Only needs a regular tile copy, which wouldn't
				// have needed the [tile_copy_*] assignments above.
				tile_egc_copy_lines_8(vo_col, image);

				tile_x++;
				vo_col += TILE_VRAM_W;
			}
			tile_y++;
			vo_row += (TILE_H * ROW_SIZE);
		}
	} else {
		grcg_setcolor(GC_RMW, 0);
		grcg_boxfill_8( \
			PLAYFIELD_LEFT, PLAYFIELD_TOP, PLAYFIELD_RIGHT, PLAYFIELD_BOTTOM \
		);
		grcg_off();
	}
	egc_off();
}

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

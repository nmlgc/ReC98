#include "th01/sprites/shape8x8.h"
#include "th01/main/shape.hpp"

#define shape8x8_put(shape, left, top, col) \
	dots8x8_t sprite = sSHAPE8X8[shape]; \
	vram_offset_t vram_offset_topleft = vram_offset_divmul(left, top); \
	int first_bit = (left % BYTE_DOTS); \
	if((left < 0) || (left >= RES_X) || (top < 0) || (top >= RES_Y)) { \
		return; \
	} \
	grcg_put_8x8_mono(vram_offset_topleft, first_bit, sprite.rows, col);

void shape8x8_diamond_put(screen_x_t left, vram_y_t top, int col)
{
	shape8x8_put(SHAPE8X8_DIAMOND, left, top, col);
}

void shape8x8_star_put(screen_x_t left, vram_y_t top, int col)
{
	shape8x8_put(SHAPE8X8_STAR, left, top, col);
}

void shape8x8_flake_put(screen_x_t left, vram_y_t top, int col)
{
	shape8x8_put(SHAPE8X8_FLAKE, left, top, col);
}

void shape_ellipse_arc_put(
	screen_x_t center_x,
	vram_y_t center_y,
	pixel_t radius_x,
	pixel_t radius_y,
	int col,
	unsigned char angle_step,
	unsigned char angle_start,
	unsigned char angle_end
)
{
	int angle; // 16 bits to correctly work for an [angle_end] of 0xFF
	dots8_t cache_dots = 0;
	vram_offset_t cache_vram_offset = -1;

	grcg_setcolor_rmw(col);

	if(angle_start > angle_end) {
		return;
	}

	for(angle = angle_start; angle <= angle_end; angle += angle_step) {
		vram_offset_t vram_offset;
		screen_x_t cur_x = polar_x(center_x, radius_x, angle);
		vram_y_t   cur_y = polar_y(center_y, radius_y, angle);

		vram_offset = vram_offset_shift(cur_x, cur_y);
		if(cache_vram_offset != vram_offset) {
			if(
				(cur_x >= 0) && (cur_x < RES_X) &&
				(cache_vram_offset >= 0) && (cache_vram_offset < PLANE_SIZE)
			) {
				VRAM_PUT(B, cache_vram_offset, cache_dots, 8);
			}
			cache_dots = ((0x80) >> (cur_x & (BYTE_DOTS - 1)));
			cache_vram_offset = vram_offset;
		} else {
			cache_dots |= ((0x80) >> (cur_x & (BYTE_DOTS - 1)));
		}
	}
	grcg_off();
}

void shape_ellipse_arc_sloppy_unput(
	screen_x_t center_x,
	vram_y_t center_y,
	pixel_t radius_x,
	pixel_t radius_y,
	unsigned char angle_step,
	unsigned char angle_start,
	unsigned char angle_end
)
{
	int angle; // 16 bits to correctly work for an [angle_end] of 0xFF

	 // ZUN bug: Should all be initialized
	screen_x_t cur_x;
	vram_y_t cur_y;
	screen_x_t prev_x;
	vram_y_t prev_y;

	if(angle_start > angle_end) {
		return;
	}

	for(angle = angle_start; angle <= angle_end; angle += angle_step) {
		cur_x = polar_x(center_x, radius_x, angle);
		cur_y = polar_y(center_y, radius_y, angle);
		if((prev_y != cur_y) || ((prev_x >> 3) != (cur_x >> 3))) {
			egc_copy_rect_1_to_0_16(cur_x, cur_y, BYTE_DOTS, 1);
			prev_x = cur_x;
			prev_y = cur_y;
		}
	}
}

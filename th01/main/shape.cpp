#include "th01/v_colors.hpp"
#include "th01/sprites/shape8x8.hpp"
#include "th01/main/shape.hpp"

#define shape8x8_put(shape, left, top, col) \
	dot_rect_t(8, 8) sprite = sSHAPE8X8[shape]; \
	vram_offset_t vram_offset_topleft = vram_offset_divmul(left, top); \
	int first_bit = (left % BYTE_DOTS); \
	if((left < 0) || (left >= RES_X) || (top < 0) || (top >= RES_Y)) { \
		return; \
	} \
	grcg_put_8x8_mono(vram_offset_topleft, first_bit, sprite, col);

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
				grcg_put(cache_vram_offset, cache_dots, 8);
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

void shape8x8_invincibility_put_with_mask_from_B_plane(
	screen_x_t left, vram_y_t top, int cel
);

void shape8x8_invincibility_put(screen_x_t left, vram_y_t top, int cel)
{
	if(left < 0) {
		return;
	}
	shape8x8_invincibility_put_with_mask_from_B_plane(left, top, cel);

	vram_offset_t vram_offset = vram_offset_divmul(left, top);
	int first_bit = (left % BYTE_DOTS);

	if(cel > (SHAPE8X8_INVINCIBILITY_CELS - 1)) {
		return;
	}

	grcg_setcolor_rmw(V_RED);
	for(pixel_t y = 0; y < sSHAPE8X8[0].h(); y++) {
		#define sprite sSHAPE8X8[SHAPE8X8_INVINCIBILITY + cel][y]

		if(first_bit == 0) {
			grcg_put(vram_offset, sprite, 8);
		} else {
			grcg_put(
				vram_offset, (
					(sprite << ((BYTE_DOTS * 2) - first_bit)) +
					(sprite >> first_bit)
				),
				16
			);
		}
		vram_offset += ROW_SIZE;
		if(vram_offset > PLANE_SIZE) { // Clip at the bottom edge
			break;
		}

		#undef sprite
	}
	grcg_off();
}

// Surely this function was meant to just regularly unblit the sprite via the
// EGC? The GRCG RMW mode has no effect on VRAM reads, and simply returns the
// exact bytes at the given offset on the given (that is, the B) plane. As a
// result, this unblitting attempt actually blits the sprite again, masked by
// whatever was in VRAM plane B at the given position before calling this
// function.
void shape8x8_invincibility_put_with_mask_from_B_plane(
	screen_x_t left, vram_y_t top, int cel
)
{
	if(left < 0) {
		return;
	}

	vram_offset_t vram_offset = vram_offset_divmul(left, top);
	int first_bit = (left % BYTE_DOTS);

	if(cel > (SHAPE8X8_INVINCIBILITY_CELS - 1)) {
		return;
	}

	grcg_setcolor_rmw(V_RED);
	for(pixel_t y = 0; y < sSHAPE8X8[0].h(); y++) {
		#define sprite sSHAPE8X8[SHAPE8X8_INVINCIBILITY + cel][y]

		if(first_bit == 0) {
			dots8_t bg_B;

			graph_accesspage_func(1);
			bg_B = (grcg_chunk_8(vram_offset) & sprite);
			graph_accesspage_func(0);
			grcg_put_8(vram_offset, bg_B);
		} else {
			// MODDERS: Add clipping at the right edge
			dots8_t bg_B_left;
			dots8_t bg_B_right;

			graph_accesspage_func(1);
			bg_B_left = (grcg_chunk_8(vram_offset + 0) & (sprite >> first_bit));

			graph_accesspage_func(1);
			bg_B_right = (
				grcg_chunk_8(vram_offset + 1) &
				(sprite << (BYTE_DOTS - first_bit))
			);

			graph_accesspage_func(0); grcg_put_8((vram_offset + 0), bg_B_left);
			graph_accesspage_func(0); grcg_put_8((vram_offset + 1), bg_B_right);
		}

		vram_offset += ROW_SIZE;
		if(vram_offset > PLANE_SIZE) { // Clip at the bottom edge
			break;
		}
		#undef sprite
	}
	grcg_off();
}

// Why is this here?
void graph_r_lineloop_put(
	const screen_x_t x[], const vram_y_t y[], int point_count, int col
)
{
	int i = 0;
	while((point_count - 1) > i) {
		graph_r_line(x[i], y[i], x[i + 1], y[i + 1], col);
		i++;
	}
	graph_r_line(x[i], y[i], x[0], y[0], col);
}

void graph_r_lineloop_unput(
	const screen_x_t x[], const vram_y_t y[], int point_count
)
{
	int i = 0;
	while((point_count - 1) > i) {
		graph_r_line_unput(x[i], y[i], x[i + 1], y[i + 1]);
		i++;
	}
	graph_r_line_unput(x[i], y[i], x[0], y[0]);
}

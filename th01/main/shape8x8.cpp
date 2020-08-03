#include "th01/sprites/shape8x8.h"
#include "th01/main/shape8x8.hpp"

#define shape8x8_put(shape, left, top, col) \
	dots8x8_t sprite = sSHAPE8X8[shape]; \
	int16_t vram_offset_topleft = vram_offset_divmul(left, top); \
	int first_bit = (left % BYTE_DOTS); \
	if((left < 0) || (left >= RES_X) || (top < 0) || (top >= RES_Y)) { \
		return; \
	} \
	grcg_put_8x8_mono(vram_offset_topleft, first_bit, sprite.rows, col);

void shape8x8_diamond_put(int left, int top, int col)
{
	shape8x8_put(SHAPE8X8_DIAMOND, left, top, col);
}

void shape8x8_star_put(int left, int top, int col)
{
	shape8x8_put(SHAPE8X8_STAR, left, top, col);
}

void shape8x8_flake_put(int left, int top, int col)
{
	shape8x8_put(SHAPE8X8_FLAKE, left, top, col);
}

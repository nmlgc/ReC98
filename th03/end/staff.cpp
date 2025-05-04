#include "th03/sprites/flake.h"
#include "platform/x86real/flags.hpp"
#include "x86real.h"
#include <stdlib.h>

void pascal near flake_put(screen_x_t left, screen_y_t top, int cel)
{
	#define src      	reinterpret_cast<flake_dots_t near *>(_SI)
	#define first_bit	static_cast<int16_t>(_CX)
	#define rows_left	static_cast<pixel_t>(_BX)

	dots16_t __es *dst = reinterpret_cast<dots16_t __es *>(
		vram_offset_shift(left, top)
	);

	// ZUN bloat: src = &sFLAKE[cel].row[0];`
	#define src_bloat reinterpret_cast<uint16_t>(src)
	src_bloat = cel;
	src_bloat <<= 4;
	src_bloat += FP_OFF(sFLAKE[0].row);
	#undef src_bloat

	_ES = SEG_PLANE_B;

	// ZUN bloat: `first_bit = (left & BYTE_MASK);`. Using a 16-bit-immediate
	// for some reason.
	first_bit = left;
	asm { and cx, BYTE_MASK; }

	rows_left = FLAKE_H;
	do {
		*dst |= __rotr__(*src, first_bit);
		dst += (ROW_SIZE / sizeof(dots16_t));
		src++;
		rows_left--;
	} while(!FLAGS_ZERO);

	#undef rows_left
	#undef first_bit
	#undef src
}

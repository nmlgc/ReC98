#include "th03/sprites/flake.h"
#include "th03/score.hpp"
#include "th01/math/subpixel.hpp"
#include "platform/x86real/flags.hpp"
#include "x86real.h"
#include <stdlib.h>

// State
// -----

struct flake_t {
	bool alive;
	int8_t padding_1; // ZUN bloat: Could have squeezed [cel] in there.
	Subpixel left;
	Subpixel top;
	SPPoint velocity;
	uint16_t cel;
	int8_t padding_2[4]; // ZUN bloat
};

static const unsigned int FLAKE_COUNT = 80;

extern flake_t flakes[FLAKE_COUNT];

extern page_t page_back;

// Oh look, it's the TH02 approach!
extern screen_y_t stf_center_y_on_page[PAGE_COUNT];

extern score9_lebcd_t score;
// -----

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

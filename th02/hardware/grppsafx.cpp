#pragma codeseg SHARED
#pragma option -3

extern "C" {
#include <mbctype.h>
#include <mbstring.h>
#include "libs/master.lib/master.h"
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "th01/hardware/grppsafx.h"

#include "th01/hardware/grppsafx.cpp"

#undef grcg_off

void DEFCONV graph_putsa_fx(
	screen_x_t left, vram_y_t top, int16_t col_and_fx, const unsigned char *str
)
{
	uint16_t codepoint;
	dots16_t glyph_row;
	unsigned char far *vram;
	int fullwidth;
	int first_bit;
	int weight = (col_and_fx >> 4) & 3;
	pixel_t spacing = (col_and_fx >> 6) & 7;
	pixel_t line;
	dots16_t glyph[GLYPH_H];
	register dots16_t glyph_row_tmp;

	#if (GAME >= 3)
		grcg_setcolor(GC_RMW, (col_and_fx & (COLOR_COUNT - 1)));
	#else
		grcg_setcolor(GC_RMW, col_and_fx);
	#endif
	outportb(0x68, 0xB); // CG ROM dot access

	while(str[0]) {
		set_vram_ptr(vram, first_bit, left, top);
		get_glyph(glyph, codepoint, fullwidth, str, left, line);

		for(line = 0; line < GLYPH_H; line++) {
			apply_weight(glyph_row, glyph[line], glyph_row_tmp, weight);
			put_row_and_advance(vram, row, first_bit);
		}
		advance_left(left, fullwidth, spacing);
	}

	outportb(0x68, 0xA); // CG ROM code access
	grcg_off();
}

}

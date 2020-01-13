#include <mbctype.h>
#include <mbstring.h>
#include "th01/hardware/grppsafx.c"

void graph_putsa_fx(int left, int top, int fx, const unsigned char *str)
{
	uint16_t codepoint;
	planar16_t glyph_row;
	unsigned char far *vram;
	int fullwidth;
	int first_bit;
	int weight = (fx >> 4) & 3;
	int spacing = (fx >> 6) & 7;
	int line;
	planar16_t glyph[GLYPH_H];
	register planar16_t glyph_row_tmp;

	grcg_setcolor(GC_RMW, fx);
	OUTB(0x68, 0xB); // CG ROM dot access

	while(str[0]) {
		set_vram_ptr(vram, first_bit, left, top);
		get_glyph(glyph, codepoint, fullwidth, str, left, line);

		for(line = 0; line < GLYPH_H; line++) {
			apply_weight(glyph_row, glyph[line], glyph_row_tmp, weight);
			put_row_and_advance(vram, row, first_bit);
		}
		advance_left(left, fullwidth, spacing);
	}

	OUTB(0x68, 0xA); // CG ROM code access
	grcg_off();
}

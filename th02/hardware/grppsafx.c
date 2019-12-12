#include <mbctype.h>
#include <mbstring.h>

void graph_putsa_fx(int x, int y, int fx, const unsigned char *str)
{
	uint16_t codepoint;
	planar16_t glyph_row;
	unsigned char far *vram;
	int fullwidth;
	int first_bit;
	int weight = (fx >> 4) & 3;
	int spacing = (fx >> 6) & 7;
	int line;
	planar16_t glyph[GLYPH_HEIGHT];
	register planar16_t glyph_row_orig;

	grcg_setcolor(GC_RMW, fx);
	OUTB(0x68, 0xB); // CG ROM dot access

	while(str[0]) {
		vram = MK_FP(GRAM_400, (y * ROW_SIZE) + (x / 8));
		first_bit = x % 8;

		if(_ismbblead(str[0])) {
			codepoint = _mbcjmstojis(((char)str[0] << 8) + str[1]);
			str += 2;
		} else if(_ismbbkana((char)str[0])) {
			codepoint = str[0] + 0x2980;
			str += 1;
		} else if(isgraph((char)str[0])) {
			codepoint = str[0] + 0x2900;
			str += 1;
		} else {
			codepoint = 0x2B21;
			str += 1;
		}

		OUTB(0xA1, codepoint & 0xFF);
		OUTB(0xA3, (codepoint >> 8) - 0x20);
		if(codepoint >= 0x2921 && codepoint <= 0x2B7E) {
			if(x <= 632) {
				for(line = 0; line < GLYPH_HEIGHT; line++) {
					OUTB(0xA5, line | 0x20);
					glyph[line] = INPB(0xA9) << 8;
				}
				fullwidth = 0;
			} else {
				break;
			}
		} else if(x <= 624) {
			for(line = 0; line < GLYPH_HEIGHT; line++) {
				OUTB(0xA5, line | 0x20);
				glyph[line] = INPB(0xA9) << 8;
				OUTB(0xA5, line);
				glyph[line] += INPB(0xA9);
			}
			fullwidth = 1;
		} else {
			break;
		}

		for(line = 0; line < GLYPH_HEIGHT; line++) {
			glyph_row = glyph[line];
			#define GLYPH_DOUBLE \
				glyph_row_orig = glyph_row; \
				glyph_row |= glyph_row_orig << 1;
			switch(weight) {
			case 1:
				GLYPH_DOUBLE;
				break;
			case 3:
				GLYPH_DOUBLE;
				// fallthrough
			case 2:
				GLYPH_DOUBLE;
				glyph_row_orig ^= glyph_row;
				glyph_row &= ~(glyph_row_orig << 1);
			}
			if(first_bit) {
				vram[0] = glyph_row >> (first_bit + 8);
				vram[1] = glyph_row >> (first_bit + 0);
				vram[2] = glyph_row << (8 - first_bit);
			} else {
				vram[0] = glyph_row >> 8;
				vram[1] = glyph_row;
			}
			vram += ROW_SIZE;
		}
		if(fullwidth) {
			x += 8;
		}
		x += spacing + 8;
	}
	OUTB(0x68, 0xA); // CG ROM code access
	grcg_off();
}

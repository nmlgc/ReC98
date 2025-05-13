#include <mbctype.h>
#include <mbstring.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "platform/x86real/pc98/font.hpp"
#include "platform/x86real/pc98/grcg.hpp"
#include "th01/hardware/graph.h"
#include "th01/hardware/grp_text.hpp"
#include "th01/hardware/grppsafx.h"
#include "th01/shiftjis/fwnum.hpp"
#include "th01/v_colors.hpp"

inline int fx_weight_from(int col_and_fx) {
	return ((col_and_fx / 0x10) % 4);
}

inline pixel_t fx_spacing_from(int col_and_fx) {
	return ((col_and_fx / 0x40) % 8);
}

#include "th01/hardware/grppsafx.cpp"

void graph_putsa_fx(
	screen_x_t left, vram_y_t top, int16_t col_and_fx, const shiftjis_t *str
)
{
	register screen_x_t x = left;
	dots8_t far *vram;
	int weight = fx_weight_from(col_and_fx);
	pixel_t spacing = fx_spacing_from(col_and_fx);
	bool16 clear_bg = (col_and_fx & FX_CLEAR_BG);
	bool16 reverse = (col_and_fx & FX_REVERSE);

	if(clear_bg) {
		pixel_t w = text_extent_fx(col_and_fx, str);
		z_grcg_boxfill(x, top, (x + w - 1), (top + GLYPH_H - 1), 0);
	}

	GRCG grcg(GC_RMW);
	grcg.set_color(col_and_fx);

	while(str[0]) {
		font_glyph_t glyph;
		jis_t codepoint;
		uint8_t first_bit;

		set_vram_ptr(vram, first_bit, x, top);

		if(_ismbblead(str[0])) {
			codepoint = _mbcjmstojis((str[0] << 8) + str[1]);
			str += sizeof(shiftjis_kanji_t);
		} else if(_ismbbkana(str[0])) {
			codepoint = (str[0] + ((col_and_fx & FX_8X8) ? 0 : 0x2980));
			str += 1;
		} else if(isgraph(str[0])) {
			codepoint = (str[0] + ((col_and_fx & FX_8X8) ? 0 : 0x2900));
			str += 1;
		} else {
			codepoint = 0x2B21; // One of many JIS whitespace characters
			str += 1;
		}

		font_read(glyph, codepoint);

		bool fullwidth = (glyph.tag.w == GLYPH_FULL_W);
		if((left + glyph.tag.w) > RES_X) {
			break;
		}
		for(uint8_t line = 0; line < glyph.tag.h; line++) {
			dots_t(GLYPH_FULL_W) glyph_row_tmp;
			dots_t(GLYPH_FULL_W) glyph_row = (fullwidth
				? __rotr__(glyph.kanji[line], 8)

				// While moving halfwidth glyphs to the high byte of a glyph
				// row ensures that any additional boldface dots to the left
				// of the glyph are lost (see the bug in apply_weight()), it's
				// better than storing them in the low byte and spilling such
				// new dots into the high one. In that case, these dots would
				// appear on screen as glitched pixels if the glyph was
				// displayed at a byte-aligned position. (That's exactly what
				// happens in the ASM version of this code, introduced in
				// TH04.)
				: (glyph.ank_8x16[line] << 8)
			);
			apply_weight(glyph_row, glyph_row, glyph_row_tmp, weight);
			if(reverse) {
				if(fullwidth) {
					glyph_row ^= 0xFFFF;
				} else {
					glyph_row ^= 0xFF00;
				}
			}
			put_row_and_advance(vram, glyph_row, first_bit);
		}
		x += (glyph.tag.w + spacing);
	}
}

pixel_t text_extent_fx(int col_and_fx, const shiftjis_t *str)
{
	register pixel_t ret = 0;
	register pixel_t spacing = fx_spacing_from(col_and_fx);
	while(*str) {
		if(_ismbblead(str[0])) {
			shiftjis_kanji_t codepoint = ((char)str[0] << 8) + str[0];
			str++;
			str++;
			if(codepoint < 0x8540) {
				ret += GLYPH_FULL_W;
			} else if(codepoint > 0x869E) {
				ret += GLYPH_FULL_W;
			} else {
				ret += GLYPH_HALF_W;
			}
		} else {
			ret += GLYPH_HALF_W;
			str++;
		}
		ret += spacing;
	}
	return ret - spacing;
}

void graph_printf_fx(
	screen_x_t left,
	vram_y_t top,
	int16_t col_and_fx,
	const shiftjis_t *fmt,
	...
)
{
	char str[256];
	va_list ap;

	va_start(ap, fmt);
	vsprintf(str, fmt, ap);
	graph_putsa_fx(left, top, col_and_fx, str);
}

void graph_putfwnum_fx(
	screen_x_t left, vram_y_t top, int16_t col_and_fx, int digits,
	long num, long num_prev, bool16 put
)
{
	screen_x_t x = left;
	int divisor_i;
	int digit;
	int digit_prev;
	unsigned long divisor = 1;
	const shiftjis_t* FULLWIDTH_NUMERAL[10] = FULLWIDTH_NUMERALS;

	for(divisor_i = 0; divisor_i < digits; divisor_i++) {
		divisor *= 10;
	}
	do {
		divisor /= 10;
		if(x > (RES_X - GLYPH_FULL_W)) {
			return;
		}

		digit = ((num / divisor) % 10);
		digit_prev = ((num_prev / divisor) % 10);

		if(digit != 0) {
			put = true;
		}
		if(put && ((digit != digit_prev) || !num_prev)) {
			graph_putsa_fx(x, top, col_and_fx, FULLWIDTH_NUMERAL[digit]);
		}
		x += GLYPH_FULL_W;
	} while(divisor > 1);
}

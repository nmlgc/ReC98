#include <mbctype.h>
#include <mbstring.h>
#include <stdio.h>
#include <stdarg.h>
#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "shiftjis.hpp"
#include "th01/v_colors.hpp"
#include "th01/hardware/graph.h"
#include "th01/hardware/grp_text.hpp"
#include "th01/shiftjis/fwnum.hpp"

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
	jis_t codepoint;
	dots_t(GLYPH_FULL_W) glyph_row;
	dots8_t far *vram;
	bool16 fullwidth;
	int first_bit;
	int weight = fx_weight_from(col_and_fx);
	pixel_t spacing = fx_spacing_from(col_and_fx);
	bool16 clear_bg = (col_and_fx & FX_CLEAR_BG);
	bool16 underline = (col_and_fx & FX_UNDERLINE);
	bool16 reverse = (col_and_fx & FX_REVERSE);
	pixel_t w;
	pixel_t line;
	dot_rect_t(GLYPH_FULL_W, GLYPH_H) glyph;
	register dots_t(GLYPH_FULL_W) glyph_row_tmp;

	if(clear_bg) {
		w = text_extent_fx(col_and_fx, str);
		if(underline) {
			z_grcg_boxfill(x, top, (x + w - 1), (top + GLYPH_H + 1), 0);
			graph_r_hline(x, (x + w - 1), (top + GLYPH_H + 1), V_WHITE);
		} else {
			z_grcg_boxfill(x, top, (x + w - 1), (top + GLYPH_H - 1), 0);
		}
	} else if(underline) {
		w = text_extent_fx(col_and_fx, str);
		graph_r_hline(x, (x + w - 1), (top + GLYPH_H + 1), V_WHITE);
	}

	grcg_setcolor_rmw(col_and_fx);
	outportb(0x68, 0xB); // CG ROM dot access

	while(str[0]) {
		set_vram_ptr(vram, first_bit, x, top);
		get_glyph(glyph, codepoint, fullwidth, str, x, line);

		for(line = 0; line < GLYPH_H; line++) {
			apply_weight(glyph_row, glyph[line], glyph_row_tmp, weight);
			if(reverse) {
				if(fullwidth) {
					glyph_row ^= 0xFFFF;
				} else {
					glyph_row ^= 0xFF00;
				}
			}
			put_row_and_advance(vram, glyph_row, first_bit);
		}
		advance_left(x, fullwidth, spacing);
	}

	outportb(0x68, 0xA); // CG ROM code access
	grcg_off_func();
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

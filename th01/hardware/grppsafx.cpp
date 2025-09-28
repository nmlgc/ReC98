#include "th01/hardware/grppsafx.h"
#include "libs/master.lib/pc98_gfx.hpp"
#include "platform/x86real/pc98/font.hpp"
#include "platform/x86real/pc98/grcg.hpp"
#include <mbctype.h>
#include <mbstring.h>
#include <stdlib.h>

pixel_t pascal text_extent(const shiftjis_t *str)
{
	register pixel_t ret = 0;
	while(*str) {
		if(_ismbblead(str[0])) {
			shiftjis_kanji_t codepoint = ((str[0] << 8) | str[1]);
			str += sizeof(shiftjis_kanji_t);
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
	}
	return ret;
}

void pascal graph_putsa_fx(
	screen_x_t left, vram_y_t top, int16_t col_and_fx, const shiftjis_t *str
)
{
	int weight = ((col_and_fx >> 4) & 3);
	bool16 clear_bg = (col_and_fx & FX_CLEAR_BG);
	bool16 reverse = (col_and_fx & FX_REVERSE);

	GRCG grcg(GC_RMW);

	if(clear_bg) {
		pixel_t w = text_extent(str);
		grcg.set_color_static(0);
		grcg_boxfill(left, top, (left + w - 1), (top + GLYPH_H - 1));
	}

	grcg.set_color(col_and_fx);

	outportb(0x68, 0xB); // CG ROM dot access

	while(str[0]) {
		font_glyph_t glyph;
		dots8_t far *vram = reinterpret_cast<dots8_t far *>(
			MK_FP(SEG_PLANE_B, vram_offset_shift(left, top))
		);
		int first_bit = (left & BYTE_MASK);
		jis_t codepoint;

		// According to p. 105 of the PC-9801 Programmers' Bible, the PC-98 KCG
		// only supports single-byte ANK glyph retrieval within VBLANK,
		// regardless of whether it's in code or dot access mode. Later models
		// such as the PC9821As3 (see
		// https://github.com/joncampbell123/dosbox-x/pull/5814) seem to have
		// lifted this limitation, and no emulator replicates it as of August
		// 2025. Still, it does make sense why ZUN just pulls ANK glyphs from
		// their PC-98-specific alternate location at JIS row 0x29 instead:
		// Even at the ROM level, these are halfwidth glyphs within fullwidth
		// blocks and are thus not affected by the VBLANK restriction, and you
		// get the widest possible hardware compatibility with no further
		// downside.
		// (Well, except that Neko Project's auto-generated default font
		// renders the 0x29 row using these infamous hideous abominations of
		// ASCII glyphs, making text look much worse as a result…)
		if(_ismbblead(str[0])) {
			codepoint = _mbcjmstojis(((char)str[0] << 8) + str[1]);
			str += sizeof(shiftjis_kanji_t);
		} else if(_ismbbkana((char)str[0])) {
			codepoint = (str[0] + ((col_and_fx & FX_8X8) ? 0 : 0x2980));
			str += sizeof(shiftjis_t);
		} else if(isgraph((char)str[0])) {
			codepoint = (str[0] + ((col_and_fx & FX_8X8) ? 0 : 0x2900));
			str += sizeof(shiftjis_t);
		} else {
			// One of many JIS whitespace characters. TH03's win messages rely
			// on control characters being filtered to halfwidth spaces here.
			codepoint = 0x2B21;
			str += sizeof(shiftjis_t);
		}

		font_read(glyph, codepoint);

		bool fullwidth = (glyph.tag.w == GLYPH_FULL_W);
		if((left + glyph.tag.w) > RES_X) {
			break;
		}

		for(uint8_t line = 0; line < glyph.tag.h; line++) {
			dots_t(GLYPH_FULL_W) glyph_row = (fullwidth
				? __rotr__(glyph.kanji[line], 8)

				// While moving halfwidth glyphs to the high byte of a glyph
				// row ensures that any additional boldface dots to the left
				// of the glyph are lost (see the bug below), it's better than
				// storing them in the low byte and spilling such new dots into
				// the high one. In that case, these dots would appear on
				// screen as glitched pixels if the glyph was displayed at a
				// byte-aligned position. (That's exactly what happens in the
				// ASM version of this code, introduced in TH04.)
				: (glyph.ank_8x16[line] << 8)
			);

			// ZUN bug: The left shifts and additions here can generate new
			// dots to the left of [row_in]. Therefore, a bold glyph can (and
			// with [FX_WEIGHT_BLACK], actually does) extend into the VRAM byte
			// to the left of the calculated offset. To properly handle this
			// case, you would center [row_in] within a 32-dot variable, which
			// leaves a bit more room for both additional dots left and right
			// of the glyph, as well as [first_bit]-based shifting towards the
			// right. However, ZUN ignored this possibility by having [row_out]
			// be a 16-dot variable as well, effectively cutting off these
			// additional pixels.
			switch(weight) {
			case WEIGHT_HEAVY:
				glyph_row |= (glyph_row << 1);
				break;
			case WEIGHT_BLACK:
				glyph_row |= (glyph_row << 1);
				/* fallthrough */
			case WEIGHT_BOLD: {
				dots_t(GLYPH_FULL_W) glyph_row_tmp = glyph_row;
				glyph_row |= (glyph_row << 1);
				glyph_row_tmp ^= glyph_row;
				glyph_row &= ~(glyph_row_tmp << 1);
			}}

			if(reverse) {
				if(fullwidth) {
					glyph_row ^= 0xFFFF;
				} else {
					glyph_row ^= 0xFF00;
				}
			}
			if(first_bit) {
				vram[0] = (glyph_row >> (first_bit + BYTE_DOTS));
				vram[1] = (glyph_row >> (first_bit +         0));
				vram[2] = (glyph_row << (BYTE_DOTS - first_bit));
			} else {
				*reinterpret_cast<dots_t(GLYPH_FULL_W) far *>(vram) = (
					__rotr__(glyph_row, 8)
				);
			}
			vram += ROW_SIZE;
		}
		left += glyph.tag.w;
	}
	outportb(0x68, 0xA); // CG ROM code access
}

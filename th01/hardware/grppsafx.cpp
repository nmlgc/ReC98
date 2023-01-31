// Shared parts from all graph_putsa_fx() implementations

#define set_vram_ptr(vram, first_bit, left, top) \
	vram = (dots8_t *)(MK_FP(SEG_PLANE_B, vram_offset_muldiv(left, top))); \
	first_bit = (left % BYTE_DOTS); \

#define get_glyph(glyph, codepoint, fullwidth, str, left, line) \
	if(_ismbblead(str[0])) { \
		codepoint = _mbcjmstojis(((char)str[0] << 8) + str[1]); \
		str += 2; \
	} else if(_ismbbkana((char)str[0])) { \
		codepoint = str[0] + 0x2980; \
		str += 1; \
	} else if(isgraph((char)str[0])) { \
		codepoint = str[0] + 0x2900; \
		str += 1; \
	} else { \
		codepoint = 0x2B21; \
		str += 1; \
	} \
	\
	outportb(0xA1, codepoint & 0xFF); \
	outportb(0xA3, (codepoint >> 8) - 0x20); \
	if(codepoint >= 0x2921 && codepoint <= 0x2B7E) { \
		if(left <= (RES_X - GLYPH_HALF_W)) { \
			for(line = 0; line < GLYPH_H; line++) { \
				outportb(0xA5, line | 0x20); \
				\
				/* \
				 * While moving halfwidth glyphs to the high byte of a glyph \
				 * row ensures that any additional boldface dots to the left \
				 * of the glyph are lost (see the bug below), it's better than \
				 * storing them in the low byte and spilling such new dots \
				 * into the high one. In that case, these dots would appear on \
				 * screen as glitched pixels if the glyph was displayed at a \
				 * byte-aligned position. (That's exactly what happens in the \
				 * ASM version of this code, introduced in TH04.) \
				 */ \
				glyph[line] = (inportb(0xA9) << 8); \
			} \
			fullwidth = false; \
		} else { \
			break; \
		} \
	} else if(left <= (RES_X - GLYPH_FULL_W)) { \
		for(line = 0; line < GLYPH_H; line++) { \
			outportb(0xA5, line | 0x20); \
			glyph[line] = inportb(0xA9) << 8; \
			outportb(0xA5, line); \
			glyph[line] += inportb(0xA9); \
		} \
		fullwidth = true; \
	} else { \
		break; \
	}

#define glyph_double(row, tmp) \
	tmp = row; \
	row |= tmp << 1;

// ZUN bug: The left shifts and additions here can generate new dots to the
// left of [row_in]. Therefore, a bold glyph can (and with FX_WEIGHT_BLACK,
// actually does) extend into the VRAM byte to the left of the calculated
// offset. To properly handle this case, you would center [row_in] within a
// 32-dot variable, which leaves a bit more room for both additional dots left
// and right of the glyph, as well as [first_bit]-based shifting towards the
// right. However, ZUN ignored this possibility by having [row_out] be a 16-dot
// variable as well, effectively cutting off these additional pixels.
#define apply_weight(row_out, row_in, row_tmp, weight) \
	row_out = row_in; \
	switch(weight) { \
	case WEIGHT_HEAVY: \
		glyph_double(row_out, row_tmp); \
		break; \
	case WEIGHT_BLACK: \
		glyph_double(row_out, row_tmp); \
		/* fallthrough */ \
	case WEIGHT_BOLD: \
		glyph_double(row_out, row_tmp); \
		row_tmp ^= row_out; \
		row_out &= ~(row_tmp << 1); \
	}

#define put_row_and_advance(vram, glyph_row, first_bit) \
	if(first_bit) { \
		vram[0] = glyph_row >> (first_bit + BYTE_DOTS); \
		vram[1] = glyph_row >> (first_bit +         0); \
		vram[2] = glyph_row << (BYTE_DOTS - first_bit); \
	} else { \
		vram[0] = glyph_row >> BYTE_DOTS; \
		vram[1] = glyph_row; \
	} \
	vram += ROW_SIZE;

#define advance_left(left, fullwidth, spacing) \
	if(fullwidth) { \
		left += GLYPH_HALF_W; \
	} \
	left += spacing + GLYPH_HALF_W;

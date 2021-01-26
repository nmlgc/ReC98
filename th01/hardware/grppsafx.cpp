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
				glyph[line] = inportb(0xA9) << 8; \
			} \
			fullwidth = 0; \
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
		fullwidth = 1; \
	} else { \
		break; \
	}

#define glyph_double(row, tmp) \
	tmp = row; \
	row |= tmp << 1;

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

#define put_row_and_advance(vram, row, first_bit) \
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

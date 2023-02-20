// PC-98 font ROM access
// ---------------------

// Structure returned by INT 18h, AH=14h. The amount of bytes returned depends
// on the type of glyph (8×8, 8×16, or 16×16) as indicated by its codepoint,
// so make sure to allocate the correct subclass for it.
struct font_glyph_header_t {
	uint8_t tram_w;
	uint8_t h_divided_by_8;
};

struct font_glyph_ank_8x16_t : public font_glyph_header_t {
	dot_rect_t(GLYPH_HALF_W, GLYPH_H) dots;
};

struct font_glyph_kanji_t : public font_glyph_header_t {
	dot_rect_t(GLYPH_FULL_W, GLYPH_H) dots;
};

// Writes user-defined glyphs to the given offset inside the PC-98 gaiji RAM.
// The 256 possible gaiji IDs are mapped onto JIS X 0208 codepoints as follows:
//
// 	((0x7680 + id) & 0xFF7F)
//
// Note that not all PC-98 models support all 256 gaiji codepoints. IDs 0x00
// and 0x80 are particularly unlikely to be supported, as they collide with
// ASCII 0x56 (V) and 0x57 (W) when written into TRAM. The safest IDs range
// from 0x21 to 0x5F inclusive, which correspond to the gaiji range from the
// first PC-9801 models that supported the feature (PC-9801E/F/M).
void font_gaiji_write(
	const dot_rect_t(GLYPH_FULL_W, GLYPH_H)* gaiji,
	uint16_t count,
	uint8_t first_id
);

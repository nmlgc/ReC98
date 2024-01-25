// PC-98 font ROM access
// ---------------------

// Indicates the size of the glyph (8×8, 8×16, or 16×16), and by extension the
// amount of bytes returned from font_read().
struct font_glyph_header_t {
	uint8_t h; // in pixels
	uint8_t w; // in pixels
};

struct font_glyph_ank_8x8_t : public font_glyph_header_t {
	dot_rect_t(GLYPH_HALF_W, GLYPH_HALF_H) dots;
};

struct font_glyph_ank_8x16_t : public font_glyph_header_t {
	dot_rect_t(GLYPH_HALF_W, GLYPH_H) dots;
};

struct font_glyph_kanji_t : public font_glyph_header_t {
	dot_rect_t(GLYPH_FULL_W, GLYPH_H) dots;
};

// Tagged union for all possible glyph sizes returned from font_read().
struct font_glyph_t {
	font_glyph_header_t tag;
	union {
		dot_rect_t(GLYPH_HALF_W, GLYPH_HALF_H) ank_8x8;
		dot_rect_t(GLYPH_HALF_W, GLYPH_H) ank_8x16;
		dot_rect_t(GLYPH_FULL_W, GLYPH_H) kanji;
	};
};

// Reads the font ROM glyph for the given JIS codepoint.
void font_read(font_glyph_t& glyph, jis_t jis);

// Strongly-typed, memory-conserving wrappers around font_read() for smaller
// glyphs.
void font_read(font_glyph_ank_8x8_t& glyph, ank_t ank);
void font_read(font_glyph_ank_8x16_t& glyph, ank_t ank);

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

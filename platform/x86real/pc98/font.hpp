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

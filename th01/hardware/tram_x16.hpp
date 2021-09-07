// Font ROM glyph retrieval
// ------------------------

// Structure returned from INT 18h, AH=14h. The amount of bytes returned
// depends on the type of glyph (8×8, 8×16, or 16×16) indicated by its code
// point, so make sure to allocate the correct subclass for it.
struct pc98_glyph_t {
	uint8_t tram_w;
	uint8_t h_divided_by_8;
};

struct pc98_glyph_kanji_t : public pc98_glyph_t {
	DotRect<dots_t(GLYPH_FULL_W), GLYPH_H> dots;
};
// ------------------------

class TRAMCursor {
	struct {
		uint16_t left;
		uint16_t right;
	} near* p;

public:
	// Writes the given fullwidth JIS code point with the given attribute to
	// the left and right cells at the current cursor position, then advances
	// the cursor. Halfwidth code points will also be written to both cells.
	void putkanji(uint16_t jis_kanji, int atrb);

	// Calls putkanji() for the next 5 TRAM rows.
	void putkanji_for_5_rows(uint16_t jis_kanji, int atrb);

	// This is always called at line 21, and therefore always ends up writing
	// into the second TRAM page. Luckily, that page is used, and no code cares
	// about it...
	void putkanji_until_end(uint16_t jis_kanji, int atrb) {
		putkanji_for_5_rows(jis_kanji, atrb);
	}

	void rewind_to_topleft() {
		p = 0;
	}
};

/// 16× letter rendering
/// --------------------
/// These are rendered by retrieving the glyphs from font ROM and then printing
/// them to text RAM with one fullwidth space per glyph dot, effectively
/// scaling them up to 16× their size.

// Fills text RAM with black and renders a transparent [jis_kanji] at its
// center.
void pascal tram_x16_kanji_center_reverse(uint16_t jis_kanji);

#define tram_x16_put_center_margin(tram_cursor, x, atrb) \
	for(x = 0; x < (((RES_X / GLYPH_FULL_W) - GLYPH_FULL_W) / 2); x++) { \
		tram_cursor.putkanji(' ', atrb); \
	}

// Helper functions
// ----------------

template <class RowDots> struct TRAMx16Row {
	RowDots dot_cur;
	RowDots dots;

	pixel_t w() const {
		return ((sizeof(dots) * BYTE_DOTS));
	}
};

#define tram_x16_row_init(row, row_dots) \
	row.dots = row_dots; \
	row.dot_cur = (1 << (row.w()- 1));

#define tram_x16_row_put(row, tram_cursor, x, atrb_fg, atrb_bg) \
	for(x = 0; x < row.w(); x++) { \
		if((row.dots & row.dot_cur) == 0) { \
			tram_cursor.putkanji(' ', atrb_bg); \
		} else { \
			tram_cursor.putkanji(' ', atrb_fg); \
		} \
		row.dot_cur >>= 1; \
	}
// ----------------
// --------------------

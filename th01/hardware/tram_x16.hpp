// Font ROM glyph retrieval
// ------------------------

#include "platform/x86real/pc98/font.hpp"

void int18h_14h(REGS& in, font_glyph_header_t& glyph, jis_t jis);

inline void fontrom_get(REGS& in, font_glyph_ank_8x16_t& glyph, char ank) {
	int18h_14h(in, glyph, (0x8000 + ank));
}
// ------------------------

class TRAMCursor {
	struct {
		jis_t left;
		jis_t right;
	} near* p;

public:
	// Writes the given fullwidth JIS code point with the given attribute to
	// the left and right cells at the current cursor position, then advances
	// the cursor. Halfwidth code points will also be written to both cells.
	void putkanji(jis_t jis_kanji, int atrb);

	// Calls putkanji() for the next 5 TRAM rows.
	void putkanji_for_5_rows(jis_t jis_kanji, int atrb);

	// ZUN landmine: This is always called at the (0-based) line 21, and
	// therefore always ends up writing into the second TRAM page. Luckily,
	// that page is unused, and no code cares about it...
	void putkanji_until_end(jis_t jis_kanji, int atrb) {
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
void pascal tram_x16_kanji_center_reverse(jis_t jis_kanji);

// Shows the red "STAGE [stage_num]" letters.
void pascal tram_x16_stage(unsigned int stage_num);

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
	row.dot_cur = (1 << (row.w() - 1));

#define tram_x16_row_put(row, tram_cursor, x, atrb_fg, atrb_bg) \
	for(x = 0; x < row.w(); x++) { \
		if((row.dots & row.dot_cur) == 0) { \
			tram_cursor.putkanji(' ', atrb_bg); \
		} else { \
			tram_cursor.putkanji(' ', atrb_fg); \
		} \
		row.dot_cur >>= 1; \
	}

#define tram_x16_row_put_red(row, tram_cursor, x, row_dots) \
	tram_x16_row_init(row, row_dots); \
	tram_x16_row_put(row, tram_cursor, x, (TX_RED | TX_REVERSE), TX_BLACK);
// ----------------
// --------------------

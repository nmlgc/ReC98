#include "platform/x86real/pc98/font.hpp"

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
void tram_x16_kanji_center_reverse(jis_t jis_kanji);

// Shows the red "STAGE [stage_num]" letters.
void tram_x16_stage(unsigned int stage_num);

// Helper functions
// ----------------

// Advances the cursor by the margin of a single centered fullwidth glyph (or
// two centered halfwidth glyphs) at 16× magnification, filling all TRAM cells
// with the given attribute.
void tram_x16_put_center_margin(TRAMCursor& tram_cursor, int atrb);

// Renders the given row of pixels at 16× magnification onto TRAM. 0 dots are
// rendered with [atrb_bg], 1 dots with [atrb_fg].
void tram_x16_row_put(
	TRAMCursor& tram_cursor,
	int atrb_fg,
	int atrb_bg,
	const dots8_t* row,
	pixel_t row_w
);

inline void tram_x16_row_put_red(
	TRAMCursor& tram_cursor, const dots8_t *row, pixel_t row_w
) {
	tram_x16_row_put(tram_cursor, (TX_RED | TX_REVERSE), TX_BLACK, row, row_w);
}
// ----------------
// --------------------

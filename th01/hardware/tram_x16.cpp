#include "libs/master.lib/pc98_gfx.hpp"
#include "th01/hardware/tram_x16.hpp"

void TRAMCursor::putkanji(jis_t jis_kanji, tram_atrb2 atrb)
{
	// Yes, this is a correct way of writing any fullwidth character to TRAM.
	// More research and proof forthcoming...
	poke(SEG_TRAM_JIS, FP_OFF(&p->left), jis_kanji);
	poke(SEG_TRAM_JIS, FP_OFF(&p->right), jis_kanji);

	pokeb(SEG_TRAM_ATRB, FP_OFF(&p->left), atrb);
	pokeb(SEG_TRAM_ATRB, FP_OFF(&p->right), atrb);
	p++;
}

void TRAMCursor::putkanji_for_5_rows(jis_t jis_kanji, tram_atrb2 atrb)
{
	for(int y = 0; y < 5; y++) {
		for(int x = 0; x < (RES_X / GLYPH_FULL_W); x++) {
			putkanji(jis_kanji, atrb);
		}
	}
}

static const ushiftjis_kanji_amount_t TRAM_X16_CENTER_MARGIN = (
	((RES_X / GLYPH_FULL_W) - GLYPH_FULL_W) / 2
);

void tram_x16_put_center_margin(TRAMCursor& tram_cursor, int atrb)
{
	for(ushiftjis_kanji_amount_t x = 0; x < TRAM_X16_CENTER_MARGIN; x++) {
		tram_cursor.putkanji(' ', atrb);
	}
}

void tram_x16_row_put(
	TRAMCursor& tram_cursor,
	int atrb_fg,
	int atrb_bg,
	const dots8_t* row,
	pixel_t row_w
)
{
	uint8_t dot_cur = 0;
	for(ushiftjis_kanji_amount_t x = 0; x < row_w; x++) {
		if(dot_cur == 0) {
			dot_cur = (1 << (BYTE_DOTS - 1));
		}
		if((row[x >> 3] & dot_cur) == 0) {
			tram_cursor.putkanji(' ', atrb_bg);
		} else {
			tram_cursor.putkanji(' ', atrb_fg);
		}
		dot_cur >>= 1;
	}
}

// Heavily inspired by the INT 18h, AH=14h sample program from the PC-9801
// Programmers' Bible, on p. 121.
void tram_x16_kanji_center_reverse(jis_t jis_kanji)
{
	TRAMCursor tram_cursor;
	font_glyph_t glyph;

	font_read(glyph, jis_kanji);

	tram_cursor.rewind_to_topleft();
	tram_cursor.putkanji_for_5_rows(' ', (TX_BLACK | TX_REVERSE));

	for(upixel_t glyph_y = 0; glyph_y < GLYPH_H; glyph_y++) {
		tram_x16_put_center_margin(tram_cursor, (TX_BLACK | TX_REVERSE));
		tram_x16_row_put(
			tram_cursor,
			TX_BLACK,
			(TX_BLACK | TX_REVERSE),
			reinterpret_cast<dots8_t *>(&glyph.kanji[glyph_y]),
			glyph.kanji.w()
		);
		tram_x16_put_center_margin(tram_cursor, (TX_BLACK | TX_REVERSE));
	}
	tram_cursor.putkanji_until_end(' ', (TX_BLACK | TX_REVERSE));
}

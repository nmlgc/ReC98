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

// Heavily inspired by the INT 18h, AH=14h sample program from the PC-9801
// Programmers' Bible, on p. 121.
void pascal tram_x16_kanji_center_reverse(jis_t jis_kanji)
{
	ushiftjis_kanji_amount_t x;
	upixel_t glyph_y;
	TRAMCursor tram_cursor;
	TRAMx16Row<dots_t(GLYPH_FULL_W)> row;
	REGS in;
	REGS out;
	StupidBytewiseWrapperAround<font_glyph_kanji_t> glyph;

	in.w.bx = FP_SEG(&glyph);
	in.w.cx = FP_OFF(&glyph);
	in.w.dx = jis_kanji;
	in.h.ah = 0x14;
	int86(0x18, &in, &out);

	tram_cursor.rewind_to_topleft();
	tram_cursor.putkanji_for_5_rows(' ', (TX_BLACK | TX_REVERSE));

	for(glyph_y = 1; glyph_y <= GLYPH_H; glyph_y++) {
		tram_x16_row_init(row, (
			(glyph.ubyte[(glyph_y * sizeof(row.dots)) + 0] << BYTE_DOTS) +
			(glyph.ubyte[(glyph_y * sizeof(row.dots)) + 1])
		));

		tram_x16_put_center_margin(tram_cursor, x, (TX_BLACK | TX_REVERSE));
		tram_x16_row_put(
			row, tram_cursor, x, TX_BLACK, (TX_BLACK | TX_REVERSE)
		);
		tram_x16_put_center_margin(tram_cursor, x, (TX_BLACK | TX_REVERSE));
	}
	tram_cursor.putkanji_until_end(' ', (TX_BLACK | TX_REVERSE));
}

// Where was this function above? :P
void int18h_14h(REGS& in, font_glyph_header_t& glyph, jis_t jis)
{
	REGS out;
	in.w.bx = FP_SEG(&glyph);
	in.w.cx = FP_OFF(&glyph);
	in.w.dx = jis;
	in.h.ah = 0x14;
	int86(0x18, &in, &out);
}

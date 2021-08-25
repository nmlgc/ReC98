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
};

#include "th01/hardware/tram_x16.hpp"

void TRAMCursor::putkanji(uint16_t jis_kanji, int atrb)
{
	// Yes, this is a correct way of writing any fullwidth character to TRAM.
	// More research and proof forthcoming...
	poke(SEG_TRAM_JIS, FP_OFF(&p->left), jis_kanji);
	poke(SEG_TRAM_JIS, FP_OFF(&p->right), jis_kanji);

	pokeb(SEG_TRAM_ATRB, FP_OFF(&p->left), atrb);
	pokeb(SEG_TRAM_ATRB, FP_OFF(&p->right), atrb);
	p++;
}

void TRAMCursor::putkanji_for_5_rows(uint16_t jis_kanji, int atrb)
{
	for(int y = 0; y < 5; y++) {
		for(int x = 0; x < (RES_X / GLYPH_FULL_W); x++) {
			putkanji(jis_kanji, atrb);
		}
	}
}

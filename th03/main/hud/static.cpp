#include "th03/main/hud/static.hpp"
#include "th03/main/playfld.hpp"
#include "libs/master.lib/pc98_gfx.hpp"

void hud_wipe(void)
{
	text_fillca(' ', (TX_BLACK | TX_REVERSE));

	// Include the bottom row of TRAM, which contains the gauge.
	text_boxfilla(
		playfield_tram_x(0, 0),
		PLAYFIELD_TRAM_TOP,
		(playfield_tram_x(0, PLAYFIELD_W) - 1),
		((RES_Y / GLYPH_H) - 1),
		TX_WHITE
	);
	text_boxfilla(
		playfield_tram_x(1, 0),
		PLAYFIELD_TRAM_TOP,
		(playfield_tram_x(1, PLAYFIELD_W) - 1),
		((RES_Y / GLYPH_H) - 1),
		TX_WHITE
	);
}

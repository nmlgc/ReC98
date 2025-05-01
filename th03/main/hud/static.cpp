#include "th03/main/hud/static.hpp"
#include "th03/main/player/stuff.hpp"
#include "th03/gaiji/gaiji.h"
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

void pascal hud_static_halfhearts_put(pid_t pid)
{
	enum {
		HALFHEARTS_W = ((HALFHEARTS_MAX / 2) * GAIJI_W),
	};

	tram_x_t x;
	int halfheart_i = 0;
	if(pid == 0) {
		x = (playfield_tram_x(0, ((PLAYFIELD_W / 2) - (HALFHEARTS_W / 2))));
	} else {
		x = (playfield_tram_x(1, ((PLAYFIELD_W / 2) - (HALFHEARTS_W / 2))));
	}
	int halfhearts;
	tram_y_t y = PLAYFIELD_TRAM_TOP;

	halfhearts = players[pid].halfhearts;
	while(halfheart_i < halfhearts) {
		if((halfhearts - halfheart_i) >= 2) {
			gaiji_putca(x, y, gs_HEART_FULL, TX_WHITE);
		} else {
			gaiji_putca(x, y, gs_HEART_HALF, TX_WHITE);
		}
		x += GAIJI_TRAM_W;
		halfheart_i += 2;
	}

	while(halfheart_i < HALFHEARTS_MAX) {
		gaiji_putca(x, y, gs_HEART_EMPTY, TX_WHITE);
		x += GAIJI_TRAM_W;
		halfheart_i += 2;
	}
}

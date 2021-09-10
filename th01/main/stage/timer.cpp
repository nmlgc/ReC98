extern "C" {
#include <stddef.h>
#include "platform.h"
#include "x86real.h"
#include "decomp.hpp"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "th01/hardware/egc.h"
#include "th01/hardware/frmdelay.h"
#include "th01/hardware/tram_x16.hpp"
#include "th01/math/subpixel.hpp"
#include "th01/snd/mdrv2.h"
#include "th01/sprites/pellet.h"
#include "th01/main/vars.hpp"
#include "th01/main/playfld.hpp"
#include "th01/main/bullet/pellet.hpp"
}

extern unsigned int frames_since_harryup;

// Largely copy-pasted from stage_num_animate().
void harryup_animate(void)
{
	utram_kanji_amount_t x;
	upixel_t glyph_y;
	TRAMx16Row<dots_t(GLYPH_HALF_W)> row;
	TRAMCursor tram_cursor;
	unsigned int i;
	REGS in;
	StupidBytewiseWrapperAround<pc98_glyph_ank_8x16_t> glyphs[7];

	mdrv2_se_play(17);

	fontrom_get(in, glyphs[0].t, 'H');
	fontrom_get(in, glyphs[1].t, 'A');
	fontrom_get(in, glyphs[2].t, 'R');
	fontrom_get(in, glyphs[3].t, 'R');
	fontrom_get(in, glyphs[4].t, 'Y');
	fontrom_get(in, glyphs[5].t, 'U');
	fontrom_get(in, glyphs[6].t, 'P');

	tram_cursor.rewind_to_topleft();
	tram_cursor.putkanji_for_5_rows(' ', TX_BLACK);

	glyph_y = offsetof(pc98_glyph_ank_8x16_t, dots);
	while(glyph_y <= (sizeof(pc98_glyph_ank_8x16_t) - 1)) {
		for(i = 0; i < 5; i++) {
			tram_x16_row_put_red(row, tram_cursor, x, glyphs[i].byte[glyph_y]);
		}
		// 5 halfwidth glyphs scaled a factor of 16 just happen to exactly fit
		// into one TRAM row, so we're already at the next one here.
		glyph_y++;
	}

	frame_delay(27);

	tram_cursor.rewind_to_topleft();
	tram_cursor.putkanji_for_5_rows(' ', TX_BLACK);

	glyph_y = offsetof(pc98_glyph_ank_8x16_t, dots);
	while(glyph_y <= (sizeof(pc98_glyph_ank_8x16_t) - 1)) {
		tram_x16_put_center_margin(tram_cursor, x, TX_BLACK);
		for(i = 5; i < 7; i++) {
			tram_x16_row_put_red(row, tram_cursor, x, glyphs[i].byte[glyph_y]);
		}
		tram_x16_put_center_margin(tram_cursor, x, TX_BLACK);
		glyph_y++;
	}

	frame_delay(27);
	text_clear();
}

void pattern_harryup(void)
{
	extern unsigned char harryup_cycle;

	frames_since_harryup++;
	harryup_cycle++;

	bool fire =
		(frames_since_harryup < 200) ? ((harryup_cycle % 5) == 0) :
		(frames_since_harryup < 300) ? ((harryup_cycle % 4) == 0) :
		(frames_since_harryup < 400) ? ((harryup_cycle % 3) == 0) :
		(frames_since_harryup < 500) ? ((harryup_cycle % 2) == 0) :
		/*                   >= 500 */ true;

	if(!fire) {
		return;
	}
	for(unsigned char i = 0; i <= rank; i++) {
		Pellets.add_group(
			playfield_rand_x(), PLAYFIELD_TOP, PG_1_RANDOM_WIDE, to_sp(3.0f)
		);
	}
}

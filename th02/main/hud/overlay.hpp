#include "pc98.h"

#if (GAME == 2)
	// Prints the rightmost [digits] of [val] using the bold gaiji font onto
	// TRAM, right-aligned at
	//
	// 	(([left] + ([digits] * GAIJI_W)), [y])
	//
	// Leading zeroes are skipped. [digits] is expected to be ≤8.
	void pascal near overlay_uint_put(
		tram_x_t left, tram_y_t y, int digits, long val
	);

	// Fills the playfield's area on the text RAM with transparency.
	// (Future games use a near function.)
	void far overlay_wipe(void);
#endif

#define overlay_line_fill(y, atrb) { \
	extern const shiftjis_t* PLAYFIELD_BLANK_ROW; \
	text_putsa(PLAYFIELD_TRAM_LEFT, y, PLAYFIELD_BLANK_ROW, atrb); \
}

// ZUN bloat: Use a single function.
#if (GAME == 5)
	#define overlay_line_fill_slow overlay_line_fill
#else
	#define overlay_line_fill_slow(y, atrb) { \
		for(tram_x_t x = PLAYFIELD_TRAM_LEFT; x < PLAYFIELD_TRAM_RIGHT; x++) { \
			text_putca(x, y, ' ', atrb); \
		} \
	}
#endif

#define overlay_fill(atrb) { \
	for(tram_y_t y = PLAYFIELD_TRAM_TOP; y < PLAYFIELD_TRAM_BOTTOM; y++) { \
		overlay_line_fill_slow(y, atrb); \
	} \
}

// Shows the stage fade-in effect in a blocking way. Returns with the playfield
// area in TRAM filled with empty gaiji cells.
void overlay_stage_enter_animate(void);

// Shows the stage fade-out effect in a blocking way. Returns with the
// playfield area in TRAM filled with opaque black cells.
void overlay_stage_leave_animate(void);

#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "shiftjis.hpp"
#include "master.hpp"
#include "th02/v_colors.hpp"
extern "C" {
#if (GAME >= 4)
	#include "th04/hardware/bgimage.hpp"
	#include "th04/hardware/grppsafx.h"
#else
	#include "th01/hardware/grppsafx.h"
#endif
}
#if (GAME == 5)
	#include "th05/shiftjis/music.hpp"

	int game_sel = (GAME_COUNT - 1);
	extern const int TRACK_COUNT[GAME_COUNT] = { 14, 18, 24, 28, 23 };
#else
	#if (GAME == 4)
		#include "th04/shiftjis/music.hpp"
	#elif (GAME == 3)
		#include "th03/shiftjis/music.hpp"
	#elif (GAME == 2)
		#include "th02/shiftjis/music.hpp"
	#endif
#endif

// Colors
// ------

static const vc_t COL_TRACKLIST_SELECTED = ((GAME >= 4) ? 3 : V_WHITE);
static const vc_t COL_TRACKLIST          = ((GAME >= 4) ? 5 : 3);
// ------

// Coordinates
// -----------

static const screen_x_t TRACKLIST_LEFT = ((GAME == 5) ? 12 : 16);
#if (GAME == 5)
	static const int TRACKLIST_VISIBLE_COUNT = 12;

	static const screen_y_t TRACKLIST_TOP = 96;
	static const pixel_t TRACKLIST_H = (TRACKLIST_VISIBLE_COUNT * GLYPH_H);

	static const screen_y_t LABEL_GAME_TOP = 32;
	static const screen_y_t LABEL_UP_TOP = (TRACKLIST_TOP - GLYPH_H);
	static const screen_y_t LABEL_DOWN_TOP = (TRACKLIST_TOP + TRACKLIST_H);
#else
	inline screen_y_t track_top(uint8_t sel) {
		#if (GAME == 4)
			return (8 + (sel * GLYPH_H));
		#elif (GAME == 3)
			return (40 + (sel * GLYPH_H));
		#elif (GAME == 2)
			return ((static_cast<tram_y_t>(sel) + 6) * GLYPH_H);
		#endif
	}

	inline int16_t track_fx(vc_t col) {
		if(GAME >= 4) {
			return col;
		} else {
			return (col | FX_WEIGHT_BOLD);
		}
	}
#endif
// -----------

// Polygon state
// -------------

bool polygons_initialized = false;
// -------------

// Selection state
// ---------------

#if (GAME <= 4)
	uint8_t track_playing = 0;
#endif
extern page_t music_page;
// ---------------

#if (GAME == 5)
	// TH05 selection state
	// --------------------

	extern int track_id_at_top;
	extern int track_playing;
	extern int track_count_cur;
	// --------------------

	void pascal near track_unput_or_put(uint8_t track_sel, bool16 put)
	{
		enum {
			CURSOR_LEFT = TRACKLIST_LEFT,
			CURSOR_RIGHT = (CURSOR_LEFT + TRACKLIST_W),
			CURSOR_TOP = TRACKLIST_TOP,
			CURSOR_BOTTOM = (TRACKLIST_TOP + GLYPH_H - 1),
		};

		const shiftjis_t* choice;
		vc_t col = COL_TRACKLIST;

		// ZUN bloat: The code could have been a lot simpler if [TRACKLIST_TOP]
		// was added here rather than just before graph_putsa_fx(). Then, [top]
		// could have been a `screen_y_t`.
		pixel_t top = ((track_sel - track_id_at_top) * GLYPH_H);
		if((top < 0) || (top >= TRACKLIST_H)) {
			return;
		}
		if(put) {
			grcg_setcolor(GC_RMW, COL_TRACKLIST);
			grcg_hline(CURSOR_LEFT, CURSOR_RIGHT, (CURSOR_TOP + top));
			grcg_hline(CURSOR_LEFT, CURSOR_RIGHT, (CURSOR_BOTTOM + top));
			grcg_vline(CURSOR_LEFT, (CURSOR_TOP + top), (CURSOR_BOTTOM + top));
			grcg_vline(CURSOR_RIGHT, (CURSOR_TOP + top), (CURSOR_BOTTOM + top));
			grcg_off();
		} else {
			// ZUN bloat: Blitting [TRACKLIST_W] pixels starting at
			// [TRACKLIST_LEFT] is enough.
			bgimage_put_rect_16(0, (CURSOR_TOP + top), 320, GLYPH_H);
		}
		if(track_sel == track_playing) {
			col = COL_TRACKLIST_SELECTED;
		}

		choice = MUSIC_CHOICES[game_sel][track_sel];
		top += TRACKLIST_TOP;
		graph_putsa_fx(TRACKLIST_LEFT, top, col, choice);
	}

	void pascal near tracklist_put(uint8_t sel)
	{
		for(int i = 0; i < (track_count_cur + 2); i++) {
			track_unput_or_put(i, (i == sel));
		}
		graph_putsa_fx(TRACKLIST_LEFT, LABEL_UP_TOP, COL_TRACKLIST, LABEL_UP);
		graph_putsa_fx(
			TRACKLIST_LEFT, LABEL_DOWN_TOP, COL_TRACKLIST, LABEL_DOWN
		);
		graph_putsa_fx(
			TRACKLIST_LEFT,
			LABEL_GAME_TOP,
			COL_TRACKLIST_SELECTED,
			LABEL_GAME[game_sel]
		);
	}
#else
	void pascal near track_put(uint8_t sel, vc_t col)
	{
		page_t other_page = (1 - music_page);
		graph_accesspage(other_page);
		graph_putsa_fx(
			TRACKLIST_LEFT, track_top(sel), track_fx(col), MUSIC_CHOICES[sel]
		);
		graph_accesspage(music_page);
		graph_putsa_fx(
			TRACKLIST_LEFT, track_top(sel), track_fx(col), MUSIC_CHOICES[sel]
		);
	}

	void pascal near tracklist_put(uint8_t sel)
	{
		int i;
		for(i = 0; i < sizeof(MUSIC_CHOICES) / sizeof(MUSIC_CHOICES[0]); i++) {
			track_put(i, ((i == sel) ? COL_TRACKLIST_SELECTED : COL_TRACKLIST));
		}
	}
#endif


#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "shiftjis.hpp"
#include "libs/master.lib/master.hpp"
#include "libs/master.lib/pc98_gfx.hpp"
#include "th01/hardware/grppsafx.h"
#include "th02/v_colors.hpp"
#include "th03/common.h"
#include "th03/playchar.hpp"
#include "th03/score.hpp"
#include "th03/resident.hpp"
#include "th03/formats/cdg.h"
#include "th03/formats/win.hpp"
#include "th03/sprites/playchar.hpp"

extern const char near* PIC_FN[PLAYCHAR_COUNT];
shiftjis_t win_text[WIN_LINES][WIN_LINE_SIZE + 1];
PlaycharPaletted playchar[PLAYER_COUNT];

// Win screen
// ----------

static const int LOGO_FADE_CELS = 5;

enum win_cdg_slot_t {
	CDG_LOGO_FADE = 0,
	CDG_LOGO = (CDG_LOGO_FADE + LOGO_FADE_CELS),
	CDG_PIC_WINNER,
};

static const screen_y_t WIN_PIC_TOP = 64;
static const screen_y_t WIN_PIC_BOTTOM = (64 + PLAYCHAR_PIC_H);

inline playchar_t loser_char_id(void) {
	return static_cast<playchar_t>((resident->pid_winner == 0)
		? playchar[1].char_id()
		: playchar[0].char_id()
	);
}

void near win_load(void)
{
	extern const char logo0_rgb[];
	extern const char logo_cd2[];
	extern const char logo5_cdg[];
	extern const char* WIN_MESSAGE_FN[PLAYCHAR_COUNT];

	playchar_paletted_t playchar_winner;
	uint8_t message_id;

	// MODDERS: [playchar_winner] has to be declared as a scalar type to cause
	// Turbo C++ 4.0J to place it at its original stack position, and I'd like
	// to still use the `PlaycharPaletted` methods. Just turn [playchar_winner]
	// into a `PlaycharPaletted` and remove this macro.
	#define playchar_winner ( \
		reinterpret_cast<PlaycharPaletted &>(playchar_winner) \
	)

	palette_entry_rgb_show(logo0_rgb);
	cdg_load_all_noalpha(CDG_LOGO_FADE, logo_cd2);
	cdg_load_single(CDG_LOGO, logo5_cdg, 0);

	// ZUN bloat: playchar[resident->pid_winner]
	playchar_winner = ((resident->pid_winner == 0) ? playchar[0] : playchar[1]);

	if(resident->pid_winner == 0) {
		// The usually 0-based [story_stage] has already been incremented when
		// we get here, so these refer to the *next* stage, not the one that
		// has just been won.
		if(resident->story_stage == STAGE_DECISIVE) {
			message_id = (PLAYCHAR_COUNT + 0);
		} else if(resident->story_stage == STAGE_CHIYURI) {
			message_id = (PLAYCHAR_COUNT + 1);
		} else {
			message_id = loser_char_id();
		}
	} else {
		message_id = loser_char_id();
	}

	cdg_load_single_noalpha(
		CDG_PIC_WINNER,
		PIC_FN[playchar_winner.char_id_16()],
		playchar_winner.palette_id()
	);

	static_assert(WIN_LINES == 3);
	file_ropen(WIN_MESSAGE_FN[playchar_winner.char_id_16()]);
	file_seek((message_id * (WIN_LINES * WIN_LINE_SIZE)), SEEK_SET);
	file_read(win_text[0], WIN_LINE_SIZE);	win_text[0][WIN_LINE_SIZE] = '\0';
	file_read(win_text[1], WIN_LINE_SIZE);	win_text[1][WIN_LINE_SIZE] = '\0';
	file_read(win_text[2], WIN_LINE_SIZE);	win_text[2][WIN_LINE_SIZE] = '\0';
	file_close();

	#undef playchar_winner
}

void near win_text_put(void)
{
	enum {
		LEFT = ((RES_X / 2) - ((WIN_LINE_SIZE / 2) * GLYPH_HALF_W)),
		TOP = (WIN_PIC_BOTTOM + GLYPH_H),
		COL_AND_FX = (FX_WEIGHT_BOLD | V_WHITE),
	};

	static_assert(WIN_LINES == 3);
	graph_putsa_fx(LEFT, (TOP + (0 * GLYPH_H)), COL_AND_FX, win_text[0]);
	graph_putsa_fx(LEFT, (TOP + (1 * GLYPH_H)), COL_AND_FX, win_text[1]);
	graph_putsa_fx(LEFT, (TOP + (2 * GLYPH_H)), COL_AND_FX, win_text[2]);
}
// ----------

// Stage splash screen
// -------------------

bool do_not_show_stage_number;
// -------------------

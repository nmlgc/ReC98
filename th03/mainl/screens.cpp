#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "shiftjis.hpp"
#include "master.hpp"
#include "th03/common.h"
#include "th03/playchar.hpp"
#include "th03/score.h"
#include "th03/resident.hpp"
extern "C" {
#include "th03/formats/cdg.h"
}
#include "th03/formats/win.hpp"

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
// ----------

// Stage splash screen
// -------------------

bool do_not_show_stage_number;
// -------------------

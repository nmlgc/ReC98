// CDG slots for TH04's and TH05's OP.EXE

#if (GAME == 5)
#include "th05/playchar.h"
#else
#include "th04/playchar.h"
#endif
#include "th04/snd/snd.h"
#include "th03/formats/cdg.h"
#include "th01/rank.h"

typedef enum {
	// sft1.cd2
	// --------
	CDG_NUMERAL = 0,
	CDG_NUMERAL_last = (CDG_NUMERAL + 9),
	// --------
	// sft2.cd2
	// --------
	CDG_MAIN,
	CDG_MAIN_GAME = CDG_MAIN,
	CDG_MAIN_EXTRA,
	CDG_MAIN_REGIST_VIEW,
	CDG_MAIN_MUSICROOM,
	CDG_MAIN_OPTION,
	CDG_QUIT,

	CDG_OPTION_LABEL_RANK,
	CDG_OPTION_LABEL_LIVES,
	CDG_OPTION_LABEL_BOMBS,
	CDG_OPTION_LABEL_BGM,
	CDG_OPTION_LABEL_SE,

	CDG_OPTION_VALUE_RANK,
	CDG_OPTION_VALUE_RANK_last = (CDG_OPTION_VALUE_RANK + RANK_LUNATIC),

	CDG_OPTION_VALUE_BGM,
	CDG_OPTION_VALUE_BGM_last = (
		CDG_OPTION_VALUE_BGM + (SND_BGM_MIDI - SND_BGM_FM26)
	),

	CDG_OPTION_VALUE_OFF,

	// ZUN bloat: Does not match the order in snd_se_mode_t.
	CDG_OPTION_VALUE_SE_BEEP,
	CDG_OPTION_VALUE_SE_FM,

	CDG_OPTION_RESET,

	CDG_OPTION_TURBO,
	CDG_OPTION_SLOW,
	CDG_EMPTY,
	// --------

	// car.cd2
	// -------
	CDG_CURSOR,
	CDG_CURSOR_LEFT = CDG_CURSOR,
	CDG_CURSOR_RIGHT,
	// -------

	CDG_PIC = 40,
	CDG_PIC_last = (CDG_PIC + PLAYCHAR_COUNT - 1),
#if (GAME == 5)
	CDG_CLEARED,
	CDG_PIC_NOT_CLEARED,
#endif

	_op_cdg_slot_t_FORCE_INT16 = 0x7FFF
} op_cdg_slot_t;

inline void op_cdg_load_shared(void) {
	// `sft2.cdg` only contains sprites for 4 difficulties
	static_assert(CDG_OPTION_VALUE_RANK_last == (CDG_OPTION_VALUE_RANK + 3));

	cdg_load_all(CDG_NUMERAL, "sft1.cd2");
	cdg_load_all(CDG_MAIN, "sft2.cd2");
	cdg_load_all(CDG_CURSOR, "car.cd2");
}

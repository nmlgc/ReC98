// CDG slots for TH03's OP.EXE

#include "th03/common.h"
#include "th03/playchar.hpp"

typedef enum {
	CDG_SELECT_FIRST,

	// Portrait of each player's selected character. Each of these can use the
	// alternate palette.
	CDG_PIC_SELECTED = CDG_SELECT_FIRST,
	CDG_PIC_SELECTED_last = (CDG_PIC_SELECTED + PLAYER_COUNT - 1),

	// Portraits of all characters using the regular palette.
	CDG_PIC,
	CDG_PIC_last = (CDG_PIC + PLAYCHAR_COUNT - 1),

	CDG_STATS, // Has the full 5 stars on all 3 rows.
	CDG_EXTRA_BG,
	CDG_EXTRA_FOR_PLAYCHAR,
	CDG_EXTRA_FOR_PLAYCHAR_last = (CDG_EXTRA_FOR_PLAYCHAR + PLAYCHAR_COUNT - 1),

	CDG_SELECT_COUNT,
} op_cdg_slot_t;

#include "th01/common.h"
#include "th01/score.h"

#define last_for_quarters(base, quarters) \
	((base + ((quarters + 3) / 4)) - 1)

static const int CARDCOMBO_DIGITS = 2;

typedef enum {
	PTN_SLOT_STG = 0, // stg(_b).ptn
	PTN_SLOT_MIKO = 1, // miko.ptn
	PTN_SLOT_BG_HUD = 5,
	PTN_SLOT_NUMB = 7, // numb.ptn
} main_ptn_slot_t;

typedef enum {
	// stg(_b).ptn
	// -----------
	PTN_HUD = PTN_ID(PTN_SLOT_STG, 0),
	PTN_SHOT,
	PTN_BLAST, // ???
	PTN_ORB,
	// -----------

	// HUD (snapped backgrounds)
	// -------------------------
	// The usage code doesn't really cap either of these, though...
	PTN_BG_LIVES = PTN_ID(PTN_SLOT_BG_HUD, 0),
	PTN_BG_LIVES_last = last_for_quarters(PTN_BG_LIVES, LIVES_MAX),
	PTN_BG_BOMBS = PTN_ID(PTN_SLOT_BG_HUD, 4),
	PTN_BG_BOMBS_last = last_for_quarters(PTN_BG_BOMBS, BOMBS_MAX),

	PTN_BG_CUR_SCORE,
	PTN_BG_CUR_SCORE_last = last_for_quarters(PTN_BG_CUR_SCORE, SCORE_DIGITS),
	PTN_BG_CUR_CARDCOMBO,

	PTN_BG_MAX_SCORE = PTN_ID(PTN_SLOT_BG_HUD, 10),
	PTN_BG_MAX_SCORE_last = last_for_quarters(PTN_BG_MAX_SCORE, SCORE_DIGITS),
	PTN_BG_MAX_CARDCOMBO,
	// -------------------------
} main_ptn_id_t;

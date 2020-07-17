#include "th01/score.h"

#define last_for_quarters(base, quarters) \
	((base + ((quarters + 3) / 4)) - 1)

static const int CARDCOMBO_DIGITS = 2;

typedef enum {
	PTN_SLOT_BG_HUD = 5,
} main_ptn_slot_t;

typedef enum {
	// HUD (snapped backgrounds)
	// -------------------------
	PTN_BG_CUR_SCORE = PTN_ID(PTN_SLOT_BG_HUD, 6),
	PTN_BG_CUR_SCORE_last = last_for_quarters(PTN_BG_CUR_SCORE, SCORE_DIGITS),
	PTN_BG_CUR_CARDCOMBO,

	PTN_BG_MAX_SCORE = PTN_ID(PTN_SLOT_BG_HUD, 10),
	PTN_BG_MAX_SCORE_last = last_for_quarters(PTN_BG_MAX_SCORE, SCORE_DIGITS),
	PTN_BG_MAX_CARDCOMBO,
	// -------------------------
} main_ptn_id_t;

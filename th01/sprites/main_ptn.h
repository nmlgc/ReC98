#include "th01/common.h"
#include "th01/score.h"

#define last_for_quarters(base, quarters) \
	((base + ((quarters + 3) / 4)) - 1)

static const int CARDCOMBO_DIGITS = 2;
static const int PORTAL_ANIM_CELS = 2;

typedef enum {
	PTN_SLOT_STG = 0, // stg(_b).ptn
	PTN_SLOT_MIKO = 1, // miko.ptn
	PTN_SLOT_BG_BOSS = 2, // Backgrounds behind animated boss entities
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

	PTN_CARD_UNUSED = 7,
	PTN_CARD_3HP, PTN_CARD_3HP_HALF, PTN_CARD_3HP_EDGE,
	PTN_CARD_2HP, PTN_CARD_2HP_HALF, PTN_CARD_2HP_EDGE,
	PTN_CARD_1HP, PTN_CARD_1HP_HALF, PTN_CARD_1HP_EDGE,
	PTN_CARD_0HP, PTN_CARD_0HP_HALF, PTN_CARD_0HP_EDGE,
	PTN_CARD_REMOVED_HALF,
	PTN_CARD_REMOVED,

	PTN_BUMPER,
	PTN_TURRET,
	PTN_TURRET_FIRING,
	PTN_BAR_TOP,
	PTN_BAR_LEFT,
	PTN_BAR_BOTTOM,
	PTN_BAR_RIGHT,
	PTN_PORTAL,
	PTN_PORTAL_ANIM,
	PTN_PORTAL_ANIM_last = (PTN_PORTAL_ANIM + (PORTAL_ANIM_CELS - 1)),
	// -----------

	// HUD (snapped backgrounds)
	// -------------------------
	// The usage code doesn't really cap either of these, though...
	PTN_BG_LIVES = PTN_ID(PTN_SLOT_BG_HUD, 0),
	PTN_BG_LIVES_last = last_for_quarters(PTN_BG_LIVES, LIVES_MAX),
	PTN_BG_STAGE,
	PTN_BG_STAGE_last, // But the original game only need a single quarter?
	PTN_BG_BOMBS,
	PTN_BG_BOMBS_last = last_for_quarters(PTN_BG_BOMBS, BOMBS_MAX),

	PTN_BG_CUR_SCORE,
	PTN_BG_CUR_SCORE_last = last_for_quarters(PTN_BG_CUR_SCORE, SCORE_DIGITS),
	PTN_BG_CUR_CARDCOMBO,

	PTN_BG_MAX_SCORE = PTN_ID(PTN_SLOT_BG_HUD, 10),
	PTN_BG_MAX_SCORE_last = last_for_quarters(PTN_BG_MAX_SCORE, SCORE_DIGITS),
	PTN_BG_MAX_CARDCOMBO,

	PTN_BG_HP = PTN_ID(PTN_SLOT_BG_HUD, 14),
	// -------------------------
} main_ptn_id_t;

#include "th01/common.h"
#include "th01/score.h"

// ID system
// ---------
// Internal assumption for mapping a ptn_id to a slot and image.

#define PTN_IMAGES_PER_SLOT 64
#define PTN_SLOT(slot) ((slot) * PTN_IMAGES_PER_SLOT)
#define PTN_ID(slot, image) (PTN_SLOT(slot) + image)
// ---------

#define last_for_quarters(base, quarters) \
	((base + ((quarters + 3) / 4)) - 1)

static const int ORB_CELS = 4;
static const int CARDCOMBO_DIGITS = 2;
static const int PORTAL_ANIM_CELS = 2;
static const int TIMER_DIGITS = 4;

static const int MISS_EFFECT_CELS = 2;
static const int DASH_CELS = 2;

#define HP_POINT_W 8
#define HP_H 15

// ZUN bug: The actual limit is half of this number, due to another bug in
// hud_hp_render(). (Not a landmine because this number controls when the
// observable heap corruption in debug mode occurs.)
static const int HP_MAX = 96;

typedef enum {
	PTN_SLOT_STG = 0, // stg(_b).ptn
	PTN_SLOT_MIKO = 1, // miko.ptn

	// .PTN slots that can be freely used by bosses. Randomly assigned to the
	// backgrounds behind animated boss entities, as well as the missile
	// sprites from boss3_m.ptn and Kikuri's ripple sprites from tamayen.ptn.
	PTN_SLOT_BOSS_1 = 2,
	PTN_SLOT_BOSS_2 = 3,

	PTN_SLOT_BG_HUD = 5,
	PTN_SLOT_NUMB = 7, // numb.ptn
	PTN_SLOT_COUNT,

	_main_ptn_slot_t_FORCE_INT16 = 0x7FFF
} main_ptn_slot_t;

typedef enum {
	/// stg(_b).ptn
	/// -----------
	PTN_HUD = PTN_ID(PTN_SLOT_STG, 0),
	PTN_SHOT,
	PTN_BLAST, // ???
	PTN_ORB,
	PTN_ORB_last = (PTN_ORB + ORB_CELS - 1),

	// stg.ptn exclusives
	// ------------------
	PTN_CARD_UNUSED,
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

	PTN_ITEM_BOMB,
	PTN_ITEM_POINT,
	// ------------------
	/// -----------

	// miko.ptn
	// --------
	// Facing left
	PTN_MIKO_L = PTN_ID(PTN_SLOT_MIKO, 0),
	PTN_MIKO_L_DASH,
	PTN_MIKO_L_DASH_last = (PTN_MIKO_L_DASH + DASH_CELS - 1),
	PTN_MIKO_L_CAST,
	PTN_MIKO_L_DASH_SHOOT,
	PTN_MIKO_L_DASH_SHOOT_last = (PTN_MIKO_L_DASH_SHOOT + DASH_CELS - 1),
	// Facing right
	PTN_MIKO_R = PTN_ID(PTN_SLOT_MIKO, 10),
	PTN_MIKO_R_DASH,
	PTN_MIKO_R_DASH_last = (PTN_MIKO_R_DASH + DASH_CELS - 1),
	PTN_MIKO_R_CAST,
	PTN_MIKO_R_DASH_SHOOT,
	PTN_MIKO_R_DASH_SHOOT_last = (PTN_MIKO_R_DASH_SHOOT + DASH_CELS - 1),

	PTN_MISS_EFFECT = PTN_ID(PTN_SLOT_MIKO, 20),
	PTN_MISS_EFFECT_last = (PTN_MISS_EFFECT + MISS_EFFECT_CELS - 1),

	PTN_MIKO_MISS,
	PTN_MIKO_MISS_ALTERNATE,
	// --------

	// HUD (snapped backgrounds)
	// -------------------------
	// The usage code doesn't really cap either of these, though...
	PTN_BG_first = PTN_ID(PTN_SLOT_BG_HUD, 0),
	PTN_BG_LIVES = PTN_BG_first,
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

	PTN_BG_TIMER,
	PTN_BG_TIMER_last = last_for_quarters(PTN_BG_TIMER, (TIMER_DIGITS / 2)),

	PTN_BG_HP,
	PTN_BG_HP_last = (PTN_BG_HP + (
		(HP_MAX / ((PTN_W * PTN_H) / (HP_POINT_W * HP_H)))
	) - 1),

	PTN_BG_last = PTN_BG_HP_last,
	// -------------------------

	// Numerals on the TOTLE screen
	// -----------------------------
	PTN_TOTLE_NUMERAL_32 = PTN_ID(PTN_SLOT_NUMB, 0),
	PTN_TOTLE_NUMERAL_32_last = (PTN_TOTLE_NUMERAL_32 + 9),
	PTN_TOTLE_NUMERAL_16,
	PTN_TOTLE_NUMERAL_16_last = last_for_quarters(PTN_TOTLE_NUMERAL_16, 10),
	// -----------------------------
} main_ptn_id_t;

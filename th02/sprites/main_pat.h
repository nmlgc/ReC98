#define MISS_ANIM_CELS 6

/// Sprite sizes
/// ------------

#define DIALOG_BOX_PART_W 32
#define DIALOG_BOX_PART_H 32

#define DIALOG_BOX_LEFT_W 96

#define DIALOG_BOX_LEFT_PARTS (DIALOG_BOX_LEFT_W / DIALOG_BOX_PART_W)
/// ------------

/// Stage-independent pattern numbers for the super_*() functions
/// -------------------------------------------------------------
typedef enum {
	// miko.bft
	// --------
	PAT_PLAYCHAR_STILL = 0,
	PAT_PLAYCHAR_LEFT = 2,
	PAT_PLAYCHAR_RIGHT,
	PAT_PLAYCHAR_MISS,
	PAT_PLAYCHAR_MISS_last = (PAT_PLAYCHAR_MISS + MISS_ANIM_CELS - 1),
	// --------
	// miko32.bft
	// ----------
	PAT_DIALOG_BOX_LEFT_TOP = 34,
	PAT_DIALOG_BOX_LEFT_TOP_last = (
		PAT_DIALOG_BOX_LEFT_TOP + DIALOG_BOX_LEFT_PARTS - 1
	),
	PAT_DIALOG_BOX_MIDDLE_TOP,
	PAT_DIALOG_BOX_RIGHT_TOP,

	PAT_DIALOG_BOX_LEFT_BOTTOM = 42,
	PAT_DIALOG_BOX_LEFT_BOTTOM_last = (
		PAT_DIALOG_BOX_LEFT_BOTTOM + DIALOG_BOX_LEFT_PARTS - 1
	),
	PAT_DIALOG_BOX_MIDDLE_BOTTOM,
	PAT_DIALOG_BOX_RIGHT_BOTTOM,
	// ----------
	// miko16.bft
	// ----------
	PAT_ITEM_POWER = 68,
	PAT_ITEM_POINT,
	PAT_ITEM_BOMB,
	PAT_ITEM_BIGPOWER,
	PAT_OPTION_A,
	PAT_OPTION_B,
	PAT_OPTION_C,
	PAT_ITEM_1UP = 87,
	// ----------

	_main_patnum_t_FORCE_UINT8 = 0xFF
} main_patnum_t;
/// -------------------------------------------------------------

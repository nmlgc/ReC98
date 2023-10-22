#define MISS_ANIM_CELS 6

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

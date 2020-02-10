/// Stage-independent pattern numbers for the super_*() functions
/// -------------------------------------------------------------
/// Since super_entry_bfnt() doesn't take a "start patnum" parameter, the
/// order in which the files are loaded has to match the order here.
typedef enum {
	// reimu16.bft / mari16.bft / mima16.bft / yuka16.bft
	// --------------------------------------------------
	PAT_SHOT_SUB = 22,
	PAT_OPTION = 26,
	// --------------------------------------------------
	// miko16.bft
	// ----------
	PAT_ITEM = 36,
	PAT_EXPLOSION_SMALL = 164,
	// ----------
} main_patnum_t;
/// -------------------------------------------------------------

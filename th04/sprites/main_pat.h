/// Stage-independent pattern numbers for the super_*() functions
/// -------------------------------------------------------------
/// Since super_entry_bfnt() doesn't take a "start patnum" parameter, the
/// order in which the files are loaded has to match the order here.
typedef enum {
	// miko16.bft
	// ----------
	PAT_OPTION_REIMU = 38,
	PAT_OPTION_MARISA,
	PAT_ITEM = 44,
	PAT_EXPLOSION_SMALL = 68,
	// ----------
} main_patnum_t;
/// -------------------------------------------------------------

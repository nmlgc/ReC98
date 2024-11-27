/// View-only High Score menu
/// -------------------------

#include "th04/formats/scoredat/recreate.cpp"
#include "th04/hiscore/scoredat.cpp"

enum hiscore_patnum_t {
	// scnum.bft
	// ---------
	PAT_SCNUM = 0,
	PAT_SCNUM_last = (PAT_SCNUM + 9),
	#if (GAME == 5)
		PAT_SCNUM_UNUSED,
		PAT_SCNUM_UNUSED_last = (PAT_SCNUM_UNUSED + 9),
	#endif
	// ---------
	// hi_m.bft
	// --------
	PAT_RANK_1,
	PAT_RANK_2,
	PAT_RANK_last = (PAT_RANK_1 + (RANK_COUNT * 2) - 1),
	// --------
};

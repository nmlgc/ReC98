// Startup code shared between TH04 and TH05

#if (GAME == 5)
#include "th05/resident.hpp"
#else
#include "th04/resident.hpp"
#endif
#include "th04/op/op.hpp"
#include "th04/formats/cfg.hpp"
#include "th04/snd/snd.h"
#include "th04/shiftjis/fnshared.hpp"
#include "th02/core/initexit.h"
#include "libs/master.lib/pc98_gfx.hpp"
#include <process.h>

inline void op_exit_into_main(bool fade_out_bgm, bool allow_debug) {
	main_cdg_free();
	cfg_save();
#if (GAME == 4)
	// TH04's gaiji are still managed via master.lib, and we'd lose the old
	// ones upon switching the process. Kind of wasteful since MAIN.EXE
	// immediately calls gaiji_backup() to load them back into its heap and it
	// would have been faster to keep them resident, but not too big of a deal.
	gaiji_restore();
#endif
	if(fade_out_bgm) {
		snd_kaja_func(KAJA_SONG_FADE, 10);
	}
	game_exit();
	if(!allow_debug || !resident->debug) {
		execl(BINARY_MAIN, BINARY_MAIN, 0, 0);
	} else {
		execl(BINARY_DEB, BINARY_DEB, 0, 0);
	}
}

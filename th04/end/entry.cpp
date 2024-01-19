#include <process.h>
#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
extern "C" {
#include "th03/formats/cdg.h"
}
#include "th03/formats/cfg_impl.hpp"
#include "th03/core/initexit.h"

resident_t far* resident;

// ZUN bloat: Should be its own translation unit.
resident_t __seg* near cfg_load_resident_ptr(void)
{
	#undef CFG_FN
	extern const char CFG_FN[];
	cfg_t cfg;
	return cfg_load_and_set_resident(cfg, CFG_FN);
}

void pascal near game_exit_and_exec(char* fn)
{
	cdg_free_all();
	graph_hide();
	text_clear();
	#if (GAME != 5)
		gaiji_restore();
	#endif
	game_exit();
	execl(fn, fn, nullptr);
}

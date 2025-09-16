#pragma option -zCSHARED -3

#include "libs/master.lib/master.hpp"
#include "libs/master.lib/pc98_gfx.hpp"
#include "th02/hardware/vplanset.h"
#include "th03/core/initexit.h"

#if (GAME <= 3)
#define mem_assign_paras (288000 >> 4)
#endif

int pascal game_init_main(const unsigned char *pf_fn)
{
	if(mem_assign_dos(mem_assign_paras)) {
		return 1;
	}
#if (GAME >= 4)
	pfsetbufsiz(4096);
#endif
#if (GAME <= 4)
	vram_planes_set();
#endif
	vsync_start();
	egc_start();
	graph_400line();
	js_start();
	pfstart(pf_fn);
#if (GAME >= 4)
	bgm_init(2048);
#endif
	return 0;
}

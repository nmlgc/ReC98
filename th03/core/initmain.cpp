#pragma option -3

extern "C" {
#include <stddef.h>
#include "master.hpp"
#include "th01/hardware/vplanset.h"
#include "th03/core/initexit.h"

int pascal game_init_main(const unsigned char *pf_fn)
{
	__asm { nop; nop; nop; }
	#if (GAME >= 4)
		__asm { nop; }
	#endif
	mem_assign_all();
	__asm { nop; nop; nop; nop; nop; nop; nop; nop; nop; nop; nop; }
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

}

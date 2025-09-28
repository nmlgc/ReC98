#pragma option -zCSHARED -3

#include "libs/master.lib/master.hpp"
#include "libs/master.lib/pc98_gfx.hpp"
#include "th02/hardware/vplanset.h"
#include "th03/core/initexit.h"

#if (GAME <= 3)
#define mem_assign_paras (352000 >> 4)
#endif

int game_init_op(const unsigned char *pf_fn)
{
	if(mem_assign_dos(mem_assign_paras)) {
		return 1;
	}
#if (GAME <= 4)
	vram_planes_set();
#endif
	graph_start();
	graph_clear_both();
#if (GAME >= 4)
	pfsetbufsiz(8192);
#endif
	vsync_start();
	key_beep_off();
	text_systemline_hide();
	text_cursor_hide();
	egc_start();
	js_start();

#if (GAME >= 4)
	if(pf_fn[0]) {
		pfstart(pf_fn);
	}
	bgm_init(1024);
#else
	pfstart(pf_fn);
#endif
	return 0;
}

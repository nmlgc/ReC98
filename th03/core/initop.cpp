#pragma option -3

#include <stddef.h>
#include "platform.h"
#include "x86real.h"
#include "master.hpp"
#include "th01/hardware/vplanset.h"
extern "C" {
#include "th03/core/initexit.h"

#if (GAME <= 3)
	#include "th03/mem.h"
	#define mem_assign_paras MEM_ASSIGN_PARAS_OP
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

}

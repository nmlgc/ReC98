#include "th01/hardware/vplanset.h"

int game_init_op(void)
{
#if GAME >= 4
# define PARAS (mem_assign_paras)
#else
# define PARAS (MEM_ASSIGN_PARAS_OP)
#endif
	if(mem_assign_dos(PARAS)) {
		return 1;
	}
#undef PARAS

	vram_planes_set();
	graph_start();
	graph_clear_both();
	vsync_start();
	key_beep_off();
	text_systemline_hide();
	text_cursor_hide();
	egc_start();
	game_pfopen();
	return 0;
}

#pragma option -zCSHARED

extern "C" {
#include "platform.h"
#include "x86real.h"
#include "master.hpp"
#include "th01/hardware/vplanset.h"
#include "th02/shiftjis/fns.hpp"
#include "th02/mem.h"
#include "th02/core/initexit.h"
#include "th02/formats/pf.hpp"

const char pf_fn[] = PF_FN;

int game_init_op(void)
{
	_asm { nop; nop; nop; }
	mem_assign_all();
	_asm { nop; nop; nop; nop; nop; nop; nop; nop; nop; }
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

}

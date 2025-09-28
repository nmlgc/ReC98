#pragma option -zCSHARED

#include "libs/master.lib/pc98_gfx.hpp"
#include "th02/hardware/vplanset.h"
#include "th02/shiftjis/fns.hpp"
#include "th02/core/initexit.h"
#include "th02/formats/pf.hpp"

const char pf_fn[] = PF_FN;

int game_init_op(void)
{
	// Very specifically fits exactly the High Score viewer's 「東方封魔録」
	// sprite, the title screen animation, the main menu's background image,
	// and the 16 KiB .PI load buffer. (Remember that the game launches
	// directly into the High Score viewer after a demo, and that it wants to
	// only load the 「東方封魔録」 sprite once and then keep it around for the
	// lifetime of the process.)
	if(mem_assign_dos(336416 >> 4)) {
		return 1;
	}

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

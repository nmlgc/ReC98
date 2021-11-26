#pragma option -zCSHARED

extern "C" {
#include "master.hpp"
#include "th01/hardware/vplanset.h"
#include "th02/mem.h"
#include "th02/formats/pf.hpp"

int game_init_main(void)
{
	_asm { nop; nop; nop; }
	mem_assign_all();
	_asm { nop; nop; nop; nop; nop; nop; nop; nop; nop; }
	vram_planes_set();
	vsync_start();
	egc_start();
	graph_400line();
	game_pfopen();
	return 0;
}

}

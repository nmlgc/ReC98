#pragma option -zCSHARED

#include "master.hpp"
#include "th02/hardware/vplanset.h"
#include "th02/mem.h"
extern "C" {
#include "th02/formats/pf.hpp"

int game_init_main(void)
{
	if(mem_assign_dos(MEM_ASSIGN_PARAS_MAIN)) {
		return 1;
	}
	vram_planes_set();
	vsync_start();
	egc_start();
	graph_400line();
	game_pfopen();
	return 0;
}

}

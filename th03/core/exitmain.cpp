#pragma option -zCSHARED -Z

extern "C" {
#include <stddef.h>
#include "platform.h"
#include "x86real.h"
#include "master.hpp"
#include "th03/core/initexit.h"
}

void game_exit_from_mainl_to_main()
{
	pfend();
	graph_accesspage(0);
	graph_showpage(0);
	vsync_end();
	mem_unassign();
	js_end();
	egc_start();
}

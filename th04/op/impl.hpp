#include "x86real.h"
#include "libs/master.lib/master.hpp"
#include "th02/hardware/frmdelay.h"

// Synchronizes both VRAM pages within a 2-frame delay.
inline void sync_pages_and_delay() {
	vsync_Count1 = 0;
	frame_delay(1);

	graph_showpage(1);
	graph_copy_page(0);
	vsync_Count1 = 0;
	frame_delay(1);

	graph_showpage(0);
}

#include "platform.h"
#include "libs/master.lib/master.hpp"
#include "th04/main/slowdown.hpp"

void near slowdown_frame_delay(void)
{
	while(vsync_Count1 < slowdown_factor) {
	}
	vsync_Count1 = 0;
	slowdown_factor = 1;
}

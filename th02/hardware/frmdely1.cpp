#pragma option -zCSHARED

#include "libs/master.lib/master.hpp"
#include "th02/hardware/frmdelay.h"

void pascal frame_delay(int frames)
{
	vsync_Count1 = 0;
	while(vsync_Count1 < frames) {}
}

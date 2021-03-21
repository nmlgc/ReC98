#pragma option -zCSHARED

#include "master.hpp"
#include "th02/hardware/frmdelay.h"

void pascal frame_delay(int frames)
{
	vsync_reset1();
	while(vsync_Count1 < frames) {}
}

#pragma option -zCSHARED

#include "master.hpp"
#include "th02/hardware/frmdelay.h"

void pascal frame_delay_2(int frames)
{
	vsync_Count1 = 0;
	while(vsync_Count1 < frames) {}
}

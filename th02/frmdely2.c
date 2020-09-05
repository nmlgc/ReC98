#pragma codeseg seg2

#include "libs/master.lib/master.h"
#include "th02/hardware/frmdelay.h"

void pascal far frame_delay_2(int frames)
{
	vsync_reset1();
	while(vsync_Count1 < frames) {}
}

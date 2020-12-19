#pragma codeseg SHARED

#include "libs/master.lib/master.h"
#include "th02/hardware/frmdelay.h"

void pascal frame_delay(int frames)
{
	vsync_reset1();
	while(vsync_Count1 < frames) {}
}

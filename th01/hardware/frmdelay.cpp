#include "th01/hardware/vsync.hpp"
#include "th01/hardware/frmdelay.h"

void frame_delay(unsigned int frames)
{
	while(z_vsync_Count1 < frames) {}
	z_vsync_Count1 = 0;
}

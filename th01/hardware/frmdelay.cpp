#include "th01/hardware/vsync.hpp"
extern "C" {
#include "th01/hardware/frmdelay.h"
}

#define z_vsync_reset1() (z_vsync_Count1 = 0)
// #define z_vsync_reset2() (vsync_unused = 0)

void frame_delay(unsigned int frames)
{
	while(z_vsync_Count1 < frames) {}
	z_vsync_reset1();
}

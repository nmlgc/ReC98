#include "th01/hardware/vsync.h"

#define z_vsync_reset1() (vsync_frame = 0)
// #define z_vsync_reset2() (vsync_unused = 0)

void far frame_delay(unsigned int frames)
{
	while(vsync_frame < frames) {}
	z_vsync_reset1();
}

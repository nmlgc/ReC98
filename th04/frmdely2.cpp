// Temporary workaround copy of TH02's version, until we can put it into the
// regular SHARED segment for TH04's OP.EXE as well.
#pragma option -zCSHARED_

#include "master.hpp"
#include "th02/hardware/frmdelay.h"

void pascal frame_delay_2(int frames)
{
	vsync_Count1 = 0;
	while(vsync_Count1 < frames) {}
}

#pragma option -zCSHARED -k-

#include "master.hpp"
#include "th02/hardware/frmdelay.h"

void pascal frame_delay(int frames)
{
	_BX = _SP;
	asm { mov	bx, ss:[bx+4]; } /* = */ (frames);
	vsync_Count1 = 0;
	while(vsync_Count1 < _BX) {}
}

#pragma codestring "\x00"

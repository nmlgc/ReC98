#pragma option -zCSHARED_ -k-

extern "C" {
#include "master.hpp"
#include "th02/hardware/frmdelay.h"

void pascal frame_delay(int frames)
{
	_BX = _SP;
	_asm { mov bx, ss:[bx+4]; } /* = */ (frames);
	vsync_reset1();
	while(vsync_Count1 < _BX) {}
}

#pragma codestring "\x00"

}

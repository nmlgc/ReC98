#pragma option -zCPLATFORM_TEXT

#include "platform/x86real/pc98/vblank.hpp"
#include "x86real.h"

bool vblank_in(void)
{
	return ((_inportb_(0xA0) & 0x20) ? true : false);
}

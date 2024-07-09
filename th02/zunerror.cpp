#pragma option -zCSHARED

#include "x86real.h"
#include "th02/core/zunerror.h"

void pascal zun_error(zun_error_t err)
{
	_AX = err;
	geninterrupt(0x59);
}

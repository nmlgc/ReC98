#pragma codeseg SHARED

#include "th02/core/zunerror.h"

void pascal zun_error(zun_error_t err)
{
	__asm	mov ax, err;
	__asm	int 0x59
}

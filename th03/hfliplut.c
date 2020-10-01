#pragma codeseg seg2
#pragma option -k-

#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "decomp.h"
#include "th03/formats/hfliplut.h"

void hflip_lut_generate(void)
{
	#define p (dots8_t near *)(_DI)
	_AX = 0;
	p = hflip_lut;
	_DL ^= _DL;
	goto set_and_loop;

permutation_loop:
	_DL ^= _DL;
	_CX = BYTE_DOTS;
	generation_loop: __asm {
		rol 	al, 1
		rcr 	dl, 1
		loop	generation_loop
	}

set_and_loop:
	*(p++) = _DL;
	_AL++;
	if(!FLAGS_ZERO) {
		goto permutation_loop;
	}
	#undef p
}

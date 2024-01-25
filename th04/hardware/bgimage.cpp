#pragma option -zCSHARED_ -k-

#include <mem.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "decomp.hpp"
#include "master.hpp"
#include "platform/x86real/flags.hpp"
extern "C" {
#include "th04/hardware/bgimage.hpp"

inline void memcpy_movsd(
	uint16_t, uint16_t dst_off, uint16_t, uint16_t src_off, size_t size
) {
	_SI = src_off;
	_DI = dst_off;
	_CX = (size / sizeof(uint32_t));
	REP MOVSD;
}

#define bgimage_push() _asm { \
	push	SEG_PLANE_E; \
	push	word ptr [bgimage.E]; \
	push	SEG_PLANE_G; \
	push	word ptr [bgimage.G]; \
	push	SEG_PLANE_R; \
	push	word ptr [bgimage.R]; \
	push	SEG_PLANE_B; \
	push	word ptr [bgimage.B]; \
}

void bgimage_snap(void)
{
	if(bgimage.B == nullptr) {
		bgimage.B = HMem<dots8_t>::alloc(PLANE_SIZE);
		bgimage.R = HMem<dots8_t>::alloc(PLANE_SIZE);
		bgimage.G = HMem<dots8_t>::alloc(PLANE_SIZE);
		bgimage.E = HMem<dots8_t>::alloc(PLANE_SIZE);
	}

	_DL = PLANE_COUNT;
	_asm { push	ds; }
	bgimage_push();
	do {
		_asm { pop 	es; }
		_asm { pop 	ds; }
		memcpy_movsd(_ES, 0, _DS, 0, PLANE_SIZE);
		_DL--;
	} while(!FLAGS_ZERO);
	_asm { pop 	ds; }
}

void bgimage_put(void)
{
	_DL = PLANE_COUNT;
	_asm { push	ds; }
	bgimage_push();
	do {
		_asm { pop 	ds; }
		_asm { pop 	es; }
		memcpy_movsd(_ES, 0, _DS, 0, PLANE_SIZE);
		_DL--;
	} while(!FLAGS_ZERO);
	_asm { pop 	ds; }
}
#pragma codestring "\x90"

void bgimage_free(void)
{
	if(bgimage.B != nullptr) {
		HMem<dots8_t>::free(bgimage.B);
		HMem<dots8_t>::free(bgimage.R);
		HMem<dots8_t>::free(bgimage.G);
		HMem<dots8_t>::free(bgimage.E);
		bgimage.B = nullptr;
	}
}

}

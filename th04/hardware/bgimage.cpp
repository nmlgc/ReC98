#pragma codeseg SHARED_
#pragma option -k-

extern "C" {
#include <mem.h>
#include <stddef.h>
#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "decomp.hpp"
#include "master.hpp"
#include "th04/hardware/bgimage.hpp"

inline void memcpy_movsd(
	uint16_t, uint16_t dst_off, uint16_t, uint16_t src_off, size_t size
) {
	_SI = src_off;
	_DI = dst_off;
	_CX = (size / sizeof(uint32_t));
	REP MOVSD;
}

#define bgimage_push() __asm { \
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
	if(bgimage.B == NULL) {
		bgimage.B = reinterpret_cast<dots8_t __seg *>(hmem_allocbyte(PLANE_SIZE));
		bgimage.R = reinterpret_cast<dots8_t __seg *>(hmem_allocbyte(PLANE_SIZE));
		bgimage.G = reinterpret_cast<dots8_t __seg *>(hmem_allocbyte(PLANE_SIZE));
		bgimage.E = reinterpret_cast<dots8_t __seg *>(hmem_allocbyte(PLANE_SIZE));
	}

	_DL = PLANE_COUNT;
	__asm {	push	ds; }
	bgimage_push();
	do {
		__asm { pop 	es; }
		__asm { pop 	ds; }
		memcpy_movsd(_ES, 0, _DS, 0, PLANE_SIZE);
		_DL--;
	} while(!FLAGS_ZERO);
	__asm { pop 	ds; }
}

void bgimage_put(void)
{
	_DL = PLANE_COUNT;
	__asm {	push	ds; }
	bgimage_push();
	do {
		__asm { pop 	ds; }
		__asm { pop 	es; }
		memcpy_movsd(_ES, 0, _DS, 0, PLANE_SIZE);
		_DL--;
	} while(!FLAGS_ZERO);
	__asm { pop 	ds; }
}
#pragma codestring "\x90"

void bgimage_free(void)
{
	if(bgimage.B != NULL) {
		hmem_free(FP_SEG(bgimage.B));
		hmem_free(FP_SEG(bgimage.R));
		hmem_free(FP_SEG(bgimage.G));
		hmem_free(FP_SEG(bgimage.E));
		bgimage.B = NULL;
	}
}

}

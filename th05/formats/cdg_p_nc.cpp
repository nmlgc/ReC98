#pragma codeseg SHARED_

extern "C" {
#include <stddef.h>
#include <dos.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "decomp.h"
#include "th04/formats/cdg.h"
}

void pascal cdg_put_nocolors_8(screen_x_t left, vram_y_t top, int slot)
{
	#define _DI	static_cast<vram_offset_t>(_DI)
	#define cdg	reinterpret_cast<cdg_t near *>(_SI)
	#define stride	static_cast<vram_byte_amount_t>(_DX)
	#define tmp	static_cast<upixel_t>(_AX)
	#define top_tmp	static_cast<pixel_t>(_CX)
	register vram_byte_amount_t cdg_dword_w;

	// cdg = cdg_slots[slot];
	_SI = slot;
	_SI <<= 4;	// MODDERS: Should be sizeof(cdg_t);
	_SI += FP_OFF(cdg_slots);

	// _DI = (vram_offset_shift(left, 0) + cdg->offset_at_bottom_left);
	// [top] is calculated into the segment later, not the offset.
	_DI = left;
	_DI >>= 3;
	_DI += cdg->offset_at_bottom_left;

	tmp = cdg->vram_dword_w;
	cdg_dword_w = tmp;
	// One additional full line, since we move from the end of one CDG line to
	// the beginning of the previous one.
	stride = ((tmp * 4) + ROW_SIZE);

	// _ES = (SEG_PLANE_B + (top * (ROW_SIZE / 16)));
	tmp = top;
	top_tmp = tmp;
	_ES = (((tmp * 4) + top_tmp) + SEG_PLANE_B);

	__asm { push ds };
	_DS = reinterpret_cast<seg_t>(cdg->seg_alpha());
	_SI = 0;

	do {
		_CX = cdg_dword_w;
		REP MOVSD;
		_DI -= stride;
	} while(!FLAGS_SIGN);

	__asm { pop ds };

	#undef top_tmp
	#undef tmp
	#undef stride
	#undef cdg
	#undef _DI
}

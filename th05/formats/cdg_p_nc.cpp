#pragma option -zCSHARED_

#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
extern "C" {
#include "th04/formats/cdg.h"
}
#include "th04/formats/cdg_impl.hpp"

void pascal cdg_put_nocolors_8(screen_x_t left, vram_y_t top, int slot)
{
	#define _DI	static_cast<vram_offset_t>(_DI)
	#define cdg	reinterpret_cast<CDG near *>(_SI)
	#define stride	static_cast<vram_byte_amount_t>(_DX)
	#define tmp	static_cast<upixel_t>(_AX)
	#define cdg_dword_w	static_cast<vram_byte_amount_t>(_BX)

	cdg = cdg_slot_offset(slot);
	_DI = cdg_dst_offset(_DI, cdg, left);

	tmp = cdg->vram_dword_w;
	cdg_dword_w = tmp;
	// One additional full line, since we move from the end of one CDG line to
	// the beginning of the previous one.
	stride = ((tmp * 4) + ROW_SIZE);

	tmp = cdg_dst_segment(tmp, top, _CX);
	_ES = tmp;
	_asm { push	ds };
	reinterpret_cast<dots8_t __seg *>(_DS) = cdg->seg_alpha();
	cdg_put_plane_raw(_ES, _DI, _DS, 0, cdg_dword_w);
	_asm { pop 	ds };

	#undef cdg_dword_w
	#undef tmp
	#undef stride
	#undef cdg
	#undef _DI
}

#pragma option -zCSHARED_

extern "C" {
#include <stddef.h>
#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "th04/formats/cdg.h"
#include "th04/formats/cdg_impl.hpp"
}

void pascal cdg_put_noalpha_8(screen_x_t left, vram_y_t top, int slot)
{
	#define cdg	reinterpret_cast<cdg_t near *>(_SI)
	#define tmp	static_cast<upixel_t>(_AX)
	#define cdg_dword_w	static_cast<vram_byte_amount_t>(_BP)
	#define dst_offset	static_cast<vram_byte_amount_t>(_BX)
	#define planes_left	static_cast<char>(_AL)
	register vram_byte_amount_t stride;

	__asm { push ds };

	_AX = cdg_dst_segment(_AX, top, _BX);
	_ES = _AX;
	_AX += (SEG_PLANE_E - SEG_PLANE_B); // AX == SEG_PLANE_E
	__asm { push	ax; }
	_AX -= SEG_PLANE_DIST_E; // AX == SEG_PLANE_E
	__asm { push	ax; }
	_AX -= SEG_PLANE_DIST_BRG; // AX == SEG_PLANE_R
	__asm { push	ax; }

	cdg = cdg_slot_offset(slot);
	dst_offset = cdg_dst_offset(dst_offset, cdg, left);

	tmp = cdg->vram_dword_w;
	cdg_dword_w = tmp;
	// One additional full line, since we move from the end of one CDG line to
	// the beginning of the previous one.
	stride = ((tmp * 4) + ROW_SIZE);

	reinterpret_cast<dots8_t __seg *>(tmp) = cdg->seg_colors();
	_DS = tmp;
	_SI = 0;
	planes_left = PLANE_COUNT;
	__asm { cld; }
	__asm { nop; }
	do {
		cdg_put_plane_raw(_ES, dst_offset, _DS, _SI, cdg_dword_w);
		// SI is now at the beginning of the next plane
		--planes_left;
		if(FLAGS_ZERO) {
			break;
		}
		__asm { pop	es; }
	} while(1);

	__asm { pop ds };

	#undef planes_left
	#undef dst_offset
	#undef cdg_dword_w
	#undef tmp
	#undef cdg
}
#pragma codestring "\x90"

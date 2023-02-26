#pragma option -zCSHARED_

#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "decomp.hpp"
#include "master.hpp"
#include "platform/x86real/flags.hpp"
extern "C" {
#include "th01/hardware/egc.h"

#define graph_accesspage_1() \
	outportb2(0xA6, 1);

#define graph_accesspage_0()  \
	_AX ^= _AX; \
	asm { out 0xA6, al; }

extern vram_word_amount_t egcrect_w;

static void near egc_start_copy(void);

void DEFCONV egc_copy_rect_1_to_0_16(
	screen_x_t left, vram_y_t top, pixel_t w, pixel_t h
)
{
	#define vo_tmp	_BX // vram_offset_t
	#define first_bit	_CX
	#define stride	static_cast<vram_byte_amount_t>(_BP)
	#define w_tmp	static_cast<vram_word_amount_t>(_AX)
	#define rows_remaining	static_cast<pixel_t>(_BX)
	#define dots	static_cast<dots16_t>(_DX)

	#if (GAME == 4)
		// TH04 wants to blit using a forward STOSW (DF = 0)
		_asm { cld; }
	#endif
	egc_start_copy();
	egc_setrop(EGC_COMPAREREAD | EGC_WS_ROP | EGC_RL_MEMREAD | 0xF0);

	// Using inline assembly rather than register pseudovariables to prevent
	// parameters from being moved to the SI register
	asm { mov	ax, left; }
	asm { mov	dx, top; }

	vo_tmp = _AX;
	static_cast<vram_offset_t>(vo_tmp) >>= EGC_REGISTER_BITS;
	asm { shl	bx, 1; }
	_DX <<= 6;
	vo_tmp += _DX;
	_DX >>= 2;
	vo_tmp += _DX;

	_DI = vo_tmp;
	_AX &= EGC_REGISTER_MASK;
	first_bit = _AX;

	w_tmp = ((_AX + w) >> EGC_REGISTER_BITS);
	if(first_bit) {
		w_tmp++;
	}
	egcrect_w = w_tmp;

	_CX = (ROW_SIZE / EGC_REGISTER_SIZE);
	_CX -= w_tmp;
	asm { shl	cx, 1; }
	rows_remaining = h;
	stride = _CX;
	_ES = SEG_PLANE_B;

	do {
		_CX = egcrect_w;
		put_loop: {
			#if (GAME == 5)
				_DI |= _DI;
				if((!FLAGS_SIGN) && (_DI < PLANE_SIZE)) {
					graph_accesspage_1();	dots = peek(_ES, _DI);
					graph_accesspage_0();	_poke_(_ES, _DI, dots);
				}
				_DI += 2;
			#else
				graph_accesspage_1();  	dots = peek(_ES, _DI);
				graph_accesspage_0();	_AX = dots; asm { stosw; }
			#endif
			asm { loop put_loop; }
		}
		_DI += stride;
		rows_remaining--;
	} while(!FLAGS_SIGN);
	egc_off();
}

#pragma codestring "\x90"
#pragma option -k-

static void near egc_start_copy(void)
{
	_asm {
		push 	es
		push 	0
		pop  	es
		pushf
		cli

		// The EGC does in fact require an active GRCG in TDW mode.
		// (See PC-9801 Programmers' Bible, p. 456)
		mov  	al, GC_TDW
		out  	0x7C, al	// grcg_setmode()

		// According to MEMSYS.TXT, GRCG mode changes should always be
		// reflected in this memory location, for compatibility with interrupt
		// routines?
		mov  	byte ptr es:[0x495], al
		popf
		pop es
	}
	graph_egc_on();
	outport(EGC_ACTIVEPLANEREG, 0xFFF0);
	egc_selectpat();
	outport(EGC_MASKREG, 0xFFFF);
	_DX = EGC_ADDRRESSREG;
	outport(_DX, (_AX - _AX)); // :zunpet:
	outport(EGC_BITLENGTHREG, 0xF);
}

#pragma codestring "\x90"

}

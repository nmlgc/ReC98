// Second TH05 .PI C++ translation unit.

#pragma option -zCSHARED_

#include <stddef.h>
#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
extern "C" {
#include "th05/formats/pi.hpp"
}
#include "th05/formats/pi_impl.hpp"

extern dots16_t near *pi_mask_ptr;
extern unsigned int pi_mask_y;

// Additionally takes:
// • `void far *pi_buf` in ES:SI
// • `pixel_t h` in DI
void pascal near pi_put_8_rowloop(
	screen_x_t left, vram_y_t top, pixel_t w, size_t stride_packed
);

#pragma option -k-

// MODDERS: Just give egc_setup_copy() a mask parameter and remove this
// abomination of a function.
void near pi_mask_setup_egc_and_advance(void)
{
	#define mask_ptr   	_BX

	egc_on();
	outport2(EGC_ACTIVEPLANEREG, 0xFFF0);
	outport2(EGC_READPLANEREG, 0xFF);
	// EGC_COMPAREREAD | EGC_WS_PATREG | EGC_RL_MEMREAD
	outport2(EGC_MODE_ROP_REG, 0x3100);
	outport(EGC_ADDRRESSREG, keep_0(0));
	outport2(EGC_BITLENGTHREG, 0xF);

	mask_ptr = reinterpret_cast<uint16_t>(pi_mask_ptr);
	_AX = (pi_mask_y & (PI_MASK_H - 1));
	// Turbo C++ is too smart to emit this instruction with pseudo-registers!
	asm { shl	ax, 1; }
	mask_ptr += _AX;
	outport(EGC_MASKREG, *reinterpret_cast<dots16_t near *>(mask_ptr));
	pi_mask_y++;

	#undef mask_ptr
}

#pragma option -k

int DEFCONV pi_load(int slot, const char *fn)
{
	_DI = slot;
	/* TODO: Replace with the decompiled call
	 * 	pi_free(slot);
	 * once the segmentation allows us to, if ever */
	asm { push di; push cs; call near ptr pi_free; }

	/* Actually, also replace this garbage with simply
	 * 	return graph_pi_load_pack(fn, &pi_headers[slot], &pi_buffers[slot]);
	 * Even Turbo C++ can generate better code than *that*. */
	_SI = _DI;
	_SI <<= 2;	// *= sizeof(void far *)
	_SI += reinterpret_cast<uint16_t>(pi_buffers);
	imul_reg_to_reg(_DI, _DI, sizeof(PiHeader));
	_DI += reinterpret_cast<uint16_t>(pi_headers);
	return graph_pi_load_pack(
		fn,
		reinterpret_cast<PiHeader near *>(_DI),
		reinterpret_cast<void far *near *>(_SI)
	);
}

void DEFCONV pi_put_8(screen_x_t left, vram_y_t top, int slot)
{
	#define rowloop_func _asm { \
		push	left;	/* left */ \
		push	top; 	/* top */ \
		mov 	ax, word ptr pi_headers[di].xsize; \
		push	ax; 	/* w */ \
		shr 	ax, 1; \
		push	ax; 	/* stride_packed */ \
		mov 	di, word ptr pi_headers[di].ysize; \
		call	near ptr pi_put_8_rowloop; \
	}
	pi_put_impl(slot, rowloop_func);
	#undef rowloop_func
}

#pragma codestring "\x90"

void pascal pi_put_quarter_8(
	screen_x_t left, vram_y_t top, int slot, int quarter
)
{
	#define rowloop_func _asm { \
		push	left; \
		push	top; \
		push	PI_QUARTER_W; \
		push	(PI_W / 2); \
		mov 	di, PI_QUARTER_H; \
		call	near ptr pi_put_8_rowloop; \
	}
	pi_put_quarter_impl(slot, quarter, rowloop_func);
	#undef rowloop_func
}

// Second TH05 .PI C++ translation unit.

#pragma codeseg SHARED_

extern "C" {
#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "th05/formats/pi.h"
#include "th05/formats/pi_impl.hpp"

// Additionally takes:
// • `void far *pi_buf` in ES:SI
// • `pixel_t h` in DI
void pascal near pi_put_8_rowloop(
	screen_x_t left, vram_y_t top, pixel_t w, size_t stride_packed
);

int DEFCONV pi_load(int slot, const char *fn)
{
	_DI = slot;
	/* TODO: Replace with the decompiled call
	 * 	pi_free(slot);
	 * once the segmentation allows us to, if ever */
	__asm { push di; push cs; call near ptr pi_free; }

	/* Actually, also replace this garbage with simply
	 * 	return graph_pi_load_pack(fn, &pi_headers[slot], &pi_buffers[slot]);
	 * Even Turbo C++ can generate better code than *that*. */
	_SI = _DI;
	_SI <<= 2;	// *= sizeof(void far *)
	_SI += reinterpret_cast<uint16_t>(pi_buffers);
	imul_di(sizeof(PiHeader));
	_DI += reinterpret_cast<uint16_t>(pi_headers);
	return graph_pi_load_pack(
		fn,
		reinterpret_cast<PiHeader near *>(_DI),
		reinterpret_cast<void far *near *>(_SI)
	);
}

void DEFCONV pi_put_8(screen_x_t left, vram_y_t top, int slot)
{
	#define rowloop_func __asm { \
		push	left;	/* left */ \
		push	top; 	/* top */ \
		mov 	ax, word ptr pi_headers[di].xsize; \
		push	ax; 	/* w */ \
		shr 	ax, 1; \
		push	ax; 	/* stride_packed */ \
		mov 	di, word ptr pi_headers[di].ysize; \
		call	near ptr pi_put_8_rowloop; \
	}
	pi_put_impl(left, top, slot, rowloop_func);
	#undef rowloop_func
}

#pragma codestring "\x90"

void pascal pi_put_quarter_8(
	screen_x_t left, vram_y_t top, int slot, int quarter
)
{
	#define rowloop_func __asm { \
		push	left; \
		push	top; \
		push	PI_QUARTER_W; \
		push	(PI_W / 2); \
		mov 	di, PI_QUARTER_H; \
		call	near ptr pi_put_8_rowloop; \
	}
	pi_put_quarter_impl(left, top, slot, quarter, rowloop_func);
	#undef rowloop_func
}

}

// First TH05 .PI C++ translation unit.

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
// • `int mask_id` in AX
// • `void far *pi_buf` in ES:SI
// • `pixel_t h` in DI
void pascal near pi_put_masked_8_rowloop(
	screen_x_t left, vram_y_t top, pixel_t w, size_t stride_packed
);

void pascal pi_put_masked_8(
	screen_x_t left, vram_y_t top, int slot, int mask_id
)
{
	#define rowloop_func __asm { \
		push	left;	/* left */ \
		push	top; 	/* top */ \
		mov 	ax, word ptr pi_headers[di].xsize; \
		push	ax; 	/* w */ \
		shr 	ax, 1; \
		push	ax; 	/* stride_packed */ \
		mov 	di, word ptr pi_headers[di].ysize; \
		mov 	ax, mask_id; \
		call	near ptr pi_put_masked_8_rowloop; \
	}
	pi_put_impl(left, top, slot, rowloop_func);
	#undef rowloop_func
}

void pascal pi_put_quarter_masked_8(
	screen_x_t left, vram_y_t top, int slot, int quarter, int mask_id
)
{
	#define rowloop_func __asm { \
		mov 	di, PI_QUARTER_H; \
		push	left; \
		push	top; \
		push	PI_QUARTER_W; \
		push	(PI_W / 2); \
		mov 	ax, mask_id; \
		call	near ptr pi_put_masked_8_rowloop; \
	}
	pi_put_quarter_impl(left, top, slot, quarter, rowloop_func);
	#undef rowloop_func
}

#pragma codestring "\x90"

}

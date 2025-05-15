/// Low-level implementations for the optimized byte-aligned sprite blitter
/// -----------------------------------------------------------------------

#include "platform/x86real/pc98/blitter.hpp"
#include "x86real.h"

static const upixel_t UNROLL_H = 8;

#define FOREACH_WIDTH \
	X(8) \
	X(16) \

// Supported widths
// ----------------
// Refer to blitter_body() for the register allocation.

// We want to use a pseudoregister for optimal code generation, but Turbo C++
// 4.0J insists on seeing the template type in the function arguments. So, we
// just pass a dummy value we never actually use.
template <class RowDots> inline void single_write(RowDots *) {
	*((RowDots __es *)(_DI)) = *((RowDots __ds *)(_SI));
}

template <class RowDots> inline void single_or(RowDots *) {
	*((RowDots __es *)(_DI)) |= *((RowDots __ds *)(_SI));
}
// ----------------

// Row blitters
// ------------

#define row(func_single, type) \
	func_single(reinterpret_cast<type *>(0)); _SI += _DX; _DI += ROW_SIZE;

#define blitter_body(plane_seg, sprite, func_row, row_p1, row_p2) { \
	register int16_t loops_unrolled = blit_state.loops_unrolled; \
	_SI = FP_OFF(sprite); \
	_SI += blit_state.sprite_offset; \
	_DI = blit_state.vo; \
	_DX = blit_state.sprite_w; \
	_BX = blit_state.loops_remainder; \
	\
	/* Turbo C++ 4.0J does not back up DS if the function mutates it. */ \
	/* [blit_state] can't be accessed anymore beyond this point! */ \
	_asm { push ds; } \
	_DS = FP_SEG(sprite); \
	_ES = plane_seg; \
	\
	static_assert(UNROLL_H == 8); \
	switch(_BX) { \
	case 0: do { func_row(row_p1, row_p2) \
	case 7:      func_row(row_p1, row_p2) \
	case 6:      func_row(row_p1, row_p2) \
	case 5:      func_row(row_p1, row_p2) \
	case 4:      func_row(row_p1, row_p2) \
	case 3:      func_row(row_p1, row_p2) \
	case 2:      func_row(row_p1, row_p2) \
	case 1:      func_row(row_p1, row_p2) \
	/*       */} while(--loops_unrolled > 0); \
	} \
	\
	_asm { pop ds; } \
}
// ----------------

// Non-`const` because BLITPERF wants to patch these.
extern Blitter BLITTER_FUNCS[];

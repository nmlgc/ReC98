/// Low-level implementations for the optimized byte-aligned sprite blitter
/// -----------------------------------------------------------------------

#include "platform/x86real/pc98/blitter.hpp"
#include "x86real.h"

static const upixel_t UNROLL_H = 8;

#define FOREACH_WIDTH \
	X(8) \
	X(16) \

// Displaced memory manipulation
// -----------------------------
// Uses MOV instructions with displacements for wider sprites. Supports both
// `write` and `or`.

// We want to use a pseudoregister for optimal code generation, but Turbo C++
// 4.0J insists on seeing the template type in the function arguments. So, we
// just pass a dummy value we never actually use.
template <class RowDots> inline void d_write(RowDots *) {
	*((RowDots __es *)(_DI)) = *((RowDots __ds *)(_SI));
}

template <class RowDots> inline void d_or(RowDots *) {
	*((RowDots __es *)(_DI)) |= *((RowDots __ds *)(_SI));
}

#define displaced(func_single, type) \
	func_single(reinterpret_cast<type *>(0))
// -----------------------------

// String unit manipulation
// ------------------------
// Uses individual MOVS instructions. Only supports `write`.

inline void u_8(void) {
	__emit__(0xA4); // MOVSB
}

inline void u_16(void) {
	__emit__(0xA5); // MOVSW
}
// ------------------------

// Stationary rows
// ---------------
// SI and DI stay constant throughout the memory manipulation of each row.

#define stationary_impl(plane_seg, sprite, func, row_p1, row_p2) { \
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
	case 0: do { func(row_p1, row_p2); _SI += _DX; _DI += ROW_SIZE; \
	case 7:      func(row_p1, row_p2); _SI += _DX; _DI += ROW_SIZE; \
	case 6:      func(row_p1, row_p2); _SI += _DX; _DI += ROW_SIZE; \
	case 5:      func(row_p1, row_p2); _SI += _DX; _DI += ROW_SIZE; \
	case 4:      func(row_p1, row_p2); _SI += _DX; _DI += ROW_SIZE; \
	case 3:      func(row_p1, row_p2); _SI += _DX; _DI += ROW_SIZE; \
	case 2:      func(row_p1, row_p2); _SI += _DX; _DI += ROW_SIZE; \
	case 1:      func(row_p1, row_p2); _SI += _DX; _DI += ROW_SIZE; \
	/*       */} while(--loops_unrolled > 0); \
	} \
	\
	_asm { pop ds; } \
}
// ---------------

// Marching rows
// -------------
// SI and DI are adjusted for every byte written. The end of each row has to
// add the difference.

inline void march_advance(uint16_t width) {
	__emit__(0x03, 0xF2); // ADD SI, DX

	// ADD DI, (ROW_SIZE - (width / BYTE_DOTS))
	__emit__(0x83, 0xC7, static_cast<uint8_t>(ROW_SIZE - (width / BYTE_DOTS)));
}

#define march_impl(plane_seg, sprite, func, width) { \
	register int16_t loops_unrolled = blit_state.loops_unrolled; \
	_SI = FP_OFF(sprite); \
	_SI += blit_state.sprite_offset; \
	_DI = blit_state.vo; \
	_DX = blit_state.sprite_w; \
	_DX -= (width / BYTE_DOTS); \
	_BX = blit_state.loops_remainder; \
	__emit__(0xFC); /* CLD */ \
	\
	/* Turbo C++ 4.0J does not back up DS if the function mutates it. */ \
	/* [blit_state] can't be accessed anymore beyond this point! */ \
	_asm { push ds; } \
	_DS = FP_SEG(sprite); \
	_ES = plane_seg; \
	\
	static_assert(UNROLL_H == 8); \
	switch(_BX) { \
	case 0: do { func(); march_advance(width); \
	case 7:      func(); march_advance(width); \
	case 6:      func(); march_advance(width); \
	case 5:      func(); march_advance(width); \
	case 4:      func(); march_advance(width); \
	case 3:      func(); march_advance(width); \
	case 2:      func(); march_advance(width); \
	case 1:      func(); march_advance(width); \
	/*       */} while(--loops_unrolled > 0); \
	} \
	_asm { pop ds; } \
}
// -------------

// Non-`const` because BLITPERF wants to patch these.
extern Blitter BLITTER_FUNCS[];

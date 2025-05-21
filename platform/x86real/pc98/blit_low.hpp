/// Low-level implementations for the optimized byte-aligned sprite blitter
/// -----------------------------------------------------------------------
/// All low-level functions spell out opcode bytes for multiple reasons:
/// • Turbo C++ 4.0J doesn't allow inline assembly in inlined functions.
/// • Its inline assembler also doesn't support ≥386 instructions.
/// • If we ever decide to move blitter prolog and epilog code into a shared
///   function, we avoid additional PUSH and POP instructions for SI and DI in
///   the core memory manipulation functions.

#include "platform/x86real/pc98/blitter.hpp"
#include "x86real.h"

#define FOREACH_WIDTH \
	X(8) \
	X(16) \

// Row unrolling via Duff's Device
// -------------------------------

inline void unroll_setup(upixel_t unroll_h) {
	_DX = blit_state.h_clipped; \
	_BX = _DX;
	_DX += (unroll_h - 1);

	// Generates better code than using /=...
	if(unroll_h == 8) {
		_DX >>= 3;
	}
	_BX &= (unroll_h - 1);
}
// -------------------------------

// Displaced memory manipulation
// -----------------------------
// Uses MOV instructions with displacements for wider sprites. Supports both
// `write` and `or`.

inline void d_8(uint8_t op, uint8_t) {
	__emit__(0x8A, 0x04); // MOV AL, [SI]
	__emit__(0x26, (op + 0x08), 0x05); // op ES:DI, AL
}

inline void d_16(uint8_t op, uint8_t) {
	__emit__(0x8B, 0x04); // MOV AX, [SI]
	__emit__(0x26, (op + 0x09), 0x05); // op ES:DI, AX
}
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

inline void stationary_next(void) {
	__emit__(0x03, 0xF1); // ADD SI, CX
	__emit__(0x83, 0xC7, ROW_SIZE); // ADD DI, ROW_SIZE
}

#define stationary_impl(plane_seg, sprite, func, row_p1, row_p2) { \
	unroll_setup(8); /* Must come first because it uses CL on 8086. */ \
	_SI = FP_OFF(sprite); \
	_SI += blit_state.sprite_offset; \
	_DI = blit_state.vo; \
	_CX = blit_state.sprite_w; \
	\
	/* Turbo C++ 4.0J does not back up DS if the function mutates it. */ \
	/* [blit_state] can't be accessed anymore beyond this point! */ \
	__emit__(0x1E); /* PUSH DS */ \
	_DS = FP_SEG(sprite); \
	_ES = plane_seg; \
	\
	switch(_BX) { \
	case 0: do { func(row_p1, row_p2); stationary_next(); \
	case 7:      func(row_p1, row_p2); stationary_next(); \
	case 6:      func(row_p1, row_p2); stationary_next(); \
	case 5:      func(row_p1, row_p2); stationary_next(); \
	case 4:      func(row_p1, row_p2); stationary_next(); \
	case 3:      func(row_p1, row_p2); stationary_next(); \
	case 2:      func(row_p1, row_p2); stationary_next(); \
	case 1:      func(row_p1, row_p2); stationary_next(); \
	/*       */} while(--static_cast<int16_t>(_DX) > 0); \
	} \
	\
	__emit__(0x1F); /* POP DS */ \
}
// ---------------

// Marching rows
// -------------
// SI and DI are adjusted for every byte written. The end of each row has to
// add the difference.

inline void march_advance(uint16_t width) {
	__emit__(0x03, 0xF1); // ADD SI, CX

	// ADD DI, (ROW_SIZE - (width / BYTE_DOTS))
	__emit__(0x83, 0xC7, static_cast<uint8_t>(ROW_SIZE - (width / BYTE_DOTS)));
}

#define march_impl(plane_seg, sprite, func, width) { \
	unroll_setup(8); /* Must come first because it uses CL on 8086. */ \
	_SI = FP_OFF(sprite); \
	_SI += blit_state.sprite_offset; \
	_DI = blit_state.vo; \
	_CX = blit_state.sprite_w; \
	_CX -= (width / BYTE_DOTS); \
	__emit__(0xFC); /* CLD */ \
	\
	/* Turbo C++ 4.0J does not back up DS if the function mutates it. */ \
	/* [blit_state] can't be accessed anymore beyond this point! */ \
	__emit__(0x1E); /* PUSH DS */ \
	_DS = FP_SEG(sprite); \
	_ES = plane_seg; \
	\
	switch(_BX) { \
	case 0: do { func(); march_advance(width); \
	case 7:      func(); march_advance(width); \
	case 6:      func(); march_advance(width); \
	case 5:      func(); march_advance(width); \
	case 4:      func(); march_advance(width); \
	case 3:      func(); march_advance(width); \
	case 2:      func(); march_advance(width); \
	case 1:      func(); march_advance(width); \
	/*       */} while(--static_cast<int16_t>(_DX) > 0); \
	} \
	__emit__(0x1F); /* POP DS */ \
}
// -------------

// Non-`const` because BLITPERF wants to patch these.
extern Blitter BLITTER_FUNCS[];

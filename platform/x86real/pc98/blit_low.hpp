/// Low-level implementations for the optimized byte-aligned sprite blitter
/// -----------------------------------------------------------------------
/// All low-level functions spell out opcode bytes for multiple reasons:
/// • Turbo C++ 4.0J doesn't allow inline assembly in inlined functions.
/// • Its inline assembler also doesn't support ≥386 instructions.
/// • If we ever decide to move blitter prolog and epilog code into a shared
///   function, we avoid additional PUSH and POP instructions for SI and DI in
///   the core memory manipulation functions.

#include "platform/x86real/pc98/blitter.hpp"
#include "codegen.hpp"
#include "x86real.h"

#pragma warn -ccc
#pragma warn -rch

// Row unrolling via Duff's Device
// -------------------------------

#define unroll_1(func, step, row_p1, row_p2) \
	do { \
		func(row_p1, row_p2); step; \
	} while(--static_cast<int16_t>(_DX) > 0);

#define unroll_2(func, step, row_p1, row_p2) \
	if(_BX == 1) { \
		goto rem_1; \
	}; \
	do { \
	/*  */ func(row_p1, row_p2); step; \
	rem_1: func(row_p1, row_p2); step; \
	} while(--static_cast<int16_t>(_DX) > 0);

#define unroll_4(func, step, row_p1, row_p2) \
	switch(_BX) { \
	case 0: do { func(row_p1, row_p2); step; \
	case 3:      func(row_p1, row_p2); step; \
	case 2:      func(row_p1, row_p2); step; \
	case 1:      func(row_p1, row_p2); step; \
	/*   */ } while(--static_cast<int16_t>(_DX) > 0); \
	}

#define unroll_8(func, step, row_p1, row_p2) \
	switch(_BX) { \
	case 0: do { func(row_p1, row_p2); step; \
	case 7:      func(row_p1, row_p2); step; \
	case 6:      func(row_p1, row_p2); step; \
	case 5:      func(row_p1, row_p2); step; \
	case 4:      func(row_p1, row_p2); step; \
	case 3:      func(row_p1, row_p2); step; \
	case 2:      func(row_p1, row_p2); step; \
	case 1:      func(row_p1, row_p2); step; \
	/*   */ } while(--static_cast<int16_t>(_DX) > 0); \
	}

inline void unroll_setup(upixel_t width) {
	_DX = blit_state.h_clipped;
	if(width <= 64) {
		_BX = _DX;
		_DX += 7;
		_DX >>= 3u;
		_BX &= 7u;
	} else if(width <= 128) {
		_BX = _DX;
		_DX += 3;
		_DX >>= 2u;
		_BX &= 3u;
	} else if(width <= 192) {
		_BX = _DX;
		_DX += 1;
		_DX >>= 1u;
		_BX &= 1u;
	}
}

// Since the C preprocessor can't do arithmetic and Turbo C++ 4.0J's optimizer
// breaks with `switch` statements, we have to hardcode the unroll height for
// every sprite width.
#define unroll_16  unroll_8
#define unroll_24  unroll_8
#define unroll_32  unroll_8
#define unroll_40  unroll_8
#define unroll_48  unroll_8
#define unroll_56  unroll_8
#define unroll_64  unroll_8
#define unroll_72  unroll_4
#define unroll_80  unroll_4
#define unroll_88  unroll_4
#define unroll_96  unroll_4
#define unroll_104 unroll_4
#define unroll_112 unroll_4
#define unroll_120 unroll_4
#define unroll_128 unroll_4
#define unroll_136 unroll_2
#define unroll_144 unroll_2
#define unroll_152 unroll_2
#define unroll_160 unroll_2
#define unroll_168 unroll_2
#define unroll_176 unroll_2
#define unroll_184 unroll_2
#define unroll_192 unroll_2
#define unroll_200 unroll_1
#define unroll_208 unroll_1
#define unroll_216 unroll_1
#define unroll_224 unroll_1
#define unroll_232 unroll_1
#define unroll_240 unroll_1
#define unroll_248 unroll_1
#define unroll_256 unroll_1
#define unroll_264 unroll_1
#define unroll_272 unroll_1
#define unroll_280 unroll_1
#define unroll_288 unroll_1
#define unroll_296 unroll_1
#define unroll_304 unroll_1
#define unroll_312 unroll_1
#define unroll_320 unroll_1
#define unroll_328 unroll_1
#define unroll_336 unroll_1
#define unroll_344 unroll_1
#define unroll_352 unroll_1
#define unroll_360 unroll_1
#define unroll_368 unroll_1
#define unroll_376 unroll_1
#define unroll_384 unroll_1
#define unroll_392 unroll_1
#define unroll_400 unroll_1
#define unroll_408 unroll_1
#define unroll_416 unroll_1
#define unroll_424 unroll_1
#define unroll_432 unroll_1
#define unroll_440 unroll_1
#define unroll_448 unroll_1
#define unroll_456 unroll_1
#define unroll_464 unroll_1
#define unroll_472 unroll_1
#define unroll_480 unroll_1
#define unroll_488 unroll_1
#define unroll_496 unroll_1
#define unroll_504 unroll_1
#define unroll_512 unroll_1
#define unroll_520 unroll_1
#define unroll_528 unroll_1
#define unroll_536 unroll_1
#define unroll_544 unroll_1
#define unroll_552 unroll_1
#define unroll_560 unroll_1
#define unroll_568 unroll_1
#define unroll_576 unroll_1
#define unroll_584 unroll_1
#define unroll_592 unroll_1
#define unroll_600 unroll_1
#define unroll_608 unroll_1
#define unroll_616 unroll_1
#define unroll_624 unroll_1
#define unroll_632 unroll_1
#define unroll_640 unroll_1
// -------------------------------

#define FOREACH_WIDTH \
	X(8) \
	X(16) \

// Recursion rules for blitting wide sprites with unit instructions
// ----------------------------------------------------------------

#define recurse_impl(prefix, this, large_part, small_part) \
	inline uint8_t prefix##_##this(uint8_t op, uint8_t p) { \
		return prefix##_##small_part(op, prefix##_##large_part(op, p)); \
	}

#define recurse_impl_all(prefix) \
	recurse_impl(prefix,  24,  16,  8) \
	recurse_impl(prefix,  40,  32,  8) \
	recurse_impl(prefix,  48,  32, 16) \
	recurse_impl(prefix,  56,  32, 24) \
	recurse_impl(prefix,  64,  32, 32) \
	recurse_impl(prefix,  72,  64,  8) \
	recurse_impl(prefix,  80,  64, 16) \
	recurse_impl(prefix,  88,  64, 24) \
	recurse_impl(prefix,  96,  64, 32) \
	recurse_impl(prefix, 104,  96,  8) \
	recurse_impl(prefix, 112,  96, 16) \
	recurse_impl(prefix, 120,  96, 24) \
	recurse_impl(prefix, 128,  96, 32) \
	recurse_impl(prefix, 136, 128,  8) \
	recurse_impl(prefix, 144, 128, 16) \
	recurse_impl(prefix, 152, 128, 24) \
	recurse_impl(prefix, 160, 128, 32) \
	recurse_impl(prefix, 168, 160,  8) \
	recurse_impl(prefix, 176, 160, 16) \
	recurse_impl(prefix, 184, 160, 24) \
	recurse_impl(prefix, 192, 160, 32) \
	recurse_impl(prefix, 200, 192,  8) \
	recurse_impl(prefix, 208, 192, 16) \
	recurse_impl(prefix, 216, 192, 24) \
	recurse_impl(prefix, 224, 192, 32) \
	recurse_impl(prefix, 232, 224,  8) \
	recurse_impl(prefix, 240, 224, 16) \
	recurse_impl(prefix, 248, 224, 24) \
	recurse_impl(prefix, 256, 224, 32) \
	recurse_impl(prefix, 264, 256,  8) \
	recurse_impl(prefix, 272, 256, 16) \
	recurse_impl(prefix, 280, 256, 24) \
	recurse_impl(prefix, 288, 256, 32) \
	recurse_impl(prefix, 296, 288,  8) \
	recurse_impl(prefix, 304, 288, 16) \
	recurse_impl(prefix, 312, 288, 24) \
	recurse_impl(prefix, 320, 288, 32) \
	recurse_impl(prefix, 328, 320,  8) \
	recurse_impl(prefix, 336, 320, 16) \
	recurse_impl(prefix, 344, 320, 24) \
	recurse_impl(prefix, 352, 320, 32) \
	recurse_impl(prefix, 360, 352,  8) \
	recurse_impl(prefix, 368, 352, 16) \
	recurse_impl(prefix, 376, 352, 24) \
	recurse_impl(prefix, 384, 352, 32) \
	recurse_impl(prefix, 392, 384,  8) \
	recurse_impl(prefix, 400, 384, 16) \
	recurse_impl(prefix, 408, 384, 24) \
	recurse_impl(prefix, 416, 384, 32) \
	recurse_impl(prefix, 424, 416,  8) \
	recurse_impl(prefix, 432, 416, 16) \
	recurse_impl(prefix, 440, 416, 24) \
	recurse_impl(prefix, 448, 416, 32) \
	recurse_impl(prefix, 456, 448,  8) \
	recurse_impl(prefix, 464, 448, 16) \
	recurse_impl(prefix, 472, 448, 24) \
	recurse_impl(prefix, 480, 448, 32) \
	recurse_impl(prefix, 488, 480,  8) \
	recurse_impl(prefix, 496, 480, 16) \
	recurse_impl(prefix, 504, 480, 24) \
	recurse_impl(prefix, 512, 480, 32) \
	recurse_impl(prefix, 520, 512,  8) \
	recurse_impl(prefix, 528, 512, 16) \
	recurse_impl(prefix, 536, 512, 24) \
	recurse_impl(prefix, 544, 512, 32) \
	recurse_impl(prefix, 552, 544,  8) \
	recurse_impl(prefix, 560, 544, 16) \
	recurse_impl(prefix, 568, 544, 24) \
	recurse_impl(prefix, 576, 544, 32) \
	recurse_impl(prefix, 584, 576,  8) \
	recurse_impl(prefix, 592, 576, 16) \
	recurse_impl(prefix, 600, 576, 24) \
	recurse_impl(prefix, 608, 576, 32) \
	recurse_impl(prefix, 616, 608,  8) \
	recurse_impl(prefix, 624, 608, 16) \
	recurse_impl(prefix, 632, 608, 24) \
	recurse_impl(prefix, 640, 608, 32) \
// ----------------------------------------------------------------

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

inline void u_8(uint8_t, uint8_t) {
	__emit__(0xA4); // MOVSB
}

inline void u_16(uint8_t, uint8_t) {
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

#define stationary_impl(plane_seg, width, func, row_p1, row_p2) { \
	_ES = plane_seg; /* First __fastcall parameter */ \
	unroll_setup(width); /* Must come first because it uses CL on 8086. */ \
	_SI = blit_source.dots_start.part.off; \
	_SI += blit_state.sprite_offset; \
	_DI = blit_state.vo; \
	_CX = blit_source.stride; \
	\
	/* Turbo C++ 4.0J does not back up DS if the function mutates it. */ \
	/* [blit_state] can't be accessed anymore beyond this point! */ \
	__emit__(0x1E); /* PUSH DS */ \
	_DS = blit_source.dots_start.part.seg; \
	unroll_##width(func, stationary_next(), row_p1, row_p2); \
	__emit__(0x1F); /* POP DS */ \
}
// ---------------

// Marching rows
// -------------
// SI and DI are adjusted for every byte written. The end of each row has to
// add the difference.

inline void march_advance(uint16_t width, X86::Reg16 skip_w_reg) {
	__emit__(0x03, (0xF0 + skip_w_reg)); // ADD SI, [skip_w_reg]

	// ADD DI, (ROW_SIZE - (width / BYTE_DOTS))
	__emit__(0x83, 0xC7, static_cast<uint8_t>(ROW_SIZE - (width / BYTE_DOTS)));
}

#define march_impl(plane_seg, width, func, skip_w_reg) { \
	_ES = plane_seg; /* First __fastcall parameter */ \
	unroll_setup(width); /* Must come first because it uses CL on 8086. */ \
	_SI = blit_source.dots_start.part.off; \
	_SI += blit_state.sprite_offset; \
	_DI = blit_state.vo; \
	if(skip_w_reg == X86::R_AX) { \
		_AX = blit_source.stride; \
		_AX -= (width / BYTE_DOTS); \
	} else if(skip_w_reg == X86::R_CX) { \
		_CX = blit_source.stride; \
		_CX -= (width / BYTE_DOTS); \
	} \
	__emit__(0xFC); /* CLD */ \
	\
	/* Turbo C++ 4.0J does not back up DS if the function mutates it. */ \
	/* [blit_state] can't be accessed anymore beyond this point! */ \
	__emit__(0x1E); /* PUSH DS */ \
	_DS = blit_source.dots_start.part.seg; \
	unroll_##width(func, march_advance(width, skip_w_reg), 0, 0); \
	__emit__(0x1F); /* POP DS */ \
}
// -------------

// Non-`const` because BLITPERF wants to patch these.
extern Blitter BLITTER_FUNCS[];

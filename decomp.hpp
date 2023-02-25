/* ReC98
 * -----
 * Declarations to help decompiling the seemingly impossible
 */

#define DECOMP_HPP

// Alternate version that sets the value first
#define outport2(port, val) _asm { \
	mov ax, val; \
	mov dx, port; \
	out dx, ax; \
}

// Should just be unwrapped wherever it appears. Code that directly uses T
// would be much cleaner.
template <class T> union StupidBytewiseWrapperAround {
	T t;
	int8_t byte[sizeof(T)];
	uint8_t ubyte[sizeof(T)];
};

// Does exactly the same as Turbo C++'s __memcpy__() intrinsic, just with
// stupidly reordered instructions. Can be replaced with regular copy
// assignment wherever it appears.
#if (GAME == 5)
	#define copy_near_struct_member(dst, src, src_type, member) { \
		_CX = (sizeof(dst) / sizeof(uint16_t)); \
		asm { push ds; pop es; } \
		_DI = FP_OFF(&dst); \
		_SI = FP_OFF(&src); \
		_SI += offsetof(src_type, member); \
		asm { rep movsw; } \
	}
#else
	#define copy_near_struct_member(dst, src, src_type, member) { \
		asm { push ds; pop es; } \
		_DI = FP_OFF(&dst); \
		__memcpy__(MK_FP(_ES, _DI), &src.member, sizeof(dst)); \
	}
#endif

// Circumventing compiler optimizations
// ------------------------------------
// If you don't want to recreate the code layout of the original PC-98
// binaries, these can be safely deleted. They just make the code worse.

#if defined(__TURBOC__) && defined(__MSDOS__)
	// Use this function wherever the original code used a immediate 0 literal
	// that Turbo C++ would optimize away, e.g. in register assignments
	// (_AX = 0 → XOR AX, AX) or comparisons (_AX == 0 → OR AX, AX). This way,
	// the compiler is forced to leave space for any potential offset, with the
	// literal 0 then being spelled out by the linker.
	template <class T> inline T keep_0(T x) {
		if(x == 0) {
			extern void *near address_0;
			return reinterpret_cast<T>(&address_0);
		}
		return x;
	}

	// Bypasses the -Z -3 function parameter optimization, where [x] would be
	// combined with any potential subsequent 16-bit parameter adjacent in
	// memory to form a 32-bit PUSH.
	// (Interestingly, using a template function inlines either too well or
	// too badly. Only this macro guarantees the intended 16-bit PUSH to be
	// consistently emitted.)
	#define inhibit_Z3(x) \
		*reinterpret_cast<int16_t near *>(reinterpret_cast<uint16_t>(&x))

	// Calling an empty inlined function prevents certain jump optimizations.
	inline void optimization_barrier(void) {
	}

#else
	#define keep_0(x) x
	#define inhibit_Z3(x) x
	#define optimization_barrier()
#endif
// ------------------------------------

// 32-bit ASM instructions not supported by Turbo C++ 4.0J's built-in
// assembler. Makes no sense to compile with `#pragma inline` (and thus,
// require a 16-bit TASM) just for those.
#define MOVSD	__emit__(0x66, 0xA5);
#define REP  	__emit__(0xF3);

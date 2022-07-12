/* ReC98
 * -----
 * Declarations to help decompiling the seemingly impossible
 */

// Flag comparisons
// ----------------
// When used inside a conditional expression like
//	if(FLAGS_*) { goto some_label; | return; }
// these assemble into the single given instruction. Apply the ! operator to
// get the N versions.
#define FLAGS_CARRY (_FLAGS & 0x01) /* JC / JAE / JB */
#define FLAGS_ZERO (_FLAGS & 0x40) /* JZ */
#define FLAGS_SIGN (_FLAGS & 0x80) /* JS */
// ----------------

// Alternate version that doesn't spill the port number to DX
#define outportb2(port, val) _asm { \
	mov al, val; \
	out port, al; \
}

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

// Trying to assign a `near` function to a nearfunc_t_near* outside the group
// of the function will cause a fixup overflow error at link time. The only
// known workaround involves lying to the compiler about the true distance of
// the function, removing any declaration of the function from global scope to
// prevent a redefinition error, and casting away its segment.
// TODO: Might no longer be necessary once we can fully rely on segment names
// for code layout, and don't have to mess with groups anymore.
#define set_nearfunc_ptr_to_farfunc(ptr, func) { \
	void pascal far func(void); \
	ptr = reinterpret_cast<nearfunc_t_near>(func); \
}

// poke() versions that actually inline with pseudoregisters
// ---------------------------------------------------------
#define pokew(sgm, off, val) { *(uint16_t far *)(MK_FP(sgm, off)) = val; }

// Turbo C++ 4.0 generates wrong segment prefix opcodes for the _FS and _GS
// pseudoregisters - 0x46 (INC SI) and 0x4E (DEC SI) rather than the correct
// 0x64 and 0x65, respectively. These prefixes are also not supported in
// inline assembly, which is limited to pre-386 anyway. Compiling via assembly
// (`#pragma inline`) would work and generate the correct instructions here,
// but that would incur yet another dependency on a 16-bit TASM, for something
// honestly quite insignificant.
//
// So, can we somehow work around this issue while retaining the readability
// of the usage code and pretending that this bug doesn't exist? Comparisons
// with segment registers unfortunately don't inline, so something like
// 	if(sgm == _FS)
// wouldn't work, even inside a macro that replaces [sgm] with _FS. But since
// __emit__() *does* inline, we can use function templates! The default
// versions provide the regularly intended C code for all other registers,
// while explicit specializations for _FS and _GS __emit__() the correct
// instruction opcodes for all offset registers needed. Then, we only need to
// somehow move the pseudoregisters up into the type system... which can
// simply be done by turning them into class names via preprocessor token
// pasting. Sure, this limits this approach to raw registers with no immediate
// offsets, but let's hope we won't ever need those...
//
// Also, hey, no need for the MK_FP() macro if we directly return the correct
// types.

#if defined(__TURBOC__) && defined(__MSDOS__)
	// Declared in <dos.h> in these compilers.
	void __emit__(uint8_t __byte, ...);
#endif

struct Decomp_ES { void  __seg* value() { return (void  __seg *)(_ES); } };
struct Decomp_FS { void  __seg* value() { return (void  __seg *)(_FS); } };
struct Decomp_GS { void  __seg* value() { return (void  __seg *)(_GS); } };
struct Decomp_DI { void __near* value() { return (void __near *)(_DI); } };

// Removing [val] from the parameter lists of the template functions below
// perfects the inlining.
#define poked(sgm, off, val) \
	_EAX = val; \
	poked_eax((Decomp##sgm *)nullptr, (Decomp##off *)nullptr, (uint8_t)(0x89));

#define poke_or_d(sgm, off, val) \
	_EAX = val; \
	poked_eax((Decomp##sgm *)nullptr, (Decomp##off *)nullptr, (uint8_t)(0x09));

template <class Segment, class Offset> inline void poked_eax(
	Segment *sgm, Offset *off, uint8_t op
) {
	if(op == 0x89) {
		*(uint32_t far *)(sgm->value() + off->value()) = _EAX;
	} else if(op == 0x09) {
		*(uint32_t far *)(sgm->value() + off->value()) |= _EAX;
	}
}

inline void poked_eax(Decomp_FS *sgm, Decomp_DI *off, uint8_t op) {
	__emit__(0x66, 0x64, op, 0x05); // [op] FS:[DI], EAX
}

inline void poked_eax(Decomp_GS *sgm, Decomp_DI *off, uint8_t op) {
	__emit__(0x66, 0x65, op, 0x05); // [op] GS:[DI], EAX
}
// ---------------------------------------------------------

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
			return reinterpret_cast<pixel_t>(&address_0);
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

// Neither WAIT nor FWAIT emit the emulated WAIT we want...
#define FWAIT_EMU	db 0xCD, 0x3D;

// 32-bit ASM instructions not supported by Turbo C++ 4.0J's built-in
// assembler. Makes no sense to compile with `#pragma inline` (and thus,
// require a 16-bit TASM) just for those.
#define MOVSD	__emit__(0x66, 0xA5);
#define REP  	__emit__(0xF3);

/* ReC98
 * -----
 * Macros to help decompiling the seemingly impossible
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
#define outportb2(port, val) __asm { \
	mov al, val; \
	out port, al; \
}

// Alternate version that sets the value first
#define outport2(port, val) __asm { \
	mov ax, val; \
	mov dx, port; \
	out dx, ax; \
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
#ifdef __cplusplus
}
	#if defined(__TURBOC__) && defined(__MSDOS__)
		// Declared in <dos.h> in these compilers.
		void __emit__(unsigned char __byte, ...);
	#endif

	struct Decomp_ES { void  __seg* value() { return (void  __seg *)(_ES); } };
	struct Decomp_FS { void  __seg* value() { return (void  __seg *)(_FS); } };
	struct Decomp_GS { void  __seg* value() { return (void  __seg *)(_GS); } };
	struct Decomp_DI { void __near* value() { return (void __near *)(_DI); } };

	// Removing [val] from the parameter lists of the template functions below
	// perfects the inlining.
	#define poked(sgm, off, val) \
		_EAX = val; \
		poked_eax((Decomp##sgm *)NULL, (Decomp##off *)NULL, (uint8_t)(0x89));

	#define poke_or_d(sgm, off, val) \
		_EAX = val; \
		poked_eax((Decomp##sgm *)NULL, (Decomp##off *)NULL, (uint8_t)(0x09));

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

extern "C" {
#endif
// ---------------------------------------------------------

// 32-bit ASM instructions not supported by Turbo C++ 4.0J's built-in
// assembler. Makes no sense to compile with `#pragma inline` (and thus,
// require a 16-bit TASM) just for those.
#define MOVSD	__emit__(0x66, 0xA5);
#define REP  	__emit__(0xF3);

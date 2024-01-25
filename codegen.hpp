/// Custom code generation for pseudoregisters
/// ------------------------------------------
/// Since __emit__() always inlines, we can use it implement our own code
/// generation to bypass compiler bugs or quirks related to pseudoregisters, by
/// directly outputting the intended machine code:
///
/// • Step 1: Define opcodes and R/M bytes for all needed instructions and
///           registers
/// • Step 2: Implement needed operations as inlined functions via __emit__(),
///           taking all required instruction components as parameters
/// • Step 3: Add macros that token-paste pseudoregisters onto the prefixes of
///           the opcode byte constants. This way, we hide the pseudoregisters
///           from the compiler, and the constants from usage code.
///
/// Provides workarounds for the following issues:
///
/// 1) Turbo C++ 4.0 generates wrong segment prefix opcodes for the _FS and _GS
///    pseudoregisters - 0x46 (INC SI) and 0x4E (DEC SI) rather than the correct
///    0x64 and 0x65, respectively. These prefixes are also not supported in
///    inline assembly, which is limited to pre-386 anyway. Compiling via
///    assembly (`#pragma inline`) would work and generate the correct
///    instructions, but that would incur yet another dependency on a 16-bit
///    TASM for something honestly quite insignificant.
/// 2) If _SI or _DI are used within a function, Turbo C++ 4.0 always generates
///    a `PUSH SI` and `PUSH DI` instruction in the function prolog, and a
///    `POP DI` and `POP SI` instruction in the epilog, in this order. If a
///    function needs both these registers and a different prolog or epilog, all
///    use of these registers must be hidden via __emit__(). These macros can
///    help retain some readability in this case.
///
/// Provides access to the following instructions that are unavailable in Turbo
/// C++ 4.0's inline assembler, for arbitrary registers:
///
/// • IMUL r16, r/m16, imm8

#if defined(__TURBOC__) && defined(__MSDOS__)
	// Declared in <dos.h> in these compilers.
	void __emit__(uint8_t __byte, ...);
#endif

struct X86 {
	enum Prefix {
		P_DS = 0x3E,
		P_SS = 0x36,
		P_ES = 0x26,
		P_FS = 0x64,
		P_GS = 0x65,
		P_OPERAND_SIZE = 0x66,
	};

	enum Reg8 {
		R_CL = 1,
	};

	enum Reg16 {
		R_AX = 0,
		R_DX = 2,
		R_BX = 3,
		R_SI = 6,
		R_DI = 7,
	};

	enum Reg32 {
		R_EAX = 0,
	};

	enum RM {
		RM_ADDRESS_DI = 0x05,
		RM_ADDRESS_BP = 0x06,
	};

	enum OpRegMem {
		OR_RM_R_32  = 0x09,	// OR  r/m32, r32
		MOV_RM_R_16 = 0x89,	// MOV r/m16, r16
		MOV_RM_R_32 = 0x89,	// MOV r/m32, r32
		MOV_R_RM_8  = 0x8A,	// MOV r8, r/m8
		MOV_R_RM_16 = 0x8B,	// MOV r16, r/m16
		MOV_R_RM_32 = 0x8B,	// MOV r32, r/m32
		LEA_R_M_16  = 0x8D,	// LEA r16, m
	};

	enum OpRegRegMem {
		CMP_RM_R_16 = 0x3B,	// CMP r/m16, r16
		IMUL_R_RM_IMM_8 = 0x6B,	// IMUL r16, r/m16, imm8
	};

	// Emitters
	// --------

	static void reg_reg(OpRegRegMem op, Reg16 dst, Reg16 src, uint8_t imm = 0) {
		if(imm) {
			__emit__(op, (0xC0 + (dst * 8) + src), imm);
		} else {
			__emit__(op, (0xC0 + (dst * 8) + src));
		}
	}

	static void reg_mem(
		OpRegMem op, Prefix prefix, RM rm, Reg16 reg, uint8_t disp = 0
	) {
		if(!(
			((prefix == P_SS) && (rm == RM_ADDRESS_BP)) ||
			((prefix == P_DS) && (rm != RM_ADDRESS_BP))
		)) {
			__emit__(prefix);
		}
		if(disp || (rm == RM_ADDRESS_BP)) {
			__emit__(op, (0x40 + ((reg * 8) + rm)), disp);
		} else {
			__emit__(op, ((reg * 8) + rm));
		}
	}

	static void reg_mem(
		OpRegMem op, Prefix prefix, RM rm, Reg32 reg, uint8_t disp = 0
	) {
		__emit__(P_OPERAND_SIZE);
		reg_mem(op, prefix, rm, static_cast<Reg16>(reg), disp);
	}

	static void mov_to_reg(Prefix prefix, RM rm, Reg8 reg, uint8_t disp = 0) {
		reg_mem(MOV_R_RM_8, prefix, rm, static_cast<Reg16>(reg), disp);
	}

	static void mov_to_reg(Prefix prefix, RM rm, Reg16 reg, uint8_t disp = 0) {
		reg_mem(MOV_R_RM_16, prefix, rm, reg, disp);
	}

	static void mov_to_reg(Prefix prefix, RM rm, Reg32 reg, uint8_t disp = 0) {
		reg_mem(MOV_R_RM_32, prefix, rm, reg, disp);
	}

	static void mov_to_mem(Prefix prefix, RM rm, Reg16 reg, uint8_t disp = 0) {
		reg_mem(MOV_RM_R_16, prefix, rm, reg, disp);
	}

	static void mov_to_mem(Prefix prefix, RM rm, Reg32 reg, uint8_t disp = 0) {
		reg_mem(MOV_RM_R_32, prefix, rm, reg, disp);
	}
	// --------
};

// First macro layer to transform pseudoregisters into x86 constants
// -----------------------------------------------------------------

#define _stack_to_reg(op, dst_reg, imm) \
	X86::reg_mem(op, X86::P_SS, X86::RM_ADDRESS_BP, X86::R##dst_reg, imm);

#define _cmp_reg_reg(dst_reg, src_reg) \
	X86::reg_reg(X86::CMP_RM_R_16, X86::R##dst_reg, X86::R##src_reg);

#define _imul_reg_to_reg(dst_reg, src_reg, imm) \
	X86::reg_reg(X86::IMUL_R_RM_IMM_8, X86::R##dst_reg, X86::R##src_reg, imm);

#define _lea_local_to_reg(dst_reg, src_top, src_ptr) \
	_stack_to_reg(X86::LEA_R_M_16, dst_reg, ( \
		reinterpret_cast<uint8_t __ss *>(src_ptr) - \
		reinterpret_cast<uint8_t __ss *>(src_top) \
	));

#define _mov_param_to_reg(dst_reg, offset) \
	_stack_to_reg(X86::MOV_R_RM_16, dst_reg, offset);

#define _mov_to_reg(dst_reg, src_seg, src_off, src_disp) \
	X86::mov_to_reg( \
		X86::P##src_seg, X86::RM_ADDRESS##src_off, X86::R##dst_reg, src_disp \
	);

#define _mov_to_mem(dst_seg, dst_off, dst_disp, src_reg) \
	X86::mov_to_mem( \
		X86::P##dst_seg, X86::RM_ADDRESS##dst_off, X86::R##src_reg, dst_disp \
	);

// Removing [val] from the parameter lists of the template functions below
// perfects the inlining.
#define poked(seg, off, val) \
	_EAX = val; \
	X86::reg_mem( \
		X86::MOV_RM_R_32, X86::P##seg, X86::RM_ADDRESS##off, X86::R_EAX \
	);

#define poke_or_d(seg, off, val) \
	_EAX = val; \
	X86::reg_mem( \
		X86::OR_RM_R_32, X86::P##seg, X86::RM_ADDRESS##off, X86::R_EAX \
	);
// -----------------------------------------------------------------

// Second macro layer to allow pseudoregister renaming
// ---------------------------------------------------

#define cmp_reg_reg(dst_reg, src_reg) \
	_cmp_reg_reg(dst_reg, src_reg)

#define imul_reg_to_reg(dst_reg, src_reg, imm) \
	_imul_reg_to_reg(dst_reg, src_reg, imm)

#define lea_local_to_reg(dst_reg, src_top, src_ptr) \
	_lea_local_to_reg(dst_reg, src_top, src_ptr)

#define mov_param_to_reg(dst_reg, src_ptr) \
	_mov_param_to_reg(dst_reg, src_ptr)

#define mov_to_reg(dst_reg, src_seg, src_off, src_disp) \
	_mov_to_reg(dst_reg, src_seg, src_off, src_disp)

#define mov_to_mem(dst_seg, dst_off, dst_disp, src_reg) \
	_mov_to_mem(dst_seg, dst_off, dst_disp, src_reg)
// ---------------------------------------------------
/// ----------------------

/// Blitters for the wide benchmark
/// -------------------------------

#include "platform/x86real/pc98/blit_low.hpp"

// Marching memory manipulation
// ----------------------------
// Uses MOV instructions without displacements to find out how much they hurt.

inline uint8_t m_8(uint8_t op, uint8_t) {
	__emit__(0x8A, 0x04); // MOV AL, [SI]
	__emit__(0x26, 0x88, 0x05); // MOV ES:[DI], AL
	__emit__(0x46); // INC SI
	__emit__(0x47); // INC DI
	return 0;
}

inline uint8_t m_16(uint8_t op, uint8_t) {
	__emit__(0x8B, 0x04); // MOV AX, [SI]
	__emit__(0x26, 0x89, 0x05); // MOV ES:[DI], AX
	__emit__(0x83, 0xC6, 0x02); // ADD SI, 2
	__emit__(0x83, 0xC7, 0x02); // ADD DI, 2
	return 0;
}

inline uint8_t m_32(uint8_t op, uint8_t) {
#if (CPU == 386)
	__emit__(0x66, 0x8B, 0x04); // MOV EAX, [SI]
	__emit__(0x66, 0x26, 0x89, 0x05); // MOV ES:[DI], EAX
	__emit__(0x83, 0xC6, 0x04); // ADD SI, 4
	__emit__(0x83, 0xC7, 0x04); // ADD DI, 4
	return 0;
#else
	return m_16(op, m_16(op, 0));
#endif
}

recurse_impl_all(m)
// -----------------------------

#define FOREACH_WIDTH_WITHOUT_640(X, param) \
	X(32, param) \
	X(64, param) \
	X(96, param) \
	X(128, param) \
	X(160, param) \
	X(192, param) \
	X(224, param) \
	X(256, param) \
	X(288, param) \
	X(320, param) \
	X(352, param) \
	X(384, param) \
	X(416, param) \
	X(448, param) \
	X(480, param) \
	X(512, param) \
	X(544, param) \
	X(576, param) \
	X(608, param) \

#define X(width, _) \
	blitter_impl_displaced_write(width) \
	blitter_impl_march_op(MW, m, X86::R_CX, width) \
	blitter_impl_march_unit(width) \
	blitter_impl_march_string(width) \

	FOREACH_WIDTH_WITHOUT_640(X, 0);
	blitter_impl_displaced_write(640)
	blitter_impl_march_op(MW, m, X86::R_CX, 640)
	blitter_impl_march_unit(640)
	blitter_impl_march_string_640()
#undef X

#define instantiate(X, param) \
	nullptr FOREACH_WIDTH_WITHOUT_640(X, param) X(640, param)

#define X(width, prefix) \
	, prefix##width::blit

	void (__fastcall *DISPLACED[])(seg_t) = { instantiate(X, DisplacedRW) };
	void (__fastcall *MARCHING[])(seg_t) = { instantiate(X, MarchMW) };
	void (__fastcall *MOVS[])(seg_t) = { instantiate(X, MarchUW) };
	void (__fastcall *REP_MOVS[])(seg_t) = { instantiate(X, MarchSW) };
#undef X

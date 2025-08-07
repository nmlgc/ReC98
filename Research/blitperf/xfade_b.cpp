/// Blitters for the crossfading benchmark
/// --------------------------------------

#include "platform/x86real/pc98/blit_low.hpp"

// Masked OR
// ---------
// Uses string unit instructions for loading and displaced instructions for the
// OR.

inline void masked_or_mask_set(void) {
	__emit__(0x8B, 0x1F); // MOV BX, [BX]
#if (CPU == 386)
	_AX = _BX;
	__emit__(0x66, 0xC1, 0xE3, 0x10); // SHL EBX, 16
	_BX  =_AX;
#endif
}

inline uint8_t mo_8(uint8_t, uint8_t p) {
	__emit__(0xAC); // LODSB
	__emit__(0x22, 0xC3); // AND AL, BL
	if(p == 0) {
		__emit__(0x26, 0x08, 0x05); // OR ES:[DI], AL
	} else {
		__emit__(0x26, 0x08, 0x45, p); // OR ES:[DI+p], AL
	}
	return (p + 1);
}

inline uint8_t mo_16(uint8_t, uint8_t p) {
	__emit__(0xAD); // LODSW
	__emit__(0x23, 0xC3); // AND AX, BX
	if(p == 0) {
		__emit__(0x26, 0x09, 0x05); // OR ES:[DI], AX
	} else {
		__emit__(0x26, 0x09, 0x45, p); // OR ES:[DI+p], AX
	}
	return (p + 2);
}

inline uint8_t mo_32(uint8_t, uint8_t p) {
#if (CPU == 386)
	__emit__(0x66, 0xAD); // LODSD
	__emit__(0x66, 0x23, 0xC3); // AND EAX, EBX
	if(p == 0) {
		__emit__(0x66, 0x26, 0x09, 0x05); // OR ES:[DI], EAX
	} else {
		__emit__(0x66, 0x26, 0x09, 0x45, p); // OR ES:[DI+p], EAX
	}
	return (p + 4);
#else
	return mo_16(0, mo_16(0, p));
#endif
}

inline uint8_t erase_mo_8(uint8_t, uint8_t) {
	__emit__(0xAC); // LODSB
	_AL &= _BL;
	__emit__(0xF6, 0xD3); // NOT BL
	__emit__(0x26, 0x8A, 0x0D); // MOV CL, ES:[DI]
	_CL &= _BL;
	_AL |= _CL;
	__emit__(0xAA); // STOSB
	__emit__(0xF6, 0xD3); // NOT BL
	return 0;
}

inline uint8_t erase_mo_16(uint8_t, uint8_t p) {
	__emit__(0xAD); // LODSW
	_AX &= _BX;
	__emit__(0xF7, 0xD3); // NOT BX
	__emit__(0x26, 0x8B, 0x0D); // MOV CX, ES:[DI]
	_CX &= _BX;
	_AX |= _CX;
	__emit__(0xAB); // STOSW
	__emit__(0xF7, 0xD3); // NOT BX
	return p;
}

inline uint8_t erase_mo_32(uint8_t, uint8_t p) {
#if (CPU == 386)
	__emit__(0x66, 0xAD); // LODSD
	_EAX &= _EBX;
	__emit__(0x66, 0xF7, 0xD3); // NOT EBX
	__emit__(0x66, 0x26, 0x8B, 0x0D); // MOV ECX, ES:[DI]
	_ECX &= _EBX;
	_EAX |= _ECX;
	__emit__(0x66, 0xAB); // STOSD
	__emit__(0x66, 0xF7, 0xD3); // NOT EBX
	return p;
#else
	return erase_mo_16(0, erase_mo_16(0, p));
#endif
}

recurse_impl_all(mo)
recurse_impl_all(erase_mo)
// ---------

#define blitter_impl_masked_or(width) \
	void masked_or_##width( \
		seg_t plane_seg, const dots16_t __ds *masks, uint16_t mask_h \
	) { \
		_ES = plane_seg; \
		uint16_t mask_offset = 0; \
		uint16_t mask_offset_mask = ((mask_h * sizeof(masks[0])) - 1); \
		_SI = blit_source.dots_start.part.off; \
		_SI += blit_state.sprite_offset; \
		_DI = blit_state.vo; \
		_DX = blit_state.h_clipped; \
		\
		do { \
			_BX = mask_offset; \
			_BX += FP_OFF(masks); \
			masked_or_mask_set(); \
			__emit__(0x1E); /* PUSH DS */ \
			_DS = blit_source.dots_start.part.seg; \
			mo_##width(0, 0); \
			__emit__(0x1F); /* POP DS */ \
			_SI -= (width / BYTE_DOTS); \
			_SI += blit_source.stride; \
			_DI += ROW_SIZE; \
			mask_offset += sizeof(masks[0]); \
			mask_offset &= mask_offset_mask; \
		} while(--static_cast<int16_t>(_DX) > 0); \
	}

#define blitter_impl_erase_masked_or(width) \
	void erase_masked_or_##width( \
		seg_t plane_seg, const dots16_t __ds *masks, uint16_t mask_h \
	) { \
		_ES = plane_seg; \
		uint16_t mask_offset; \
		uint16_t mask_offset_mask = ((mask_h * sizeof(masks[0])) - 1); \
		_SI = blit_source.dots_start.part.off; \
		_SI += blit_state.sprite_offset; \
		_DI = blit_state.vo; \
		_DX = blit_state.h_clipped; \
		\
		_BX = 0; \
		do { \
			mask_offset = _BX; \
			_BX += FP_OFF(masks); \
			masked_or_mask_set(); \
			__emit__(0x1E); /* PUSH DS */ \
			_DS = blit_source.dots_start.part.seg; \
			erase_mo_##width(0, 0); \
			__emit__(0x1F); /* POP DS */ \
			_SI -= (width / BYTE_DOTS); \
			_SI += blit_source.stride; \
			_DI += (ROW_SIZE - (width / BYTE_DOTS)); \
			_BX = mask_offset; \
			_BX += sizeof(masks[0]); \
			_BX &= mask_offset_mask; \
		} while(--static_cast<int16_t>(_DX) > 0); \
	}

#define FOREACH_WIDTH(X, param) \
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
	X(640, param) \

#define X(width, _) \
	blitter_impl_masked_or(width); \
	blitter_impl_erase_masked_or(width); \

	FOREACH_WIDTH(X, 0)
#undef X

#define X(width, prefix) \
	, prefix##_##width

	void (*MASKED_OR[])(seg_t, const dots16_t __ds *, uint16_t) = {
		nullptr FOREACH_WIDTH(X, masked_or)
	};
	void (*ERASE_MASKED_OR[])(seg_t, const dots16_t __ds *, uint16_t) = {
		nullptr FOREACH_WIDTH(X, erase_masked_or)
	};
#undef X

void xfade_blitters_setup(void)
{
	#define X(width, _) \
		blitter_use_write_offscreen(width); \

		FOREACH_WIDTH(X, 0)
	#undef X
}

#pragma startup xfade_blitters_setup

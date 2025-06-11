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

inline void erase_masked_or_mask_set(void) {
	masked_or_mask_set();
#if (CPU == 386)
	_ECX = _EBX; // Prevent the call site from using these registers for locals
	__emit__(0x66, 0xF7, 0xD1); // NOT ECX
#else
	_CX = _BX; // Prevent the call site from using these registers for locals
	__emit__(0xF7, 0xD1); // NOT CX
#endif
}

inline uint8_t mo_8(uint8_t erase, uint8_t p) {
	__emit__(0xAC); // LODSB
	__emit__(0x22, 0xC3); // AND AL, BL
	if(p == 0) {
		if(erase) {
			__emit__(0x26, 0x20, 0x0D); // AND ES:[DI], CL
		}
		__emit__(0x26, 0x08, 0x05); // OR ES:[DI], AL
	} else {
		if(erase) {
			__emit__(0x26, 0x20, 0x4D, p); // AND ES:[DI+p], CL
		}
		__emit__(0x26, 0x08, 0x45, p); // OR ES:[DI+p], AL
	}
	return (p + 1);
}

inline uint8_t mo_16(uint8_t erase, uint8_t p) {
	__emit__(0xAD); // LODSW
	__emit__(0x23, 0xC3); // AND AX, BX
	if(p == 0) {
		if(erase) {
			__emit__(0x26, 0x21, 0x0D); // AND ES:[DI], CX
		}
		__emit__(0x26, 0x09, 0x05); // OR ES:[DI], AX
	} else {
		if(erase) {
			__emit__(0x26, 0x21, 0x4D, p); // AND ES:[DI+p], CX
		}
		__emit__(0x26, 0x09, 0x45, p); // OR ES:[DI+p], AX
	}
	return (p + 2);
}

inline uint8_t mo_32(uint8_t erase, uint8_t p) {
#if (CPU == 386)
	__emit__(0x66, 0xAD); // LODSD
	__emit__(0x66, 0x23, 0xC3); // AND EAX, EBX
	if(p == 0) {
		if(erase) {
			__emit__(0x66, 0x26, 0x21, 0x0D); // AND ES:[DI], ECX
		}
		__emit__(0x66, 0x26, 0x09, 0x05); // OR ES:[DI], EAX
	} else {
		if(erase) {
			__emit__(0x66, 0x26, 0x21, 0x4D, p); // AND ES:[DI+p], ECX
		}
		__emit__(0x66, 0x26, 0x09, 0x45, p); // OR ES:[DI+p], EAX
	}
	return (p + 4);
#else
	return mo_16(erase, mo_16(erase, p));
#endif
}

recurse_impl_all(mo)
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
			mo_##width(false, 0); \
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
			erase_masked_or_mask_set(); \
			__emit__(0x1E); /* PUSH DS */ \
			_DS = blit_source.dots_start.part.seg; \
			mo_##width(true, 0); \
			__emit__(0x1F); /* POP DS */ \
			_SI -= (width / BYTE_DOTS); \
			_SI += blit_source.stride; \
			_DI += ROW_SIZE; \
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

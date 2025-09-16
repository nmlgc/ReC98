#include "platform/x86real/pc98/blit_low.hpp"
#include "game/coords.hpp"

extern LTRB<vram_x_t, screen_y_t> GrpClip;

// Generic default blitter
// -----------------------

// Abusing the fact that we're never going to blit (127 × 8) pixels...
inline void def_rep_setup(void) {
	_BH = _BL;
#if (CPU >= 386)
	_BL >>= 2;
#else
	_BL >>= 1;
#endif
}

#if (CPU == 386)
#define def_s_dwords_or_words() { \
	__emit__(0xF3, 0x66, 0xA5); /* REP MOVSD */ \
	if(_BH & 2) { \
		__emit__(0xA5); /* MOVSW */ \
	} \
}
#else
#define def_s_dwords_or_words() { \
	__emit__(0xF3, 0xA5); /* REP MOVSW */ \
}
#endif

#define def_impl(name, offscreen, reg_vram, reg_mem) \
	void __fastcall name(seg_t /* _AX */) \
	{ \
		_ES = _AX; /* First __fastcall parameter */ \
		_BX = blit_state.w_clipped; \
		_AX = blit_source.stride; \
		_AX -= _BX; \
		def_rep_setup(); \
		_SI = blit_source.dots_start.part.off; \
		_SI += blit_state.sprite_offset; \
		_DI = (offscreen ? vram_offset_shift(0, RES_Y) : blit_state.vo); \
		_DX = blit_state.h_clipped; \
		asm cld; \
		asm push ds; \
		_DS = blit_source.dots_start.part.seg; \
		_CX = 0; \
		do { \
			_CL = _BL; \
			def_s_dwords_or_words(); \
			if(_BH & 1) { \
				asm movsb; \
			} \
			reg_mem += _AX; \
			if(!offscreen) { \
				_CL = _BH; \
				reg_vram -= _CX; \
				reg_vram += ROW_SIZE; \
			} \
		} while(--static_cast<int16_t>(_DX) > 0); \
		asm pop ds; \
	}

def_impl(write_def, false, _DI, _SI);
def_impl(write_offscreen_def, true, _DI, _SI);
def_impl(near Blitter::snap, false, _SI, _DI);
// -----------------------

blit_state_t blit_state;
blit_source_t blit_source;

// Dynamic initialization saves code lines and keeps the binary small.
Blitter BLITTER_FUNCS[ROW_SIZE + 1];

void blitter_funcs_init(void)
{
	Blitter near *p = &BLITTER_FUNCS[1];
	for(vram_byte_amount_t i = 0; i < ROW_SIZE; (i++, p++)) {
		// The program might have added its own `#pragma startup` function that
		// could have ended up before this one in the `_INIT_` segment.
		if(!p->write) {
			p->write = write_def;
		}
		if(!p->write_offscreen) {
			p->write_offscreen = write_offscreen_def;
		}
	}
};

#pragma startup blitter_funcs_init

// Initialization
// --------------

const Blitter __ds* __fastcall blitter_init_clip(
	vram_x_t /* _AX */, vram_y_t /* _DX */
)
{
	#define _AX static_cast<int>(_AX)
	#define _CX static_cast<int>(_CX)
	#define _DX static_cast<int>(_DX)
	#define sprite_left static_cast<int>(_BX)
	#define sprite_top  static_cast<int>(_DX)

	sprite_left = _AX;
	sprite_top = _DX;

	// Top and bottom edges
	_CX = GrpClip.top;
	if(sprite_top < _CX) {
		sprite_top -= _CX;
		_AX = blit_source.h;
		_AX += sprite_top;
		if(_AX <= 0) {
			return nullptr;
		}
		blit_state.h_clipped = _AX;
		blit_state.sprite_offset = (
			blit_source.offset + (-sprite_top * blit_source.stride)
		);
		sprite_top = _CX;
	} else {
		_CX = GrpClip.bottom;
		_CX -= sprite_top;
		_AX = blit_source.h;
		if(_CX < _AX) {
			if(_CX <= 0) {
				return nullptr;
			}
			blit_state.h_clipped = _CX;
			_AX = blit_source.offset; // Turbo C++ 4.0J would put it into DX?!
			blit_state.sprite_offset = _AX;
		} else {
			blit_state.h_clipped = _AX;
			_AX = blit_source.offset; // Turbo C++ 4.0J would put it into DX?!
			blit_state.sprite_offset = _AX;
		}
	}
	_AX = sprite_top;
	sprite_top <<= 6;
	_AX <<= 4;
	_AX += sprite_top;
	blit_state.vo = _AX;

	// Left and right edges
	_CX = GrpClip.left;
	if(sprite_left < _CX) {
		sprite_left -= _CX;
		_AX = blit_source.w;
		_AX += sprite_left;
		if(_AX <= 0) {
			return nullptr;
		}
		blit_state.sprite_offset -= sprite_left;
		blit_state.vo += _CX;
		blit_state.w_clipped = _AX;
		return &BLITTER_FUNCS[_AX];
	} else {
		_DX = GrpClip.right;
		_DX -= sprite_left;
		_AX = blit_source.w;
		if(_DX < _AX) {
			if(_DX <= 0) {
				return nullptr;
			}
			blit_state.vo += sprite_left;
			blit_state.w_clipped = _DX;
			return &BLITTER_FUNCS[_DX];
		} else {
			blit_state.vo += sprite_left;
			blit_state.w_clipped = _AX;
			return &BLITTER_FUNCS[_AX];
		}
	}

	#undef sprite_top
	#undef sprite_left
	#undef _DX
	#undef _CX
	#undef _AX
}

const Blitter __ds& __fastcall blitter_init_noclip(
	vram_x_t /* _AX */, vram_y_t /* _DX */
)
{
	_BX = _AX;
	_AX = _DX;
	_DX <<= 6;
	_AX <<= 4;
	_AX += _DX;
	_AX += _BX;
	blit_state.vo = _AX;
	blit_state.sprite_offset = blit_source.offset;
	blit_state.h_clipped = blit_source.h;
	blit_state.w_clipped = blit_source.w;
	return BLITTER_FUNCS[blit_source.w];
}
// --------------

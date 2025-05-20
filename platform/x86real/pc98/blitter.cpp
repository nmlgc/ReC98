#include "platform/x86real/pc98/blit_low.hpp"
#include "game/coords.hpp"

extern LTRB<vram_x_t, screen_y_t> GrpClip;

blit_state_t blit_state;
blit_source_t blit_source;
Blitter BLITTER_FUNCS[ROW_SIZE + 1];

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

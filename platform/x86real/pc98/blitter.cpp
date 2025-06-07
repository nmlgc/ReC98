#include "platform/x86real/pc98/blit_low.hpp"

#define X(width) \
	void write_##width##(seg_t plane_seg, const void far* sprite) \
	{ \
		stationary_impl(plane_seg, sprite, width, d_##width, 0x80, 0); \
	} \
	\
	void or_##width##(seg_t plane_seg, const void far* sprite) \
	{ \
		stationary_impl(plane_seg, sprite, width, d_##width, 0x00, 0); \
	} \

	FOREACH_WIDTH
#undef X

blit_state_t blit_state;
blit_source_t blit_source;
Blitter BLITTER_FUNCS[] = {
	{ nullptr, nullptr }, // We want this array to be 1-based
	#define X(width) \
		{ write_##width, or_##width },

		FOREACH_WIDTH
	#undef X
};

// Initialization
// --------------

#define _AX static_cast<int>(_AX)
#define _CX static_cast<int>(_CX)
#define _DX static_cast<int>(_DX)

const Blitter __ds* __fastcall blitter_init_clip_lrtb(
	vram_x_t /* _AX */, vram_y_t /* _DX */
)
{
	#define sprite_left static_cast<int>(_BX)
	#define sprite_top  static_cast<int>(_DX)

	sprite_left = _AX;
	sprite_top = _DX;

	// Top and bottom edges
	if(sprite_top < 0) {
		_AX = blit_source.h;
		_AX += sprite_top;
		if(_AX <= 0) {
			return nullptr;
		}
		blit_state.h_clipped = _AX;
		blit_state.sprite_offset = (
			blit_source.offset + (-sprite_top * blit_source.stride)
		);
		sprite_top = 0;
	} else {
		_CX = RES_Y;
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
	if(sprite_left < 0) {
		_AX = blit_source.w;
		_AX += sprite_left;
		if(_AX <= 0) {
			return nullptr;
		}
		blit_state.sprite_offset -= sprite_left;
		return &BLITTER_FUNCS[_AX];
	} else {
		_DX = ROW_SIZE;
		_DX -= sprite_left;
		_AX = blit_source.w;
		if(_DX < _AX) {
			if(_DX <= 0) {
				return nullptr;
			}
			blit_state.vo += sprite_left;
			return &BLITTER_FUNCS[_DX];
		} else {
			blit_state.vo += sprite_left;
			return &BLITTER_FUNCS[_AX];
		}
	}

	#undef sprite_top
	#undef sprite_left
	#undef _DX
	#undef _CX
	#undef _AX
}

const Blitter __ds* blitter_init_clip_b(vram_x_t left, vram_y_t top)
{
	_DX = RES_Y;
	_DX -= top;
	_AX = blit_source.h;
	if(_DX < _AX) {
		if(_DX <= 0) {
			return nullptr;
		}
		blit_state.h_clipped = _DX;
	} else {
		blit_state.h_clipped = _AX;
	}
	blit_state.sprite_offset = blit_source.offset;
	blit_state.vo = vram_offset_shift_fast(left, top);
	return &BLITTER_FUNCS[blit_source.w];
}

#undef _DX
#undef _AX
// --------------

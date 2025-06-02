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
#define _DX static_cast<int>(_DX)

const Blitter __ds* blitter_init_clip_lrtb(vram_x_t left, vram_y_t top)
{
	// Top and bottom edges
	if(top < 0) {
		register pixel_t h = blit_source.h;
		if(top <= -h) {
			return nullptr;
		}
		blit_state.h_clipped = (h + top);
		blit_state.sprite_offset = (
			blit_source.offset - (top * blit_source.stride)
		);
		blit_state.vo = 0;
	} else {
		_DX = RES_Y;
		_DX -= top;
		_AX = blit_source.h;
		if(_DX < _AX) {
			if(_DX <= 0) {
				return nullptr;
			}
			blit_state.h_clipped = _DX;
			blit_state.sprite_offset = blit_source.offset;
			blit_state.vo = vram_offset_shift_fast(0, top);
		} else {
			blit_state.h_clipped = _AX;
			blit_state.sprite_offset = blit_source.offset;
			blit_state.vo = vram_offset_shift_fast(0, top);
		}
	}

	// Left and right edges
	if(left < 0) {
		register pixel_t w = blit_source.w;
		if(left <= -w) {
			return nullptr;
		}
		blit_state.sprite_offset -= left;
		return &BLITTER_FUNCS[w + left];
	} else {
		_DX = ROW_SIZE;
		_DX -= left;
		_AX = blit_source.w;
		if(_DX < _AX) {
			if(_DX <= 0) {
				return nullptr;
			}
			blit_state.vo += left;
			return &BLITTER_FUNCS[_DX];
		} else {
			blit_state.vo += left;
			return &BLITTER_FUNCS[_AX];
		}
	}
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

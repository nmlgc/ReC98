#include "platform/x86real/pc98/blit_low.hpp"

#define X(width) \
	void write_##width##(seg_t plane_seg, const void far* sprite) \
	{ \
		stationary_impl( \
			plane_seg, sprite, displaced, d_write, dots##width##_t \
		); \
	} \
	\
	void or_##width##(seg_t plane_seg, const void far* sprite) \
	{ \
		stationary_impl(plane_seg, sprite, displaced, d_or, dots##width##_t); \
	} \

	FOREACH_WIDTH
#undef X

blit_state_t blit_state;
Blitter BLITTER_FUNCS[] = {
	{ nullptr, nullptr }, // We want this array to be 1-based
	#define X(width) \
		{ write_##width, or_##width },

		FOREACH_WIDTH
	#undef X
};

// Initialization
// --------------

#define clip_b(rows, top, h, left) \
	/* Sneaky! That's how we can pretend this is an actual function that */ \
	/* returns a value. */ \
	(RES_Y - top); \
	if(rows <= 0) { \
		return nullptr; \
	} else if(rows > h) { \
		rows = h; \
	} \
	blit_state.sprite_offset = 0; \
	blit_state.vo = (vram_offset_shift(0, top) + left);

#define init_wh(w, rows) { \
	blit_state.sprite_w = w; \
	blit_state.loops_unrolled = ((rows + (UNROLL_H - 1)) / UNROLL_H); \
	blit_state.loops_remainder = (rows % UNROLL_H); \
}

const Blitter __ds* blitter_init_clip_lrtb(
	vram_x_t left, vram_y_t top, vram_byte_amount_t w, pixel_t h
)
{
	const Blitter __ds* ret;
	pixel_t rows;

	// Top and bottom edges
	if(top < 0) {
		if(top <= -h) {
			return nullptr;
		}
		blit_state.sprite_offset = (-top * w);
		rows = (h + top);
		blit_state.vo = 0;
	} else {
		rows = clip_b(rows, top, h, 0);
	}

	// Left and right edges
	if(left < 0) {
		if(left <= -w) {
			return nullptr;
		}
		blit_state.sprite_offset -= left;
		ret = &BLITTER_FUNCS[-left];
	} else if(left > (ROW_SIZE - w)) {
		if(left >= ROW_SIZE) {
			return nullptr;
		}
		blit_state.vo += left;
		ret = &BLITTER_FUNCS[ROW_SIZE - left];
	} else {
		blit_state.vo += left;
		ret = &BLITTER_FUNCS[w];
	}
	init_wh(w, rows);
	return ret;
}

const Blitter __ds* blitter_init_clip_b(
	vram_x_t left, vram_y_t top, vram_byte_amount_t w, pixel_t h
)
{
	pixel_t rows = clip_b(rows, top, h, left);
	init_wh(w, rows);
	return &BLITTER_FUNCS[w];
}
// --------------

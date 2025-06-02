/// Optimized byte-aligned sprite blitter
/// -------------------------------------

#include "planar.h"

typedef void (* blit_func_t)(seg_t plane_seg, const void far* sprite);

struct Blitter {
	blit_func_t write;
	blit_func_t or;
};

// Persistent state that defines the region of the blitted sprite.
struct blit_source_t {
	vram_byte_amount_t stride;
	uint16_t offset; // Byte offset to the top-left pixel to be blitted
	vram_byte_amount_t w;
	pixel_t h;
};

extern blit_source_t blit_source;

#define blitter_set_source_region(left, top, w_, h_, stride_) { \
	blit_source.stride = stride_; \
	blit_source.offset = ((top * stride_) + left); \
	blit_source.w = w_; \
	blit_source.h = h_; \
}

// Temporary state for the current blitter run.
struct blit_state_t {
	vram_offset_t vo;

	// First blitted byte within the sprite. Can be nonzero if the sprite was
	// clipped at the left or top edge of VRAM.
	uint16_t sprite_offset;

	upixel_t h_clipped;
};

extern blit_state_t blit_state;

// Initialization
// --------------
// All of these set up blitting of the previously configured sprite region at
// the given VRAM offset, cutting it at the indicated VRAM boundaries and
// assuming that it does not touch the others. If the sprite would be cut to a
// width or height of 0, they return a `nullptr` and leave the blitter in an
// invalid state.

// Checks all 4 edges of VRAM.
const Blitter __ds* blitter_init_clip_lrtb(vram_x_t left, vram_y_t top);

// Checks the bottom edge of VRAM.
const Blitter __ds* blitter_init_clip_b(vram_x_t left, vram_y_t top);
// --------------

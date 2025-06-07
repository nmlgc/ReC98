/// Optimized byte-aligned sprite blitter
/// -------------------------------------

#include "planar.h"

struct Blitter {
	void (__fastcall *write)(seg_t plane_seg);
};

// Persistent state that defines the region of the blitted sprite.
struct blit_source_t {
	// Start of the sprite's bitplane
	union {
		struct {
			uint16_t off;
			seg_t seg;
		} part;
		const void far *fp;
	} dots_start;
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

// Sets up blitting of the previously configured sprite region at the given
// VRAM offset, cutting it to the clipping region set with Grp_SetClip().
// Returns a blitter if the sprite is visible, or a `nullptr` if it isn't.
const Blitter __ds* __fastcall blitter_init_clip(vram_x_t left, vram_y_t top);

// Sets up blitting of the previously configured sprite region at the given
// VRAM offset. Always returns a blitter.
const Blitter __ds& __fastcall blitter_init_noclip(vram_x_t left, vram_y_t top);
// --------------

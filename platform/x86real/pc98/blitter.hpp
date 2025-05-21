/// Optimized byte-aligned sprite blitter
/// -------------------------------------

#include "planar.h"

typedef void (* blit_func_t)(seg_t plane_seg, const void far* sprite);

struct Blitter {
	blit_func_t write;
	blit_func_t or;
};

struct blit_state_t {
	vram_offset_t vo;

	// First blitted byte within the sprite. Can be nonzero if the sprite was
	// clipped at the left or top edge of VRAM.
	uint16_t sprite_offset;

	// Always set to the original width of the sprite. Can be larger than the
	// blitted width if the sprite is clipped.
	vram_byte_amount_t sprite_w;

	upixel_t h_clipped;
};

extern blit_state_t blit_state;

// Initialization
// --------------
// All of these set up blitting of a ([w]*8)×[h]-pixel sprite at the given VRAM
// offset, cutting it at the respectively checked VRAM boundaries and assuming
// that it does not touch the others. If the sprite would be cut to a width or
// height of 0, they return a `nullptr` and leave the blitter in an invalid
// state.

// Checks all 4 edges of VRAM.
const Blitter __ds* blitter_init_clip_lrtb(
	vram_x_t left, vram_y_t top, vram_byte_amount_t w, pixel_t h
);

// Checks the bottom edge of VRAM.
const Blitter __ds* blitter_init_clip_b(
	vram_x_t left, vram_y_t top, vram_byte_amount_t w, pixel_t h
);
// --------------

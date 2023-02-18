/// Optimized byte-aligned sprite blitter
/// -------------------------------------

typedef void (* blit_func_t)(seg_t plane_seg, const void far* sprite);

struct Blitter {
	blit_func_t write;
	blit_func_t or;
};

// Internals
// ---------

static const upixel_t UNROLL_H = 8;

struct blit_state_t {
	vram_offset_t vo;

	// First blitted byte within the sprite. Can be nonzero if the sprite was
	// clipped at the left or top edge of VRAM.
	uint16_t sprite_offset;

	// Always set to the original width of the sprite. Can be larger than the
	// blitted width if the sprite is clipped.
	vram_byte_amount_t sprite_w;

	// 16-bit because it gets loaded into BX anyway.
	pixel_t loops_remainder;

	int16_t loops_unrolled;
};

extern blit_state_t blit_state;

#define blitter_body(plane_seg, sprite, func_row, row_p1, row_p2) { \
	register int16_t loops_unrolled = blit_state.loops_unrolled; \
	_SI = FP_OFF(sprite); \
	_SI += blit_state.sprite_offset; \
	_DI = blit_state.vo; \
	_DX = blit_state.sprite_w; \
	_BX = blit_state.loops_remainder; \
	\
	/* Turbo C++ 4.0J does not back up DS if the function mutates it. */ \
	/* [blit_state] can't be accessed anymore beyond this point! */ \
	_asm { push ds; } \
	_DS = FP_SEG(sprite); \
	_ES = plane_seg; \
	\
	static_assert(UNROLL_H == 8); \
	switch(_BX) { \
	case 0: do { func_row(row_p1, row_p2) \
	case 7:      func_row(row_p1, row_p2) \
	case 6:      func_row(row_p1, row_p2) \
	case 5:      func_row(row_p1, row_p2) \
	case 4:      func_row(row_p1, row_p2) \
	case 3:      func_row(row_p1, row_p2) \
	case 2:      func_row(row_p1, row_p2) \
	case 1:      func_row(row_p1, row_p2) \
	/*       */} while(--loops_unrolled > 0); \
	} \
	\
	_asm { pop ds; } \
}
// ---------

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

// Checks the bottom edge of VRAM, assumes that the sprite does not intersect
const Blitter __ds* blitter_init_clip_b(
	vram_x_t left, vram_y_t top, vram_byte_amount_t w, pixel_t h
);
// --------------

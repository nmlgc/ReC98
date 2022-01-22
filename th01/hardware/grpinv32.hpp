// Inverts the 32×32 square at (⌊left/8⌋*8, top) on the given VRAM [plane].
// Returns true if the square is not fully within the boundaries of VRAM and
// was not inverted, false otherwise.
bool16 graph_invert_32x32_8(screen_x_t left, vram_y_t top, dots8_t far *plane);

/// Expanding 4-stack, 32-square boss entrance rings
/// ------------------------------------------------
/// Final part of Kikuri's and Sariel's entrance animation. Renders the
/// individual squares in order, and thus only requires a single control
/// variable to indicate both the ring number and the angle within the ring.

static const int ENTRANCE_RING_STACK = 4;
static const int ENTRANCE_RING_SQUARES = 32;

inline long entrance_ring_radius(pixel_t base, unsigned int square_i) {
	return (base * static_cast<long>(square_i / ENTRANCE_RING_SQUARES));
}

#define entrance_ring_invert(square_i, radius_base) \
	graph_invert_32x32_8( \
		polar_y( \
			static_cast<long>((RES_X / 2) - (32 / 2)), \
			entrance_ring_radius(radius_base, square_i), \
			(i * (0x100 / ENTRANCE_RING_SQUARES)) \
		), \
		polar_x(\
			static_cast<long>(((RES_Y / 2) - 4) - (32 / 2)), \
			entrance_ring_radius(radius_base, square_i), \
			(i * (0x100 / ENTRANCE_RING_SQUARES)) \
		), \
		VRAM_PLANE_R \
	); \

// Stupid inconsistencies deserve stupid macro treatment...
#define entrance_rings_invert(square_i, invert_lhs, radius_base) { \
	for( \
		square_i = (1 * ENTRANCE_RING_SQUARES); \
		square_i < ((1 + ENTRANCE_RING_STACK) * ENTRANCE_RING_SQUARES); \
		i++ \
	) { \
		invert_lhs entrance_ring_invert(square_i, radius_base); \
	} \
}

#define entrance_rings_done(squares_offscreen) \
	(squares_offscreen >= (ENTRANCE_RING_STACK * ENTRANCE_RING_SQUARES))
/// ------------------------------------------------

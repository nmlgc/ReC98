#include "th01/math/polar.hpp"
#include "planar.h"

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

#define entrance_ring_radius(base, square_i) ( \
	base * static_cast<long>(square_i / ENTRANCE_RING_SQUARES) \
)

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
		square_i++ \
	) { \
		invert_lhs entrance_ring_invert(square_i, radius_base); \
	} \
}

// Well, well, we'd *really* like call sites to use this macro within an `if`
// statement. That makes it looks as if this macro is actually a function that
// returns whether the animation is done or not. Unfortunately, the completion
// condition is itself nested within a conditional branch. This only leaves
// ugly workarounds:
//
// 1) Forcing calling sites to close a block they didn't open
// 2) A fake lambda function in another macro parameter
// 3) Using `goto` and jumping to a label (`entrance_rings_still_active`) that
//    we force the call site to define
//
// Option 3) doesn't introduce weird syntax and thus feels like the most
// natural choice.
#define entrance_rings_update_and_render( \
	radius_base, i, squares_offscreen, frame, radius_base_initial, frame_first \
) \
	frame == frame_first) { \
		radius_base = radius_base_initial; \
		goto entrance_rings_still_active; \
	} else if(frame == (frame_first + 1)) { \
		entrance_rings_invert(i, {}, radius_base); \
		goto entrance_rings_still_active; \
	} else if((frame > (frame_first + 1)) && ((frame % 4) == 0)) { \
		/* "Un-invert" the previous frame */ \
		entrance_rings_invert(i, {}, radius_base); \
		\
		radius_base += 16; \
		squares_offscreen = 0; \
		\
		entrance_rings_invert(i, squares_offscreen +=, radius_base); \
	} else { \
		goto entrance_rings_still_active; \
	} \
	if(squares_offscreen >= (ENTRANCE_RING_STACK * ENTRANCE_RING_SQUARES)
/// ------------------------------------------------

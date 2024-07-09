#pragma option -k-

#include "planar.h"
#include "platform/x86real/flags.hpp"
#include "th04/hardware/grcg.hpp"
#include "th04/main/playfld.hpp"
#include "th04/main/checkerb.hpp"

// Constants
// ---------

#define CHECKERBOARD_W 32
#define CHECKERBOARD_H 32
static const pixel_t CHECKERBOARD_SPEED = 4;

// In the very unusual unit of "VRAM bytes per frame".
static const vram_byte_amount_t CHECKERBOARD_VO_SPEED = (
	CHECKERBOARD_SPEED * ROW_SIZE
);

static const vram_byte_amount_t CHECKERBOARD_VRAM_W = (
	CHECKERBOARD_W / BYTE_DOTS
);
// ---------

struct checkerboard_t {
	// Points to the top row of the bottommost square.
	// Should technically be the unsigned `seg_t` type, *especially* since it's
	// used in comparisons. Luckily, all values we compare remain in the
	// "negative" range from 0x8000 to 0xFFFF and don't cross over into
	// positive values, which makes signed comparisons still correct.
	int16_t seg_bottom;

	// Not vram_offset_t, as they're relative to the custom segments calculated
	// from [seg_bottom].
	vram_byte_amount_t off_bottom;
	vram_byte_amount_t off_top;

	union {
		struct {
			uint8_t vo_x_of_dark; // ACTUAL TYPE: vram_offset_t

			// ZUN bloat: Doesn't make sense with any value other than 2.
			uint8_t loops;
		} var;
		uint16_t both;
	} u1;
};

extern checkerboard_t checkerboard;

#define checkerboard_vo_x_flip(v) { \
	/* Overly clever trick that relies on the position for the first and \
	 * second square not sharing any bits. */ \
	static_assert((PLAYFIELD_LEFT & (PLAYFIELD_LEFT + CHECKERBOARD_W)) == 0); \
	v ^= (PLAYFIELD_VRAM_LEFT | (PLAYFIELD_VRAM_LEFT + CHECKERBOARD_VRAM_W)); \
}

// ZUN bloat: Turbo C++ 4.0J even warns that the result should be unsigned
// because [SEG_PLANE_B] doesn't fit into a signed variable, and then
// automatically treats it as unsigned. Therefore, we need this additional cast
// to retain the signed comparisons from ZUN's original code.
#define grcg_segment_(x, y) static_cast<int16_t>(grcg_segment(x, y))

void near playfield_checkerboard_grcg_tdw_update_and_render(void)
{
	#define loops_and_vo_x	_BX
	#define loops         	_BH
	#define vo_x          	_BL

	// Not vram_offset_t, as it's relative to the custom segments calculated
	// from [seg_bottom].
	#define vram_off static_cast<int16_t>(_DI)

	// Same signedness issue as with [seg_bottom].
	#define vram_seg static_cast<int16_t>(_DX)

	grcg_setcolor_direct_constant(0);
	loops_and_vo_x = checkerboard.u1.both;

	// Bottom row
	while(1) {
		vram_seg = checkerboard.seg_bottom;
		vram_off = loops_and_vo_x;
		vram_off &= 0xFF; // Isolate [vo_x], ignoring the loop count
		vram_off += checkerboard.off_bottom;
		goto put;

		// Top row
		do {
			vram_seg = grcg_segment(0, PLAYFIELD_TOP);
			vram_off = loops_and_vo_x;
			vram_off &= 0xFF; // Isolate [vo_x], ignoring the loop count
			vram_off += checkerboard.off_top;
			goto put;

			// Fully visible, regular rows within the playfield
			do {
				vram_off = loops_and_vo_x;
				vram_off &= 0xFF; // Isolate [vo_x], ignoring the loop count
				vram_off += ((CHECKERBOARD_H - 1) * ROW_SIZE);

			put:
				_ES = vram_seg;
				do {
					_CX = ((PLAYFIELD_W / CHECKERBOARD_W) / 2);
					put_loop: {
						*reinterpret_cast<dots_t(CHECKERBOARD_W) __es *>(
							vram_off
						) = _EAX;
						vram_off += (CHECKERBOARD_VRAM_W * 2);
						asm { loop put_loop; }
					}
				} while((vram_off -= (ROW_SIZE + PLAYFIELD_VRAM_W)) >= 0);

				// Move [vram_seg] to the next column and row, and continue if
				// we haven't reached the top of the playfield yet.
				checkerboard_vo_x_flip(vo_x);
				vram_seg -= ((CHECKERBOARD_H * ROW_SIZE) / 16);
			} while(vram_seg > grcg_segment_(0, PLAYFIELD_TOP));

			// If we came here from the top row, [vram_seg] is in fact exactly
			// equal to this value. Otherwise, jump there.
		} while(vram_seg != grcg_segment_(0, (PLAYFIELD_TOP - CHECKERBOARD_H)));

		loops--;
		if(FLAGS_ZERO) {
			break;
		}

		grcg_setcolor_direct_constant(1);
		vo_x = checkerboard.u1.var.vo_x_of_dark;
		checkerboard_vo_x_flip(vo_x);
	}

	checkerboard.seg_bottom -= (CHECKERBOARD_VO_SPEED / 16);
	checkerboard.off_bottom += CHECKERBOARD_VO_SPEED;
	if(checkerboard.seg_bottom < grcg_segment_(
		0, (PLAYFIELD_BOTTOM - CHECKERBOARD_H)
	)) {
		// The bottom row would be (CHECKERBOARD_H + CHECKERBOARD_SPEED) pixels
		// high on the next frame, which means that we've fully scrolled the
		// bottommost square onto the playfield during this frame. Start the
		// new frame at the CHECKERBOARD_SPEED offset, and flip the colors
		// accordingly.
		checkerboard.seg_bottom = grcg_segment(
			0, (PLAYFIELD_BOTTOM - CHECKERBOARD_SPEED)
		);
		checkerboard.off_bottom = CHECKERBOARD_VO_SPEED;
		checkerboard_vo_x_flip(checkerboard.u1.var.vo_x_of_dark);
	}
	checkerboard.off_top -= CHECKERBOARD_VO_SPEED;
	if(FLAGS_SIGN) {
		// Scrolled the top row off the playfield, so we start a new one at the
		// bottom of a full square in the next frame. No color flip necessary
		// here, since we render from bottom to top. (There's also always a
		// half-scrolled square at the bottom whenever we get here.)
		checkerboard.off_top = ((CHECKERBOARD_H - 1) * ROW_SIZE);
	}

	#undef vram_seg
	#undef vram_off
	#undef vo_x
	#undef loops
	#undef loops_and_vo_x
}

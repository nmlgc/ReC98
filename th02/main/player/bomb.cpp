#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "th01/math/overlap.hpp"
#include "th02/main/playfld.hpp"
#include "th02/main/scroll.hpp"
#include "th02/sprites/bombpart.h"

extern int bomb_frame;
extern point_t bomb_circle_center;
extern int bomb_circle_frame;

extern nearfunc_t_near playchar_bomb_func;

// Function ordering fails
// -----------------------

// These assume the GRCG to be set to RMW mode, with a tile in the intended
// color.
void pascal near bomb_circle_point_put(screen_x_t left, screen_y_t top);
// -----------------------

void pascal near bomb_reimu_a(void);
void pascal near bomb_reimu_c(void);
void pascal near bomb_reimu_b(void);

// ZUN bloat: Needed to circumvent 16-bit promotion in a single comparison.
inline int8_t bomb_particle_h(void) {
	return BOMB_PARTICLE_H;
}

void pascal near bomb_circle_point_put(screen_x_t left, screen_y_t top)
{
	#define vram_top          	static_cast<vram_y_t>(_DX)
	#define first_bit_mirrored	_DX

	register const bomb_particle_dots_t near* sprite;
	int8_t y;
	unsigned int first_bit;

	if(!overlap_xy_ltrb_lt_gt(
		left, top,
		(PLAYFIELD_LEFT - BOMB_PARTICLE_W),
		(PLAYFIELD_TOP  - BOMB_PARTICLE_H),
		PLAYFIELD_RIGHT,
		PLAYFIELD_BOTTOM
	)) {
		return;
	}

	_ES = SEG_PLANE_B;
	vram_top = scroll_screen_y_to_vram(vram_top, top);
	_BX = left;
	vram_offset_shift_fast_asm(di, bx, vram_top);

	// ZUN bloat: Turbo C++ 4.0J would otherwise only ever generate an 8-bit
	// AND.
	asm { and	bx, BYTE_MASK; }

	first_bit = _BX;
	first_bit_mirrored = (sizeof(dots16_t) * BYTE_DOTS);

	// ZUN bloat: first_bit_mirrored -= _BX;
	asm { sub	dx, bx; }

	sprite = sBOMB_CIRCLE;
	y = 0;
	do {
		// ZUN bloat: A manual 16-bit right rotation. Turbo C++ 4.0J has
		// intrinsics for that, which compile into a single ROR instruction:
		//
		// 	*reinterpret_cast<dots16_t __es *>(vo) = __rotr__(
		// 		*sprite, first_bit
		// );
		asm { xor	ax, ax; }
		_AL = *sprite;
		asm { mov	bx, ax; }
		_CX = first_bit;
		_BX >>= _CL;
		asm { mov	cx, dx; }
		_AX <<= _CL;
		asm { add	ax, bx; }
		*reinterpret_cast<dots16_t __es *>(_DI) = _AX;

		vram_offset_add_and_roll(_DI, ROW_SIZE);
		sprite++;
		y++;
	} while(y < bomb_particle_h());

	#undef first_bit_mirrored
	#undef vram_top
}

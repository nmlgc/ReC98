#include "planar.h"
#include "th01/sprites/pellet.h"

extern const dots16_t sPELLET[PELLET_CELS][PRESHIFT][PELLET_H];

void pascal near pellet_render(screen_x_t left, vram_y_t top)
{
	_ES = SEG_PLANE_B;
	_BX = _BX; // Keeps any parameters from being put into BX
	_DI = vram_offset_shift_fast(left, top);
	_SI = reinterpret_cast<uint16_t>(sPELLET[0][left & BYTE_MASK]);
	_CX = PELLET_H;
	put_loop: {
		asm { movsw; }
		vram_offset_add_and_roll(_DI, (ROW_SIZE - sizeof(dots16_t)));
		asm { loop put_loop; }
	}
}

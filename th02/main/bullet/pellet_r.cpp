#include "th01/sprites/pellet.h"

extern const dots16_t sPELLET[PELLET_CELS][PRESHIFT][PELLET_H];

void pascal near pellet_render(screen_x_t left, vram_y_t top)
{
	_ES = SEG_PLANE_B;
	_BX = _BX; // Keeps any parameters from being put into BX

	_AX = (left >> 3);
	_DX = top;
	_DX <<= 6;
	_AX += _DX;
	_DX >>= 2;
	_DI = _AX + _DX;

	_SI = reinterpret_cast<uint16_t>(sPELLET[0][left & BYTE_MASK]);
	_CX = 8;
	put_loop: {
		asm { movsw; }
		_DI += (ROW_SIZE - sizeof(dots16_t));
		if(static_cast<int16_t>(_DI) >= PLANE_SIZE) {
			_DI -= PLANE_SIZE;
		}
	}
	asm { loop put_loop; }
}

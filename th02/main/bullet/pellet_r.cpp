#include "th01/sprites/pellet.h"

void pascal near pellet_render(int left, int top)
{
	_ES = SEG_PLANE_B;
	_BX = _BX; // Keeps any parameters from being put into BX

	_AX = (left >> 3);
	_DX = top;
	_DX <<= 6;
	_AX += _DX;
	_DX >>= 2;
	_DI = _AX + _DX;

	_SI = reinterpret_cast<uint16_t>(sPELLET[left & 7]);
	_CX = 8;
	put_loop: {
		asm movsw
		_DI += (ROW_SIZE - sizeof(dots16_t));
		if(static_cast<int16_t>(_DI) >= PLANE_SIZE) {
			_DI -= PLANE_SIZE;
		}
	}
	asm loop put_loop;
}

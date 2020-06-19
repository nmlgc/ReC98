#include "th01/sprites/pellet.h"

void pellet_put(int left, int top, int cel)
{
	// Some `__asm` statements here look like they could be expressed using
	// register pseudovariables. However, TCC would then use a different
	// instruction than the one in ZUN's original binary.
	_ES = SEG_PLANE_B;

	_AX = (left >> 3);
	_DX = top;
	_DX <<= 6;
	__asm add	ax, dx;
	_DX >>= 2;
	__asm add	ax, dx;
	__asm mov	di, ax;

	_AX = (left & 7) << 4;
	_BX = cel;
	_BX <<= 7;
	__asm add	ax, bx;
	_AX += reinterpret_cast<uint16_t>(sPELLET);

	__asm mov	si, ax;
	_CX = PELLET_H;
	put_loop: {
		__asm movsw
		_DI += (ROW_SIZE - sizeof(dots16_t));
		if(static_cast<int16_t>(_DI) >= PLANE_SIZE) {
			return;
		}
	}
	__asm loop	put_loop;
}

void pellet_render(int left, int top, int cel)
{
	grcg_setcolor_rmw(7);
	pellet_put(left, top, cel);
	grcg_off();
}

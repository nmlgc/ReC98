#include "th03/op/m_main.hpp"
#include "platform/x86real/pc98/page.hpp"
#include "platform/x86real/flags.hpp"
#include "planar.h"

void pascal near box_column16_unput(uscreen_x_t left)
{
	register dots16_t px_b;
	register dots16_t px_g;
	register dots16_t px_r;
	register dots16_t px_e;

	_AX = (left / BYTE_DOTS);
	_DI = vram_offset_shift(0, (BOX_BOTTOM - 1));
	_DI += _AX;
	_ES = vram_segment(B, 0, BOX_TOP);
	do {
		page_access(1);
		/*                              */	px_b = _peek_(_ES, _DI);
		_ES = vram_segment(R, 0, BOX_TOP);	px_r = _peek_(_ES, _DI);
		_ES = vram_segment(G, 0, BOX_TOP);	px_g = _peek_(_ES, _DI);
		_ES = vram_segment(E, 0, BOX_TOP);	px_e = _peek_(_ES, _DI);
		page_access(_AL ^= _AL);
		/*                              */	_poke_(_ES, _DI, px_e);
		_ES = vram_segment(G, 0, BOX_TOP);	_poke_(_ES, _DI, px_g);
		_ES = vram_segment(R, 0, BOX_TOP);	_poke_(_ES, _DI, px_r);
		_ES = vram_segment(B, 0, BOX_TOP);	_poke_(_ES, _DI, px_b);
		_DI -= ROW_SIZE;
	} while(!FLAGS_CARRY);
}

#include "platform.h"
#include "pc98.h"
#include "th03/main/playfld.hpp"

bool pascal playfield_clip(
	PlayfieldSubpixel center_x, PlayfieldSubpixel center_y
)
{
	// ZUN bloat: Needlessly micro-optimized.
	_AX = false;
	playfield_subpixel_t y;
	playfield_subpixel_t x = center_x;
	y = center_y;

	_BX = playfield_clip_negative_radius.x;
	if(x <= static_cast<playfield_subpixel_t>(_BX)) {
		goto outside;
	}
	asm { neg bx };
	_BX += to_sp(PLAYFIELD_W);
	if(x >= static_cast<playfield_subpixel_t>(_BX)) {
		goto outside;
	}

	_BX = playfield_clip_negative_radius.y;
	if(y <= static_cast<playfield_subpixel_t>(_BX)) {
		goto outside;
	}
	asm { neg bx };
	_BX += to_sp(PLAYFIELD_H);
	if(y < static_cast<playfield_subpixel_t>(_BX)) {
		goto inside;
	}
outside:
	_AL = true;
inside:
	return _AX;
}

#pragma codestring "\x90"

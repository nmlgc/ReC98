#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "th03/main/playfld.hpp"

screen_x_t pascal playfield_fg_x_to_screen(playfield_subpixel_t x, pid2 pid)
{
	// ZUN bloat: (PLAYFIELD_LEFT +
	// 	(pid * PLAYFIELD_W_BORDERED) + TO_PIXEL(x) + playfield_fg_shift_x[pid]
	// ). It's that simple and wouldn't even have required branching. Maybe put
	// the left coordinate of both playfields into an array if you really don't
	// like that multiplication.
	#define ret   	static_cast<screen_x_t>(_AX)
	#define offset	_BX

	ret = x;
	offset = pid;
	ret = TO_PIXEL(ret);
	if(offset) {
		ret += PLAYFIELD_W_BORDERED;
		offset = sizeof(playfield_fg_shift_x[0]);
	}
	ret += *reinterpret_cast<screen_x_t *>(
		reinterpret_cast<uint8_t *>(playfield_fg_shift_x) + offset
	);
	ret += PLAYFIELD_LEFT;
	return ret;

	#undef offset
	#undef ret
}

#pragma codestring "\x90"

playfield_subpixel_t pascal screen_x_to_playfield(screen_x_t x, pid2 pid)
{
	_BX = _SP; // ZUN bloat: Has no effect.

	// ZUN bloat: Abuses the assertion.
	screen_x_t playfield_left = pid;
	static_assert(PLAYFIELD1_CLIP_LEFT == 0);
	if(static_cast<int8_t>(playfield_left)) { // ZUN bloat: Needless 8-bit cast
		playfield_left = PLAYFIELD_W_BORDERED;
	}
	return TO_SP(((x - playfield_left) - PLAYFIELD_BORDER));
}

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

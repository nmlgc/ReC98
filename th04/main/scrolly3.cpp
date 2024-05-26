#pragma option -k- -G

#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "th01/math/subpixel.hpp"
#include "th04/main/scroll.hpp"

#define roll(y) \
	/* Sneaky! That's how we can pretend this is an actual function that */ \
	/* returns a value. */ \
	y; \
	if(y >= RES_Y) { \
		y -= RES_Y; \
	} else if(y < 0) { \
		y += RES_Y; \
	}

vram_y_t pascal near scroll_subpixel_y_to_vram_seg3(subpixel_t y)
{
	#define ret static_cast<vram_y_t>(_AX) // Must be signed!

	_BX = _SP;
	ret = peek(_SS, (_BX + 2)); /* = */ (y);

	ret = TO_PIXEL(ret);
	if(scroll_active) {
		ret += scroll_line;
	}
	ret = roll(ret);
	return ret;

	#undef ret
}

vram_y_t pascal near scroll_subpixel_y_to_vram_always(subpixel_t y)
{
	#define ret static_cast<vram_y_t>(_AX) // Must be signed!

	_BX = _SP;
	ret = peek(_SS, (_BX + 2)); /* = */ (y);

	ret = (TO_PIXEL(ret) + scroll_line);
	ret = roll(ret);
	return ret;

	#undef ret
}
#pragma codestring "\x90"

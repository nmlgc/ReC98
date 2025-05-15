#pragma option -k- -G

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
	vram_y_t ret = TO_PIXEL(y);
	if(scroll_active) {
		ret += scroll_line;
	}
	ret = roll(ret);
	return ret;
}

vram_y_t pascal near scroll_subpixel_y_to_vram_always(subpixel_t y)
{
	vram_y_t ret = (TO_PIXEL(y) + scroll_line);
	ret = roll(ret);
	return ret;
}
#pragma codestring "\x90"

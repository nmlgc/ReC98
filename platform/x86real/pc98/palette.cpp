#include "x86real.h"
#include "platform/palette.hpp"

void palette_show_single(vc_t col, const RGB4& c)
{
	outportb(0xA8, col);
	outportb(0xAA, c.c.g);
	outportb(0xAC, c.c.r);
	outportb(0xAE, c.c.b);
}

void palette_show(const Palette4& pal)
{
	const RGB4* color = pal.colors;
	for(vc_t i = 0; i < COLOR_COUNT; i++) {
		palette_show_single(i, *(color++));
	}
}

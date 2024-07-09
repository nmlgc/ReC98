#include <stdio.h>
#include <stdarg.h>
#include "th01/hardware/grp_text.hpp"

void graph_printf_fx(
	screen_x_t left,
	vram_y_t top,
	int16_t col_and_fx,
	const shiftjis_t *fmt,
	...
)
{
	char str[256];
	va_list ap;

	va_start(ap, fmt);
	vsprintf(str, fmt, ap);
	graph_putsa_fx(left, top, col_and_fx, str);
}

#include <stdio.h>
#include <stdarg.h>
#include "platform.h"
#include "pc98.h"
#include "shiftjis.hpp"
extern "C" {
#include "th01/hardware/grppsafx.h"
}

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

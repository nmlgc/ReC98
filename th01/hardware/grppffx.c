#pragma option -Z

#include <stdio.h>
#include <stdarg.h>
#include "ReC98.h"
#include "th01/hardware/graph.h"

void graph_printf_fx(int left, int top, int fx, const char *fmt, ...)
{
	char str[256];
	va_list ap;

	va_start(ap, fmt);
	vsprintf(str, fmt, ap);
	graph_putsa_fx(left, top, fx, str);
}

#pragma option -Z-

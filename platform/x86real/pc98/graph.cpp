#include "platform.h"
#include "x86real.h"
#include "platform/x86real/pc98/graph.hpp"

void graph_show_16color_400line(void)
{
	// Enter 400-line mode
	_AH = 0x42;
	_CH = 0xC0;
	geninterrupt(0x18);

	// Enter 16-color mode
	outportb(0x6A, 1);

	// Show VRAM
	_AH = 0x40;
	geninterrupt(0x18);
}

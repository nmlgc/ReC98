#pragma option -zCGRAPH_EX_TEXT -2 -Z-

#include "x86real.h"
#include "th01/hardware/scrollup.hpp"

static const int GDC_ROW_SIZE = (ROW_SIZE / 2);

// Actually taken straight from the setgsta() example function from the
// PC-9801 Programmers' Bible, p. 150.
void z_vsync_wait_and_scrollup(vram_y_t line_on_top)
{
	line_on_top %= RES_Y;

	int16_t dp1sta = (line_on_top * GDC_ROW_SIZE);
	// Line counts start at the 5th bit of the parameter
	int16_t dp1lin = ((RES_Y - line_on_top) << 4);
	int16_t dp2sta = (0 * GDC_ROW_SIZE);
	int16_t dp2lin = (line_on_top << 4);

	// Display address increment time; depends on the GDC clock frequency
	int im;
	if((peekb(0, 0x54D) & 4) == 0) {	// GDC clock == 2.5 MHz?
		im = 0;
	} else {
		im = (1 << 6); // 6th bit inside the parameter
	}
	// Wait until VSYNC
	while( (inportb(0xA0) & 0x20) != 0 );
	while( (inportb(0xA0) & 0x20) == 0 );
	// Wait until the graphics GDC's command FIFO is empty
	while( (inportb(0xA0) & 0x04) == 0 );

	// Graphics GDC SCROLL command
	// (see PC-9801 Programmers' Bible, p. 143)
	// ---------------------------
	// 7 = SCROLL, 0 = starting regularly with the first parameter
	outport(0xA2, 0x70);
	// Display partition #1
	outportb(0xA0, (dp1sta % 0x100));
	outportb(0xA0, (dp1sta / 0x100));
	outportb(0xA0, (dp1lin % 0x100));
	outportb(0xA0, ((dp1lin / 0x100) + im));
	// Display partition #2
	outportb(0xA0, (dp2sta % 0x100));
	outportb(0xA0, (dp2sta / 0x100));
	outportb(0xA0, (dp2lin % 0x100));
	outportb(0xA0, ((dp2lin / 0x100) + im));
	// ---------------------------
}

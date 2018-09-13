/* ReC98 Research
 * --------------
 * PC-98 keyboard key hold behavior test
 */

#pragma option -ms

#include "../libs/master.lib/master.h"

#if defined(__TURBOC__) && defined(__MSDOS__)
// Remove C++ exception handler bloat on Borland compilers
// (see https://community.embarcadero.com/article/technical-articles/162/14700)
void _ExceptInit(void)
{
}
#endif

// Should cover the number of possible input states within a frame
// ⌈(19200 baud / 11 bit) / 56.4 fps⌉ ≈ 31, but let's rather be extra safe...
#define STATES_MAX 64

void hr(int len)
{
	int i;
	dos_puts("\r\n");
	for(i = 0; i < len; i++) {
		dos_puts("\x86\x44");
	}
	dos_puts("\r\n");
}

void frame(void)
{
	char states[STATES_MAX];
	char state_prev = 0;
	unsigned int states_recorded = 0;
	unsigned int i = 0;
	int flipped = 0;

	vsync_Count1 = 0;
	do {
		int delayloop = 1024;
		unsigned char input = *(volatile unsigned char far*)(0x531);
		states[states_recorded++] = (input >> 2) & 0xF;

		while(delayloop && vsync_Count1 < 1) {
			_asm out 0x5F, AL;
			delayloop--;
		}
	} while(vsync_Count1 < 1);

	dos_puts("\r                                                                               \r");
	for(i = 0; i < states_recorded; i++) {
		char state = states[i];

		if(state_prev != state && i > 0) {
			flipped++;
			dos_puts("\x1B[17m");
		} else {
			dos_puts("\x1B[0m");
		}

		dos_putch((state < 10) ? ('0' + state) : ('A' - 10 + state));
		dos_putch(' ');
		state_prev = state;
	}
	if(flipped >= 2) {
		dos_puts("\r\n");
	}
}

void main(void)
{
	vsync_start();
	hr(79);
	dos_puts(
		"Hold any of the cursor keys. The line below will show all states of the cursor\r\n"
		"keys, read using the keyboard state memory bitmap at 0x52A (which is also how\r\n"
		"TH02 and later read input), within a single frame.\r\n"
		"The 0.6ms delay between the states roughly matches the keyboard UART delay.\r\n"
		"\r\n"
		"After the typematic delay, you might see the occasional wrong state popping up.\r\n"
		"This will be highlighted in\x1B[17m red \x1B[0mand kept on screen when it happens.\r\n"
		"Unlike on IBM PC/XT/AT where holding a key repeats only the down scancode,\r\r\n"
		"PC-98 keyboards repeat up AND down scancodes, leading to these state flips.\r\n"
		"So, polling the keyboard twice within a frame, ~0.6ms apart, is indeed a good\r\n"
		"idea for a game engine, which is why ZUN chose to do it from TH03 onwards.\r\n"
		"\r\n"
		"Hold Q to quit."
	);
	hr(79);
	while(!(*(volatile char far*)(0x52C) & 0x01)) {
		frame();
	}
	hr(79);
	vsync_end();
}

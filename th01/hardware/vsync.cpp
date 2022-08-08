/* ReC98
 * -----
 * VSync interrupt handler
 */

#pragma option -2 -Z-
#pragma warn -aus

#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "th01/hardware/vsync.hpp"

extern bool vsync_initialized;
extern int vsync_callback_is_set;

extern pixel_t RES_X_HALF;
extern pixel_t RES_Y_HALF;

extern int vsync_unused;
extern void interrupt (*vsync_callback_old)(...);
extern void (*vsync_callback)(void);

static void interrupt vsync_intfunc(...)
{
	pixel_t res_x_half = RES_X_HALF;
	pixel_t res_y_half = RES_Y_HALF;
	vsync_frame++;
	vsync_unused++;
	if(vsync_callback_is_set) {
		vsync_callback();
	}
	outportb(0x00, 0x20); // End of Interrupt
	outportb(0x64, 0); // VSync interrupt trigger
}

void vsync_init(void)
{
	if(vsync_initialized == false) {
		vsync_initialized = true;
		disable();
		vsync_callback_old = getvect(0x0A);
		setvect(0x0A, vsync_intfunc);

		// Disable all interrupts from 0x08 to 0x0F except for 0x0A
		outportb(0x02, (inportb(0x02) & 0xFB));

		outportb(0x64, 0); // VSync interrupt trigger
		enable();
	}
}

void vsync_exit(void)
{
	if(vsync_initialized == true) {
		vsync_initialized = false;
		disable();

		// Reenable all interrupts from 0x08 to 0x0F except for 0x0A
		outportb(0x02, (inportb(0x02) | 0x04));

		setvect(0x0a, vsync_callback_old);
		enable();
	}
}

void z_vsync_wait(void)
{
	do {
		_AL = inportb(0x60);
	} while((_AL & 0x20) != 0);
	do {
		_AL = inportb(0x60);
	} while((_AL & 0x20) == 0);
}

void vsync_callback_set(void (*vsync_callback_new)())
{
	vsync_callback_is_set = 0;
	vsync_callback = vsync_callback_new;
	vsync_callback_is_set = 1;
}

void vsync_callback_clear(void)
{
	vsync_callback_is_set = 0;
}

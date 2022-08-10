/* ReC98
 * -----
 * VSync interrupt handler
 */

#pragma option -2 -Z-
#pragma warn -aus

#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "th01/hardware/vsync.hpp"

extern bool vsync_initialized = false;
extern bool16 vsync_callback_is_set = false;

static int32_t unused_7 = 7; // ZUN bloat
static int32_t unused_0 = 0; // ZUN bloat

static pixel_t RES_X_HALF = (RES_X / 2);
static pixel_t RES_Y_HALF = (RES_Y / 2);

// Unused mouse cursor (?!)
// -------------------

// (These meanings are just a guess.)
static screen_x_t MOUSE_MIN_X = 0;
static screen_y_t MOUSE_MIN_Y = 0;
static screen_x_t MOUSE_MAX_X = (RES_X - 1);
static screen_x_t MOUSE_MAX_Y = (RES_Y - 1);
static int8_t mouse_unused = 0;
#include "th01/sprites/mousecur.csp"
// -------------------

int z_vsync_Count1;
int z_vsync_Count2;
static void interrupt (*vsync_callback_old)(...);
static void (*vsync_callback)(void);

static void interrupt vsync_intfunc(...)
{
	pixel_t res_x_half = RES_X_HALF;
	pixel_t res_y_half = RES_Y_HALF;
	z_vsync_Count1++;
	z_vsync_Count2++;
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
	vsync_callback_is_set = false;
	vsync_callback = vsync_callback_new;
	vsync_callback_is_set = true;
}

void vsync_callback_clear(void)
{
	vsync_callback_is_set = false;
}

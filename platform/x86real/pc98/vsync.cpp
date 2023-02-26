#include <stdlib.h>
#include "platform.h"
#include "x86real.h"
#include "platform/x86real/pc98/vsync.hpp"

volatile uint16_t vsync_count_16;
volatile uint32_t vsync_count_32;
static void interrupt (*vsync_callback_old)(...);
bool vsync_active;

static void interrupt vsync_intfunc(...)
{
	vsync_count_16++;
	vsync_count_32++;
	_outportb_(0x00, 0x20); // End of Interrupt
	_outportb_(0x64, _AL); // VSync interrupt trigger
}

void __cdecl vsync_init(void)
{
	if(vsync_active) {
		return;
	}
	disable();
	vsync_callback_old = getvect(0x0A);
	setvect(0x0A, vsync_intfunc);

	// Disable all interrupts from 0x08 to 0x0F except for 0x0A
	_outportb_(0x02, (_inportb_(0x02) & 0xFB));

	_outportb_(0x64, _AL); // VSync interrupt trigger
	enable();
	vsync_active = true;
	atexit(vsync_exit);
}

void __cdecl vsync_exit(void)
{
	if(!vsync_active) {
		return;
	}
	disable();

	// Reenable all interrupts from 0x08 to 0x0F except for 0x0A
	_outportb_(0x02, (_inportb_(0x02) | 0x04));

	setvect(0x0A, vsync_callback_old);
	enable();
	vsync_active = false;
}

bool vsync_is_active(void)
{
	return vsync_active;
}

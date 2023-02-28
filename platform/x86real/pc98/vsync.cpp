#include <stdlib.h>
#include "platform.h"
#include "x86real.h"
#include "platform/x86real/pc98/vsync.hpp"

volatile uint16_t vsync_count_16;
volatile uint32_t vsync_count_32;
static void interrupt (*vsync_callback_old)(...);
static void interrupt (*int18h)(...);
bool vsync_active;

static void interrupt vsync_intfunc(...)
{
	vsync_count_16++;
	vsync_count_32++;
	_outportb_(0x00, 0x20); // End of Interrupt
	_outportb_(0x64, _AL); // VSync interrupt trigger
}

// Some real-hardware BIOS implementations of certain INT 18h functions (in
// particular the gaiji upload function, AH=14h) seem to return with the VSync
// interrupt trigger disabled, causing any successive delay loop based on our
// VSync counters to deadlock. This is quite awful to debug, especially because
// no emulator replicates this nuisance, as of February 2023...
// This workaround of retriggering INT 0Ah ourselves, was taken from
// master.lib's VSYNC.ASM, and the CRTBIOS_COOK handler in particular.
static void interrupt vsync_retrigger_after_int18h(...)
{
	int18h();
	_outportb_(0x64, _AL); // VSync interrupt trigger
}

void __cdecl vsync_init(void)
{
	if(vsync_active) {
		return;
	}
	disable();

	vsync_callback_old = getvect(0x0A);
	int18h = getvect(0x18);
	setvect(0x0A, vsync_intfunc);
	setvect(0x18, vsync_retrigger_after_int18h);

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
	setvect(0x18, int18h);
	enable();
	vsync_active = false;
}

bool vsync_is_active(void)
{
	return vsync_active;
}

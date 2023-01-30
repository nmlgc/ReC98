#include "platform.h"
#include "th01/resident.hpp"
#include "th01/hardware/vsync.hpp"
#include "th01/hardware/frmdelay.h"

void frame_delay(unsigned int frames)
{
	// In TH01, FUUIN.EXE resets [z_vsync_Count1] before the loop, while the
	// other two binaries reset the counter after the loop. This difference
	// matters if this function is called with an already nonzero value of
	// [z_vsync_Count1], which indicates slowdown. As a result, we get two
	// different behaviors here:
	//
	// • FUUIN.EXE will always wait at least one frame. This effectively rounds
	//   up any slowdown to the the next full frame, now matter how small it
	//   might have been.
	//
	// • OP.EXE and REIIDEN.EXE subtract the slowdown from [frames] and thus
	//   avoid this problem by breaking the loop earlier.
	//
	// These semantics could have been preserved in a simpler way if all
	// FUUIN-specific code simply called its own version of frame_delay().
	// However, TH01 contains frame_delay()-calling code shared between
	// FUUIN.EXE and a different binary (e.g. regist()), as well as code whose
	// exclusive use in FUUIN.EXE isn't immediately obvious (e.g. the .GRP
	// palette functions). Moving the distinction to runtime will always be
	// correct.

	if(end_flag != ES_NONE) {
		z_vsync_Count1 = 0;
	}
	while(z_vsync_Count1 < frames) {}
	if(end_flag == ES_NONE) {
		z_vsync_Count1 = 0;
	}
}

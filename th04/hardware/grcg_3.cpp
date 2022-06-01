// Only necessary because gather_render() is in segment #3 for some reason...
// MODDERS: Inline that call into gather_render(), and remove this translation
// unit.

#include "platform.h"
#include "x86real.h"
#include "decomp.hpp"
#include "th04/hardware/grcg.hpp"

#pragma option -k-

void near grcg_setcolor_direct_seg3_raw(void)
{
	grcg_setcolor_direct_inlined(_AH);
}

void near grcg_setmode_rmw_seg3(void)
{
	grcg_setmode_rmw_inlined();
}
#pragma codestring "\x90"

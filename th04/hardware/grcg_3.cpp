// Only necessary because gather_render() is in segment #3 for some reason...
// MODDERS: Inline that call into gather_render(), and remove this translation
// unit.

#include "platform/x86real/pc98/grcg.hpp"
#include "th04/hardware/grcg.hpp"

void near grcg_setcolor_direct_seg3_raw(void)
{
	grcg_setcolor_direct_inlined(_AH);
}

void near grcg_setmode_rmw_seg3(void)
{
	grcg_setmode_rmw_inlined();
}

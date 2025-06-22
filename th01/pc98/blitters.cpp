// Fast blitters for TH01
// ----------------------

#pragma option -zCPLATFORM_TEXT

#include "platform/x86real/pc98/blit_low.hpp"

void blitter_setup(void)
{
	blitter_use_write_8();
	blitter_use_write_16();
}

#pragma startup blitter_setup

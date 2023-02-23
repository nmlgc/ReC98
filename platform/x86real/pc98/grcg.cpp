#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "platform/x86real/pc98/grcg.hpp"

void GRCG::setcolor(uint4_t col)
{
	// By shifting each successive bit of [col] into the carry flag and using
	// tile_register_from_carry(), we get the minimum of three instructions
	// (SHR, SBB, OUT) per bitplane, with no register spills. Quite a beautiful
	// optimization!
	_AH = col;
	outportb(0x7E, tile_register_from_carry(_AH >>= 1));
	outportb(0x7E, tile_register_from_carry(_AH >>= 1));
	outportb(0x7E, tile_register_from_carry(_AH >>= 1));
	outportb(0x7E, tile_register_from_carry(_AH >>= 1));
}

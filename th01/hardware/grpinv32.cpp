#include "th01/hardware/grpinv32.hpp"

bool16 graph_invert_32x32_8(screen_x_t left, vram_y_t top, dots8_t far *plane)
{
	vram_offset_t vram_offset = vram_offset_shift(left, top);

	if(
		(left < 0) ||
		(top < 0) ||
		(left >= (RES_X - 32)) ||
		(top >= (RES_Y - 32))
	) {
		return true;
	}

	for(pixel_t y = 0; y < 32; y++, vram_offset += ROW_SIZE) {
		reinterpret_cast<dots32_t far &>(plane[vram_offset]) ^= -1;
	}
	return false;
}

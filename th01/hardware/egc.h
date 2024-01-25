#include "defconv.h"

// Requires the EGC to have been activated before.
#define egc_setup_copy() \
	outport2(EGC_ACTIVEPLANEREG, 0xFFF0); \
	outport2(EGC_READPLANEREG, 0x00FF); \
	/* EGC_COMPAREREAD | EGC_WS_PATREG | EGC_RL_MEMREAD */ \
	outport2(EGC_MODE_ROP_REG, 0x3100);  \
	outport2(EGC_MASKREG, 0xFFFF);  \
	outport2(EGC_ADDRRESSREG, 0);  \
	outport2(EGC_BITLENGTHREG, 0xF);

// Requires the EGC to have been activated and set up for a copy before.
// ZUN bloat: Can be merged into egc_setup_copy().
#define egc_setup_copy_masked(mask) { \
	outport2(EGC_READPLANEREG, 0x00ff); \
	/* EGC_COMPAREREAD | EGC_WS_PATREG | EGC_RL_MEMREAD */ \
	outport2(EGC_MODE_ROP_REG, 0x3100); \
	outport2(EGC_BITLENGTHREG, 0xF); \
	outport(EGC_MASKREG, mask); \
}

// Blits the rectangle from
// 	(⌊left/16⌋*16, top)
// to
// 	((⌈(left + w)/16⌉*16), (top + h))
// from VRAM page 1 to the same position on VRAM page 0.
// Does not clamp the X coordinate to the horizontal resolution; if
// ([left] + [w]) exceeds it or is negative, the blit operation will wrap
// around into the next or previous line.
void DEFCONV egc_copy_rect_1_to_0_16(
	screen_x_t left, vram_y_t top, pixel_t w, pixel_t h
);

// Unnecessary wrapper, as the regular function word-aligns [w] anyway.
#define egc_copy_rect_1_to_0_16_word_w(left, top, w, h) \
	egc_copy_rect_1_to_0_16(left, top, (((w / 16) * 16) + 16), h);

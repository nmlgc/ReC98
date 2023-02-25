#include "defconv.h"

/// Enabling and disabling
/// ----------------------

#ifdef X86REAL_H
	inline void graph_mode_change(bool enable_or_disable) {
		_outportb_(0x6A, (0x06 + enable_or_disable));
	}

	// Requires graphics mode changing to be enabled via
	// graph_mode_change(true).
	inline void graph_mode_egc(bool enable_or_disable) {
		_outportb_(0x6A, (0x04 + enable_or_disable));
	}

	inline void graph_egc(bool enable_or_disable) {
		graph_mode_change(true);
		graph_mode_egc(enable_or_disable);
		graph_mode_change(false);
	}

	inline void graph_egc_on(void) {
		graph_egc(true);
	}

	inline void graph_egc_off(void) {
		graph_egc(false);
	}
#endif
/// ----------------------

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

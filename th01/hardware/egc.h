#include "defconv.h"

/// Enabling and disabling
/// ----------------------

#define graph_mode_change(enable_or_disable) \
	outportb2(0x6A, (0x06 + enable_or_disable))

// Requires graphics mode changing to be enabled via graph_mode_change(true).
#define graph_mode_egc(enable_or_disable) \
	outportb2(0x6A, (0x04 + enable_or_disable))

#define graph_egc(enable_or_disable) \
	graph_mode_change(true); \
	graph_mode_egc(enable_or_disable); \
	graph_mode_change(false);

#define graph_egc_on() \
	graph_egc(true);

#define graph_egc_off() \
	graph_egc(false);
/// ----------------------

// Requires the EGC to have been activated before.
#define egc_setup_copy() \
	outport2(EGC_ACTIVEPLANEREG, 0xFFF0); \
	outport2(EGC_READPLANEREG, 0x00FF); \
	/* EGC_COMPAREREAD | EGC_WS_PATREG | EGC_RL_MEMREAD */  \
	outport2(EGC_MODE_ROP_REG, 0x3100);  \
	outport2(EGC_MASKREG, 0xFFFF);  \
	outport2(EGC_ADDRRESSREG, 0);  \
	outport2(EGC_BITLENGTHREG, 0xF);

// Blits the rectangle from
// 	(⌊left/16⌋*16, top)
// to
// 	(⌈((left + w)/16)*16⌉, (top + h))
// from VRAM page 1 to the same position on VRAM page 0.
void DEFCONV egc_copy_rect_1_to_0_16(
	screen_x_t left, vram_y_t top, pixel_t w, pixel_t h
);

// Unnecessary wrapper, as the regular function word-aligns [w] anyway.
#define egc_copy_rect_1_to_0_16_word_w(left, top, w, h) \
	egc_copy_rect_1_to_0_16(left, top, (((w / 16) * 16) + 16), h);

// Blits [h] rows starting at [top] from VRAM page 1 to the same position on
// VRAM page 0. Mainly used after a previous GDC scroll of [h] rows, to
// smoothly scroll between two full background images.
void egc_copy_rows_1_to_0(vram_y_t top, pixel_t h);

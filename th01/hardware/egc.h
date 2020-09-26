#include "defconv.h"
#include "decomp.h"

// Requires the EGC to have been activated before.
#define egc_setup_copy() \
	OUTW2(EGC_ACTIVEPLANEREG, 0xFFF0); \
	OUTW2(EGC_READPLANEREG, 0x00FF); \
	/* EGC_COMPAREREAD | EGC_WS_PATREG | EGC_RL_MEMREAD */  \
	OUTW2(EGC_MODE_ROP_REG, 0x3100);  \
	OUTW2(EGC_MASKREG, 0xFFFF);  \
	OUTW2(EGC_ADDRRESSREG, 0);  \
	OUTW2(EGC_BITLENGTHREG, 0xF);

// Blits the rectangle from (⌊x/16⌋*16, y) to (⌈((x + w)/16)*16⌉, (y + h))
// from VRAM page 1 to the same position on VRAM page 0.
void DEFCONV egc_copy_rect_1_to_0_16(
	screen_x_t x, vram_y_t y, pixel_t w, pixel_t h
);

// Blits [h] rows starting at [top] from VRAM page 1 to the same position on
// VRAM page 0. Mainly used after a previous GDC scroll of [h] rows, to
// smoothly scroll between two full background images.
void egc_copy_rows_1_to_0(vram_y_t top, pixel_t h);

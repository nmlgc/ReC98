#include "ReC98.h"
#include "decomp.h"

// Note that this does not correspond to the tiled area painted into TH05's
// EDBK?.PI images.
static const screen_x_t BOX_LEFT = 80;
static const screen_y_t BOX_TOP = 320;
static const pixel_t BOX_W = 480;
static const pixel_t BOX_H = (GLYPH_H * 4);

static const screen_y_t BOX_RIGHT = (BOX_LEFT + BOX_W);
static const screen_y_t BOX_BOTTOM = (BOX_TOP + BOX_H);

typedef enum {
	BOX_MASK_0,
	BOX_MASK_1,
	BOX_MASK_2,
	BOX_MASK_3,
	BOX_MASK_COPY,
	BOX_MASK_COUNT,

	_box_mask_t_FORCE_UINT16 = 0xFFFF
} box_mask_t;

// Copies the text box area from VRAM page 1 to VRAM page 0, applying the
// given [mask]. Assumes that the EGC is active, and initialized for a copy.
void pascal near box_1_to_0_mask(box_mask_t mask)
{
	extern dots16_t BOX_MASKS[BOX_MASK_COUNT][4];
	dots16_t dots;
	#define CHUNK_W static_cast<int>(sizeof(dots) * BYTE_DOTS)

	for(screen_y_t y = BOX_TOP; y < BOX_BOTTOM; y++) {
		OUTW2(EGC_READPLANEREG, 0x00ff);
		// EGC_COMPAREREAD | EGC_WS_PATREG | EGC_RL_MEMREAD
		OUTW2(EGC_MODE_ROP_REG, 0x3100);
		OUTW2(EGC_BITLENGTHREG, 0xF);
		OUTW(EGC_MASKREG, BOX_MASKS[mask][y & 3]);

		vram_offset_t vram_offset = vram_offset_shift(BOX_LEFT, y);
		pixel_t x = 0;
		while(x < BOX_W) {
			graph_accesspage(1);	VRAM_SNAP(dots, B, vram_offset, 16);
			graph_accesspage(0);	VRAM_PUT(B, vram_offset, dots, 16);
			x += CHUNK_W;
			vram_offset += (CHUNK_W / BYTE_DOTS);
		}
	}
	#undef CHUNK_W
}
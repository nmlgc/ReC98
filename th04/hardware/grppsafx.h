#include "th01/hardware/grppsafx.h"

// TH04 adds 4 dissolve masks with patterns of increasing strength, and splits
// the [fx] parameter into two separate global variables.
extern enum {
	FX_WEIGHT_NORMAL = WEIGHT_NORMAL,
	FX_WEIGHT_HEAVY  = WEIGHT_HEAVY,
	FX_WEIGHT_BOLD   = WEIGHT_BOLD,
	FX_WEIGHT_BLACK  = WEIGHT_BLACK,

	FX_MASK,
	FX_MASK_1 = FX_MASK,
	FX_MASK_2,
	FX_MASK_3,
	FX_MASK_4,
	FX_MASK_END,
	_graph_putsa_fx_func_FORCE_INT16 = 0x7FFF
} graph_putsa_fx_func;
extern pixel_t graph_putsa_fx_spacing;

void pascal graph_putsa_fx(
	screen_x_t left, vram_y_t top, int color, const unsigned char *str
);

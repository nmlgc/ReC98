// Combines dots from VRAM page 1 (where the mask is 0) with dots from VRAM
// page 0 (where the mask is 1).
static const int INTERLEAVE_MASK_COUNT = 10;
#define INTERLEAVE_W 8
#define INTERLEAVE_H 8

extern const dot_rect_t(INTERLEAVE_W, INTERLEAVE_H) sINTERLEAVE_MASKS[
	INTERLEAVE_MASK_COUNT
];

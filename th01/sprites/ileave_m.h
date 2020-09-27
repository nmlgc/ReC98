// Combines dots from VRAM page 1 (where the mask is 0) with dots from VRAM
// page 0 (where the mask is 1).
static const int INTERLEAVE_MASK_COUNT = 10;
static const pixel_t INTERLEAVE_W = 8;
static const pixel_t INTERLEAVE_H = 8;

typedef struct {
	dots8_t dots[INTERLEAVE_MASK_COUNT][INTERLEAVE_H];
} interleave_masks_t;

extern const interleave_masks_t sINTERLEAVE_MASKS;

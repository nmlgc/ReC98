// Combines dots from VRAM page 1 (where the mask is 0) with dots from VRAM
// page 0 (where the mask is 1).
static const int INTERLEAVE_MASK_COUNT = 10;
#define INTERLEAVE_W 8
#define INTERLEAVE_H 8

typedef struct {
	dot_rect_t(INTERLEAVE_W, INTERLEAVE_H) dots[INTERLEAVE_MASK_COUNT];
} interleave_masks_t;

extern const interleave_masks_t sINTERLEAVE_MASKS;

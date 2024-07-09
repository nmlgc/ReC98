#include "planar.h"

// Lookup table for horizontally flipping a dots8_t.
extern dots8_t hflip_lut[256];

// Fills [hflip_lut].
void hflip_lut_generate(void);

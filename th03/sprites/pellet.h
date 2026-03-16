#include "planar.h"

static const pixel_t PELLET_W = 8;
static const vram_h_t PELLET_VRAM_H = 4;

// Doubly preshifted and loaded using a 32-bit `MOV`, for a change...
typedef dots32_t pellet_dots_t;

typedef enum {
	C_PELLET,
	C_PELLET_TRANSFER,
	PELLET_CELS,
} pellet_cel_t;

extern const DotRect<
	pellet_dots_t, PELLET_VRAM_H
> near sPELLET[PELLET_CELS][PRESHIFT * 2];

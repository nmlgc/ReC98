// Cutscene/ending picture dimensions
// ----------------------------------

#include "pc98.h"

static const pixel_t CUTSCENE_PIC_W = (RES_X / 2);
static const pixel_t CUTSCENE_PIC_H = (RES_Y / 2);

// Always horizontally centered, but shown at different vertical positions
// depending on the game.
static const screen_x_t CUTSCENE_PIC_LEFT = (
	(RES_X / 2) - (CUTSCENE_PIC_W / 2)
);

static const pixel_t CUTSCENE_PIC_VRAM_W = (CUTSCENE_PIC_W / BYTE_DOTS);

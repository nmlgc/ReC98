// Cutscene/ending picture dimensions
// ----------------------------------

#include "game/coords.hpp"

static const pixel_t CUTSCENE_PIC_W = (RES_X / 2);
static const pixel_t CUTSCENE_PIC_H = (RES_Y / 2);

// Always horizontally centered, but shown at different vertical positions
// depending on the game.
static const screen_x_t CUTSCENE_PIC_LEFT = (
	(RES_X / 2) - (CUTSCENE_PIC_W / 2)
);

static const pixel_t CUTSCENE_PIC_VRAM_W = (CUTSCENE_PIC_W / BYTE_DOTS);

static const int CUTSCENE_QUARTER_COUNT = 4;

// ZUN stores cutscene pictures by arranging up to 4 of them into a single .PI
// image and then addressing the resulting quarters using clockwise indices:
// | 0 | 1 |
// | 2 | 3 |
extern const LTWH<upixel_t> pascal CUTSCENE_QUARTERS[CUTSCENE_QUARTER_COUNT];

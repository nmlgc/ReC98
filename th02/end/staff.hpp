#include "game/cutscene.hpp"

static const screen_x_t STAFFROLL_PIC_LEFT = (RES_X / 20);
static const screen_x_t STAFFROLL_PIC_RIGHT = (
	STAFFROLL_PIC_LEFT + CUTSCENE_PIC_W
);
static const screen_y_t STAFFROLL_PIC_TOP  = (
	(RES_Y / 2) - (CUTSCENE_PIC_H / 2)
);

// Clears the staff roll picture area in VRAM and shows the rotating rectangle
// animation, ending with the area containing the single white final rectangle
// and a fully white hardware color palette.
void pascal staffroll_rotrect_animate(
	unsigned char angle_speed, unsigned char angle_start
);

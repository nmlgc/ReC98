#include "platform.h"
#include "pc98.h"

// State
// -----

// Corresponds to the .CDG slot of the full-color image; dissolve effects will
// use (this slot + 1).
extern uint8_t cdg_slot;

extern unsigned char radial_angle;

// Distance == 0: Blits [cdg_slot] to (base_left, base_top).
// Distance  > 0: Transforms (base_left, base_top) into a different coordinate
//                for every one of the 4 planes, then blits each plane of
//                ([cdg_slot] + 1) to the respective transformed position.
extern void (near pascal *near dissolve_put_func)(
	screen_x_t base_left, screen_y_t base_top, pixel_t distance
);
// -----

/* ReC98
 * -----
 * TH05 Staff Roll
 */

#pragma codeseg maine_01__TEXT

extern "C" {
#include "ReC98.h"
#include "th01/math/subpixel.hpp"

// State
// -----
extern pixel_t space_window_w;
extern pixel_t space_window_h;
extern screen_point_t space_window_center;

// Effectively just moves all the entities into the opposite direction.
extern SPPoint space_camera_velocity;
// -----

void pascal near space_window_set(
	screen_x_t center_x, screen_y_t center_y, pixel_t w, pixel_t h
)
{
	space_window_center.x = center_x;
	space_window_center.y = center_y;
	space_window_w = w;
	space_window_h = h;
	grc_setclip(
		(space_window_center.x - (space_window_w / 2)) - 8,
		(space_window_center.y - (space_window_h / 2)) - 8,
		(space_window_center.x + (space_window_w / 2)) + 7,
		(space_window_center.y + (space_window_h / 2)) + 7
	);
}

}

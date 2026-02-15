/// Dynamic HUD elements, rendered partially to VRAM
/// ------------------------------------------------

#include "pc98.h"

// Takes the 5-digit number of [points], appends the 0 as the sixth digit, and
// renders the result to VRAM using the score font, right-aligned at
//
// 	((([left] + ([SCORE_FONT_W] * 6)), [top])
//
// in the given color.
void pascal hud_dynamic_5_digit_points_put(
	screen_x_t left, vram_y_t top, uint16_t points, vc_t col
);

#include "pc98.h"

// Blits the hardcoded diamond, star, or snowflake sprites in the given [col]
// to the given position.
void shape8x8_diamond_put(screen_x_t left, vram_y_t top, vc2 col);
void shape8x8_star_put(screen_x_t left, vram_y_t top, vc2 col);
void shape8x8_flake_put(screen_x_t left, vram_y_t top, vc2 col);

// Blits the given [cel] of the hardcoded invincibility sprites to the given
// position.
void shape8x8_invincibility_put(screen_x_t left, vram_y_t top, int cel);

// Attempts to unblit a 8×8 sprite, but ends up unblitting a 16×8 rectangle
// instead.
#define shape8x8_sloppy_unput(left, top) \
	egc_copy_rect_1_to_0_16_word_w(left, top, 8, 8);

// Draws the outline dots of an ellipse arc at the given X and Y radius away
// from the center point, defined by a start and end angle. The original
// version draws nothing if [angle_start] == [angle_end].
void shape_ellipse_arc_put(
	screen_x_t center_x,
	vram_y_t center_y,
	pixel_t radius_x,
	pixel_t radius_y,
	vc2 col,
	unsigned char angle_step,
	unsigned char angle_start,
	unsigned char angle_end
);

#define shape_circle_put(center_x, center_y, radius, col, angle_step) \
	shape_ellipse_arc_put( \
		center_x, center_y, radius, radius, col, angle_step, 0x00, 0xFF \
	);

// Makes a sloppy attempt at restoring the pixels along the given ellipse arc
// from VRAM page 1, but ends up restoring horizontal 16×1 lines along that
// arc.
void shape_ellipse_arc_sloppy_unput(
	screen_x_t center_x,
	vram_y_t center_y,
	pixel_t radius_x,
	pixel_t radius_y,
	unsigned char angle_step,
	unsigned char angle_start,
	unsigned char angle_end
);

#define shape_circle_sloppy_unput(center_x, center_y, radius, angle_step) \
	shape_ellipse_arc_sloppy_unput( \
		center_x, center_y, radius, radius, angle_step, 0x00, 0xFF \
	);

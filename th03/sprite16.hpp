#include "th03/hardware/vram.hpp"

extern pixel_t sprite16_put_h;
extern VRAMWord sprite16_put_w;
extern screen_x_t sprite16_clip_left;
extern screen_x_t sprite16_clip_right;

enum sprite16_put_func_t {
	SPF_NORMAL = 0,
	// Repeatedly draws the sprite to form a gapless column, starting from the
	// top Y coordinate given to sprite16_putx() down to the bottom of VRAM.
	SPF_DOWNWARDS_COLUMN = 24,

	_sprite16_put_func_t_FORCE_INT = 0xFFFF
};

// Draws the sprite with the given offset in the SPRITE16_SPRITE_AREA at the
// given (left, top) position in screen (not VRAM) coordinates. The left and
// right parts of the sprite are clipped in 16-pixel increments to stay within
// the left and right clipping points, so make sure to hide at least 16 more
// pixels right of `sprite16_clip_left` and left of `sprite16_clip_right` on
// purpose.
void pascal sprite16_put(screen_x_t left, screen_y_t top, int sprite_offset);
// Like sprite16_put(), but using an optional drawing function.
void pascal sprite16_putx(
	screen_x_t left, screen_y_t top, int sprite_offset, sprite16_put_func_t func
);
// Like sprite16_put(), but ignores the clipping points.
void pascal sprite16_put_noclip(
	screen_x_t left, screen_y_t top, int sprite_offset
);

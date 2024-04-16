#include "th03/hardware/vram.hpp"

// Relative offset inside the SPRITE16 sprite area, with 0 corresponding to
// SPRITE16_OFFSET.
typedef uvram_byte_amount_t sprite16_offset_t;

extern pixel_t sprite16_put_h;
extern VRAMWord sprite16_put_w;
extern screen_x_t sprite16_clip_left;
extern screen_x_t sprite16_clip_right;

enum sprite16_put_func_t {
	SPF_NORMAL = 0,
	// Repeatedly draws the sprite to form a gapless column, starting from the
	// top Y coordinate given to sprite16_putx() down to the bottom of VRAM.
	SPF_DOWNWARDS_COLUMN = 24,

	_sprite16_put_func_t_FORCE_UINT16 = 0xFFFF
};

// Copies the entire sprite area in VRAM from page [dst_page ^ 1] to
// [dst_page]. Returns true if successful, false if the temporary memory
// couldn't be allocated.
bool16 pascal sprite16_sprites_copy_page(int dst_page);

// Initializes SPRITE16 for double-buffered blitting of the sprites that have
// been blitted to the sprite area on VRAM page 0.
void pascal sprite16_sprites_commit(void);

// Draws the sprite with the given offset in the SPRITE16 sprite area at the
// given (left, top) position in screen (not VRAM) coordinates. The left and
// right parts of the sprite are clipped in 16-pixel increments to stay within
// the left and right clipping points, so make sure to hide at least 16 more
// pixels right of `sprite16_clip_left` and left of `sprite16_clip_right` on
// purpose.
void pascal sprite16_put(screen_x_t left, screen_y_t top, sprite16_offset_t so);

// Like sprite16_put(), but using an optional drawing function.
void pascal sprite16_putx(
	screen_x_t left,
	screen_y_t top,
	sprite16_offset_t so,
	sprite16_put_func_t func
);

// Like sprite16_put(), but ignores the clipping points.
void pascal sprite16_put_noclip(
	screen_x_t left, screen_y_t top, sprite16_offset_t so
);

#include "pc98.h"

#define SCROLL_HPP

// Current line at the top of VRAM.
extern vram_y_t scroll_line;

#if (GAME == 2)
// Amount of pixels to be added to [scroll_line] on every scrolling operation.
extern pixel_length_8_t scroll_speed;

extern uint8_t scroll_cycle;

// Interval between successive scrolling operations, used to achieve scrolling
// speeds below 1 pixel per frame. Must be ≥1.
extern uint8_t scroll_interval;

// Set to 1 when the top of the map was reached and the boss should be started.
extern bool scroll_done;
#endif

#define scroll_screen_y_to_vram(ret, screen_y) \
	/* Sneaky! That's how we can pretend this is an actual function that */ \
	/* returns a value. */ \
	screen_y; \
	ret += scroll_line; \
	if(ret >= RES_Y) { \
		ret -= RES_Y; \
	}

// Adds an already [scrolled_vram_y] plus some [delta_pixels] to [ret], and
// rolls around the result as necessary.
// ZUN bloat: This can certainly be done with less mutation.
#define scroll_add_scrolled(ret, scrolled_vram_y, delta_pixels) { \
	ret += (scrolled_vram_y + delta_pixels); \
	if(ret >= RES_Y) { \
		ret -= RES_Y; \
	} \
}

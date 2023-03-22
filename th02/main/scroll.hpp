#define SCROLL_HPP

// Current line at the top of VRAM.
extern vram_y_t scroll_line;

#if (GAME == 2)
	// Amount of pixels to be added to [scroll_line] on every scrolling
	// operation.
	extern uint8_t scroll_speed;

	extern uint8_t scroll_cycle;

	// Interval between successive scrolling operations, used to achieve
	// scrolling speeds below 1 pixel per frame. Must be ≥1.
	extern uint8_t scroll_interval;
#endif

#define scroll_screen_y_to_vram(ret, screen_y) \
	/* Sneaky! That's how we can pretend this is an actual function that */ \
	/* returns a value. */ \
	screen_y; \
	ret += scroll_line; \
	if(ret >= RES_Y) { \
		ret -= RES_Y; \
	}

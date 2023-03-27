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

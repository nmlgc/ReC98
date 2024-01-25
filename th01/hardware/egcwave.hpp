// Applies a wave function with the given [len], [amp], and [phase] parameters
// to the starting X coordinate of each row inside a rectangle from
// 	(⌊left/16⌋*16, top)
// to
// 	(⌈((left + w)/16)*16⌉, (top + h))
// and blits the resulting rows from VRAM page 1 to the same position on VRAM
// page 0. Does not clamp the per-row X coordinates; if their values plus [w]
// ([left] + [w]) exceed the horizontal resolution or are negative, the blit
// operation will wrap around into the next or previous line.
void egc_wave_unput(
	screen_x_t left,
	vram_y_t top,
	int len,
	pixel_t amp,
	int phase,
	pixel_t w,
	pixel_t h
);

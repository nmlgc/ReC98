// Additional 640×400 4-plane background image buffer.
extern Planar<dots8_t __seg *> bgimage;

void bgimage_snap(void);

// Blits garbage data if bgimage_snap() wasn't called before.
void bgimage_put(void);

void bgimage_free(void);
// Blits the rectangle from (⌊x/16⌋*16, y) to (⌈((x + w)/16)*16⌉, (y + h))
// on the [bgimage] to the same position in VRAM.
void pascal bgimage_put_rect(
	screen_x_t left, screen_y_t top, pixel_t w, pixel_t h
);

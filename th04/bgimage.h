// Additional 640×400 4-plane background image buffer.
extern char __seg *bgimage[PL_COUNT];

void pascal bgimage_snap(void);
void pascal bgimage_put(void);
void pascal bgimage_free(void);
// Blits the rectangle from (⌊x/16⌋*16, y) to (⌈((x + w)/16)*16⌉, (y + h))
// on the [bgimage] to the same position in VRAM.
void pascal bgimage_put_rect(screen_x_t left, screen_y_t top, int w, int h);

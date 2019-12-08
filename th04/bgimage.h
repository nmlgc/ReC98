// Additional 640×400 4-plane background image buffer.
extern char __seg *bgimage[PL_COUNT];

void pascal bgimage_snap(void);
void pascal bgimage_put(void);
void pascal bgimage_free(void);
// Blits the rectangle from (⌊x/16⌋*16, y) to (⌈((x + w)/16)*16⌉, (y + h))
// to the same position in VRAM.
void pascal bgimage_put_rect(int x, int y, int w, int h);

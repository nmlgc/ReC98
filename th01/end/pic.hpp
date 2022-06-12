static const pixel_t PIC_W = (RES_X / 2);
static const pixel_t PIC_H = (RES_Y / 2);
static const screen_x_t PIC_LEFT   = ((RES_X / 2) - (PIC_W / 2));
static const screen_y_t PIC_TOP    = ((RES_Y / 2) - (PIC_H / 2));
static const screen_y_t PIC_RIGHT  = (PIC_LEFT + PIC_W);
static const screen_y_t PIC_BOTTOM = (PIC_TOP + PIC_H);

static const pixel_t PIC_VRAM_W = (PIC_W / BYTE_DOTS);

// Loads the ending pictures from the .GRP file [fn] onto graphics page #1,
// and sets the hardware color palette to the one in [fn]'s header.
void pascal end_pics_load_palette_show(const char *fn);

// Blits the given [quarter] of the set of ending pictures currently loaded
// onto graphics page #1 to the center of page #0.
// The quarters are numbered like this:
// | 0 | 1 |
// | 2 | 3 |
void end_pic_show(int quarter);

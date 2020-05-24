// Loads the ending pictures from the .GRP file [fn] onto graphics page #1,
// and sets the hardware color palette to the one in [fn]'s header.
void pascal end_pics_load_palette_show(const char *fn);

// Blits the given [quarter] of the set of ending pictures currently loaded
// onto graphics page #1 to the center of page #0.
// The quarters are numbered like this:
// | 0 | 1 |
// | 2 | 3 |
void end_pic_show(int quarter);

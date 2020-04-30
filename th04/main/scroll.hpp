// [scroll_line] is advanced by 1 for every 16 units.
extern SubpixelLength8 scroll_subpixel_line;

// Amount to add to [scroll_subpixel_line] every frame.
extern SubpixelLength8 scroll_speed;

// Current line at the top of VRAM.
extern int scroll_line;
extern int scroll_line_on_page[2];

// Playfield-space pixels scrolled in the last frame.
extern Subpixel scroll_last_delta;

// If false, the game doesn't draw stage tiles, assuming that someone else
// draws the background.
extern bool scroll_active;

// Transforms [y] to its corresponding VRAM line, adding the current
// [scroll_line] or 0 if scrolling is disabled.
int pascal near scroll_subpixel_y_to_vram_seg1(subpixel_t y);
int pascal near scroll_subpixel_y_to_vram_seg3(subpixel_t y);
// Like the one above, but always adds [scroll_line], even if scrolling is
// disabled.
int pascal near scroll_subpixel_y_to_vram_always(subpixel_t y);

#include "th02/main/scroll.hpp"

// [scroll_line] is advanced by 1 for every 16 units.
extern SubpixelLength8 scroll_subpixel_line;

// Amount to add to [scroll_subpixel_line] every frame. Replaces TH02's
// separate pixel-based [scroll_speed] and [scroll_interval] with a single
// variable.
extern SubpixelLength8 scroll_speed;

extern vram_y_t scroll_line_on_page[2];

// Playfield-space pixels scrolled in the last frame.
extern Subpixel scroll_last_delta;

// If false, the game doesn't draw stage tiles, assuming that someone else
// draws the background.
extern bool scroll_active;

#pragma codeseg mai_TEXT main_01

// Transforms [y] to its corresponding VRAM line, adding the current
// [scroll_line] or 0 if scrolling is disabled.
extern "C" vram_y_t pascal near scroll_subpixel_y_to_vram_seg1(subpixel_t y);

#pragma codeseg

// Transforms [y] to its corresponding VRAM line, adding the current
// [scroll_line] or 0 if scrolling is disabled.
vram_y_t pascal near scroll_subpixel_y_to_vram_seg3(subpixel_t y);

// Like the one above, but always adds [scroll_line], even if scrolling is
// disabled.
vram_y_t pascal near scroll_subpixel_y_to_vram_always(subpixel_t y);

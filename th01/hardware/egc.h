#include "defconv.h"

#if (GAME == 2)
// TH02 actually calls this by its proper name from a different segment!
void egc_start_copy(void);
#endif

// Blits the rectangle from
// 	(⌊left/16⌋*16, top)
// to
// 	((⌈(left + w)/16⌉*16), (top + h))
// from VRAM page 1 to the same position on VRAM page 0.
// Does not clamp the X coordinate to the horizontal resolution; if
// ([left] + [w]) exceeds it or is negative, the blit operation will wrap
// around into the next or previous line.
void DEFCONV egc_copy_rect_1_to_0_16(
	screen_x_t left, vram_y_t top, pixel_t w, pixel_t h
);

// Unnecessary wrapper, as the regular function word-aligns [w] anyway.
#define egc_copy_rect_1_to_0_16_word_w(left, top, w, h) \
	egc_copy_rect_1_to_0_16(left, top, (((w / 16) * 16) + 16), h);

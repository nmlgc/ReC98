#pragma option -zCGRAPH_EX_TEXT -2 -O- -Z-

#include "platform.h"
#include "pc98.h"
#include "libs/master.lib/master.hpp"
#include "th01/math/wave.hpp"
#include "th01/hardware/egc.h"
#include "th01/hardware/egcwave.hpp"

void egc_wave_unput(
	screen_x_t left,
	vram_y_t top,
	int len,
	pixel_t amp,
	int phase,
	pixel_t w,
	pixel_t h
)
{
	int t = phase;
	for(pixel_t y = 0; y < h; y++) {
		screen_x_t x = (wave_x(amp, t) + left);
		t += (0x100 / len);
		egc_copy_rect_1_to_0_16(x, top + y, w, 1);
	}
}

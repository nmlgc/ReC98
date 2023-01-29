/* ReC98
 * -----
 * Code segment #4 of TH01's FUUIN.EXE
 */

#pragma option -1 -Z-

#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "shiftjis.hpp"
#include "th01/hardware/graph.h"
#include "th01/hardware/grp_text.hpp"
#include "th01/hardware/vsync.hpp"
#include "th01/end/type.hpp"

#define TYPE_DELAY 3
static const int TYPE_FX = (COL_TYPE | FX_WEIGHT_NORMAL);

#include "th01/end/pic.cpp"

// Special FUUIN.EXE version of frame_delay() that resets [z_vsync_Count1]
// first.
void frame_delay(unsigned int frames)
{
	z_vsync_Count1 = 0;
	while(z_vsync_Count1 < frames) {
	}
}

#pragma option -O-

void pascal graph_type_ank_n(
	screen_x_t left, vram_y_t top, int len, const sshiftjis_t *str
)
{
	for(int i = 0; i < len; i++) {
		graph_printf_fx(
			left + (i * GLYPH_HALF_W), top, TYPE_FX, "%c", str[i]
		);
		frame_delay(TYPE_DELAY);
	}
}

void pascal graph_type_kanji_n(
	screen_x_t left, vram_y_t top, int len, const sshiftjis_kanji_t *str
)
{
	for(int i = 0; i < len; i++) {
		graph_printf_fx(
			left + (i * GLYPH_FULL_W), top, TYPE_FX,
			"%c%c", str[(2 * i) + 0], str[(2 * i) + 1]
		);
		frame_delay(TYPE_DELAY);
	}
}

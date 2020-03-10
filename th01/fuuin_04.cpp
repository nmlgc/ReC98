/* ReC98
 * -----
 * Code segment #4 of TH01's FUUIN.EXE
 */

#pragma option -O-

extern "C" {
#include "ReC98.h"
#include "th01/hardware/graph.h"
#include "th01/hardware/vsync.h"
#include "th01/end/type.h"

#define TYPE_DELAY 3
#define TYPE_FX FX(15, 0, 0)

/// Temporary translation unit mismatch workarounds
/// -----------------------------------------------
#define FRAME_DELAY(frames) __asm { \
	push	frames; \
	push 	cs; \
	call	near ptr frame_delay; \
	pop 	cx; \
}
/// -----------------------------------------------

void pascal graph_type_ank(int left, int top, int len, const char *str)
{
	extern const char graph_type_ank_fmt[];
	for(int i = 0; i < len; i++) {
		graph_printf_fx(
			left + (i * GLYPH_HALF_W), top, TYPE_FX,
			graph_type_ank_fmt, str[i]
		);
		FRAME_DELAY(TYPE_DELAY);
	}
}

void pascal graph_type_kanji(int left, int top, int len, const char *str)
{
	extern const char graph_type_kanji_fmt[];
	for(int i = 0; i < len; i++) {
		graph_printf_fx(
			left + (i * GLYPH_FULL_W), top, TYPE_FX,
			graph_type_kanji_fmt, str[(2 * i) + 0], str[(2 * i) + 1]
		);
		FRAME_DELAY(TYPE_DELAY);
	}
}

}

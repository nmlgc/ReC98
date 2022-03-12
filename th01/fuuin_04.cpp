/* ReC98
 * -----
 * Code segment #4 of TH01's FUUIN.EXE
 */

#pragma option -1 -Z-

extern "C" {
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "th01/formats/grp.h"
#include "th01/hardware/graph.h"
#include "th01/hardware/palette.h"
#include "th01/hardware/vsync.h"
#include "th01/end/type.h"

#define TYPE_DELAY 3
#define TYPE_FX (15 | FX_WEIGHT_NORMAL)

#define TONE_STEP_PER_FRAME 5

#include "th01/end/pic.cpp"

inline void optimization_barrier() {}

// Special FUUIN.EXE version of frame_delay() that resets [vsync_frame] first.
void frame_delay(unsigned int frames)
{
	vsync_frame = 0;
	while(1) {
		if(vsync_frame >= frames) {
			break;
		}
		optimization_barrier();
	}
}

/// .GRP palette fades
/// ------------------
void pascal grp_palette_settone(int tone)
{
	int col;
	int comp;
	int blend;

	if(tone < 0) {
		tone = 0;
	} else if(tone > 200) {
		tone = 200;
	}
	for(col = 1; col < COLOR_COUNT; col++) {
		for(comp = 0; comp < COMPONENT_COUNT; comp++) {
			if(tone > 100) {
				blend = (RGB4::max() - grp_palette[col].v[comp]);
				blend *= (tone - 100);
				blend /= 100;
				z_Palettes[col].v[comp] = (grp_palette[col].v[comp] + blend);
			} else {
				blend = grp_palette[col].v[comp];
				blend *= (100 - tone);
				blend /= 100;
				z_Palettes[col].v[comp] = (-blend + grp_palette[col].v[comp]);
			}
		}
	}
	grp_palette_tone = tone;
	z_palette_set_all_show(z_Palettes);
}

#define fade_loop(tone_start, direction, delay) \
	int i; \
	int tone = tone_start; \
	for(i = 0; i < (100 / TONE_STEP_PER_FRAME); i++) { \
		tone direction TONE_STEP_PER_FRAME; \
		grp_palette_settone(tone); \
		frame_delay(delay); \
	}

void pascal grp_palette_black_out(unsigned int frames)
{
	fade_loop(100, -=, frames);
}

void pascal grp_palette_black_in(unsigned int frames)
{
	fade_loop(0, +=, frames);
}

void pascal grp_palette_white_out(unsigned int frames)
{
	fade_loop(100, +=, frames);
}

void pascal grp_palette_white_in(unsigned int frames)
{
	fade_loop(200, -=, frames);
}
/// ------------------

#pragma option -O-

void pascal graph_type_ank(
	screen_x_t left, vram_y_t top, int len, const char *str
)
{
	extern const char graph_type_ank_fmt[];
	for(int i = 0; i < len; i++) {
		graph_printf_fx(
			left + (i * GLYPH_HALF_W), top, TYPE_FX,
			graph_type_ank_fmt, str[i]
		);
		frame_delay(TYPE_DELAY);
	}
}

void pascal graph_type_kanji(
	screen_x_t left, vram_y_t top, int len, const char *str
)
{
	extern const char graph_type_kanji_fmt[];
	for(int i = 0; i < len; i++) {
		graph_printf_fx(
			left + (i * GLYPH_FULL_W), top, TYPE_FX,
			graph_type_kanji_fmt, str[(2 * i) + 0], str[(2 * i) + 1]
		);
		frame_delay(TYPE_DELAY);
	}
}

}

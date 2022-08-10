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
extern "C" {
#include "th01/hardware/graph.h"
#include "th01/hardware/grppsafx.h"
#include "th01/hardware/palette.h"
}
#include "th01/hardware/vsync.hpp"
#include "th01/formats/grp.h"
#include "th01/end/type.hpp"

#define TYPE_DELAY 3
static const int TYPE_FX = (COL_TYPE | FX_WEIGHT_NORMAL);

#define TONE_STEP_PER_FRAME 5

#include "th01/end/pic.cpp"

// Special FUUIN.EXE version of frame_delay() that resets [z_vsync_Count1]
// first.
extern "C" void frame_delay(unsigned int frames)
{
	z_vsync_Count1 = 0;
	while(1) {
		if(z_vsync_Count1 >= frames) {
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

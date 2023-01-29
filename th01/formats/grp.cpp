#pragma option -zCPTN_GRP_GRZ

#include "platform.h"
#include "pc98.h"
#include "master.hpp"
#include "libs/piloadc/piloadc.hpp"
#include "th01/hardware/frmdelay.h"
#include "th01/hardware/palette.h"
#include "th01/formats/grp.h"

// The same size that master.lib uses in graph_pi_load_pack(), with no
// explanation for it given in either master.lib or PILOADC.DOC...
#define GRP_BUFFER_SIZE 0x4000

// *Not* offsetof(PiHeader, palette)!
#define PI_PALETTE_OFFSET 0x12

// Palette
// -------

static const int TONE_STEP_PER_FRAME = 5;

Palette4 grp_palette;
static int grp_palette_tone = 100;

void pascal grp_palette_settone(int tone)
{
	if(tone < 0) {
		tone = 0;
	} else if(tone > 200) {
		tone = 200;
	}
	for(int col = 1; col < COLOR_COUNT; col++) {
		for(int comp = 0; comp < COMPONENT_COUNT; comp++) {
			int blend;
			if(tone > 100) {
				blend = (RGB4::max() - grp_palette[col].v[comp]);
				blend *= (tone - 100);
				blend /= 100;
				z_Palettes[col].v[comp] = (grp_palette[col].v[comp] + blend);
			} else {
				blend = grp_palette[col].v[comp];
				blend *= (100 - tone);
				blend /= 100;
				z_Palettes[col].v[comp] = (grp_palette[col].v[comp] - blend);
			}
		}
	}
	grp_palette_tone = tone;
	z_palette_set_all_show(z_Palettes);
}

void pascal grp_palette_inout(
	int tone_start, int speed, unsigned int frame_delay_per_step
)
{
	int tone = tone_start;
	for(int i = 0; i < (100 / TONE_STEP_PER_FRAME); i++) {
		tone += (TONE_STEP_PER_FRAME * speed);
		grp_palette_settone(tone);
		frame_delay(frame_delay_per_step);
	}
}

void pascal grp_palette_black_out(unsigned int frame_delay_per_step)
{
	grp_palette_inout(100, -1, frame_delay_per_step);
}

void pascal grp_palette_black_in(unsigned int frame_delay_per_step)
{
	grp_palette_inout(  0, +1, frame_delay_per_step);
}

void pascal grp_palette_white_out(unsigned int frame_delay_per_step)
{
	grp_palette_inout(100, +1, frame_delay_per_step);
}

void pascal grp_palette_white_in(unsigned int frame_delay_per_step)
{
	grp_palette_inout(200, -1, frame_delay_per_step);
}

bool grp_palette_load(const char *fn)
{
	if(!file_ropen(fn)) {
		return true;
	}
	file_seek(PI_PALETTE_OFFSET, 0);
	file_read(&grp_palette, sizeof(grp_palette));
	file_close();
	return false;
}

bool grp_palette_load_show(const char *fn)
{
	if(grp_palette_load(fn)) {
		return true;
	}
	if(grp_palette_tone != 100) {
		grp_palette_settone(grp_palette_tone);
	} else {
		z_palette_set_all_show(grp_palette);
	}
	return false;
}
// -------

int grp_put(const char *fn, grp_put_flag_t flag)
{
	extern int8_t* grp_buf;
	int option = 0;
	char ret;

	grp_buf = new int8_t[GRP_BUFFER_SIZE];
	if(flag & GPF_COLORKEY) {
		option = PILOAD_OPT_COLORKEY(15);
	}
	ret = PiLoad(fn, grp_buf, GRP_BUFFER_SIZE, 0, 0, 100, option);
	if(flag & GPF_PALETTE_SHOW) {
		grp_palette_load_show(fn);
	} else {
		grp_palette_load(fn);
	}

	delete[] grp_buf;
	return ret;
}

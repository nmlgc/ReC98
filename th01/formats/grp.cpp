#pragma option -zCPTN_GRP_GRZ

#include "libs/master.lib/master.hpp"
#include "libs/piloadc/piloadm.hpp"
#include "th01/hardware/frmdelay.h"
#include "th01/hardware/palette.h"
#include "th01/formats/grp.h"
#include "x86real.h"

// The same size that master.lib uses in graph_pi_load_pack(), with no
// explanation for it given in either master.lib or PILOADC.DOC...
#define GRP_BUFFER_SIZE 0x4000

// Palette
// -------

static const int TONE_STEP_PER_FRAME = 5;

Palette4 grp_palette;
static int grp_palette_tone = 100;

void grp_palette_settone(int tone)
{
	if(tone < 0) {
		tone = 0;
	} else if(tone > 200) {
		tone = 200;
	}
	for(vc_t col = 1; col < COLOR_COUNT; col++) {
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

void grp_palette_inout(
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

void grp_palette_black_out(unsigned int frame_delay_per_step)
{
	grp_palette_inout(100, -1, frame_delay_per_step);
}

void grp_palette_black_in(unsigned int frame_delay_per_step)
{
	grp_palette_inout(  0, +1, frame_delay_per_step);
}

void grp_palette_white_out(unsigned int frame_delay_per_step)
{
	grp_palette_inout(100, +1, frame_delay_per_step);
}

void grp_palette_white_in(unsigned int frame_delay_per_step)
{
	grp_palette_inout(200, -1, frame_delay_per_step);
}
// -------

int grp_put(const char *fn, grp_put_flag_t flag)
{
	static int8_t* grp_buf;
	int option = 0;
	int ret;
	const int8_t *grp_buf_aligned;

	grp_buf = new int8_t[GRP_BUFFER_SIZE];
	if(flag & GPF_COLORKEY) {
		option = PILOAD_OPT_COLORKEY(15);
	}
	if(!file_ropen(fn)) {
		ret = FileNotFound;
		goto err;
	}
	ret = PiBlitL(grp_buf, GRP_BUFFER_SIZE, 0, 0, option, file_read);
	file_close();

	// Pulling the palette out of the buffer this way might look like reliance
	// on implementation details, but it is, in fact, officially sanctioned
	// by PILOADC.DOC. Slightly ugly how we have also to replicate PiLoad's
	// paragraph rounding of the address, though...
	grp_buf_aligned = reinterpret_cast<const char *>(MK_FP(
		FP_SEG(grp_buf), ((FP_OFF(grp_buf) + 15) & ~15)
	));
	grp_palette = *reinterpret_cast<const Palette4 *>(grp_buf_aligned + 0x100);

	if(flag & GPF_PALETTE_SHOW) {
		if(grp_palette_tone != 100) {
			grp_palette_settone(grp_palette_tone);
		} else {
			z_palette_set_all_show(grp_palette);
		}
	}
err:
	delete[] grp_buf;
	return ret;
}

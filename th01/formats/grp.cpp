#pragma codeseg PTN_GRP_GRZ

extern "C" {
#include <stdio.h>
#include "platform.h"
#include "pc98.h"
#include "master.hpp"
#include "libs/piloadc/piloadc.h"
#include "th01/hardware/palette.h"
#include "th01/formats/grp.h"

// The same size that master.lib uses in graph_pi_load_pack(), with no
// explanation for it given in either master.lib or PILOADC.DOC...
#define GRP_BUFFER_SIZE 0x4000

// *Not* offsetof(PiHeader, palette)!
#define PI_PALETTE_OFFSET 0x12

extern int8_t* grp_buf;
extern int flag_palette_show; // = true
extern int flag_grp_put; // = true
extern bool flag_grp_colorkey; // = false

int grp_palette_load_show_sane(const char *fn)
{
	if(!file_ropen(fn)) {
		return 1;
	}
	file_seek(PI_PALETTE_OFFSET, 0);
	file_read(&grp_palette, sizeof(grp_palette));
#if (BINARY == 'E')
	grp_palette_settone(grp_palette_tone);
#else
	z_palette_set_all_show(grp_palette);
#endif
	file_close();
	return 0;
}

int grp_palette_load(const char *fn)
{
	if(!file_ropen(fn)) {
		return 1;
	}
	file_seek(PI_PALETTE_OFFSET, 0);
	file_read(&grp_palette, sizeof(grp_palette));
	file_close();
	return 0;
}

// Random unused function is random
int getkanji(FILE *fp)
{
	int low = getc(fp);
	low += (getc(fp) << 8);
	return low;
}

void grp_palette_set_all(const Palette4& pal)
{
	for(int col = 0; col < COLOR_COUNT; col++) {
		for(int comp = 0; comp < sizeof(RGB4); comp++) {
			grp_palette[col].v[comp] = pal[col].v[comp];
		}
	}
}

int grp_put_palette_show(const char *fn)
{
	int option = 0;
	char ret;

	grp_buf = new int8_t[GRP_BUFFER_SIZE];
	if(flag_palette_show == true) {
		// Setting bit 1 should set a resident palette of sorts, but this is
		// not actually supported by the PC-98 version of piloadc...
		option |= 2;
	}
	if(flag_grp_colorkey == true) {
		option = PILOAD_OPT_COLORKEY(15);
	}
	if(flag_grp_put == true) {
		ret = PiLoad(fn, grp_buf, GRP_BUFFER_SIZE, 0, 0, 100, option);
	}
	if(flag_palette_show == true) {
		grp_palette_load_show_sane(fn);
	} else {
		grp_palette_load(fn);
	}

	delete[] grp_buf;
	return ret;
}

int grp_put(const char *fn)
{
	flag_palette_show = false;
	int ret = grp_put_palette_show(fn);
	flag_palette_show = true;
	return ret;
}

int grp_palette_load_show(const char *fn)
{
	flag_grp_put = false;
	int ret = grp_put_palette_show(fn);
	flag_grp_put = true;
	return ret;
}

int grp_put_colorkey(const char *fn)
{
	flag_grp_colorkey = true;
	flag_palette_show = false;
	int ret = grp_put_palette_show(fn);
	flag_palette_show = true;
	flag_grp_colorkey = false;
	return ret;
}

}

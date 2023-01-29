#pragma option -zCPTN_GRP_GRZ

#include "platform.h"
#include "pc98.h"
#include "master.hpp"
#include "libs/piloadc/piloadc.hpp"
#include "th01/hardware/palette.h"
#include "th01/formats/grp.h"

// The same size that master.lib uses in graph_pi_load_pack(), with no
// explanation for it given in either master.lib or PILOADC.DOC...
#define GRP_BUFFER_SIZE 0x4000

// *Not* offsetof(PiHeader, palette)!
#define PI_PALETTE_OFFSET 0x12

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
#if (BINARY == 'E')
	grp_palette_settone(grp_palette_tone);
#else
	z_palette_set_all_show(grp_palette);
#endif
	return false;
}

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

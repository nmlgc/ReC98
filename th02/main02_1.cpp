/* ReC98
 * -----
 * 1st part of code segment #2 of TH02's MAIN.EXE
 */

#pragma codeseg SHARED
#pragma option -3

extern "C" {
#include <dos.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "th02/hardware/frmdelay.h"
#include "th02/formats/mptn.hpp"

#include "th02/hardware/keydelay.c"

int pascal mptn_load(const char *fn)
{
	extern bool mptn_show_palette_on_load;

	int ret;
	mptn_show_palette_on_load = false;
	ret = mptn_load_palette_show(fn);
	mptn_show_palette_on_load = true;
	return ret;
}

void mptn_free(void)
{
	if(mptn_buffer) {
		hmem_free(FP_SEG(mptn_buffer));
	}
	mptn_buffer = 0;
}

#include "th01/hardware/vplanset.c"
}

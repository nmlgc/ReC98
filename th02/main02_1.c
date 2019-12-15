/* ReC98
 * -----
 * 1st part of code segment #2 of TH02's MAIN.EXE
 */

#include "th02/th02.h"
#include "th02/formats/pi.h"

#pragma codeseg main_02_TEXT
#pragma option -3

#include "th02/zunerror.c"
#include "th02/hardware/keydelay.c"

int pascal mptn_load_inner(const char *fn);

int pascal mptn_load(const char *fn)
{
	int ret;
	mptn_show_palette_on_load = 0;
	ret = mptn_load_inner(fn);
	mptn_show_palette_on_load = 1;
	return ret;
}

void pascal mptn_free(void)
{
	if(mptn_buffer) {
		hmem_free(FP_SEG(mptn_buffer));
	}
	mptn_buffer = 0;
}

#include "th01/hardware/vplanset.c"
#include "th02/formats/pi_load.c"
#include "th02/math/vector.c"
#include "th02/hardware/frmdely1.c"

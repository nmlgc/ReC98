/* ReC98
 * -----
 * 1st part of code segment #2 of TH02's MAIN.EXE
 */

#pragma option -zCSHARED -3

extern "C" {
#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "master.hpp"
#include "th02/formats/mptn.hpp"

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

}

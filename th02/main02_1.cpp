/* ReC98
 * -----
 * 1st part of code segment #2 of TH02's MAIN.EXE
 */

#pragma option -zCSHARED -3

extern "C" {
#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "master.hpp"
#include "th02/formats/mpn.hpp"

int pascal mpn_load(const char *fn)
{
	extern bool mpn_show_palette_on_load;

	int ret;
	mpn_show_palette_on_load = false;
	ret = mpn_load_palette_show(fn);
	mpn_show_palette_on_load = true;
	return ret;
}

void mpn_free(void)
{
	if(mpn_buffer) {
		HMem<int>::free(mpn_buffer);
	}
	mpn_buffer = 0;
}

}

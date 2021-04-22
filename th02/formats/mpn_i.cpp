#pragma option -zCSHARED -3

extern "C" {
#include <mem.h>
#include "platform.h"
#include "pc98.h"
#include "master.hpp"
#include "th02/formats/mpn.hpp"

void mpn_palette_show(void)
{
	palette_set_all(mpn_palette);
	palette_show();
}

int pascal mpn_load_palette_show(const char *fn)
{
	extern bool mpn_show_palette_on_load;
	mpn_header_t header;

	file_ropen(fn);
	file_read(&header, sizeof(header));
	mpn_count = header.count;
	file_read(&mpn_palette, sizeof(mpn_palette));
	if(mpn_show_palette_on_load) {
		mpn_palette_show();
	}
	if(mpn_buffer) {
		mpn_free();
	}
	mpn_buffer = reinterpret_cast<int __seg*>(
		hmem_allocbyte((mpn_count + 1) * MPN_SIZE)
	);
	if(!mpn_buffer) {
		file_close();
		return -1;
	}
	file_read(mpn_buffer, (mpn_count + 1) * MPN_SIZE);
	file_close();
	return 0;
}

}

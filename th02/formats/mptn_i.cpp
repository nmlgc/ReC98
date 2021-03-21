#pragma option -zCSHARED -3

extern "C" {
#include <mem.h>
#include "platform.h"
#include "pc98.h"
#include "master.hpp"
#include "th02/formats/mptn.hpp"

void mptn_palette_show(void)
{
	palette_set_all(mptn_palette);
	palette_show();
}

int pascal mptn_load_palette_show(const char *fn)
{
	extern bool mptn_show_palette_on_load;
	mptn_header_t header;

	file_ropen(fn);
	file_read(&header, sizeof(header));
	mptn_count = header.count;
	file_read(&mptn_palette, sizeof(mptn_palette));
	if(mptn_show_palette_on_load) {
		mptn_palette_show();
	}
	if(mptn_buffer) {
		mptn_free();
	}
	mptn_buffer = reinterpret_cast<int *>(reinterpret_cast<int __seg*>(
		hmem_allocbyte((mptn_count + 1) * MPTN_SIZE)
	));
	if(!mptn_buffer) {
		file_close();
		return -1;
	}
	file_read(mptn_buffer, (mptn_count + 1) * MPTN_SIZE);
	file_close();
	return 0;
}

}

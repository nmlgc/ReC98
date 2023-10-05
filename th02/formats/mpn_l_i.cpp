#pragma option -zCSHARED

#include <mem.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "th02/formats/tile.hpp"
extern "C" {
#include "th02/formats/mpn.hpp"

// TH04 copied this code and adjusted it to work with multiple .MPN slots.

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

	if(mpn_images) {
		mpn_free();
	}
	mpn_images = reinterpret_cast<mpn_image_t __seg* >(hmem_allocbyte(
		(mpn_count + 1) * sizeof(mpn_image_t)
	));
	if(!mpn_images) {
		file_close();
		return -1;
	}
	file_read(mpn_images, (mpn_count + 1) * sizeof(mpn_image_t));

	file_close();
	return 0;
}

}

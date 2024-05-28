#pragma option -zCSHARED

#include <mem.h>
#include "libs/master.lib/master.hpp"
#include "th02/formats/tile.hpp"
#include "th04/formats/mpn.hpp"

// Basically just a copy of the TH02 one, adjusted to work with multiple slots.

void pascal mpn_palette_show(int slot)
{
	palette_set_all(mpn_slots[slot].palette);
	palette_show();
}

int pascal mpn_load_palette_show(int slot, const char *fn)
{
	extern bool mpn_show_palette_on_load;
	mpn_header_t header;

	file_ropen(fn);

	mpn_t near &mpn = mpn_slots[slot];

	file_read(&header, sizeof(header));
	mpn.count = header.count;

	// Uh... what? It's simply sizeof(mpn_image_t).
	size_t mpn_size = ((mpn.count + 1) * sizeof(mpn_plane_t) * PLANE_COUNT);

	file_read(&mpn.palette, sizeof(mpn.palette));
	if(mpn_show_palette_on_load) {
		mpn_palette_show(slot);
	}

	mpn_free(slot);
	mpn.images = reinterpret_cast<mpn_image_t __seg *>(hmem_allocbyte(
		mpn_size
	));
	if(!mpn.images) {
		file_close();
		return -1;
	}
	file_read(mpn.images, mpn_size);

	file_close();
	return 0;
}

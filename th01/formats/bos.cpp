/// Uncompressed, 5-plane, 16-color + alpha, arbitrary-size sprite format
/// ---------------------------------------------------------------------

#include "th01/formats/bos.hpp"
#include "planar.h"

vram_byte_amount_t BOS::load(bos_image_t *image, const char fn[PF_FN_LEN])
{
	bos_header_t header;
	arc_file_open(fn);
	arc_file_read_far(header);
	arc_file_seek(sizeof(Palette4), SEEK_CUR); // Skip over the palette

	vram_w = header.vram_w;
	h = header.h;
	bos_image_count = header.inner.image_count;
	vram_byte_amount_t plane_size = (vram_w * h);

	for(uint8_t i = 0; i < header.inner.image_count; i++) {
		image->alpha = new dots8_t[plane_size];
		image->planes.B = new dots8_t[plane_size];
		image->planes.R = new dots8_t[plane_size];
		image->planes.G = new dots8_t[plane_size];
		image->planes.E = new dots8_t[plane_size];

		arc_file_read(image->alpha, plane_size);
		arc_file_read(image->planes.B, plane_size);
		arc_file_read(image->planes.R, plane_size);
		arc_file_read(image->planes.G, plane_size);
		arc_file_read(image->planes.E, plane_size);

		image++;
	}
	arc_file_close();
	return plane_size;
}

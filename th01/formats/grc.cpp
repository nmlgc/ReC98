#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "th01/formats/pf.hpp"
#include "th01/formats/grc.hpp"

int grc_load(int slot, const char fn[PF_FN_LEN])
{
	union {
		spriteformat_header_inner_t inner;
		Palette4 pal;
		int8_t space[50];
	} header;

	arc_file_load(fn);
	arc_file_seek(offsetof(grc_header_t, vram_w));
	arc_file_get_near(grc_images[slot].vram_w);
	arc_file_get_near(grc_images[slot].h);

	arc_file_get_far(header.inner);
	grc_images[slot].image_count = header.inner.image_count;
	// MODDERS:
	/* if(
		header.inner.image_count < 0 ||
		header.inner.image_count > GRC_IMAGES_PER_SLOT
	) {
		return 1;
	} */

	size_t image_size = (grc_images[slot].vram_w * grc_images[slot].h);
	arc_file_get_far(header.pal); // yeah, should have been a seek

	for(int image = 0; grc_images[slot].image_count > image; image++) {
		if(grc_images[slot].dots[image]) {
			delete[] grc_images[slot].dots[image];
		}
		grc_images[slot].dots[image] = new dots8_t[image_size];
		arc_file_get(grc_images[slot].dots[image], image_size);
	}
	arc_file_free();
	return 0;
}

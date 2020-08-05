#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "th01/formats/sprfmt_h.hpp"
#include "th01/formats/pf.hpp"
#include "th01/formats/bos.hpp"
#include "th01/main/boss/entity.hpp"

extern bool bos_header_only;

void bos_reset_all_broken(void)
{
	for(int slot = 0; slot < 10; slot++) { // should be BOS_SLOT_COUNT
		for(int image = 0; image < BOS_IMAGES_PER_SLOT; image++) {
			bos_images[slot].image[image].alpha = NULL;
			bos_images[slot].image[image].planes.B = NULL;
			bos_images[slot].image[image].planes.R = NULL;
			bos_images[slot].image[image].planes.G = NULL;
			bos_images[slot].image[image].planes.E = NULL;
		}
	}
}

int CBossEntity::bos_load(const char fn[PF_FN_LEN], int slot)
{
	union {
		bos_header_t outer;
		Palette4 pal;
		int8_t space[50];
	} header;

	arc_file_load(fn);

	arc_file_get_far(header.outer);
	vram_w = header.outer.vram_w;
	h = header.outer.h;
	bos_image_count = header.outer.inner.image_count;
	int image_size = (vram_w * h);

	arc_file_get_far(header.pal); // yeah, should have been a seek

	if(!bos_header_only) {
		/* TODO: Replace with the decompiled call
		 * 	bos_free(slot);
		 * once that function is part of this translation unit */
		__asm { push slot; nop; push cs; call near ptr bos_free; pop cx; }
		for(int i = 0; bos_image_count > i; i++) {
			#define bos bos_images[slot].image[i]
			bos.alpha = new dots16_t[image_size / 2];
			bos.planes.B = new dots16_t[image_size / 2];
			bos.planes.R = new dots16_t[image_size / 2];
			bos.planes.G = new dots16_t[image_size / 2];
			bos.planes.E = new dots16_t[image_size / 2];
			arc_file_get(reinterpret_cast<char *>(bos.alpha), image_size);
			arc_file_get(reinterpret_cast<char *>(bos.planes.B), image_size);
			arc_file_get(reinterpret_cast<char *>(bos.planes.R), image_size);
			arc_file_get(reinterpret_cast<char *>(bos.planes.G), image_size);
			arc_file_get(reinterpret_cast<char *>(bos.planes.E), image_size);
			#undef bos
		}
	}

	bos_slot = slot;
	arc_file_free();
	return 0;
}

void CBossEntity::bos_metadata_get(
	int &image_count, unsigned char &slot, int &vram_w, int &h
) const
{
	image_count = this->bos_image_count;
	slot = this->bos_slot;
	h = this->h;
	vram_w = this->vram_w;
}

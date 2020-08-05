#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "th01/hardware/graph.h"
#include "th01/formats/sprfmt_h.hpp"
#include "th01/formats/pf.hpp"
#include "th01/formats/bos.hpp"
#include "th01/main/boss/entity.hpp"

extern bool bos_header_only;

/// Helper functions
/// ----------------
// Part of ZUN's attempt at clipping at the left or right edges of VRAM, by
// comparing [vram_offset] against the value returned from this function.
inline int16_t vram_intended_y_for(int16_t vram_offset, int first_x) {
	return (first_x < 0)
		? ((vram_offset / ROW_SIZE) + 1)
		: ((vram_offset / ROW_SIZE) + 0);
}
/// ----------------

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

/// Blitting
/// --------
void CBossEntity::put_8(int left, int top, int image) const
{
	int16_t vram_offset_row = vram_offset_divmul(left, top);
	int16_t vram_offset;
	size_t bos_p = 0;
	int bos_y;
	int bos_word_x;
	int16_t intended_y;

	bos_image_t &bos = bos_images[bos_slot].image[image];
	if(bos_image_count <= image) {
		return;
	}

	for(bos_y = 0; h > bos_y; bos_y++) {
		int16_t vram_offset = vram_offset_row;
		intended_y = vram_intended_y_for(vram_offset_row, left);
		for(bos_word_x = 0; (vram_w / 2) > bos_word_x; bos_word_x++) {
			if((vram_offset / ROW_SIZE) == intended_y) {
				if(~bos.alpha[bos_p]) {
					grcg_setcolor_rmw(0);
					VRAM_PUT(B, vram_offset, ~bos.alpha[bos_p], 16);
					grcg_off();

					vram_or_emptyopt(B, vram_offset, bos.planes.B[bos_p], 16);
					vram_or_emptyopt(R, vram_offset, bos.planes.R[bos_p], 16);
					vram_or_emptyopt(G, vram_offset, bos.planes.G[bos_p], 16);
					vram_or_emptyopt(E, vram_offset, bos.planes.E[bos_p], 16);
				}
			}
			vram_offset += 2;
			bos_p++;
		}
		vram_offset_row += ROW_SIZE;
		if(vram_offset_row >= PLANE_SIZE) { // Clip at the bottom edge
			break;
		}
	}
}
/// --------

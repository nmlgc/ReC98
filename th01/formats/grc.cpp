#include "th01/hardware/graph.h"
#include "th01/formats/pf.hpp"
#include "th01/formats/grc.hpp"

grc_t grc_images[GRC_SLOT_COUNT];

int grc_load(main_grc_slot_t slot, const char fn[PF_FN_LEN])
{
	spriteformat_header_inner_t header;

	arc_file_load(fn);
	arc_file_seek(offsetof(grc_header_t, vram_w), SEEK_SET);
	arc_file_get_near(grc_images[slot].vram_w);
	arc_file_get_near(grc_images[slot].h);

	arc_file_get_far(header);
	grc_images[slot].image_count = header.image_count;
	// MODDERS:
	/* if(header.image_count < 0 || header.image_count > GRC_IMAGES_PER_SLOT) {
		return 1;
	} */

	size_t image_size = (grc_images[slot].vram_w * grc_images[slot].h);
	arc_file_seek(sizeof(Palette4), SEEK_CUR);

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

void grc_put_8(
	screen_x_t left, vram_y_t top, main_grc_slot_t slot, int image, vc2 col
)
{
	vram_offset_t vram_offset_row = vram_offset_shift(left, top);
	vram_offset_t vram_offset;
	pixel_t grc_y;
	vram_byte_amount_t grc_x;
	size_t grc_p = 0;
	vram_y_t vram_y;
	#define grc_slot grc_images[slot]

	if(
		((grc_slot.vram_w * -BYTE_DOTS) > left) || (left >= RES_X) ||
		((grc_slot.h      *         -1) > top)  || (top  >= RES_Y)
	) {
		return;
	}

	grcg_setcolor_rmw(col);
	for(grc_y = 0; grc_slot.h > grc_y; grc_y++) {
		vram_offset = vram_offset_row;
		vram_y = (vram_offset / ROW_SIZE);
		if(vram_offset_row >= 0) { // Clip at the top edge
			for(grc_x = 0; grc_slot.vram_w > grc_x; grc_x++) {
				if(grc_slot.dots[image][grc_p]) {
					// Clip at the left and right edges
					if(
						((left >= 0) && ((vram_offset / ROW_SIZE) == vram_y)) ||
						((left <  0) && ((vram_offset / ROW_SIZE) != vram_y))
					) {
						grcg_put(vram_offset, grc_slot.dots[image][grc_p], 8);
					}
				}
				grc_p++;
				vram_offset++;
			}
		} else {
			grc_p += grc_slot.vram_w;
		}
		vram_offset_row += ROW_SIZE;
		if(vram_offset_row >= PLANE_SIZE) { // Clip at the bottom edge
			break;
		}
	}
	grcg_off_func();

	#undef grc_slot
}

void grc_free(main_grc_slot_t slot)
{
	for(int i = 0; grc_images[slot].image_count > i; i++) {
		if(grc_images[slot].dots[i]) {
			delete[] grc_images[slot].dots[i];
			grc_images[slot].dots[i] = nullptr;
		}
	}
}

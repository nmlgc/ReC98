extern "C" {
#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "th01/hardware/graph.h"
#include "th01/hardware/planar.h"
#include "th01/formats/pf.hpp"
#include "th01/formats/sprfmt_h.hpp"
#include "th01/formats/bos.hpp"
#include "th01/main/player/anim.hpp"
}

int CPlayerAnim::load(const char fn[PF_FN_LEN])
{
	vram_byte_amount_t plane_size;
	vram_byte_amount_t bos_p;

	bos_header_load(this, plane_size, fn, false);
	// MODDERS: [bos_image_count] must be < [PLAYER_ANIM_IMAGES_PER_SLOT]
	for(int i = 0; bos_image_count > i; i++) {
		alpha[i] = new dots8_t[plane_size];
		planes.B[i] = new dots8_t[plane_size];
		planes.R[i] = new dots8_t[plane_size];
		planes.G[i] = new dots8_t[plane_size];
		planes.E[i] = new dots8_t[plane_size];
		arc_file_get(reinterpret_cast<char *>(alpha[i]), plane_size);
		arc_file_get(reinterpret_cast<char *>(planes.B[i]), plane_size);
		arc_file_get(reinterpret_cast<char *>(planes.R[i]), plane_size);
		arc_file_get(reinterpret_cast<char *>(planes.G[i]), plane_size);
		arc_file_get(reinterpret_cast<char *>(planes.E[i]), plane_size);

		for(bos_p = 0; bos_p < plane_size; bos_p++) {
			alpha[i][bos_p] = ~alpha[i][bos_p];
			planes.B[i][bos_p] &= alpha[i][bos_p];
			planes.R[i][bos_p] &= alpha[i][bos_p];
			planes.G[i][bos_p] &= alpha[i][bos_p];
			planes.E[i][bos_p] &= alpha[i][bos_p];
		}
	}
	arc_file_free();
	return 0;
}

void CPlayerAnim::unput_8(screen_x_t left, vram_y_t top, int image) const
{
	vram_offset_t vram_offset;
	vram_byte_amount_t bos_p = 0;
	vram_offset_t vram_offset_row;
	pixel_t bos_y;
	vram_byte_amount_t bos_byte_x;

	if(bos_image_count <= image) {
		return;
	}

	vram_offset_row = vram_offset_divmul_wtf(left, top);

	for(bos_y = 0; h > bos_y; bos_y++) {
		vram_offset = vram_offset_row;
		vram_y_t intended_y = vram_intended_y_for(vram_offset_row, left);
		for(bos_byte_x = 0; vram_w > bos_byte_x; bos_byte_x++) {
			if(
				((vram_offset / ROW_SIZE) == intended_y) &&
				(vram_offset >= 0) // Clip at the top edge
			) {
				if(alpha[image][bos_p]) {
					dots8_t bg_dots;
					vram_erase_on_0(vram_offset, alpha[image][bos_p], 8);
					vram_unput_masked_emptyopt_planar(
						vram_offset, 8, alpha[image][bos_p], bg_dots
					);
				}
			}
			vram_offset++;
			bos_p++;
		}
		vram_offset_row += ROW_SIZE;
		if(vram_offset_row >= PLANE_SIZE) { // Clip at the bottom edge
			break;
		}
	}
	graph_accesspage_func(0);
}

#define put_row(byte_x, vram_offset, bos_p, image) \
	for(bos_byte_x = 0; vram_w > bos_byte_x; bos_byte_x++) { \
		if( \
			((vram_offset / ROW_SIZE) == intended_y) && \
			(vram_offset >= 0) /* Clip at the top edge */ \
		) { \
			if(alpha[image][bos_p]) { \
				vram_erase_on_0(vram_offset, alpha[image][bos_p], 8); \
				vram_or_emptyopt(B, vram_offset, planes.B[image][bos_p], 8); \
				vram_or_emptyopt(R, vram_offset, planes.R[image][bos_p], 8); \
				vram_or_emptyopt(G, vram_offset, planes.G[image][bos_p], 8); \
				vram_or_emptyopt(E, vram_offset, planes.E[image][bos_p], 8); \
			} \
		} \
		vram_offset++; \
		bos_p++; \
	}

void CPlayerAnim::put_0_8(screen_x_t left, vram_y_t top, int image) const
{
	vram_byte_amount_t bos_p = 0;
	vram_offset_t vram_offset_row;
	vram_offset_t vram_offset;
	pixel_t bos_y;
	vram_byte_amount_t bos_byte_x;

	if(bos_image_count <= image) {
		return;
	}

	vram_offset_row = vram_offset_divmul_wtf(left, top);

	for(bos_y = 0; h > bos_y; bos_y++) {
		vram_offset = vram_offset_row;
		vram_y_t intended_y = vram_intended_y_for(vram_offset_row, left);
		put_row(bos_byte_x, vram_offset, bos_p, image);
		vram_offset_row += ROW_SIZE;
		if(vram_offset_row >= PLANE_SIZE) { // Clip at the bottom edge
			break;
		}
	}
	graph_accesspage_func(0);
}

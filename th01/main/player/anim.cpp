#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "th01/hardware/graph.h"
#include "th01/hardware/grph1to0.hpp"
#include "th01/hardware/planar.h"
#include "th01/formats/pf.hpp"
#include "th01/formats/sprfmt_h.hpp"
#include "th01/formats/bos.hpp"
#include "th01/main/playfld.hpp"
#include "th01/main/player/player.hpp"
#include "th01/main/player/anim.hpp"

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

#define put_row(bos_byte_x, vram_offset, intended_y, bos_p, image) \
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
		put_row(bos_byte_x, vram_offset, intended_y, bos_p, image);
		vram_offset_row += ROW_SIZE;
		if(vram_offset_row >= PLANE_SIZE) { // Clip at the bottom edge
			break;
		}
	}
	graph_accesspage_func(0);
}

void CPlayerAnim::unput_and_put_overlapped_8(
	screen_x_t put_left,
	vram_y_t put_top,
	screen_x_t unput_left,
	vram_y_t unput_top,
	int put_image,
	int unput_image
) const
{
	vram_byte_amount_t bos_p;
	vram_byte_amount_t unput_byte_x;
	pixel_t bos_y;
	vram_offset_t vram_offset_row;
	vram_byte_amount_t vram_distance_from_unput_to_put;

	// MODDERS: This obviously imposes a practical limit of 64 pixels on .BOS
	// sprite widths
	dots8_t unput_mask[64 / BYTE_DOTS];

	vram_offset_t vram_offset;
	vram_byte_amount_t bos_byte_x;

	// Probably supposed to needlessly make sure that both values are positive?
	vram_distance_from_unput_to_put = (
		((put_left + PLAYER_W) >> 3) - ((unput_left + PLAYER_W) >> 3)
	);
	bos_p = 0;

	if(bos_image_count <= put_image) {
		return;
	}

	vram_offset_row = vram_offset_divshift_wtf(put_left, put_top);

	for(bos_y = 0; h > bos_y; bos_y++) {
		vram_offset = vram_offset_row;
		vram_y_t intended_y = vram_intended_y_for(vram_offset_row, put_left);

		if(vram_distance_from_unput_to_put > 0) {
			unput_mask[0] = alpha[unput_image][bos_p];
			for(unput_byte_x = 1; (vram_w - 0) > unput_byte_x; unput_byte_x++) {
				unput_mask[unput_byte_x] = (
					~alpha[  put_image][bos_p + unput_byte_x - 1] &
					 alpha[unput_image][bos_p + unput_byte_x - 0]
				);
			}
		} else if(vram_distance_from_unput_to_put < 0) {
			for(unput_byte_x = 0; (vram_w - 1) > unput_byte_x; unput_byte_x++) {
				unput_mask[unput_byte_x] = (
					~alpha[  put_image][bos_p + unput_byte_x + 1] &
					 alpha[unput_image][bos_p + unput_byte_x + 0]
				);
			}
			unput_mask[vram_w - 1] = alpha[unput_image][bos_p + vram_w - 1];
		} else if(vram_distance_from_unput_to_put == 0) {
			for(unput_byte_x = 0; (vram_w - 0) > unput_byte_x; unput_byte_x++) {
				unput_mask[unput_byte_x] = (
					~alpha[  put_image][bos_p + unput_byte_x] &
					 alpha[unput_image][bos_p + unput_byte_x]
				);
			}
		}
		if(unput_left >= 0) {
			graph_hline_unput_masked_8(
				unput_left, (unput_top + bos_y), unput_mask, vram_w
			);
		} else {
			graph_hline_unput_masked_8(
				0, (unput_top + bos_y), (unput_mask + 1), (vram_w - 1)
			);
		}
		put_row(bos_byte_x, vram_offset, intended_y, bos_p, put_image);

		vram_offset_row += ROW_SIZE;
		if(vram_offset_row >= PLANE_SIZE) { // Clip at the bottom edge
			break;
		}
	}
	graph_accesspage_func(0);
}

void CPlayerAnim::free(void)
{
	for(int i = 0; bos_image_count > i; i++) {
		delete[] alpha[i];
		delete[] planes.B[i];
		delete[] planes.R[i];
		delete[] planes.G[i];
		delete[] planes.E[i];
	}
}

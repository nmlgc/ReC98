#include "th01/hardware/graph.h"
#include "th01/hardware/grph1to0.hpp"
#include "th01/hardware/planar.h"
#include "th01/formats/pf.hpp"
#include "th01/formats/bos.hpp"
#include "th01/main/player/player.hpp"
#include "th01/main/player/anim.hpp"
#include "platform/x86real/pc98/page.hpp"

CPlayerAnim player_48x48;
CPlayerAnim player_48x32;

int CPlayerAnim::load(const char fn[PF_FN_LEN])
{
	vram_byte_amount_t plane_size;
	vram_byte_amount_t bos_p;

	bos_header_load(this, plane_size, fn, false);

	// MODDERS: [bos_image_count] must be < [PLAYER_ANIM_IMAGES_PER_SLOT]
	bos_image_t *bos = images;
	for(int i = 0; bos_image_count > i; i++) {
		bos->alpha = new dots8_t[plane_size];
		bos->planes.B = new dots8_t[plane_size];
		bos->planes.R = new dots8_t[plane_size];
		bos->planes.G = new dots8_t[plane_size];
		bos->planes.E = new dots8_t[plane_size];
		arc_file_get(bos->alpha, plane_size);
		arc_file_get(bos->planes.B, plane_size);
		arc_file_get(bos->planes.R, plane_size);
		arc_file_get(bos->planes.G, plane_size);
		arc_file_get(bos->planes.E, plane_size);

		for(bos_p = 0; bos_p < plane_size; bos_p++) {
			const dots8_t negated_alpha = ~bos->alpha[bos_p];
			bos->alpha[bos_p] = negated_alpha;
			bos->planes.B[bos_p] &= negated_alpha;
			bos->planes.R[bos_p] &= negated_alpha;
			bos->planes.G[bos_p] &= negated_alpha;
			bos->planes.E[bos_p] &= negated_alpha;
		}
		bos++;
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
	const bos_image_t& anim = images[image];

	vram_offset_row = vram_offset_divmul_wtf(left, top);

	for(bos_y = 0; h > bos_y; bos_y++) {
		vram_offset = vram_offset_row;
		vram_y_t intended_y = vram_intended_y_for(vram_offset_row, left);
		for(bos_byte_x = 0; vram_w > bos_byte_x; bos_byte_x++) {
			if(
				((vram_offset / ROW_SIZE) == intended_y) &&
				(vram_offset >= 0) // Clip at the top edge
			) {
				const uint8_t alpha_dots = anim.alpha[bos_p];
				if(alpha_dots) {
					dots8_t bg_dots;
					vram_erase_on_0(vram_offset, alpha_dots, 8);
					vram_unput_masked_emptyopt_planar(
						vram_offset, 8, alpha_dots, bg_dots
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
	page_access(0);
}

#define put_row(bos_byte_x, vram_offset, intended_y, bos, bos_p) \
	for(bos_byte_x = 0; vram_w > bos_byte_x; bos_byte_x++) { \
		if( \
			((vram_offset / ROW_SIZE) == intended_y) && \
			(vram_offset >= 0) /* Clip at the top edge */ \
		) { \
			if(bos.alpha[bos_p]) { \
				vram_erase_on_0(vram_offset, bos.alpha[bos_p], 8); \
				vram_or_emptyopt(B, vram_offset, bos.planes.B[bos_p], 8); \
				vram_or_emptyopt(R, vram_offset, bos.planes.R[bos_p], 8); \
				vram_or_emptyopt(G, vram_offset, bos.planes.G[bos_p], 8); \
				vram_or_emptyopt(E, vram_offset, bos.planes.E[bos_p], 8); \
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
	const bos_image_t& bos = images[image];

	vram_offset_row = vram_offset_divmul_wtf(left, top);

	for(bos_y = 0; h > bos_y; bos_y++) {
		vram_offset = vram_offset_row;
		vram_y_t intended_y = vram_intended_y_for(vram_offset_row, left);
		put_row(bos_byte_x, vram_offset, intended_y, bos, bos_p);
		vram_offset_row += ROW_SIZE;
		if(vram_offset_row >= PLANE_SIZE) { // Clip at the bottom edge
			break;
		}
	}
	page_access(0);
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
		((  put_left + PLAYER_W) >> BYTE_BITS) -
		((unput_left + PLAYER_W) >> BYTE_BITS)
	);
	bos_p = 0;

	if(bos_image_count <= put_image) {
		return;
	}
	const bos_image_t& unput_bos = images[unput_image];
	const bos_image_t& put_bos = images[put_image];

	vram_offset_row = vram_offset_divshift_wtf(put_left, put_top);

	for(bos_y = 0; h > bos_y; bos_y++) {
		vram_offset = vram_offset_row;
		vram_y_t intended_y = vram_intended_y_for(vram_offset_row, put_left);

		if(vram_distance_from_unput_to_put > 0) {
			unput_mask[0] = unput_bos.alpha[bos_p];
			for(unput_byte_x = 1; (vram_w - 0) > unput_byte_x; unput_byte_x++) {
				unput_mask[unput_byte_x] = (
					 ~put_bos.alpha[bos_p + unput_byte_x - 1] &
					unput_bos.alpha[bos_p + unput_byte_x - 0]
				);
			}
		} else if(vram_distance_from_unput_to_put < 0) {
			for(unput_byte_x = 0; (vram_w - 1) > unput_byte_x; unput_byte_x++) {
				unput_mask[unput_byte_x] = (
					 ~put_bos.alpha[bos_p + unput_byte_x + 1] &
					unput_bos.alpha[bos_p + unput_byte_x + 0]
				);
			}
			unput_mask[vram_w - 1] = unput_bos.alpha[bos_p + vram_w - 1];
		} else if(vram_distance_from_unput_to_put == 0) {
			for(unput_byte_x = 0; (vram_w - 0) > unput_byte_x; unput_byte_x++) {
				unput_mask[unput_byte_x] = (
					 ~put_bos.alpha[bos_p + unput_byte_x] &
					unput_bos.alpha[bos_p + unput_byte_x]
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
		put_row(bos_byte_x, vram_offset, intended_y, put_bos, bos_p);

		vram_offset_row += ROW_SIZE;
		if(vram_offset_row >= PLANE_SIZE) { // Clip at the bottom edge
			break;
		}
	}
	page_access(0);
}

void CPlayerAnim::free(void)
{
	bos_image_t *bos = images;
	for(int i = 0; bos_image_count > i; i++) {
		delete[] bos->alpha;
		delete[] bos->planes.B;
		delete[] bos->planes.R;
		delete[] bos->planes.G;
		delete[] bos->planes.E;
		bos++;
	}
}

#include "ReC98.h"
#include "th01/math/wave.hpp"
#include "th01/hardware/egc.h"
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

#define vram_offset_at_intended_y_16(vram_offset, intended_y) \
	(((vram_offset + 0) / ROW_SIZE) == intended_y) && \
	(((vram_offset + 1) / ROW_SIZE) == intended_y)
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
void CBossEntity::put_1line(int left, int y, int image, int row) const
{
	int16_t vram_offset_row = vram_offset_shift(left, y);
	int bos_word_x;
	size_t bos_p = 0;
	int16_t intended_y;
	char first_bit = (left & (BYTE_DOTS - 1));
	char other_shift = ((1 * BYTE_DOTS) - first_bit);

	bos_image_t &bos = bos_images[bos_slot].image[image];
	if(bos_image_count <= image) {
		return;
	}

	int16_t vram_offset = vram_offset_row;
	intended_y = vram_intended_y_for(vram_offset_row, left);

	bos_p = ((vram_w / 2) * row);
	for(bos_word_x = 0; (vram_w / 2) > bos_word_x; bos_word_x++) {
		if((vram_offset / ROW_SIZE) == intended_y) {
			struct {
				twobyte_t alpha, B, R, G, E;
			} cur;

			cur.alpha.v = ~bos.alpha[bos_p];
			cur.B.v = bos.planes.B[bos_p];
			cur.R.v = bos.planes.R[bos_p];
			cur.G.v = bos.planes.G[bos_p];
			cur.E.v = bos.planes.E[bos_p];

			#define vram_byte(plane, byte) \
				(VRAM_PLANE_##plane + vram_offset)[byte]
			if(first_bit == 0) {
				for(register int byte = 0; byte < sizeof(dots16_t); byte++) {
					grcg_setcolor_rmw(0);
					vram_byte(B, byte) = cur.alpha.u[byte];
					grcg_off();

					vram_byte(B, byte) |= cur.B.u[byte];
					vram_byte(R, byte) |= cur.R.u[byte];
					vram_byte(G, byte) |= cur.G.u[byte];
					vram_byte(E, byte) |= cur.E.u[byte];
				}
			} else {
				for(register int byte = 0; byte < sizeof(dots16_t); byte++) {
					grcg_setcolor_rmw(0);
					vram_byte(B, byte + 0) = (cur.alpha.u[byte] >> first_bit);
					vram_byte(B, byte + 1) = (cur.alpha.u[byte] << other_shift);
					grcg_off();

					vram_byte(B, byte + 0) |= (cur.B.u[byte] >> first_bit);
					vram_byte(R, byte + 0) |= (cur.R.u[byte] >> first_bit);
					vram_byte(G, byte + 0) |= (cur.G.u[byte] >> first_bit);
					vram_byte(E, byte + 0) |= (cur.E.u[byte] >> first_bit);
					vram_byte(B, byte + 1) |= (cur.B.u[byte] << other_shift);
					vram_byte(R, byte + 1) |= (cur.R.u[byte] << other_shift);
					vram_byte(G, byte + 1) |= (cur.G.u[byte] << other_shift);
					vram_byte(E, byte + 1) |= (cur.E.u[byte] << other_shift);
				}
			}
			#undef vram_byte
		}
		vram_offset += 2;
		bos_p++;
	}
}
void pascal near vram_snap_masked(
	dots16_t &dst, dots8_t plane[], uint16_t vram_offset, dots16_t mask
)
{
	dst = (reinterpret_cast<dots16_t &>(plane[vram_offset]) & mask);
}

void pascal near vram_put_bg_fg(
	sdots16_t fg, dots8_t plane[], uint16_t vram_offset, sdots16_t bg_masked
)
{
	reinterpret_cast<dots16_t &>(plane[vram_offset]) = (fg | bg_masked);
}

void pascal near vram_put_unaligned_bg_fg(
	sdots16_t fg,
	dots8_t plane[],
	uint16_t vram_offset,
	uint16_t bg_masked,
	char first_bit
)
{
	sdots16_t fg_shifted = (fg >> first_bit) + (fg << (16 - first_bit));
	reinterpret_cast<dots16_t &>(plane[vram_offset]) = (fg_shifted | bg_masked);
}

#define vram_snap_masked_planar(dst, vram_offset, mask) \
	vram_snap_masked(dst.B, VRAM_PLANE_B, vram_offset, mask); \
	vram_snap_masked(dst.R, VRAM_PLANE_R, vram_offset, mask); \
	vram_snap_masked(dst.G, VRAM_PLANE_G, vram_offset, mask); \
	vram_snap_masked(dst.E, VRAM_PLANE_E, vram_offset, mask);

#define vram_put_bg_fg_planar(vram_offset, bg, fg) \
	vram_put_bg_fg(fg.B, VRAM_PLANE_B, vram_offset, bg.B); \
	vram_put_bg_fg(fg.R, VRAM_PLANE_R, vram_offset, bg.R); \
	vram_put_bg_fg(fg.G, VRAM_PLANE_G, vram_offset, bg.G); \
	vram_put_bg_fg(fg.E, VRAM_PLANE_E, vram_offset, bg.E);

#define vram_put_bg_word_planar(vram_offset, bg, planes, p) \
	vram_put_bg_fg(planes.B[p], VRAM_PLANE_B, vram_offset, bg.B); \
	vram_put_bg_fg(planes.R[p], VRAM_PLANE_R, vram_offset, bg.R); \
	vram_put_bg_fg(planes.G[p], VRAM_PLANE_G, vram_offset, bg.G); \
	vram_put_bg_fg(planes.E[p], VRAM_PLANE_E, vram_offset, bg.E);

#define vram_put_unaligned_bg_fg_planar(vram_offset, bg, fg, first_bit) \
	vram_put_unaligned_bg_fg(fg.B, VRAM_PLANE_B, vram_offset, bg.B, first_bit); \
	vram_put_unaligned_bg_fg(fg.R, VRAM_PLANE_R, vram_offset, bg.R, first_bit); \
	vram_put_unaligned_bg_fg(fg.G, VRAM_PLANE_G, vram_offset, bg.G, first_bit); \
	vram_put_unaligned_bg_fg(fg.E, VRAM_PLANE_E, vram_offset, bg.E, first_bit);

void CBossEntity::unput_and_put_1line(int left, int y, int image, int row) const
{
	int16_t vram_offset_row = vram_offset_shift(left, y);
	int bos_word_x;
	size_t bos_p = 0;
	int16_t intended_y;
	char first_bit = (left & (BYTE_DOTS - 1));
	char other_shift = ((2 * BYTE_DOTS) - first_bit);
	Planar<dots16_t> bg_masked;
	dots16_t mask_unaligned;

	bos_image_t &bos = bos_images[bos_slot].image[image];
	if(bos_image_count <= image) {
		return;
	}

	int16_t vram_offset = vram_offset_row;
	intended_y = vram_intended_y_for(vram_offset_row, left);

	bos_p = ((vram_w / 2) * row);
	for(bos_word_x = 0; (vram_w / 2) > bos_word_x; bos_word_x++) {
		if((vram_offset / ROW_SIZE) == intended_y) {
			Planar<dots16_t> fg;

			dots16_t alpha = bos.alpha[bos_p];
			fg.B = bos.planes.B[bos_p];
			fg.R = bos.planes.R[bos_p];
			fg.G = bos.planes.G[bos_p];
			fg.E = bos.planes.E[bos_p];
			if(first_bit == 0) {
				graph_accesspage_func(1);
				vram_snap_masked_planar(bg_masked, vram_offset, alpha);
				graph_accesspage_func(0);
				vram_put_bg_fg_planar(vram_offset, bg_masked, fg);
			} else {
				graph_accesspage_func(1);
				mask_unaligned = (
					(alpha >> first_bit) + (alpha << other_shift)
				);
				vram_snap_masked_planar(bg_masked, vram_offset, mask_unaligned);
				graph_accesspage_func(0);
				vram_put_unaligned_bg_fg_planar(
					vram_offset, bg_masked, fg, first_bit
				);
			}
		}
		vram_offset += 2;
		bos_p++;
	}
}

void CBossEntity::unput_and_put_8(int left, int top, int image) const
{
	int16_t vram_offset_row = vram_offset_divmul(left, top);
	int16_t vram_offset;
	size_t bos_p = 0;
	int bos_y;
	int bos_word_x;
	int16_t intended_y;
	Planar<dots16_t> bg_masked;

	bos_image_t &bos = bos_images[bos_slot].image[image];
	if(bos_image_count <= image) {
		return;
	}

	for(bos_y = 0; h > bos_y; bos_y++) {
		int16_t vram_offset = vram_offset_row;
		intended_y = vram_intended_y_for(vram_offset_row, left);
		for(bos_word_x = 0; (vram_w / 2) > bos_word_x; bos_word_x++) {
			if(
				vram_offset_at_intended_y_16(vram_offset, intended_y) &&
				(vram_offset >= 0) // Clip at the top edge
			) {
				graph_accesspage_func(1);
				if(bos.alpha[bos_p]) {
					vram_snap_planar_masked(
						bg_masked, vram_offset, 16, bos.alpha[bos_p]
					);
				} else {
					bg_masked.B = bg_masked.R = bg_masked.G = bg_masked.E = 0;
				}
				graph_accesspage_func(0);
				VRAM_PUT(B, vram_offset, bos.planes.B[bos_p] | bg_masked.B, 16);
				VRAM_PUT(R, vram_offset, bos.planes.R[bos_p] | bg_masked.R, 16);
				VRAM_PUT(G, vram_offset, bos.planes.G[bos_p] | bg_masked.G, 16);
				VRAM_PUT(E, vram_offset, bos.planes.E[bos_p] | bg_masked.E, 16);
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

#define vram_unput_masked_emptyopt(plane, offset, bit_count, mask, tmp_dots) \
	graph_accesspage_func(1); \
	VRAM_SNAP(tmp_dots, plane, offset, bit_count); \
	if(tmp_dots) { \
		graph_accesspage_func(0); \
		VRAM_CHUNK(plane, offset, bit_count) |= (mask & tmp_dots); \
	}

#define vram_unput_masked_emptyopt_planar(offset, bit_count, mask, tmp_dots) \
	vram_unput_masked_emptyopt(B, offset, bit_count, mask, tmp_dots); \
	vram_unput_masked_emptyopt(R, offset, bit_count, mask, tmp_dots); \
	vram_unput_masked_emptyopt(G, offset, bit_count, mask, tmp_dots); \
	vram_unput_masked_emptyopt(E, offset, bit_count, mask, tmp_dots);

void CBossEntity::unput_8(int left, int top, int image) const
{
	int16_t vram_offset_row = vram_offset_divmul(left, top);
	int16_t vram_offset;
	int bos_y;
	int bos_word_x;
	size_t bos_p = 0;
	int16_t intended_y;

	bos_image_t &bos = bos_images[bos_slot].image[image];
	if(bos_image_count <= image) {
		return;
	}

	for(bos_y = 0; h > bos_y; bos_y++) {
		int16_t vram_offset = vram_offset_row;
		intended_y = vram_intended_y_for(vram_offset_row, left);
		for(bos_word_x = 0; (vram_w / 2) > bos_word_x; bos_word_x++) {
			if(
				vram_offset_at_intended_y_16(vram_offset, intended_y) &&
				(vram_offset >= 0) // Clip at the top edge
			) {
				grcg_setcolor_rmw(0);
				graph_accesspage_func(0);
				VRAM_PUT(B, vram_offset, ~bos.alpha[bos_p], 16);
				grcg_off();

				if(~bos.alpha[bos_p]) {
					dots16_t bg_dots;
					vram_unput_masked_emptyopt_planar(
						vram_offset, 16, ~bos.alpha[bos_p], bg_dots
					);
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
	graph_accesspage_func(0);
}

#define wave_func(func, left, top, image, len, amp, phase) \
	int t = phase; \
	for(int bos_y = 0; h > bos_y; bos_y++) { \
		int x = (wave_x(amp, t) + left); \
		t += (0x100 / len); \
		func(x, (top + bos_y), image, bos_y); \
	}

void CBossEntity::wave_put(
	int left, int top, int image, int len, int amp, int phase
) const
{
	wave_func(put_1line, left, top, image, len, amp, phase);
}

void CBossEntity::wave_unput_and_put(
	int left, int top, int image, int len, int amp, int phase
) const
{
	wave_func(unput_and_put_1line, left, top, image, len, amp, phase);
}

inline int word_align(int v) {
	return (((v / 16) * 16) + 16);
}

void CBossEntity::egc_sloppy_wave_unput_double_broken(
	int left_1, int top, int,
	int len_1, int amp_1, int phase_1,
	int left_2,
	int len_2, int amp_2, int phase_2
) const
{
	int x_1;
	int t_1 = phase_1;
	int x_2;
	int t_2 = phase_2;
	for(int bos_y = 0; h > bos_y; bos_y++) {
		x_1 = wave_x(amp_1, t_1) + left_1;
		x_2 = wave_x(amp_2, t_2) + left_2;
		t_1 += (0x100 / len_1);
		t_2 += (0x100 / len_2);
		// ZUN bug: Shouldn't the [h] parameter be 1?
		if(x_1 > x_2) {
			egc_copy_rect_1_to_0_16(
				x_2, (top + bos_y), word_align(x_1 - x_2), bos_y
			);
		} else {
			egc_copy_rect_1_to_0_16(
				(x_1 - vram_w), (top + bos_y), word_align(x_2 - x_1), bos_y
			);
		}
	}
}

void CBossEntity::unput_and_put_16x8_8(int bos_left, int bos_top) const
{
	int16_t vram_offset_row = vram_offset_shift(cur_left, cur_top);
	int bos_row;
	size_t bos_p = 0;
	int intended_y;
	int image = bos_image;
	Planar<dots16_t> bg_masked;
	bos_image_t &bos = bos_images[bos_slot].image[image];

	// Yes, the macro form. Out of all places that could have required it, it
	// had to be an originally unused function…
	vram_offset_row += VRAM_OFFSET_SHIFT(bos_left, bos_top);
	bos_p = (((vram_w / 2) * bos_top) + (bos_left / 16));

	if(bos_image_count <= image) {
		return;
	}

	for(bos_row = 0; bos_row < 8; bos_row++) {
		int16_t vram_offset = vram_offset_row;
		// Note the difference between this and vram_offset_at_intended_y_16()!
		intended_y = (bos_left < 0)
			? ((vram_offset_row / ROW_SIZE) - 1)
			: ((vram_offset_row / ROW_SIZE) - 0);
		if(
			(((vram_offset + 1) / ROW_SIZE) == intended_y) &&
			(vram_offset >= 0) // Clip at the top edge
		) {
			graph_accesspage_func(1);
			vram_snap_masked_planar(bg_masked, vram_offset, bos.alpha[bos_p]);
			graph_accesspage_func(0);
			vram_put_bg_word_planar(vram_offset, bg_masked, bos.planes, bos_p);
			vram_offset += 2;
		}
		bos_p += (vram_w / 2);
		vram_offset_row += ROW_SIZE;
		if(vram_offset_row >= PLANE_SIZE) { // Clip at the bottom edge
			break;
		}
	}
}
/// --------

void CBossEntity::pos_set(
	int left,
	int top,
	int unknown,
	int move_clamp_left,
	int move_clamp_right,
	int move_clamp_top,
	int move_clamp_bottom
)
{
	this->cur_left = left;
	this->cur_top = top;
	this->unknown = unknown;
	this->move_clamp.left = move_clamp_left;
	this->move_clamp.right = move_clamp_right;
	this->move_clamp.top = move_clamp_top;
	this->move_clamp.bottom = move_clamp_bottom;
	this->zero_2 = 0;
}

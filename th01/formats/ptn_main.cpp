extern "C" {
#include "th01/hardware/graph.h"
}
#include "th01/hardware/egc.h"
#include "th01/hardware/planar.h"
#include "th01/formats/ptn.hpp"

bool ptn_sloppy_unput_before_alpha_put = false;

static inline ptn_t* ptn_with_id_shift(int id) {
	// Before we bother with doing compile-time integer logarithms...
	// (MODDERS: This function shouldn't exist. Just use the regular
	// ptn_with_id().)
	if(PTN_IMAGES_PER_SLOT == 64) {
		return &ptn_images[id >> 6][id % PTN_IMAGES_PER_SLOT];
	}
	return &ptn_images[id / PTN_IMAGES_PER_SLOT][id % PTN_IMAGES_PER_SLOT];
}

#define ptn_or_masked(vram_offset, w, ptn, mask) \
	VRAM_CHUNK(B, vram_offset, w) |= (ptn->planes.B[y] & mask); \
	VRAM_CHUNK(R, vram_offset, w) |= (ptn->planes.R[y] & mask); \
	VRAM_CHUNK(G, vram_offset, w) |= (ptn->planes.G[y] & mask); \
	VRAM_CHUNK(E, vram_offset, w) |= (ptn->planes.E[y] & mask);

#define ptn_or_quarter_masked(vram_offset, w, ptn, q, mask) \
	VRAM_CHUNK(B, vram_offset, w) |= ((ptn->planes.B[y] >> q.x) & mask); \
	VRAM_CHUNK(R, vram_offset, w) |= ((ptn->planes.R[y] >> q.x) & mask); \
	VRAM_CHUNK(G, vram_offset, w) |= ((ptn->planes.G[y] >> q.x) & mask); \
	VRAM_CHUNK(E, vram_offset, w) |= ((ptn->planes.E[y] >> q.x) & mask);

void ptn_unput_8(screen_x_t left, vram_y_t top, int ptn_id)
{
	ptn_plane_t::row_dots_t mask = 0;
	uvram_offset_t vram_offset = vram_offset_shift(left, top);
	ptn_t *ptn = ptn_with_id_shift(ptn_id);

	for(upixel_t y = 0; y < PTN_H; y++) {
		mask = ptn->alpha[y];
		graph_accesspage_func(0);
		if(mask) {
			Planar<ptn_plane_t::row_dots_t> page1;

			vram_erase(vram_offset, mask, PTN_W);

			graph_accesspage_func(1);
			vram_snap_planar_masked(page1, vram_offset, PTN_W, mask);

			graph_accesspage_func(0);
			vram_or_planar(vram_offset, page1, PTN_W);
		}
		vram_offset += ROW_SIZE;
		if(vram_offset > PLANE_SIZE) {
			break;
		}
	}
}

void ptn_put_8(screen_x_t left, vram_y_t top, int ptn_id)
{
	upixel_t y;
	dots_t(PTN_W) mask = 0;
	uvram_offset_t vram_offset = vram_offset_shift(left, top);
	ptn_t *ptn = ptn_with_id_shift(ptn_id);

	if(ptn_sloppy_unput_before_alpha_put) {
		ptn_sloppy_unput_16(left, top);
	}
	for(y = 0; y < PTN_H; y++) {
		mask = ptn->alpha[y];
		if(mask) {
			vram_erase(vram_offset, mask, PTN_W);
			ptn_or_masked(vram_offset, PTN_W, ptn, mask);
		}
		vram_offset += ROW_SIZE;
		if(vram_offset > PLANE_SIZE) {
			break;
		}
	}
}

void ptn_unput_quarter_8(
	screen_x_t left, vram_y_t top, int ptn_id, int quarter
)
{
	sdots_t(PTN_QUARTER_W) mask;
	upixel_t y;
	PTNQuarter q;
	Planar<dots_t(PTN_QUARTER_W)> page1;
	sdots_t(PTN_W) mask_full = 0;
	vram_offset_t vram_offset = vram_offset_shift(left, top);
	ptn_t *ptn = ptn_with_id_shift(ptn_id);

	q.init(quarter);
	for(y = q.y; y < (q.y + PTN_QUARTER_H); y++) {
		mask_full = ptn->alpha[y];

		graph_accesspage_func(0);

		mask = (mask_full >> q.x);
		if(mask) {
			vram_erase(vram_offset, mask, PTN_QUARTER_W);
			graph_accesspage_func(1);
			vram_snap_planar_masked(page1, vram_offset, PTN_QUARTER_W, mask);
			graph_accesspage_func(0);
			vram_or_planar(vram_offset, page1, PTN_QUARTER_W);
		}
		vram_offset += ROW_SIZE;
		// No vram_offset bounds check here?!
	}
}

void ptn_put_quarter_8(screen_x_t left, vram_y_t top, int ptn_id, int quarter)
{
	sdots_t(PTN_QUARTER_W) mask;
	upixel_t y;
	PTNQuarter q;
	sdots_t(PTN_W) mask_full = 0;
	vram_offset_t vram_offset = vram_offset_shift(left, top);
	ptn_t *ptn = ptn_with_id_shift(ptn_id);

	q.init(quarter);
	if(ptn_sloppy_unput_before_alpha_put) {
		ptn_sloppy_unput_quarter_16(left, top);
	}
	for(y = q.y; y < (q.y + PTN_QUARTER_H); y++) {
		mask_full = ptn->alpha[y];
		mask = (mask_full >> q.x);
		if(mask) {
			vram_erase(vram_offset, mask, PTN_QUARTER_W);
			ptn_or_quarter_masked(vram_offset, PTN_QUARTER_W, ptn, q, mask);
		}
		vram_offset += ROW_SIZE;
		// No vram_offset bounds check here?!
	}
}

void ptn_put_quarter(screen_x_t left, vram_y_t top, int ptn_id, int quarter)
{
	union dots16_unaligned_t {
		dots8_t d8[3];
		dots32_t d32;

		void set(const dots16_t& dots, const char& first_bit) {
			d8[0] = ((dots & 0xFF) >> first_bit);
			d8[1] = (
				((dots & 0xFF) << (BYTE_DOTS - first_bit)) |
				((dots & 0xFF00) >> (BYTE_DOTS + first_bit))
			);
			d8[2] = ((dots & 0xFF00) >> first_bit);
		}

		void set(
			const dots16_t& dots,
			const char& first_bit,
			const dots16_unaligned_t& mask
		) {
			d8[0] = (((dots & 0xFF) >> first_bit) & mask.d8[0]);
			d8[1] = ((
				((dots & 0xFF) << (BYTE_DOTS - first_bit)) |
				((dots & 0xFF00) >> (BYTE_DOTS + first_bit))
			) & mask.d8[1]);
			d8[2] = (((dots & 0xFF00) >> first_bit) & mask.d8[2]);
		}
	};

	static dots16_unaligned_t ptnpq_mask_unaligned_zero = { 0x000000 };
	static dots16_unaligned_t ptnpq_dots_unaligned_zero = { 0x000000 };
	static Planar<dots8_t *> ptnpq_vram = { nullptr };

	unsigned int plane;
	upixel_t y;
	dots_t(PTN_QUARTER_W) mask;
	PTNQuarter q;
	char first_bit = (left % BYTE_DOTS);
	dots16_unaligned_t mask_unaligned = ptnpq_mask_unaligned_zero;
	dots16_unaligned_t dots_unaligned = ptnpq_dots_unaligned_zero;
	Planar<dots_t(PTN_QUARTER_W)> sprite;
	dots_t(PTN_QUARTER_W) dots;

	uvram_offset_t vram_offset = vram_offset_shift(left, top);
	ptn_t *ptn = ptn_with_id_shift(ptn_id);

	ptnpq_vram.B = VRAM_PLANE_B;
	ptnpq_vram.R = VRAM_PLANE_R;
	ptnpq_vram.G = VRAM_PLANE_G;
	ptnpq_vram.E = VRAM_PLANE_E;

	Planar<dots8_t *> vram_local = ptnpq_vram;

	// MODDERS: Yes, should have been || rather than &&...
	if((left < 0) && (left > (RES_X - PTN_QUARTER_W))) {
		return;
	}
	q.init(quarter);
	for(y = q.y; y < (q.y + PTN_QUARTER_H); y++) {
		for(plane = 0; plane < PLANE_COUNT; plane++) {
			sprite[plane] = (ptn->planes[plane][y] >> q.x);
		}
		mask = ptn_alpha_from(sprite.B, sprite.R, sprite.G, sprite.E);

		if(first_bit == 0) {
			if(mask != 0) {
				#define w PTN_QUARTER_W
				vram_erase(vram_offset, mask, w);
				vram_or_masked_emptyopt(B, vram_offset, w, sprite.B, mask);
				vram_or_masked_emptyopt(R, vram_offset, w, sprite.R, mask);
				vram_or_masked_emptyopt(G, vram_offset, w, sprite.G, mask);
				vram_or_masked_emptyopt(E, vram_offset, w, sprite.E, mask);
				#undef w
			}
		} else {
			if(mask != 0) {
				mask_unaligned.set(mask, first_bit);
				vram_erase(vram_offset, mask_unaligned.d32, 32);
				for(plane = 0; plane < PLANE_COUNT; plane++) {
					dots = sprite[plane];
					if(dots) {
						dots_unaligned.set(dots, first_bit, mask_unaligned);
						*reinterpret_cast<dots32_t far *>(
							vram_local[plane] + vram_offset
						) |= dots_unaligned.d32;
					}
				}
			}
		}
		vram_offset += ROW_SIZE;
		if(vram_offset > PLANE_SIZE) {
			break;
		}
	}
}

#include "th01/hardware/graph.h"
#include "th01/hardware/egc.h"
#include "th01/formats/ptn.hpp"

static inline ptn_t* ptn_with_id_shift(int id)
{
	// Before we bother with doing compile-time integer logarithms...
	// (MODDERS: This function shouldn't exist. Just use the regular
	// ptn_with_id().)
	if(PTN_IMAGES_PER_SLOT == 64) {
		return &ptn_images[id >> 6][id % PTN_IMAGES_PER_SLOT];
	}
	return &ptn_images[id / PTN_IMAGES_PER_SLOT][id % PTN_IMAGES_PER_SLOT];
}

#define grcg_clear_masked(vram_offset, w, mask) \
	grcg_setcolor_rmw(0); \
	VRAM_PUT(B, vram_offset, mask, w); \
	grcg_off();

#define vram_snap_masked(planar_dots, vram_offset, w, mask) \
	planar_dots.B = VRAM_CHUNK(B, vram_offset, w) & mask; \
	planar_dots.R = VRAM_CHUNK(R, vram_offset, w) & mask; \
	planar_dots.G = VRAM_CHUNK(G, vram_offset, w) & mask; \
	planar_dots.E = VRAM_CHUNK(E, vram_offset, w) & mask;

#define vram_or(vram_offset, w, planar) \
	VRAM_CHUNK(B, vram_offset, w) |= planar.B; \
	VRAM_CHUNK(R, vram_offset, w) |= planar.R; \
	VRAM_CHUNK(G, vram_offset, w) |= planar.G; \
	VRAM_CHUNK(E, vram_offset, w) |= planar.E;

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

#define or_masked(plane, offset, w, dots, mask) \
	if(dots) { \
		VRAM_CHUNK(plane, offset, w) |= (dots & mask); \
	}

void ptn_unput_8(int left, int top, int ptn_id)
{
	ptn_dots_t mask = 0;
	uint16_t vram_offset = vram_offset_shift(left, top);
	ptn_t *ptn = ptn_with_id_shift(ptn_id);

	for(unsigned int y = 0; y < PTN_H; y++) {
		mask = ptn->alpha[y];
		graph_accesspage_func(0);
		if(mask) {
			planar_t(PTN_W) page1;

			grcg_clear_masked(vram_offset, PTN_W, mask);

			graph_accesspage_func(1);
			vram_snap_masked(page1, vram_offset, PTN_W, mask);

			graph_accesspage_func(0);
			vram_or(vram_offset, PTN_W, page1);
		}
		vram_offset += ROW_SIZE;
		if(vram_offset > PLANE_SIZE) {
			break;
		}
	}
}

void ptn_put_8(int left, int top, int ptn_id)
{
	unsigned int y;
	dots_t(PTN_W) mask = 0;
	uint16_t vram_offset = vram_offset_shift(left, top);
	ptn_t *ptn = ptn_with_id_shift(ptn_id);

	if(ptn_unput_before_alpha_put) {
		egc_copy_rect_1_to_0(left, top, PTN_W, PTN_H);
	}
	for(y = 0; y < PTN_H; y++) {
		mask = ptn->alpha[y];
		if(mask) {
			grcg_clear_masked(vram_offset, PTN_W, mask);
			ptn_or_masked(vram_offset, PTN_W, ptn, mask);
		}
		vram_offset += ROW_SIZE;
		if(vram_offset > PLANE_SIZE) {
			break;
		}
	}
}

void ptn_unput_quarter_8(int left, int top, int ptn_id, int quarter)
{
	sdots_t(PTN_QUARTER_W) mask;
	unsigned int y;
	PTNQuarter q;
	planar_t(PTN_QUARTER_W) page1;
	sdots_t(PTN_W) mask_full = 0;
	uint16_t vram_offset = vram_offset_shift(left, top);
	ptn_t *ptn = ptn_with_id_shift(ptn_id);

	q.init(quarter);
	for(y = q.y; y < (q.y + PTN_QUARTER_H); y++) {
		mask_full = ptn->alpha[y];

		graph_accesspage_func(0);

		mask = (mask_full >> q.x);
		if(mask) {
			grcg_clear_masked(vram_offset, PTN_QUARTER_W, mask);
			graph_accesspage_func(1);
			vram_snap_masked(page1, vram_offset, PTN_QUARTER_W, mask);
			graph_accesspage_func(0);
			vram_or(vram_offset, PTN_QUARTER_W, page1);
		}
		vram_offset += ROW_SIZE;
		// No vram_offset bounds check here?!
	}
}

void ptn_put_quarter_8(int left, int top, int ptn_id, int quarter)
{
	sdots_t(PTN_QUARTER_W) mask;
	unsigned int y;
	PTNQuarter q;
	sdots_t(PTN_W) mask_full = 0;
	uint16_t vram_offset = vram_offset_shift(left, top);
	ptn_t *ptn = ptn_with_id_shift(ptn_id);

	q.init(quarter);
	if(ptn_unput_before_alpha_put) {
		egc_copy_rect_1_to_0(left, top, PTN_QUARTER_W, PTN_QUARTER_H);
	}
	for(y = q.y; y < (q.y + PTN_QUARTER_H); y++) {
		mask_full = ptn->alpha[y];
		mask = (mask_full >> q.x);
		if(mask) {
			grcg_clear_masked(vram_offset, PTN_QUARTER_W, mask);
			ptn_or_quarter_masked(vram_offset, PTN_QUARTER_W, ptn, q, mask);
		}
		vram_offset += ROW_SIZE;
		// No vram_offset bounds check here?!
	}
}

void ptn_put_quarter(int left, int top, int ptn_id, int quarter)
{
	union dots16_unaligned_t {
		dots8_t d8[3];
		dots32_t d32;

		void set(const dots16_t& dots, const char& first_bit) {
			d8[0] = ((dots & 0xFF) >> first_bit);
			d8[1] = (
				((dots & 0xFF) << (8 - first_bit)) |
				((dots & 0xFF00) >> (8 + first_bit))
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
				((dots & 0xFF) << (8 - first_bit)) |
				((dots & 0xFF00) >> (8 + first_bit))
			) & mask.d8[1]);
			d8[2] = (((dots & 0xFF00) >> first_bit) & mask.d8[2]);
		}
	};

	struct vram_planes_t {
		dots8_t *P[PL_COUNT];
	};

	extern vram_planes_t ptnpq_vram;
	extern dots16_unaligned_t ptnpq_mask_unaligned_zero;
	extern dots16_unaligned_t ptnpq_dots_unaligned_zero;

	unsigned int plane;
	unsigned int y;
	dots_t(PTN_QUARTER_W) mask;
	PTNQuarter q;
	char first_bit = (left % 8);
	dots16_unaligned_t mask_unaligned = ptnpq_mask_unaligned_zero;
	dots16_unaligned_t dots_unaligned = ptnpq_dots_unaligned_zero;
	dots_t(PTN_QUARTER_W) sprite[PL_COUNT];
	dots_t(PTN_QUARTER_W) dots;

	uint16_t vram_offset = vram_offset_shift(left, top);
	ptn_t *ptn = ptn_with_id_shift(ptn_id);

	ptnpq_vram.P[PL_B] = VRAM_PLANE_B;
	ptnpq_vram.P[PL_R] = VRAM_PLANE_R;
	ptnpq_vram.P[PL_G] = VRAM_PLANE_G;
	ptnpq_vram.P[PL_E] = VRAM_PLANE_E;

	vram_planes_t vram_local = ptnpq_vram;

	// MODDERS: Yes, should have been || rather than &&...
	if((left < 0) && (left > (RES_X - PTN_QUARTER_W))) {
		return;
	}
	q.init(quarter);
	for(y = q.y; y < (q.y + PTN_QUARTER_H); y++) {
		for(plane = 0; plane < PL_COUNT; plane++) {
			sprite[plane] = (ptn->P[plane][y] >> q.x);
		}
		mask = ptn_alpha_from(sprite[0], sprite[1], sprite[2], sprite[3]);

		if(first_bit == 0) {
			if(mask != 0) {
				grcg_clear_masked(vram_offset, PTN_QUARTER_W, mask);
				or_masked(B, vram_offset, PTN_QUARTER_W, sprite[0], mask);
				or_masked(R, vram_offset, PTN_QUARTER_W, sprite[1], mask);
				or_masked(G, vram_offset, PTN_QUARTER_W, sprite[2], mask);
				or_masked(E, vram_offset, PTN_QUARTER_W, sprite[3], mask);
			}
		} else {
			if(mask != 0) {
				mask_unaligned.set(mask, first_bit);
				grcg_clear_masked(vram_offset, 32, mask_unaligned.d32);
				for(plane = 0; plane < PL_COUNT; plane++) {
					dots = sprite[plane];
					if(dots) {
						dots_unaligned.set(dots, first_bit, mask_unaligned);
						*reinterpret_cast<dots32_t far *>(
							vram_local.P[plane] + vram_offset
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

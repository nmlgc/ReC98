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

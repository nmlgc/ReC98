extern "C" {
#include "th01/formats/ptn.hpp"

void ptn_snap_8(screen_x_t left, vram_y_t top, int ptn_id)
{
	vram_offset_t vram_offset = vram_offset_muldiv(left, top);
	ptn_t *ptn = ptn_with_id(ptn_id);
	for(pixel_t y = 0; y < PTN_H; y++) {
		vram_snap_ptn_planar(ptn, vram_offset);
		vram_offset += ROW_SIZE;
	}
}

static inline ptn_plane_t::row_dots_t dot_mask(pixel_t x, pixel_t w)
{
	return static_cast<ptn_plane_t::row_dots_t>((1u << w) - 1u) << (w - x);
}

void ptn_snap_quarter_8(
	screen_x_t left, vram_y_t top, int ptn_id, int quarter
)
{
	pixel_t y;
	vram_offset_t vram_offset = vram_offset_muldiv(left, top);
	pixel_t q_y;
	ptn_plane_t::row_dots_t q_mask;
	long q_x;
	ptn_t *ptn = ptn_with_id(ptn_id);

	q_y = ptn_quarter_y(quarter);
	q_mask = (quarter & 1)
		? dot_mask(PTN_QUARTER_W, PTN_QUARTER_W)
		: dot_mask(            0, PTN_QUARTER_W);
	q_x = ptn_quarter_x(quarter);

	for(y = q_y; y < (q_y + PTN_QUARTER_H); y++) {
		#define snap_quarter_plane(P, offset, w) \
			ptn->planes.P[y] &= q_mask; \
			ptn->planes.P[y] |= (VRAM_CHUNK(P, offset, w) << q_x) & ~q_mask;

		#define snap_quarter(offset, w) \
			snap_quarter_plane(B, offset, w); \
			snap_quarter_plane(R, offset, w); \
			snap_quarter_plane(G, offset, w); \
			snap_quarter_plane(E, offset, w);

		snap_quarter(vram_offset, PTN_W);

		#undef snap_quarter
		#undef snap_quarter_plane
		vram_offset += ROW_SIZE;
	}
}

}

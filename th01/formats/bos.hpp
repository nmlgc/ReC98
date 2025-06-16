/// Uncompressed, 5-plane, 16-color + alpha, arbitrary-size sprite format
/// ---------------------------------------------------------------------

#include "th01/formats/sprfmt_h.hpp"
#include "th01/formats/pf.hpp"
#include "th01/hardware/graph.h"

#define BOS_MAGIC "BOSS"

// On-disk per-file header. Not the same as for .GRC!
struct bos_header_t {
	char magic[sizeof(BOS_MAGIC) - 1];
	uint8_t vram_w;
	int8_t zero;
	uint8_t h;
	int8_t unknown;
	spriteformat_header_inner_t inner;
};

// In-game bitplane slot structure
struct bos_image_t {
	Planar<dots8_t *> planes;
	dots8_t *alpha;
};

// Shared loading subfunctions
// ---------------------------

// Separate function to work around the `Condition is always true/false` and
// `Unreachable code` warnings
inline void bos_header_load_palette(Palette4 &pal, bool load) {
	if(load) {
		arc_file_get_far(pal);
	} else {
		arc_file_seek(sizeof(SpriteFormatHeader<bos_header_t>));
	}
}

#define bos_header_load(that, plane_size, fn, needlessly_load_the_palette) \
	union { \
		bos_header_t outer; \
		Palette4 pal; \
		int8_t space[50]; \
	} header; \
	\
	arc_file_load(fn); \
	\
	arc_file_get_far(header.outer); \
	that->vram_w = header.outer.vram_w; \
	that->h = header.outer.h; \
	that->bos_image_count = header.outer.inner.image_count; \
	plane_size = (that->vram_w * that->h); \
	bos_header_load_palette(header.pal, needlessly_load_the_palette);
// ---------------------------

/// Shared blitting subfunctions
/// ----------------------------

// Part of ZUN's attempt at clipping at the left or right edges of VRAM, by
// comparing [vram_offset] against the value returned from this function.
inline vram_y_t vram_intended_y_for(
	vram_offset_t vram_offset, screen_x_t first_x
) {
	return (first_x < 0)
		? ((vram_offset / ROW_SIZE) + 1)
		: ((vram_offset / ROW_SIZE) + 0);
}

#define vram_offset_at_intended_y_16(vram_offset, intended_y) \
	(((vram_offset + 0) / ROW_SIZE) == intended_y) && \
	(((vram_offset + 1) / ROW_SIZE) == intended_y)

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
/// ----------------------------

/// All functions that operate on this format are implemented redundantly for
/// both CBossEntity, CBossAnim, and CPlayerAnim with their own respective
/// entity arrays.
/// ---------------------------------------------------------------------

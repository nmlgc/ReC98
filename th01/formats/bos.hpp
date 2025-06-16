/// Uncompressed, 5-plane, 16-color + alpha, arbitrary-size sprite format
/// ---------------------------------------------------------------------

#ifndef TH01_FORMATS_BOS_HPP
#define TH01_FORMATS_BOS_HPP

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

// In-game metadata structure
struct BOS {
	uvram_byte_amount_8_t vram_w;
	uint8_t bos_image_count;
	pixel_t h;

	// Loads a .BOS file into the given image slot array. Returns the size of a
	// single bitplane.
	vram_byte_amount_t load(bos_image_t *image_first, const char fn[PF_FN_LEN]);
};

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
	page_access(1); \
	VRAM_SNAP(tmp_dots, plane, offset, bit_count); \
	if(tmp_dots) { \
		page_access(0); \
		VRAM_CHUNK(plane, offset, bit_count) |= (mask & tmp_dots); \
	}

#define vram_unput_masked_emptyopt_planar(offset, bit_count, mask, tmp_dots) \
	vram_unput_masked_emptyopt(B, offset, bit_count, mask, tmp_dots); \
	vram_unput_masked_emptyopt(R, offset, bit_count, mask, tmp_dots); \
	vram_unput_masked_emptyopt(G, offset, bit_count, mask, tmp_dots); \
	vram_unput_masked_emptyopt(E, offset, bit_count, mask, tmp_dots);
/// ----------------------------

#endif /* TH01_FORMATS_BOS_HPP */

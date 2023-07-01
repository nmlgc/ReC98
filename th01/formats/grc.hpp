/// Uncompressed monochrome 8w×h sprite format
/// ------------------------------------------
#include "th01/formats/sprfmt_h.hpp"
#include "th01/sprites/main_grc.h"

#define GRC_MAGIC "GRCG"

// On-disk per-file header. Not the same as for .BOS!
struct grc_header_t {
	char magic[sizeof(GRC_MAGIC) - 1];
	int16_t vram_w;
	int16_t h;
	spriteformat_header_inner_t inner;
};

static const int GRC_IMAGES_PER_SLOT = 8;

// In-memory slot structure
struct grc_t {
	vram_byte_amount_t vram_w;
	pixel_t h;
	int image_count;
	dots8_t* dots[GRC_IMAGES_PER_SLOT];
};

// Loads all images from the .GRC file with the given [fn] inside the
// currently active packfile into the given .GRC [slot]. Always returns 0.
int grc_load(main_grc_slot_t slot, const char fn[PF_FN_LEN]);

// Frees all images in the given [slot].
void grc_free(main_grc_slot_t slot);

// Blits the sub[image] from the given [slot] to (⌊left/8⌋*8, top) with the
// given [col]. Correctly clips the sprite at all 4 edges of VRAM.
void grc_put_8(
	screen_x_t left, vram_y_t top, main_grc_slot_t slot, int image, vc2 col
);

// For some reason, all code assumes .GRC entities to be 48×32, rather than
// 32×32. Why?!
#define grc_sloppy_unput(left, top) \
	egc_copy_rect_1_to_0_16(left, top, 48, 32);
/// ------------------------------------------

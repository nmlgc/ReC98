/// Uncompressed monochrome 8w×h sprite format
/// ------------------------------------------
#include "th01/formats/sprfmt_h.hpp"

#define GRC_MAGIC "GRCG"

// On-disk per-file header. Not the same as for .BOS!
struct grc_header_t {
	char magic[sizeof(GRC_MAGIC) - 1];
	int16_t vram_w;
	int16_t h;
	spriteformat_header_inner_t inner;
};

static const int GRC_SLOT_COUNT = 8;
static const int GRC_IMAGES_PER_SLOT = 8;

// In-memory slot structure
struct grc_t {
	int vram_w;
	int h;
	int image_count;
	dots8_t* dots[GRC_IMAGES_PER_SLOT];
};

extern grc_t grc_images[GRC_SLOT_COUNT];

// Loads all images from the .GRC file with the given [fn] inside the
// currently active packfile into the given .GRC [slot]. Always returns 0.
int grc_load(int slot, const char fn[PF_FN_LEN]);

// Frees all images in the given [slot].
void grc_free(int slot);

// Blits the sub[image] from the given [slot] to (⌊left/8⌋*8, top) with the
// given [col]. Correctly clips the sprite at all 4 edges of VRAM.
void grc_put_8(screen_x_t left, vram_y_t top, int slot, int image, int col);
/// ------------------------------------------

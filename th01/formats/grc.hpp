/// Uncompressed monochrome 8w×h sprite format
/// ------------------------------------------
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
/// ------------------------------------------

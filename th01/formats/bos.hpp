/// Uncompressed, 5-plane, 16-color + alpha, arbitrary-size sprite format
/// ---------------------------------------------------------------------
#define BOS_MAGIC "BOSS"

// On-disk per-file header. Not the same as for .GRC!
struct bos_header_t {
	char magic[sizeof(BOS_MAGIC) - 1];

	// Yes, this means that the *format* itself isn't actually restricted to
	// word-aligned / 16w×h sizes, …
	uint8_t vram_w;

	int8_t zero;
	uint8_t h;
	int8_t unknown;
	spriteformat_header_inner_t inner;
};

#define BOS_IMAGES_PER_SLOT 8

// In-memory slot structures
struct bos_image_t {
	// … as these types would suggest. That's purely an implementation choice.
	Planar<dots16_t *> planes;
	dots16_t *alpha;
};

struct bos_t {
	bos_image_t image[BOS_IMAGES_PER_SLOT];
};

/// All functions that operate on this format are implemented redundantly for
/// both CBossEntity and CBossAnim, with their own respective entity arrays.
/// ---------------------------------------------------------------------

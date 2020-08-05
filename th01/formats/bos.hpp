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

// Regular
// -------
#define BOS_SLOT_COUNT 4
extern bos_t bos_images[BOS_SLOT_COUNT];

// Frees all images in the given [slot].
void bos_free(int slot);
// -------

// Fast
// ----
// These… only have functions for direct byte-aligned blitting onto page 0, in
// exchange for the alpha plane being pre-negated at load time? No idea why.
// That 1-instruction negation is certainly not what makes the original code
// slow.
#define BOS_FAST_SLOT_COUNT 2
extern bos_t bos_fast_images[BOS_FAST_SLOT_COUNT];
// ----

/// The remaining functions that operate on this format are implemented as
/// methods of CBossEntity.
/// ---------------------------------------------------------------------

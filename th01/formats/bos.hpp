/// Uncompressed 16-color 16w×h sprite format
/// -----------------------------------------
#define BOS_IMAGES_PER_SLOT 8

struct bos_image_t {
	dots16_t *B;
	dots16_t *R;
	dots16_t *G;
	dots16_t *E;
	dots16_t *alpha;
};

struct bos_t {
	bos_image_t image[BOS_IMAGES_PER_SLOT];
};

// Regular
// -------
#define BOS_SLOT_COUNT 4
extern bos_t bos_images[BOS_SLOT_COUNT];
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
/// -----------------------------------------

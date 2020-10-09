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

// Shared loading and freeing subfunctions
// ---------------------------------------

// Separate function to work around the `Condition is always true/false` and
// `Unreachable code` warnings
inline void bos_header_load_palette(Palette4 &pal, bool load) {
	if(load) {
		arc_file_get_far(pal);
	} else {
		arc_file_seek(sizeof(spriteformat_header_t<bos_header_t>));
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

#define bos_image_new(image, plane_size) \
	image.alpha = new dots16_t[plane_size / 2]; \
	image.planes.B = new dots16_t[plane_size / 2]; \
	image.planes.R = new dots16_t[plane_size / 2]; \
	image.planes.G = new dots16_t[plane_size / 2]; \
	image.planes.E = new dots16_t[plane_size / 2];

// Always setting the pointer to NULL, for a change...
#define bos_image_ptr_free(ptr) \
	if(ptr) { \
		delete[] ptr; \
	} \
	ptr = NULL;

#define bos_free(slot_ptr) \
	for(int image = 0; image < BOS_IMAGES_PER_SLOT; image++) { \
		bos_image_ptr_free(slot_ptr.image[image].alpha); \
		bos_image_ptr_free(slot_ptr.image[image].planes.B); \
		bos_image_ptr_free(slot_ptr.image[image].planes.R); \
		bos_image_ptr_free(slot_ptr.image[image].planes.G); \
		bos_image_ptr_free(slot_ptr.image[image].planes.E); \
	}
// ---------------------------------------

/// All functions that operate on this format are implemented redundantly for
/// both CBossEntity, CBossAnim, and CPlayerAnim with their own respective
/// entity arrays.
/// ---------------------------------------------------------------------

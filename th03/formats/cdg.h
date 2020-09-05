/// Uncompressed, monochrome / 16-color / 16-color + alpha, 32w×h sprite format
/// ---------------------------------------------------------------------------

// Number of planes per image.
typedef enum {
	#if (GAME >= 4)
		CDG_COLORS = 0,          	// 4 planes per image
		CDG_COLORS_AND_ALPHA = 1,	// 5 planes per image
		CDG_ALPHA = 2,           	// 1 plane per image
	#else
		CDG_COLORS_AND_ALPHA = 0,	// 5 planes per image
	#endif
} cdg_plane_layout_t;

// Doubles as both the file format header (describing all images in a file)
// and the internal slot structure (describing a single image).
typedef struct {
	// Size of a single bitplane.
	uint16_t bitplane_size;

	// Only used by custom functions that apply effects on the image. The core
	// CDG functions mainly use the two pre-calculated values
	// [offset_at_bottom_left] and [vram_dword_w] instead.
	int16_t pixel_w;
	int16_t pixel_h;

	// vram_byte_amount_t, equal to (ROW_SIZE * ([pixel_h - 1])).
	int16_t offset_at_bottom_left;

	// vram_dword_amount_t, equal to [pixel_w / 32].
	uint16_t vram_dword_w;

	// In TH03, this can also be 0 for single-image files.
	uint8_t image_count;

	// See cdg_plane_layout_t.
	int8_t plane_layout;

	// Memory segments of the loaded data. Must be 0 in the file header!
	uint16_t seg_alpha;
	uint16_t seg_colors;
} cdg_t;

#if (GAME >= 4)
	static const int CDG_SLOT_COUNT = 64;
#else
	static const int CDG_SLOT_COUNT = 32;
#endif

extern cdg_t cdg_slots[CDG_SLOT_COUNT];

void pascal cdg_load_all_noalpha(int slot_first, const char *fn);
/// ---------------------------------------------------------------------------

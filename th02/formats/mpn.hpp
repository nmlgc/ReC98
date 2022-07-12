/// Uncompressed 16-color 16×16 image format with palette, used for map tiles
/// -------------------------------------------------------------------------

typedef dot_rect_t(TILE_W, TILE_H) mpn_plane_t;
typedef Planar<mpn_plane_t> mpn_image_t;

typedef struct {
	char magic[4]; // = "MPTN"
	uint8_t count;
	int8_t unused;
} mpn_header_t;

#if (GAME == 2)
	extern uint8_t mpn_count;
	extern mpn_image_t *mpn_images;
	extern Palette8 mpn_palette;

	// Reads the .MPN file with the given [fn] into the newly reallocated
	// [mpn_images], and sets [mpn_count] and [mpn_palette] accordingly.
	// Returns 0 if allocation succeeded and the tiles were read into
	// [mpn_images], -1 otherwise.
	int pascal mpn_load(const char *fn);

	// Like mpn_load(), but sets the hardware palette to the one in [fn]'s
	// header.
	int pascal mpn_load_palette_show(const char *fn);

	void mpn_free(void);
#endif
/// -------------------------------------------------------------------------

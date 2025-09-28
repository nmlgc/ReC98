/// Uncompressed 16-color 16×16 image format with palette, used for map tiles
/// -------------------------------------------------------------------------
extern "C" {

#include "th02/formats/tile.hpp"
#include "libs/master.lib/pc98_gfx.hpp"
#include "planar.h"

typedef dot_rect_t(TILE_W, TILE_H) mpn_plane_t;
typedef Planar<mpn_plane_t> mpn_image_t;

struct mpn_header_t {
	char magic[4]; // = "MPTN"

	// Stored minus 1. (Probably because MIKO_K.MPN contains 256 tiles and ZUN
	// absolutely wanted to store this value in a single byte regardless.)
	uint8_t count;

	int8_t unused;
};

#if (GAME == 2)
extern uint8_t mpn_count;  // Stored minus 1.
extern mpn_image_t *mpn_images;
extern Palette8 mpn_palette;

// Reads the .MPN file with the given [fn] into the newly reallocated
// [mpn_images], and sets [mpn_count] and [mpn_palette] accordingly.
// Returns 0 if allocation succeeded and the tiles were read into [mpn_images],
// -1 otherwise.
int pascal mpn_load(const char *fn);

// Like mpn_load(), but sets the hardware palette to the one in [fn]'s header.
int pascal mpn_load_palette_show(const char *fn);

// Blits the given [image] from the currently loaded .MPN to (⌊left/8⌋*8, top).
// ZUN landmine: Does not restrict [image] to ([mpn_count] + 1), which matters
// in conjunction with tile_area_init_and_put_both().
extern "C++" void pascal mpn_put_8(screen_x_t left, vram_y_t top, int image);

void mpn_free(void);
#endif
}
/// -------------------------------------------------------------------------

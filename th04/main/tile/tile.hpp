#include "th02/main/tile/tile.hpp"
#include "th01/math/subpixel.hpp"

static const int TILE_ROWS_PER_SECTION = 5;

// An absolutely pointless lookup table mapping tile section IDs to offsets in
// [map_seg], which, through its very existence, pointlessly limits the amount
// of tile sections contained in a .MAP file.
static const int TILE_SECTION_COUNT_MAX = 32;
extern const uint16_t TILE_SECTION_OFFSETS[TILE_SECTION_COUNT_MAX];

// TH04 starts addressing individual tiles directly via their 16-bit offset
// in VRAM.
extern vram_offset_t tile_ring[TILES_Y][TILES_MEMORY_X];

extern int8_t tile_row_in_section;

// Completely fills [tile_ring] with the initial screen of a stage, by loading
// the section IDs from [std_seg], and the tiles themselves from [map_seg].
void pascal near tiles_fill_initial(void);

// Blits all tiles in the ring buffer to the playfield in VRAM.
void pascal near tiles_render_all(void);

// Sets the [tile_ring] tile at (x, y) to the given VRAM offset.
void pascal tile_ring_set_vo(
	subpixel_t x, subpixel_t y, vram_offset_t image_vo
);

// Sets the [tile_ring] tile at (x, y) to the given tile_image_id_t.
#define tile_ring_set(x, y, id) ( \
	tile_ring_set_vo(x, y, tile_image_vo(id)) \
)

/// Redraw
/// ------

// Subdivides each 16×16 tile into two 16×8 halves and marks whether that half
// should be redrawn by the next call to tiles_redraw_invalidated() if its
// entry is nonzero.
extern bool halftiles_dirty[TILE_FLAGS_Y][TILES_MEMORY_X];

void near tiles_invalidate_reset(void);
void near tiles_invalidate_all(void);

// ---------------------------------------------------------------------------
// tiles_invalidate_around() marks all stage background tiles for redrawing
// that lie in the area covered by [tile_invalidate_box] around [center].
// Inconsistencies in the originally generated code revealed that ZUN must
// have used at least two different parameter lists for the same function. To
// use it, the respective prototype has to be declared separately in each
// translation unit, depending on the expected code generation:
//
// • Passing separate X and Y coordinates (including hardcoded constants
//   combined to form a single 32-bit immediate via the -3 compiler option):
//
//   extern "C" void pascal near tiles_invalidate_around(
//   	subpixel_t center_y, subpixel_t center_x
//   );
//
//   Use the tiles_invalidate_around_xy() macro declared below for a more
//   natural parameter order. (Yes, Borland/Turbo C++ only supports __stdcall
//   for Windows targets.)
//
// • Passing SPPoint instances:
//
//   extern "C" void pascal near tiles_invalidate_around(const SPPoint center);

#define tiles_invalidate_around_xy(center_x, center_y) \
	tiles_invalidate_around(center_y, center_x)

#define tiles_invalidate_around_vram_xy(center_x, center_y) \
	tiles_invalidate_around_xy(to_sp(center_x), to_sp(center_y))
// ---------------------------------------------------------------------------

// Width and height, in screen pixels, of a box around the center passed to
// tiles_invalidate_around(). *Not* the radius.
extern point_t tile_invalidate_box;

void pascal near tiles_redraw_invalidated(void);

// Invalidates all entity types, then redraws the invalidated tiles.
void pascal near tiles_render(void);

// Sets [bg_render_not_bombing] to [tiles_render].
void tiles_activate(void);

// Sets [bg_render_not_bombing] to a function that calls [tiles_render_all] for
// the next [n] frames, and then sets the function pointer back to
// [tiles_render]. With [n] = 2, this removes the remnants of in-game dialog
// graphics from both VRAM pages.
// This is only needed for TH04's post-boss dialog; it's also called for the
// pre-boss ones, but [bg_render_not_bombing] is immediately overwritten with
// the boss-specific background render function which does the same job via
// tiles_render_after_custom(). In TH05, the boss-specific functions remove the
// graphics of both the pre-boss and post-boss dialogs, and this function is
// unused.
void pascal tiles_activate_and_render_all_for_next_N_frames(uint8_t n);

// Used for switching back to a tiled background after rendering anything else,
// like in-game dialog, or a custom background. Makes sure to first render all
// tiles to both VRAM pages, then performs regular redrawing of only the
// invalidated tiles.
inline void tiles_render_after_custom(const int& frame) {
	if(frame <= 2) {
		tiles_render_all();
	} else {
		tiles_render();
	}
}
/// ------

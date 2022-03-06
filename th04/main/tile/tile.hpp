#include "th02/main/tile/tile.hpp"

// No idea why ZUN just didn't go with the actually visible space of 384
// horizontal tiles. That's 8 wasted tiles per row that the game doesn't do
// anything with?
#define TILES_MEMORY_X (512 / TILE_W)

static const int TILE_ROWS_PER_SECTION = 5;

// An absolutely pointless lookup table mapping tile section IDs to offsets in
// [map_seg], which, through its very existence, pointlessly limits the amount
// of tile sections contained in a .MAP file.
static const int TILE_SECTION_COUNT_MAX = 32;
extern const uint16_t TILE_SECTION_OFFSETS[TILE_SECTION_COUNT_MAX];

// TH04 starts addressing individual tiles directly via their 16-bit offset
// in the VRAM.
extern uint16_t tile_ring[TILES_Y][TILES_MEMORY_X];

// Completely fills [tile_ring] with the initial screen of a stage, by loading
// the section IDs from [std_seg], and the tiles themselves from [map_seg].
void pascal near tiles_fill_initial(void);

// Blits all tiles in the ring buffer to the playfield in VRAM.
void pascal near tiles_render_all(void);

/// Redraw
/// ------
// Subdivides each 16×16 tile into two 16×8 halves and marks whether that half
// should be redrawn by the next call to tiles_redraw_invalidated() if its
// entry is nonzero.
extern bool halftiles_dirty[TILE_FLAGS_Y][TILES_MEMORY_X];

void pascal near tiles_invalidate_reset(void);
void pascal near tiles_invalidate_all(void);

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

// Used for switching back to a tiled background after drawing a custom one.
inline void tiles_render_after_custom_bg(const int& phase_frame) {
	if(phase_frame <= 2) {
		tiles_render_all();
	} else {
		tiles_render();
	}
}
/// ------

#define TILE_W 16
#define TILE_H 16
#define TILE_VRAM_W (TILE_W / BYTE_DOTS)
#define TILES_Y (1 + (PLAYFIELD_H / TILE_H) + 1)
#define TILES_X (PLAYFIELD_W / TILE_W)

#define TILE_FLAG_H (TILE_H / 2)
#define TILE_FLAGS_Y (TILES_Y * (TILE_H / TILE_FLAG_H))

#define TILE_BITS_W 4
#define TILE_BITS_H 4

// Tile source area in VRAM
// ------------------------
// For fast EGC-accelerated blitting, the games blit all tiles to a reserved
// area in VRAM covered by black TRAM cells, starting to the right of the HUD
// at [TILE_AREA_LEFT] and stretching across the entire height of the screen.

static const int TILE_IMAGE_COUNT = 100;
static const int TILE_AREA_ROWS = (RES_Y / TILE_H);
static const int TILE_AREA_COLUMNS = (TILE_IMAGE_COUNT / TILE_AREA_ROWS);

static const screen_x_t TILE_AREA_LEFT = (RES_X - (TILE_AREA_COLUMNS * TILE_W));
static const screen_y_t TILE_AREA_TOP = 0;

static const vram_x_t TILE_AREA_VRAM_LEFT = (TILE_AREA_LEFT / BYTE_DOTS);

#if (GAME == 2)
	// Initializes internal tile area lookup tables, and blits all loaded .MPN
	// images to the tile area on both VRAM pages.
	void tile_area_init_and_put_both(void);

	// Sets the [tile_ring] tile at (left, y) to the given [image], then blits
	// it at (⌊left/8⌋*8, ⌊y/TILE_H⌋*TILE_H).
	// (This function would have been easier to describe if it only used [left]
	// to locate the tile and then blit it at its standard position, but it can
	// fact also blit a tile *between* two horizontal ones…)
	void pascal tile_ring_set_and_put_both_8(
		screen_x_t left, vram_y_t y, int image
	);

	// Blits the given tile [image] from its position in the source area to
	// (⌊left/8⌋*8, top), wrapping it vertically at the bottom of VRAM. Assumes
	// that the EGC is active and initialized for a copy.
	void pascal tile_egc_roll_copy_8(screen_x_t left, vram_y_t top, int image);
#endif
// ------------------------

// Column-major index of a tile within the tile source area.
typedef unsigned char tile_image_id_t;

#ifdef PLANAR_H
// Top-left VRAM offset of the tile with the given ID.
inline vram_offset_t tile_image_vo(int id) {
	return (
		(TILE_AREA_VRAM_LEFT + ((id / TILE_AREA_ROWS) * TILE_VRAM_W)) +
		(TILE_AREA_TOP + ((id % TILE_AREA_ROWS) * (TILE_H * ROW_SIZE)))
	);
}
#endif

#if (GAME == 2)
	enum tile_mode_t {
		// Fills all dirty tiles with hardware palette color 0.
		TM_COL_0 = 0,

		// Blits dirty tiles from the tile source area, according to the
		// [tile_ring]. The typical mode during a regular stage.
		TM_TILES = 1,

		// Disables tile rendering.
		TM_NONE = 2,

		_tile_mode_t_FORCE_UINT8 = 0xFF
	};

	extern tile_mode_t tile_mode;
	extern tile_image_id_t tile_ring[TILES_Y][TILES_X];

	// If `true`, the next call to tiles_egc_render() will unconditionally
	// redraw all tiles and then reset this flag to `false`.
	extern bool tiles_egc_render_all;

	// Resets a random bunch of data to its initial values at the beginning of
	// a stage.
	void tiles_stuff_reset(void);

	// Scrolls the map by [speed] pixels towards the top/end, updates the
	// [tile_ring] with any newly scrolled-in tile row, and blits the newly
	// scrolled-in tile lines from the tile source area to the playfield. Can
	// only blit lines from a single tile row, so the caller must ensure that
	// the passed [speed] values always end up exactly on a [TILE_H] boundary.
	// In addition, this also means that [speed] must be ≤[TILE_H].
	// Returns `true` if the top/end row of a map was reached.
	// Assumes the EGC to be active and initialized for a copy.
	bool16 pascal tiles_scroll_and_egc_render_both(pixel_t speed);

	// Fills [tile_ring] with the initial screen of tiles at the bottom/start
	// of the map, and blits them to the playfield area in VRAM. Reads tile
	// images from our data segment, the tile source area is neither read from
	// nor written to.
	void tiles_fill_and_put_initial(void);

	// Marks all tiles for redrawing that lie within the given area of the
	// screen.
	void pascal tiles_invalidate_rect(
		screen_x_t left, vram_y_t top, pixel_t w, pixel_t h
	);

	// Redraws the currently invalidated tiles according to the current
	// [tile_mode]. For TM_TILES, the EGC is assumed to be active and
	// initialized for a copy.
	void tiles_egc_render(void);

	// Blits all tiles in the [tile_ring] from the tile source area to the
	// playfield if [tile_mode] to TM_TILES. Fills the playfield with hardware
	// palette color 0 in all other modes.
	void tiles_render_all(void);
#endif

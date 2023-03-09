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

#if (GAME == 2)
	// Column-major index of a tile within the tile source area.
	typedef unsigned char tile_image_id_t;

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

	// Blits all tiles in the [tile_ring] from the tile source area to the
	// playfield if [tile_mode] to TM_TILES. Fills the playfield with hardware
	// palette color 0 in all other modes.
	void tiles_render_all(void);
#endif

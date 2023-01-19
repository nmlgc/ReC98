#define TILE_W 16
#define TILE_H 16
#define TILE_VRAM_W (TILE_W / BYTE_DOTS)
#define TILES_Y (1 + (PLAYFIELD_H / TILE_H) + 1)
#define TILES_X (PLAYFIELD_W / TILE_W)

#define TILE_FLAG_H (TILE_H / 2)
#define TILE_FLAGS_Y (TILES_Y * (TILE_H / TILE_FLAG_H))

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
// ------------------------

#if (GAME == 2)
	// Column-major index of a tile within the tile source area.
	typedef unsigned char tile_image_id_t;

	extern tile_image_id_t tile_ring[TILES_Y][TILES_X];
#endif

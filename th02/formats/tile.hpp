// Tile metrics
// ------------

#define TILE_W 16
#define TILE_H 16

// We *don't* define these in terms of the playfield width and height, for two
// reasons:
// 1) Having a file in /formats/ depend on a constant from /main/ breaks the
//    subsystem hierarchy.
// 2) It's definitely imaginable to mod playfield metrics independent of tile
//    counts or vice versa. In such a case, we shouldn't break compatibility
//    with the original data files by default.
#define TILES_X 24 // (PLAYFIELD_W / TILE_W)
#define TILES_Y 25 // (1 + (PLAYFIELD_H / TILE_H) + 1)

#define TILE_BITS_W 4
#define TILE_BITS_H 4

#if (GAME >= 4)
	// No idea why ZUN just didn't go with the actually visible space of 384
	// horizontal tiles. That's 8 wasted tiles per row that the game doesn't do
	// anything with?
	#define TILES_MEMORY_X (512 / TILE_W)
#endif

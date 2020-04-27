#define TILE_W 16
#define TILE_H 16
#define TILE_VRAM_W (TILE_W / 8)
#define TILES_Y (1 + (PLAYFIELD_H / TILE_H) + 1)
#define TILES_X (PLAYFIELD_W / TILE_W)

#define TILE_FLAG_H (TILE_H / 2)
#define TILE_FLAGS_Y (TILES_Y * (TILE_H / TILE_FLAG_H))

#if (GAME == 2)
	extern unsigned char tile_ring[TILES_Y][TILES_X];
#endif

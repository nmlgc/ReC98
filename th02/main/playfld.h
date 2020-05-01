#define PLAYFIELD_X (32)
#define PLAYFIELD_Y (16)
#define PLAYFIELD_W (384)
#define PLAYFIELD_H (368)

#define PLAYFIELD_LEFT (PLAYFIELD_X)
#define PLAYFIELD_TOP (PLAYFIELD_Y)
#define PLAYFIELD_RIGHT (PLAYFIELD_X + PLAYFIELD_W)
#define PLAYFIELD_BOTTOM (PLAYFIELD_Y + PLAYFIELD_H)

#define PLAYFIELD_VRAM_X (PLAYFIELD_X / 8)
#define PLAYFIELD_VRAM_W (PLAYFIELD_W / 8)
#define PLAYFIELD_VRAM_RIGHT (PLAYFIELD_RIGHT / 8)

#define PLAYFIELD_TRAM_X (PLAYFIELD_X / 8)
#define PLAYFIELD_TRAM_Y (PLAYFIELD_Y / 16)
#define PLAYFIELD_TRAM_W (PLAYFIELD_W / 8)
#define PLAYFIELD_TRAM_CENTER_X \
	((PLAYFIELD_X + (PLAYFIELD_W / 2)) / GLYPH_HALF_W)
#define PLAYFIELD_TRAM_RIGHT (PLAYFIELD_RIGHT / 8)
#define PLAYFIELD_TRAM_BOTTOM (PLAYFIELD_BOTTOM / 16)

#if (GAME == 2)
	// Fills the playfield's area on the text RAM with transparency.
	// (Future games use a near function.)
	void far playfield_tram_wipe(void);
#endif

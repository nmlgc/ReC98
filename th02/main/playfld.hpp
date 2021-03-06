#define PLAYFIELD_LEFT (32)
#define PLAYFIELD_TOP (16)
#define PLAYFIELD_W (384)
#define PLAYFIELD_H (368)

#define PLAYFIELD_RIGHT (PLAYFIELD_LEFT + PLAYFIELD_W)
#define PLAYFIELD_BOTTOM (PLAYFIELD_TOP + PLAYFIELD_H)

#define PLAYFIELD_VRAM_LEFT (PLAYFIELD_LEFT / BYTE_DOTS)
#define PLAYFIELD_VRAM_W (PLAYFIELD_W / BYTE_DOTS)
#define PLAYFIELD_VRAM_RIGHT (PLAYFIELD_RIGHT / BYTE_DOTS)

#define PLAYFIELD_TRAM_LEFT (PLAYFIELD_LEFT / 8)
#define PLAYFIELD_TRAM_TOP (PLAYFIELD_TOP / 16)
#define PLAYFIELD_TRAM_W (PLAYFIELD_W / 8)
#define PLAYFIELD_TRAM_CENTER_X \
	((PLAYFIELD_LEFT + (PLAYFIELD_W / 2)) / GLYPH_HALF_W)
#define PLAYFIELD_TRAM_RIGHT (PLAYFIELD_RIGHT / 8)
#define PLAYFIELD_TRAM_BOTTOM (PLAYFIELD_BOTTOM / 16)

#if (GAME == 2)
	// Fills the playfield's area on the text RAM with transparency.
	// (Future games use a near function.)
	void far playfield_tram_wipe(void);
#endif

#include "th01/main/playfld.hpp"

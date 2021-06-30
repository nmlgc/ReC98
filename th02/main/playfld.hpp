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

#define playfield_encloses(center_x, center_y, w, h) ( \
	(center_x > to_sp(0 - (w / 2))) && \
	(center_x < to_sp(PLAYFIELD_W + (w / 2))) && \
	(center_y > to_sp(0 - (h  / 2))) && \
	(center_y < to_sp(PLAYFIELD_H + (h / 2))) \
)

#define playfield_encloses_point(center, w, h) \
	playfield_encloses(center.x, center.y, w, h)

#ifdef SUBPIXEL_HPP
	typedef SPPoint PlayfieldPoint;
#endif

#include "th01/main/playfld.hpp"

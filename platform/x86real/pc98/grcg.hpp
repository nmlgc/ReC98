// C++ RAII GRCG implementation
// ----------------------------
// GRCG wrappers that automatically disable the GRCG if the object goes out of
// scope, and provide the optimal instructions for both dynamic and statically
// known tiles and colors.

#include "planar.h"
#include "x86real.h"

// Just in case master.hpp was included before...
#undef GC_OFF
#undef GC_TDW
#undef GC_TCR
#undef GC_RMW

enum grcg_mode_t {
	GC_OFF = 0x00,
	GC_TDW = 0x80,
	GC_TCR = 0x80,
	GC_RMW = 0xC0,
};

// TODO: Decide how to handle the collision with the master.lib GC_* flags,
// which use BRGI instead of BRGE.
typedef vc_t grcg_plane_mask_t;

// Builds the contents of a GRCG tile register from the x86 carry flag by
// extending its value to a full byte (CF=0 → 0x00, CF=1 → 0xFF).
inline dots8_t tile_register_from_carry(uint8_t unused)  {
	__emit__(0x1A, 0xC0); // SBB AL, AL
	return _AL;
}

// GRCG wrapper for tiles and colors decided at runtime.
struct GRCG {
	GRCG(grcg_mode_t mode, grcg_plane_mask_t plane_mask = 0) {
		_outportb_(0x7C, (mode | plane_mask));
	}

	void settile(
		const dots8_t& b, const dots8_t& r, const dots8_t& g, const dots8_t& e
	) {
		outportb(0x7E, b);
		outportb(0x7E, r);
		outportb(0x7E, g);
		outportb(0x7E, e);
	}

	void setcolor(vc_t col);

	~GRCG() {
		_outportb_(0x7C, GC_OFF);
	}
};

// Generates the optimal instructions for setting up the GRCG with a statically
// known tile.
template <
	int TileB, int TileR, int TileG, int TileE
> struct GRCGStaticTile : public GRCG {
	GRCGStaticTile(grcg_mode_t mode, grcg_plane_mask_t plane_mask = 0) :
		GRCG(mode, plane_mask) {
		outportb(0x7E, TileB);
		outportb(0x7E, TileR);
		outportb(0x7E, TileG);
		outportb(0x7E, TileE);
	}
};

// Generates the optimal instructions for setting up the GRCG with a statically
// known color.
template <vc_t Col> struct GRCGStaticColor : public GRCG {
	GRCGStaticColor(grcg_mode_t mode, grcg_plane_mask_t plane_mask = 0) :
		GRCG(mode, plane_mask) {
		outportb(0x7E, ((Col & 0x1) ? 0xFF : 0x00));
		outportb(0x7E, ((Col & 0x2) ? 0xFF : 0x00));
		outportb(0x7E, ((Col & 0x4) ? 0xFF : 0x00));
		outportb(0x7E, ((Col & 0x8) ? 0xFF : 0x00));
	}
};

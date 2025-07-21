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

	void set_tile(
		const dots8_t& b, const dots8_t& r, const dots8_t& g, const dots8_t& e
	) {
		set_tile_static(b, r, g, e);
	}

	void __fastcall set_color(vc_t col);

	// Generates the optimal instructions for setting up the GRCG with a
	// statically known tile.
	void set_tile_static(dots8_t b, dots8_t r, dots8_t g, dots8_t e) {
		outportb(0x7E, b);
		outportb(0x7E, r);
		outportb(0x7E, g);
		outportb(0x7E, e);
	}

	// Generates the optimal instructions for setting up the GRCG with a
	// statically known color.
	void set_color_static(vc_t col) {
		outportb(0x7E, ((col & 0x1) ? 0xFF : 0x00));
		outportb(0x7E, ((col & 0x2) ? 0xFF : 0x00));
		outportb(0x7E, ((col & 0x4) ? 0xFF : 0x00));
		outportb(0x7E, ((col & 0x8) ? 0xFF : 0x00));
	}

	~GRCG() {
		_outportb_(0x7C, GC_OFF);
	}
};

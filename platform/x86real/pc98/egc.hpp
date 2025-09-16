// C++ RAII EGC implementation
// ---------------------------
// EGC wrapper that automatically disables the EGC if the object goes out of
// scope.

#include "platform/x86real/pc98/grcg.hpp"
#include "pc98.h"

// Just in case `pc98gfx.hpp` was included before...
#undef EGC_ACTIVEPLANEREG
#undef EGC_READPLANEREG
#undef EGC_MODE_ROP_REG
#undef EGC_FGCOLORREG
#undef EGC_MASKREG
#undef EGC_BGCOLORREG
#undef EGC_ADDRRESSREG
#undef EGC_BITLENGTHREG

enum egc_register_t {
	EGC_ACTIVEPLANEREG = 0x04A0,
	EGC_READPLANEREG   = 0x04A2,
	EGC_MODE_ROP_REG   = 0x04A4,
	EGC_FGCOLORREG     = 0x04A6,
	EGC_MASKREG        = 0x04A8,
	EGC_BGCOLORREG     = 0x04AA,
	EGC_ADDRRESSREG    = 0x04AC,
	EGC_BITLENGTHREG   = 0x04AE,
};

// Internal implementation macros
// ------------------------------

inline void graph_mode_change(bool enable_or_disable) {
	_outportb_(0x6A, (0x06 + enable_or_disable));
}

// Requires graphics mode changing to be enabled via
// graph_mode_change(true).
inline void graph_mode_egc(bool enable_or_disable) {
	_outportb_(0x6A, (0x04 + enable_or_disable));
}

inline void graph_egc(bool enable_or_disable) {
	graph_mode_change(true);
	graph_mode_egc(enable_or_disable);
	graph_mode_change(false);
}

inline void graph_egc_on(void) {
	graph_egc(true);
}

inline void graph_egc_off(void) {
	graph_egc(false);
}
// ------------------------------

inline void egc_activate(void) {
	// The EGC does in fact require an active GRCG.
	// (See PC-9801 Programmers' Bible, p. 456)
	_outportb_(0x7C, GC_TDW);

	graph_egc_on();
}

inline void egc_deactivate(void) {
	graph_egc_off();
	_outportb_(0x7C, GC_OFF);
}

struct EGC {
	EGC() {
		egc_activate();
	}
	~EGC() {
		egc_deactivate();
	}
};

// Does not derive from [EGC] because it should only be used in batched
// scenarios where the one-time initialization performance doesn't matter.
struct EGCCopy {
	EGCCopy();
	~EGCCopy();

	// Rectangular blitting
	// --------------------
	// All of these assume that the given rectangles lie fully within VRAM.
	// The inter-page functions return with ![src_page] as the accessed page.

	// Blits the ([w]×[h}) rectangle starting at ([src_left], [src_top]) to
	// ([dst_left], [dst_top]) on the current VRAM page.
	void rect(
		screen_x_t src_left,
		vram_y_t src_top,
		screen_x_t dst_left,
		vram_y_t dst_top,
		pixel_t w,
		pixel_t h
	);

	// Blits the ([w]×[h}) rectangle starting at ([src_left], [src_top]) on
	// VRAM page [src_page] to ([dst_left], [dst_top]) on the other VRAM page.
	void rect_interpage(
		screen_x_t src_left,
		vram_y_t src_top,
		screen_x_t dst_left,
		vram_y_t dst_top,
		pixel_t w,
		pixel_t h,
		page_t src_page
	);

	// Blits the ([w]×[h}) rectangle starting at ([left], [top]) on VRAM page
	// [src_page] to the same position on the other VRAM page.
	void rect_interpage(
		screen_x_t left, vram_y_t top, pixel_t w, pixel_t h, page_t src_page
	);
	// ------------------
};

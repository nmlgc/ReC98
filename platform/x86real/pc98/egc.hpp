// C++ RAII EGC implementation
// ---------------------------
// EGC wrapper that automatically disables the EGC if the object goes out of
// scope.

#include "pc98.h"
#include "x86real.h"

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

// Internal EGC implementation macros
// ----------------------------------

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
// ----------------------------------

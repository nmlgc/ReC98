/// Uncompressed 16-color 32×32 sprite format
/// -----------------------------------------
/// Provides functions for both 32×32 and 16×16 sprites, and optionally
/// supports transparency for images loaded from .PTN files, hardcoded to
/// color #15. With functions for raw allocation and VRAM snapping, this can
/// also be used to store the backgrounds of frequently updated VRAM regions.

}

// Color #15 (1111) is always the transparent one, meaning that transparent
// dots are 1 in all 4 bitplanes. The alpha mask therefore simply is the
// negation of ANDing all bitplanes together. Nifty!
template <class T> inline T ptn_alpha_from(T B, T R, T G, T E)
{
	return ~((B) & (R) & (G) & (E));
}

extern "C" {

#define PTN_W 32
#define PTN_H 32

#include "th01/sprites/main_ptn.h"

typedef dot_rect_t(PTN_W, PTN_H) ptn_plane_t;

// On-disk per-image structure
struct ptn_file_image_t {
	int8_t unused_zero;
	Planar<ptn_plane_t> planes;
};

// In-memory per-image structure
struct ptn_t : public ptn_file_image_t {
	ptn_plane_t alpha; // Derived from color #15 at load time
};

extern ptn_t* ptn_images[PTN_SLOT_COUNT];
extern int8_t ptn_image_count[PTN_SLOT_COUNT];

// MODDERS: Make [id] unsigned
static inline ptn_t* ptn_with_id(int id) {
	return &ptn_images[id / PTN_IMAGES_PER_SLOT][id % PTN_IMAGES_PER_SLOT];
}

// Loading and freeing
// -------------------
typedef enum {
	PE_OK = 0,
	PE_OUT_OF_MEMORY = -3,
	PE_IMAGE_COUNT_INVALID = -9,

	_ptn_error_t_FORCE_UINT16 = 0xFFFF
} ptn_error_t;

// Frees all images in [slot], then allocates new memory for the given number
// of images.
ptn_error_t ptn_new(main_ptn_slot_t slot, int image_count);

// Frees all images in [slot], then loads all images from the .PTN file with
// the given name into the same slot, retaining the current hardware palette.
// Also derives the alpha plane from color #15 of every image.
void ptn_load(main_ptn_slot_t slot, const char *fn);

// Like ptn_load(), but sets the hardware palette to the one in [fn]'s header.
ptn_error_t ptn_load_palette_show(main_ptn_slot_t slot, const char *fn);

// Frees all images in [slot].
void ptn_free(main_ptn_slot_t slot);
// -------------------

// If true, the affected 32×32 or 16×16 area is restored from VRAM page 1
// before a byte-aligned alpha put operation.
// (Because calling egc_copy_rect_1_to_0_16() yourself is way too much to ask?)
extern bool ptn_unput_before_alpha_put;

// 32×32 access
// ------------
#define vram_put_ptn_planar(vo, ptn, y) \
	VRAM_PUT(B, vo, ptn->planes.B[y], PTN_W); \
	VRAM_PUT(R, vo, ptn->planes.R[y], PTN_W); \
	VRAM_PUT(G, vo, ptn->planes.G[y], PTN_W); \
	VRAM_PUT(E, vo, ptn->planes.E[y], PTN_W);

#define vram_snap_ptn_planar(ptn, y, vo) \
	VRAM_SNAP(ptn->planes.B[y], B, vo, PTN_W); \
	VRAM_SNAP(ptn->planes.R[y], R, vo, PTN_W); \
	VRAM_SNAP(ptn->planes.G[y], G, vo, PTN_W); \
	VRAM_SNAP(ptn->planes.E[y], E, vo, PTN_W);

// Displays the given [ptn_id] at (⌊left/8⌋*8, top), disregarding its alpha
// plane.
void ptn_put_noalpha_8(screen_x_t left, vram_y_t top, int ptn_id);

// Overwrites the 4 color planes of [ptn_id] with the current VRAM content of
// the 32×32 pixels starting at (⌊left/8⌋*8, top).
void ptn_snap_8(screen_x_t left, vram_y_t top, int ptn_id);

// Copies the 32×32 pixels starting at (⌊left/8⌋*8, top) from VRAM page 0 to
// VRAM page 1.
void ptn_copy_8_0_to_1(screen_x_t left, vram_y_t top);

// Restores the 32×32 pixels starting at (⌊left/16⌋*16, top) on VRAM page 0
// with the same (background) pixels from VRAM page 1.
#define ptn_sloppy_unput_16(left, top) \
	egc_copy_rect_1_to_0_16(left, top, PTN_W, PTN_H)

// Restores the 32×32 pixels starting at (⌊left/8⌋*8, top) on VRAM page 0 with
// the same (background) pixels from VRAM page 1, applying the alpha mask from
// the given [ptn_id].
void ptn_unput_8(screen_x_t left, vram_y_t top, int ptn_id);

// Displays the given [ptn_id] at (⌊left/8⌋*8, top).
void ptn_put_8(screen_x_t left, vram_y_t top, int ptn_id);
// ------------

// 16×16 access
// ------------
// These functions subdivide a 32×32 PTN image into four 16×16 areas, numbered
// like this:
// | 0 | 1 |
// | 2 | 3 |
#define PTN_QUARTER_W 16
#define PTN_QUARTER_H 16

#define ptn_quarter_y(quarter) ((quarter & 2) ? PTN_QUARTER_H : 0)
#define ptn_quarter_x(quarter) ((quarter & 1) ? PTN_QUARTER_W : 0)

struct PTNQuarter
{
	pixel_t x, y;

	void init(const int& quarter) {
		y = ptn_quarter_y(quarter);
		x = ptn_quarter_x(quarter);
	}
};

// Displays the given [quarter] of the given [ptn_id] at (⌊left/8⌋*8, top),
// diregarding its alpha plane.
void ptn_put_quarter_noalpha_8(
	screen_x_t left, vram_y_t top, int ptn_id, int quarter
);

// Overwrites the 4 color planes of the given [quarter] of [ptn_id] with the
// current VRAM content of the 16×16 pixels starting at (⌊left/8⌋*8, top).
void ptn_snap_quarter_8(
	screen_x_t left, vram_y_t top, int ptn_id, int quarter
);

// Restores the 16×16 pixels starting at (⌊left/16⌋*16, top) on VRAM page 0
// with the same (background) pixels from VRAM page 1.
#define ptn_sloppy_unput_quarter_16(left, top) \
	egc_copy_rect_1_to_0_16(left, top, PTN_QUARTER_W, PTN_QUARTER_H)

// Restores the 16×16 pixels starting at (⌊left/8⌋*8, top) on VRAM page 0 with
// the same (background) pixels from VRAM page 1, applying the alpha mask from
// the given [quarter] of [ptn_id].
void ptn_unput_quarter_8(
	screen_x_t left, vram_y_t top, int ptn_id, int quarter
);

// Displays the given [quarter] of the given [ptn_id] at (⌊left/8⌋*8, top).
void ptn_put_quarter_8(
	screen_x_t left, vram_y_t top, int ptn_id, int quarter
);

// Displays the given [quarter] of the given [ptn_id] at (left, top).
void ptn_put_quarter(screen_x_t left, vram_y_t top, int ptn_id, int quarter);
// ------------

// Rectangular access
// ------------------

// Calls [func] for every .PTN along a (⌈w/32⌉*32 × 32) row of successive
// sprites starting at (⌊left/8⌋*8, top), and [image_first] in [slot].
#define ptn_row(func, left, top, w, slot, image_first, tmp_ptn_x) { \
	for(tmp_ptn_x = 0; tmp_ptn_x < (w / PTN_W); tmp_ptn_x++) { \
		func((left + (tmp_ptn_x * PTN_W)), top, PTN_ID(slot, image_first)); \
		image_first++; \
	} \
}

// Overwrites the 4 color planes of the successive .PTN sprites starting at
// [image_first] in [slot] with the current content of the
// (⌈w/32⌉*32 × ⌈h/32⌉*32) rectangle starting at (⌊left/8⌋*8, top) on VRAM page
// 1.
#define ptn_snap_rect_from_1_8( \
	left, top, w, h, slot, image_first, tmp_ptn_x, tmp_ptn_y \
) { \
	graph_accesspage_func(1); \
	for(tmp_ptn_y = 0; tmp_ptn_y < (h / PTN_H); tmp_ptn_y++) { \
		ptn_row(ptn_snap_8, \
			left, (top + (tmp_ptn_y * PTN_H)), w, slot, image_first, tmp_ptn_x \
		); \
	} \
	graph_accesspage_func(0); \
}

// Blits a single (⌈w/32⌉*32 × 32) row of successive .PTN sprites, starting at
// [image_first] in [slot], to (⌊left/8⌋*8, top).
#define ptn_put_row_noalpha_8(left, top, w, slot, image_first, tmp_ptn_x) \
	ptn_row(ptn_put_noalpha_8, left, top, w, slot, image_first, tmp_ptn_x)

// Blits a (⌈w/32⌉*32 × ⌈h/32⌉*32) rectangle of successive .PTN sprites,
// starting at [image_first] in [slot], to (⌊left/8⌋*8, top).
#define ptn_put_rect_noalpha_8( \
	left, top, w, h, slot, image_first, tmp_ptn_x, tmp_ptn_y \
) { \
	for(tmp_ptn_y = 0; tmp_ptn_y < (h / PTN_H); tmp_ptn_y++) { \
		ptn_put_row_noalpha_8( \
			left, (top + (tmp_ptn_y * PTN_H)), w, slot, image_first, tmp_ptn_x \
		); \
	} \
}
// ------------------
/// -----------------------------------------

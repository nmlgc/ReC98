/// Uncompressed 16-color 32×32 sprite format
/// -----------------------------------------
/// Provides functions for both 32×32 and 16×16 sprites, and optionally
/// supports transparency for images loaded from .PTN files, hardcoded to
/// color #15. Can also be used to store the backgrounds of frequently updated
/// VRAM regions, using the functions for raw allocation and VRAM snapping.

#define PTN_W 32
#define PTN_H 32

typedef dots_t(PTN_W) ptn_dots_t;

struct ptn_planar_t {
	ptn_dots_t B[PTN_H];
	ptn_dots_t R[PTN_H];
	ptn_dots_t G[PTN_H];
	ptn_dots_t E[PTN_H];
};

// On-disk per-image structure
struct ptn_file_image_t {
	int8_t unused_zero;
	ptn_planar_t planes;
};

// In-memory per-image structure
struct ptn_t : public ptn_file_image_t {
	ptn_dots_t alpha[PTN_H]; // Derived from color #15 at load time
};

#define PTN_SLOT_COUNT 8

extern ptn_t* ptn_images[PTN_SLOT_COUNT];
extern int8_t ptn_image_count[PTN_SLOT_COUNT];

// Loading and freeing
// -------------------
typedef enum {
	PE_OK = 0,
	PE_OUT_OF_MEMORY = -3,
	PE_IMAGE_COUNT_INVALID = -9,

	_ptn_error_t_FORCE_INT = 0xFFFF
} ptn_error_t;

// Frees all images in [slot], then allocates new memory for the given number
// of images.
ptn_error_t ptn_new(int slot, int image_count);

// Frees all images in [slot], then loads all images from the .PTN file with
// the given name into the same slot, retaining the current hardware palette.
// Also derives the alpha plane from color #15 of every image.
void ptn_load(int slot, const char *fn);

// Like ptn_load(), but sets the hardware palette to the one in [fn]'s header.
ptn_error_t ptn_load_palette_show(int slot, const char *fn);

// Frees all images in [slot].
void ptn_free(int slot);
// -------------------

// ID system
// ---------
// Internal assumption for mapping a ptn_id to a slot and image.
#define PTN_IMAGES_PER_SLOT 64
#define PTN_SLOT(slot) ((slot) * PTN_IMAGES_PER_SLOT)
#define PTN_ID(slot, image) (PTN_SLOT(slot) + image)

// MODDERS: Make [id] unsigned
static inline ptn_t* ptn_with_id(int id)
{
	return &ptn_images[id / PTN_IMAGES_PER_SLOT][id % PTN_IMAGES_PER_SLOT];
}
// ---------

// If true, the affected 32×32 or 16×16 area is restored from VRAM page 1
// before a byte-aligned alpha put operation.
// (Because calling egc_copy_rect_1_to_0() yourself is way too much to ask?)
extern bool ptn_unput_before_alpha_put;

// 32×32 access
// ------------
// Displays the given [ptn_id] at (⌊left/8⌋*8, top), disregaring its alpha
// plane.
void ptn_put_noalpha_8(int left, int top, int ptn_id);

// Overwrites the 4 color planes of [ptn_id] with the current VRAM content of
// the 32×32 pixels starting at (⌊left/8⌋*8, top).
void ptn_snap_8(int left, int top, int ptn_id);

// Copies the 32×32 pixels starting at (⌊left/8⌋*8, top) from VRAM page 0 to
// VRAM page 1.
void ptn_copy_8_0_to_1(int left, int top);

// Restores the 32×32 pixels starting at (⌊left/8⌋*8, top) on VRAM page 0 with
// the same (background) pixels from VRAM page 1, applying the alpha mask from
// the given [ptn_id].
void ptn_unput_8(int left, int top, int ptn_id);

// Displays the given [ptn_id] at (⌊left/8⌋*8, top).
void ptn_put_8(int left, int top, int ptn_id);
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
	int x, y;

	void init(const int& quarter) {
		y = ptn_quarter_y(quarter);
		x = ptn_quarter_x(quarter);
	}
};

// Displays the given [quarter] of the given [ptn_id] at (⌊left/8⌋*8, top),
// diregarding its alpha plane.
void ptn_put_quarter_noalpha_8(int left, int top, int ptn_id, int quarter);

// Overwrites the 4 color planes of the given [quarter] of [ptn_id] with the
// current VRAM content of the 16×16 pixels starting at (⌊left/8⌋*8, top).
void ptn_snap_quarter_8(int left, int top, int ptn_id, int quarter);

// Restores the 16×16 pixels starting at (⌊left/8⌋*8, top) on VRAM page 0 with
// the same (background) pixels from VRAM page 1, applying the alpha mask from
// the given [quarter] of [ptn_id].
void ptn_unput_quarter_8(int left, int top, int ptn_id, int quarter);

// Displays the given [quarter] of the given [ptn_id] at (⌊left/8⌋*8, top).
void ptn_put_quarter_8(int left, int top, int ptn_id, int quarter);
// ------------
/// -----------------------------------------

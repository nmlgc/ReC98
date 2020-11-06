#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "th03/formats/mrs.hpp"

static const vram_byte_amount_t MRS_BYTE_W = (MRS_W / BYTE_DOTS);
static const vram_dword_amount_t MRS_DWORD_W = (MRS_BYTE_W / sizeof(dots32_t));

struct mrs_plane_t {
	dots32_t dots[MRS_DWORD_W][MRS_H];
};

// On-disk per-image structure
struct mrs_t {
	mrs_plane_t alpha;
	Planar<mrs_plane_t> planes;
};

extern mrs_t far *mrs_images[MRS_SLOT_COUNT];

/// Uncompressed 16-color 32×32 sprite format
/// -----------------------------------------
/// Optionally supports transparency for images loaded from .PTN files,
/// hardcoded to color #15.

#define PTN_W 32
#define PTN_H 32

typedef dots_t(PTN_W) ptn_dots_t;

#pragma option -a1
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
	ptn_dots_t alpha[PTN_H];
};
#pragma option -a.

#define PTN_SLOT_COUNT 8

extern ptn_t* ptn_images[PTN_SLOT_COUNT];
extern int8_t ptn_image_count[PTN_SLOT_COUNT];
/// -----------------------------------------

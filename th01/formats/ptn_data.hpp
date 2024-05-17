// .PTN data structures and implementation details.

#include "th01/formats/ptn.hpp"
#include "planar.h"

// Color #15 (1111) is always the transparent one, meaning that transparent
// dots are 1 in all 4 bitplanes. The alpha mask therefore simply is the
// negation of ANDing all bitplanes together. Nifty!
template <class T> inline T ptn_alpha_from(T B, T R, T G, T E) {
	return ~((B) & (R) & (G) & (E));
}

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

template <class T> inline int32_t ptn_sizeof_array(const T& count) {
	return (count * static_cast<int32_t>(sizeof(ptn_t)));
}

extern ptn_t* ptn_images[PTN_SLOT_COUNT];
extern int8_t ptn_image_count[PTN_SLOT_COUNT];

// MODDERS: Make [id] unsigned
static inline ptn_t* ptn_with_id(int id) {
	return &ptn_images[id / PTN_IMAGES_PER_SLOT][id % PTN_IMAGES_PER_SLOT];
}

/// Stage 2 Boss - Kurumi
/// ---------------------

#include "platform.h"
#include "pc98.h"
#include "th04/main/playfld.hpp"
#include "th04/main/custom.hpp"

// Spawn rays
// ----------

#define KURUMI_SPAWNRAY_COUNT 6

enum kurumi_spawnray_flag_t {
	B2SF_FREE = 0,
	B2SF_GROW = 1,
	B2SF_SHRINK = 2,
};

struct kurumi_spawnray_t {
	kurumi_spawnray_flag_t flag;
	/* ------------------------- */ int8_t unused;
	PlayfieldPoint target;
	PlayfieldPoint origin;
	PlayfieldPoint velocity;
	/* ------------------------- */ int8_t padding[12];
};

#define kurumi_spawnrays (\
	reinterpret_cast<kurumi_spawnray_t *>(custom_entities) \
)

void pascal near kurumi_spawnrays_add(
	subpixel_t distance_from_center_x, unsigned char angle
)
;
// ----------

/// Extra Stage Boss #2 - Gengetsu
/// ------------------------------

#include "platform.h"
#include "pc98.h"
#include "th04/main/custom.hpp"

// Coordinates
// -----------

static const pixel_t WAVE_TARGET_MARGIN = (PLAYFIELD_W / 12);
// -----------

// Structures
// ----------

#define SPAWNCOLUMN_COUNT 16

struct spawncolumn_t {
	int8_t unused[2];
	PlayfieldPoint pos;
	int8_t padding[20];
};

#define spawncolumns (reinterpret_cast<spawncolumn_t *>(custom_entities))
// ----------

#define wave_amp     	gengetsu_wave_amp
#define wave_target_x	gengetsu_wave_target_x
uint8_t wave_amp = 0x00; // Should really have been signed.
Subpixel wave_target_x;

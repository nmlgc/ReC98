/// Extra Stage Boss #2 - Gengetsu
/// ------------------------------

#include "platform.h"
#include "pc98.h"
#include "th01/math/subpixel.hpp"
#include "th04/main/playfld.hpp"
#include "th04/main/custom.hpp"

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

#define wave_amp	gengetsu_wave_amp
uint8_t wave_amp = 0x00; // Should really have been signed.

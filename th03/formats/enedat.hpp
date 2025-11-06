// Enemy formation script format
// -----------------------------

#include "platform.h"

static const uint8_t ENEMY_SPEED_COUNT = 4;

struct enedat_header_t {
	uint16_t size;
	uint16_t zero;
};

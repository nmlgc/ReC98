/// Extra Stage Boss - EX-Alice
/// ---------------------------

#pragma option -zCBX_UPDATE_TEXT -zPmain_03

#include "platform.h"
#include "pc98.h"
#include "th01/math/subpixel.hpp"
#include "th01/math/area.hpp"
#include "th04/math/motion.hpp"
#include "th04/main/playfld.hpp"
#include "th05/main/boss/boss.hpp"

// Structures
// ----------

struct near firewave_t {
	bool alive;
	bool is_right;
	vram_y_t bottom;
	pixel_t amp;
};
// ----------

// State
// -----

#define FIREWAVE_COUNT 2

extern firewave_t firewaves[FIREWAVE_COUNT];
// -----

// Game logic
// ----------

void pascal near firewaves_add(pixel_t amp, bool is_right)
{
	firewave_t near *firewave = firewaves;
	for(int i = 0; i < FIREWAVE_COUNT; i++, firewave++) {
		if(!firewave->alive) {
			firewave->alive = true;
			firewave->is_right = is_right;
			firewave->bottom = PLAYFIELD_TOP;
			firewave->amp = amp;
			return;
		}
	}
}

void near firewaves_update(void)
{
	firewave_t near *firewave = firewaves;
	for(int i = 0; i < FIREWAVE_COUNT; i++, firewave++) {
		if(firewave->alive) {
			firewave->bottom += 4;
			if(firewave->bottom >= (PLAYFIELD_BOTTOM + 224)) {
				firewave->alive = false;
			}
		}
	}
}

void pascal near exalice_phase_next(
	explosion_type_t explosion_type, int next_end_hp
);
// ----------

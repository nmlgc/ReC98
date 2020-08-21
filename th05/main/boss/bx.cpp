/* ReC98 / TH05
 * ------------
 * Update code for the Extra Stage boss fight, against EX-Alice
 */

#include "th05/main/boss/bx.hpp"

void pascal near firewaves_add(pixel_t amp, bool is_right)
{
	firewave_t near *firewave = firewaves;
	for(int i = 0; i < FIREWAVE_COUNT; i++, firewave++) {
		if(!firewave->alive) {
			firewave->alive = true;
			firewave->is_right = is_right;
			firewave->bottom = PLAYFIELD_Y;
			firewave->amp = amp;
			return;
		}
	}
}

void pascal near firewaves_update(void)
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

void pascal near exalice_phase_end(
	explode_type_t explode_type, int next_phase_end_hp
);

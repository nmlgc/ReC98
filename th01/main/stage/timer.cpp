extern "C" {
#include "platform.h"
#include "pc98.h"
#include "master.hpp"
#include "th01/hardware/egc.h"
#include "th01/math/subpixel.hpp"
#include "th01/sprites/pellet.h"
#include "th01/main/vars.hpp"
#include "th01/main/playfld.hpp"
#include "th01/main/bullet/pellet.hpp"
}

extern unsigned int frames_since_harryup;

void pattern_harryup(void)
{
	extern unsigned char harryup_cycle;

	frames_since_harryup++;
	harryup_cycle++;

	bool fire =
		(frames_since_harryup < 200) ? ((harryup_cycle % 5) == 0) :
		(frames_since_harryup < 300) ? ((harryup_cycle % 4) == 0) :
		(frames_since_harryup < 400) ? ((harryup_cycle % 3) == 0) :
		(frames_since_harryup < 500) ? ((harryup_cycle % 2) == 0) :
		/*                   >= 500 */ true;

	if(!fire) {
		return;
	}
	for(unsigned char i = 0; i <= rank; i++) {
		Pellets.add_group(
			playfield_rand_x(), PLAYFIELD_TOP, PG_1_RANDOM_WIDE, to_sp(3.0f)
		);
	}
}

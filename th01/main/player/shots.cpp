#include "th01/snd/mdrv2.h"
#include "th01/main/playfld.hpp"
#include "th01/main/player/shots.hpp"

void CShots::add(int new_left, int new_top)
{
	if(new_left < PLAYFIELD_LEFT || new_left > (PLAYFIELD_RIGHT - 1)) {
		return;
	}
	for(int i = 0; i < SHOT_COUNT; i++) {
		if(moving[i] == true) {
			continue;
		}
		if(decay_frame[i] != 0) {
			continue;
		}
		left[i] = new_left;
		top[i] = new_top;
		moving[i] = true;
		mdrv2_se_play(1);
		decay_frame[i] = 0;
		return;
	}
}

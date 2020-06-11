#include "th01/snd/mdrv2.h"
#include "th01/formats/ptn.hpp"
#include "th01/hardware/egc.h"
#include "th01/main/playfld.hpp"
#include "th01/main/player/shots.hpp"

static const int SHOT_W = PTN_QUARTER_W;
static const int SHOT_H = PTN_QUARTER_H;

#define sloppy_unput(i) \
	egc_copy_rect_1_to_0(left[i], top[i], SHOT_W, SHOT_H);

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

void CShots::unput_and_reset_all(void)
{
	for(int i = 0; i < SHOT_COUNT; i++) {
		if(moving[i]) {
			sloppy_unput(i);
			moving[i] = false;
		} else if(decay_frame[i]) {
			sloppy_unput(i);
			decay_frame[i] = false;
		}
	}
}

#undef sloppy_unput

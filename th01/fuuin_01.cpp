/* ReC98
 * -----
 * Code segment #1 of TH01's FUUIN.EXE
 */

#pragma option -O- -1 -Z- -d-

#include <process.h>
#include <stdio.h>
#include "libs/master.lib/master.hpp"
#include "th01/resident.hpp"
#include "th01/core/initexit.hpp"
#include "th01/end/end.hpp"
#include "th01/snd/mdrv2.h"
#include "th01/shiftjis/fns.hpp"

// Resident structure fields
// -------------------------
// Not actually redundant because ending previews can run without an allocated
// resident structure.

score_t score = 100000;
score_t score_highest = 100000;
int32_t continues_total;
int32_t continues_per_scene[SCENE_COUNT];

// ZUN bloat: 308 unused bytes… for 77 extra scenes, maybe?!
static int8_t unused[308];

int8_t credit_lives_extra;
end_sequence_t end_flag;
uint8_t rank;
// -------------------------

bool16 end_init(void)
{
	int i;
	resident_t __seg *seg = ResData<resident_t>::exist(RES_ID);
	if(seg) {
		resident_t* resident = seg;
		if(resident->end_flag != ES_NONE) {
			score = resident->score;
			continues_total = 0;
			end_flag = resident->end_flag;
			rank = resident->rank;
			score_highest = resident->score_highest;

			for(i = 0; i < SCENE_COUNT; i++) {
				continues_per_scene[i] = resident->continues_per_scene[i];
				resident->continues_per_scene[i] = 0;
				continues_total += continues_per_scene[i];
			}

			random_seed = resident->rand;
			credit_lives_extra = resident->credit_lives_extra;
			resident->score = 0;
			resident->continues_total = 0;
			resident->score_highest = 0;
		} else {
			puts("ERROR : end_flag is not ture !!");
			return false;
		}
	} else {
		puts("ERROR : cfg_id is not alloc!!");
		return false;
	}
	return true;
}

bool16 end_resident_clear(void)
{
	int i;
	resident_t __seg *seg = ResData<resident_t>::exist(RES_ID);
	if(seg) {
		resident_t* resident = seg;
		resident->score = 0;
		resident->continues_total = 0;
		resident->end_flag = ES_NONE;
		resident->score_highest = 0;
		for(i = 0; i < SCENE_COUNT; i++) {
			resident->continues_per_scene[i] = 0;
		}
		resident->stage_id = 0;
	}
	return true;
}

void main(int argc, const char *argv[])
{
	if(!mdrv2_resident()) {
		return;
	}

	// Should really be checked, but eh, it's Real Mode...
	(argc);

	// That's a hidden ending preview feature!
	if(argv[1][0] != 't') {
		if(!end_init()) {
			return;
		}
	} else {
		if(argv[1][1] == '1') {
			end_flag = ES_MAKAI;
		} else {
			end_flag = ES_JIGOKU;
		}
	}

	// ZUN bug: Should be done conditionally based on resident_t::bgm_mode.
	// This is why you still get music during this binary despite disabling BGM
	// in the options.
	mdrv2_enable_if_board_installed();

	game_init();
	end_and_verdict_and_regist_animate();
	game_switch_binary();
	execl(BINARY_OP, BINARY_OP, nullptr);
}

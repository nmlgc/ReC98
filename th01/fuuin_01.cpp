/* ReC98
 * -----
 * Code segment #1 of TH01's FUUIN.EXE
 */

#pragma option -O- -1 -Z-

extern "C" {
#include <stdio.h>
#include "platform.h"
#include "master.hpp"
#include "th01/common.h"
#include "th01/resident.hpp"
#include "th01/end/vars.hpp"

#undef RES_ID

bool16 end_init(void)
{
	int i;
	#define RES_ID RES_ID_0
	extern const char RES_ID[];
	resident_t __seg *sgm = ResData<resident_t>::exist(RES_ID);
	#undef RES_ID
	if(sgm) {
		resident_t* resident = sgm;
		if(resident->end_flag) {
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
			start_lives_extra = resident->start_lives_extra;
			resident->score = 0;
			resident->continues_total = 0;
			resident->score_highest = 0;
		} else {
			extern const char ERROR_END_FLAG[];
			puts(ERROR_END_FLAG);
			return false;
		}
	} else {
		extern const char ERROR_NO_RESDATA[];
		puts(ERROR_NO_RESDATA);
		return false;
	}
	return true;
}

bool16 end_resident_clear(void)
{
	int i;
	#define RES_ID RES_ID_1
	extern const char RES_ID[];
	resident_t __seg *sgm = ResData<resident_t>::exist(RES_ID);
	#undef RES_ID
	if(sgm) {
		resident_t* resident = sgm;
		resident->score = 0;
		resident->continues_total = 0;
		resident->end_flag = 0;
		resident->score_highest = 0;
		for(i = 0; i < SCENE_COUNT; i++) {
			resident->continues_per_scene[i] = 0;
		}
		resident->stage = 0;
	}
	return true;
}

}

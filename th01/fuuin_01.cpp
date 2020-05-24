/* ReC98
 * -----
 * Code segment #1 of TH01's FUUIN.EXE
 */

#pragma option -O- -1

extern "C" {
#include <stdio.h>
#include "th01/th01.h"
#include "th01/ranks.h"
#include "th01/end/vars.hpp"

#undef RES_ID
#undef RES_ID_STRLEN
#define RES_ID_STRLEN (sizeof("ReiidenConfig") - 1)

bool16 end_init(void)
{
	int i;
	#define RES_ID RES_ID_0
	extern const char RES_ID[];
	seg_t sgm = resdata_exist(RES_ID, RES_ID_STRLEN, RES_PARASIZE);
	#undef RES_ID
	if(sgm) {
		resident_t* resident = reinterpret_cast<resident_t*>(MK_FP(sgm, 0));
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
	seg_t sgm = resdata_exist(RES_ID, RES_ID_STRLEN, RES_PARASIZE);
	#undef RES_ID
	if(sgm) {
		resident_t* resident = reinterpret_cast<resident_t*>(MK_FP(sgm, 0));
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

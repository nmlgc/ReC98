/* ReC98
 * -----
 * Random resident structure stuff
 */

#pragma option -2 -Z-

#include "platform.h"
#include "master.hpp"
#include "th01/resident.hpp"
#include "th01/core/resstuff.hpp"

resident_t far *resident;

void resident_create_and_stuff_set(
	int8_t rank,
	bgm_mode_t bgm_mode,
	int8_t bombs,
	int8_t start_lives_extra,
	long rand
)
{
	resident_t __seg *sgm = ResData<resident_t>::exist(RES_ID);
	if(!sgm) {
		sgm = ResData<resident_t>::create(RES_ID);
		resident = sgm;
		resident->stage_id = 0;
		resident->continues_total = 0;
	}
	if(sgm) {
		resident = sgm;
		resident->rank = rank;
		resident->bgm_mode = bgm_mode;
		resident->bombs = bombs;
		resident->start_lives_extra = start_lives_extra;
		resident->rand = rand;
		resident->score = 0;
	}
}

int resident_stuff_get(
	int8_t& rank,
	bgm_mode_t& bgm_mode,
	int8_t& bombs,
	int8_t& start_lives_extra,
	unsigned long& rand,
	long& continues_total,
	int& stage_id
)
{
	resident_t __seg *sgm = ResData<resident_t>::exist(RES_ID);
	if(sgm) {
		resident = sgm;
		rank = resident->rank;
		bgm_mode = resident->bgm_mode;
		bombs = resident->bombs;
		start_lives_extra = resident->start_lives_extra;
		rand = resident->rand;
		continues_total = resident->continues_total;
		stage_id = resident->stage_id;
		return 0;
	}
	return 1;
}

void resident_free(void)
{
	resident_t __seg *sgm = ResData<resident_t>::exist(RES_ID);
	if(sgm) {
		resdata_free(sgm);
	}
}

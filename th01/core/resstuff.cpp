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
	int8_t rem_bombs,
	int8_t credit_lives_extra,
	long rand
)
{
	resident_t __seg *seg = ResData<resident_t>::exist(RES_ID);
	if(!seg) {
		seg = ResData<resident_t>::create(RES_ID);
		resident = seg;
		resident->stage_id = 0;
		resident->continues_total = 0;
	}
	if(seg) {
		resident = seg;
		resident->rank = rank;
		resident->bgm_mode = bgm_mode;
		resident->rem_bombs = rem_bombs;
		resident->credit_lives_extra = credit_lives_extra;
		resident->rand = rand;
		resident->score = 0;
	}
}

int resident_stuff_get(
	int8_t& rank,
	bgm_mode_t& bgm_mode,
	int8_t& rem_bombs,
	int8_t& credit_lives_extra,
	unsigned long& rand,
	int32_t& continues_total,
	int& stage_id
)
{
	resident_t __seg *seg = ResData<resident_t>::exist(RES_ID);
	if(seg) {
		resident = seg;
		rank = resident->rank;
		bgm_mode = resident->bgm_mode;
		rem_bombs = resident->rem_bombs;
		credit_lives_extra = resident->credit_lives_extra;
		rand = resident->rand;
		continues_total = resident->continues_total;
		stage_id = resident->stage_id;
		return 0;
	}
	return 1;
}

void resident_free(void)
{
	resident_t __seg *seg = ResData<resident_t>::exist(RES_ID);
	if(seg) {
		resdata_free(seg);
	}
}

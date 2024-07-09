/* ReC98
 * -----
 * Random resident structure stuff
 */

#include "libs/master.lib/master.hpp"
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

int resident_stuff_get(uint8_t& rank, unsigned long& rand, int& stage_id)
{
	resident_t __seg *seg = ResData<resident_t>::exist(RES_ID);
	if(seg) {
		resident = seg;
		rank = resident->rank;
		rand = resident->rand;
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

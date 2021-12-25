/* ReC98
 * -----
 * Random resident structure stuff
 */

#pragma option -2 -Z-

extern "C" {
#include "platform.h"
#include "master.hpp"
#include "th01/common.h"
#include "th01/resident.hpp"

extern const char res_id[] /* = RES_ID */;

void resident_stuff_set(
	char rank, char bgm_mode, char bombs, char start_lives_extra, long rand
)
{
	resident_t __seg *sgm = ResData<resident_t>::exist(res_id);
	if(!sgm) {
		sgm = ResData<resident_t>::create(res_id);
		resident = sgm;
		resident->stage = 0;
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
	char *rank,
	char *bgm_mode,
	char *bombs,
	char *start_lives_extra,
	long *rand,
	long *continues_total,
	int *stage
)
{
	resident_t __seg *sgm = ResData<resident_t>::exist(res_id);
	if(sgm) {
		resident = sgm;
		*rank = resident->rank;
		*bgm_mode = resident->bgm_mode;
		*bombs = resident->bombs;
		*start_lives_extra = resident->start_lives_extra;
		*rand = resident->rand;
		*continues_total = resident->continues_total;
		*stage = resident->stage;
		return 0;
	}
	return 1;
}

void resident_free(void)
{
	resident_t __seg *sgm = ResData<resident_t>::exist(res_id);
	if(sgm) {
		resdata_free(sgm);
	}
}

}

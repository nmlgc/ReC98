/* ReC98
 * -----
 * Random resident structure stuff
 */

#include "th01/th01.h"

#pragma option -2

extern const char res_id[] /* = RES_ID */;
extern resident_t *resident;

void resident_stuff_set(
	char rank, char bgm_mode, char bombs, char start_lives_extra, long rand
)
{
	seg_t res = resdata_exist(res_id, RES_ID_STRLEN, RES_PARASIZE);
	if(!res) {
		res = resdata_create(res_id, RES_ID_STRLEN, RES_PARASIZE);
		resident = MK_FP(res, 0);
		resident->stage = 0;
		resident->continues_total = 0;
	}
	if(res) {
		resident = MK_FP(res, 0);
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
	seg_t res = resdata_exist(res_id, RES_ID_STRLEN, RES_PARASIZE);
	if(res) {
		resident = MK_FP(res, 0);
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
	seg_t res = resdata_exist(res_id, RES_ID_STRLEN, RES_PARASIZE);
	if(res) {
		resdata_free(res);
	}
}

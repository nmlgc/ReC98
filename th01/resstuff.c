/* ReC98
 * -----
 * Random resident structure stuff
 */

#include "th01/th01.h"

#pragma option -2

extern const char res_id[] /* = RES_ID */;
extern resident_t *reiidenconfig;

void resident_stuff_set(
	char rank, char bgm_mode, char bombs, char start_lives_extra, long rand
)
{
	seg_t res = resdata_exist(res_id, RES_ID_STRLEN, RES_PARASIZE);
	if(!res) {
		res = resdata_create(res_id, RES_ID_STRLEN, RES_PARASIZE);
		reiidenconfig = MK_FP(res, 0);
		reiidenconfig->stage = 0;
		reiidenconfig->continues_total = 0;
	}
	if(res) {
		reiidenconfig = MK_FP(res, 0);
		reiidenconfig->rank = rank;
		reiidenconfig->bgm_mode = bgm_mode;
		reiidenconfig->bombs = bombs;
		reiidenconfig->start_lives_extra = start_lives_extra;
		reiidenconfig->rand = rand;
		reiidenconfig->score = 0;
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
		reiidenconfig = MK_FP(res, 0);
		*rank = reiidenconfig->rank;
		*bgm_mode = reiidenconfig->bgm_mode;
		*bombs = reiidenconfig->bombs;
		*start_lives_extra = reiidenconfig->start_lives_extra;
		*rand = reiidenconfig->rand;
		*continues_total = reiidenconfig->continues_total;
		*stage = reiidenconfig->stage;
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

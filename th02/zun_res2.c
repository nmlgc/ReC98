/* ReC98
 * -----
 * 2nd part of ZUN_RES.COM. Verifies HUUHI.DAT.
 */

#pragma option -O- -k-

#include <stddef.h>
#include "th02/th02.h"

extern char rank;
scoredat_section_t hi;

void pascal scoredat_recreate(void);
void pascal near scoredat_load(void);

const char *SCOREDAT_FN = "huuhi.dat";
unsigned char g_name_first_sum = 0;
unsigned char stage_sum = 0;
unsigned char unused_2 = 0;
long points_sum = 0;
long score_sum = 0;

int pascal scoredat_verify(void)
{
	if(!file_exist(SCOREDAT_FN)) {
		scoredat_recreate();
	} else {
		for(rank = 0; rank < RANK_COUNT; rank++) {
			register int unused;
			register int i;

			scoredat_load();
			_AL = 0;
			g_name_first_sum = _AL;
			stage_sum = _AL;
			_AX = 0;
			__asm {
				mov word ptr points_sum + 0, ax
				mov word ptr points_sum + 2, ax
				mov word ptr score_sum + 0, ax
				mov word ptr score_sum + 2, ax
			}
			for(i = 0; i < sizeof(hi.score); i++) {
				score_sum += *((unsigned char*)(&hi.score) + i);
			}
			for(i = 0; i < SCOREDAT_PLACES; i++) {
				points_sum += hi.score.points[i];
				g_name_first_sum += hi.score.g_name[i][0];
				stage_sum += hi.score.stage[i];
			}
			if(
				points_sum != hi.score.points_sum
				|| g_name_first_sum != hi.score.g_name_first_sum
				|| stage_sum != hi.score.stage_sum
				|| score_sum != hi.score_sum
			) {
				goto delete;
			}
		}
	}
	return 0;
delete:
	file_delete(SCOREDAT_FN);
	return 1;
}

#pragma codestring "\x90"

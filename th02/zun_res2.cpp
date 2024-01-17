/* ReC98
 * -----
 * 2nd part of ZUN_RES.COM. Verifies HUUHI.DAT.
 */

#pragma option -O- -k-

#include <dos.h>
#include "platform.h"
#include "master.hpp"
#include "th01/rank.h"
#include "th02/formats/scoredat.hpp"

extern int8_t rank;
scoredat_section_t hi;

void pascal scoredat_recreate(void);
void pascal near scoredat_load(void);

const char *SCOREDAT_FN = "huuhi.dat";
unsigned char g_name_first_sum = 0;
unsigned char stage_sum = 0;
unsigned char unused_2 = 0; // ZUN bloat
long score_sum = 0;
long section_sum = 0;

// ZUN bloat: Needed to circumvent 16-bit promotion in a single comparison.
inline int8_t rank_count(void) {
	return RANK_COUNT;
}

int pascal scoredat_verify(void)
{
	if(!file_exist(SCOREDAT_FN)) {
		scoredat_recreate();
	} else {
		for(rank = 0; rank < rank_count(); rank++) {
			register int unused; // ZUN bloat
			register int i;

			scoredat_load();
			_AL = 0;
			g_name_first_sum = _AL;
			stage_sum = _AL;
			_AX = 0;
			asm {
				mov word ptr score_sum + 0, ax
				mov word ptr score_sum + 2, ax
				mov word ptr section_sum + 0, ax
				mov word ptr section_sum + 2, ax
			}
			for(i = 0; i < sizeof(hi.score); i++) {
				section_sum += *((uint8_t *)(&hi.score) + i);
			}
			for(i = 0; i < SCOREDAT_PLACES; i++) {
				score_sum += hi.score.score[i];
				g_name_first_sum += hi.score.g_name[i][0];
				stage_sum += hi.score.stage[i];
			}
			if(
				score_sum != hi.score.score_sum
				|| g_name_first_sum != hi.score.g_name_first_sum
				|| stage_sum != hi.score.stage_sum
				|| section_sum != hi.section_sum
			) {
				goto remove;
			}
		}
	}
	return 0;

remove:
	file_delete(SCOREDAT_FN);
	return 1;
}

#pragma codestring "\x90"

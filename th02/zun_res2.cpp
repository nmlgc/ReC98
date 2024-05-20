// 2nd part of ZUN_RES.COM. Verifies HUUHI.DAT and initializes the high score
// lists.

#pragma option -O- -k- -2

#include <dos.h>
#include "platform.h"
#include "libs/master.lib/master.hpp"
#include "th01/rank.h"
#include "th02/formats/scoredat.hpp"
#include "th02/gaiji/gaiji.h"

scoredat_section_t hi;

void pascal scoredat_recreate(void);
void pascal near scoredat_load(void);

const char *SCOREDAT_FN = "huuhi.dat";
unsigned char g_name_first_sum = 0;
unsigned char stage_sum = 0;
unsigned char unused_2 = 0; // ZUN bloat
long score_sum = 0;
long section_sum = 0;
int8_t rank;

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
#pragma option -O -k

// Slightly differs from the same function in MAINE.EXE!
// And seriously, I wasted half a week trying to figure out how to get these
// exact same instructions out of the compiler, and it just didn't work.
void pascal scoredat_defaults_set(void)
{
	_SI = 0;
	_DI = 1000 * SCOREDAT_PLACES;
	goto place_loop;

place_set:
	hi.score.cleared = 0;
	hi.score.score[_SI] = _DI;
	_DI -= 1000;
	hi.score.stage[_SI] = 5 - ((int)_SI >> 1);
	_BX = _SI;
	asm {
		imul bx, bx, 7
		mov cx, 6

name_loop:
		mov byte ptr hi.(scoredat_section_t)score.g_name[bx], gs_BULLET
		inc bx
		loop name_loop
		mov byte ptr hi.(scoredat_section_t)score.g_name[bx], 0
	}
	_BX = _SI;
	_BX <<= 2;
	asm {
		mov word ptr hi.(scoredat_section_t)score.date[bx].da_year, 1900
		mov byte ptr hi.(scoredat_section_t)score.date[bx].da_day, 1
		mov byte ptr hi.(scoredat_section_t)score.date[bx].da_mon, 1
		mov byte ptr hi.(scoredat_section_t)score.shottype[si], 1
		inc si

place_loop:
		cmp si, SCOREDAT_PLACES
		jge end
		jmp place_set
	}
end:
}

#include "th02/scoreenc.c"

void pascal scoredat_create(void)
{
	SCOREDAT_ENCODE();
	file_create(SCOREDAT_FN);
	file_write(&hi, sizeof(hi));
	file_write(&hi, sizeof(hi));
	file_write(&hi, sizeof(hi));
	file_write(&hi, sizeof(hi));
	file_write(&hi, sizeof(hi));
	file_close();
}

void pascal scoredat_recreate(void)
{
	scoredat_defaults_set();
	scoredat_create();
}

#include "th02/scorelod.c"

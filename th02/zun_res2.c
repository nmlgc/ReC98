/* ReC98
 * -----
 * 2nd part of ZUN_RES.COM. Initializes the high score lists.
 */

#include "th02/th02.h"

extern scoredat_section_t hi;
extern const char *SCOREDAT_FN;

char rank;

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
	hi.score.points[_SI] = _DI;
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

#include "th02\scorelod.c"

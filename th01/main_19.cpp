/* ReC98
 * -----
 * Code segment #19 of TH01's REIIDEN.EXE
 */

#pragma option -3 -Z -d

extern "C" {
#include "ReC98.h"
#include "th01/ranks.h"
#include "th01/hiscore/scoredat.hpp"

extern char rank;

#define scoredat_cli()
#define scoredat_sti()
#define scoredat_error(str)
#define scoredat_exist(fn) file_exist(fn)
#define scoredat_create(fn) file_create(fn)
#define scoredat_ropen(fn) file_ropen(fn)
#define scoredat_read(buf, size) file_read(buf, size)
#define scoredat_write(buf, size) file_write(buf, size)
#define scoredat_close() file_close()
#include "th01/hiscore/scorelod.cpp"

uint32_t scoredat_hiscore_get()
{
	return scoredat_points[0];
}

#include "th01/hiscore/score_nm.cpp"
}

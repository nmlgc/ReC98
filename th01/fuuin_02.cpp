/* ReC98
 * -----
 * Code segment #2 of TH01's FUUIN.EXE
 */

#pragma option -O- -1

extern "C" {
#include <io.h>
#include <stdio.h>
#include "ReC98.h"
#include "th01/ranks.h"
#include "th01/hiscore/scoredat.hpp"

extern unsigned char rank;

extern const char SCOREDAT_ERROR_NOT_FOUND[];
extern const char SCOREDAT_ERROR_INVALID[];
extern const char FOPEN_RB[];
extern const char FOPEN_WB[];

#define scoredat_cli() disable()
#define scoredat_sti() enable()
#define scoredat_error(str) printf(str)
#define scoredat_exist(fn) !access(fn, 0)
#define scoredat_create(fn) (fp = fopen(fn, FOPEN_WB))
#define scoredat_ropen(fn) (fp = fopen(fn, FOPEN_RB))
#define scoredat_read(buf, size) read(fileno(fp), buf, size)
#define scoredat_write(buf, size) write(fileno(fp), buf, size)
#define scoredat_close() fclose(fp)
#include "th01/hiscore/scorelod.cpp"

#include "th01/hiscore/score_nm.cpp"
}

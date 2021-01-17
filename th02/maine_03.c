/* ReC98
 * -----
 * Code segment #3 of TH02's MAINE.EXE
 */

#include <dos.h>
#include <stddef.h>
#include "platform.h"
#include "master.hpp"
#include "th01/ranks.h"
#include "th02/resident.hpp"
#include "th02/formats/cfg.h"

char rank = RANK_NORMAL;
char unused_1 = 0;

resident_t *resident;
char unused_2;
char rem_lives;
char rem_bombs;
char unused_3;
char unused_4;
char unused_5;
long score;
int unused_6;

int pascal cfg_load(void)
{
	seg_t resident_sgm;

	file_ropen(CFG_FN);
	file_seek(offsetof(cfg_t, resident), 0);
	file_read(&resident_sgm, sizeof(resident_sgm));
	file_close();
	if(!resident_sgm) {
		return 0;
	}
	resident = MK_FP(resident_sgm, 0);
	rem_lives = resident->rem_lives;
	rem_bombs = resident->rem_bombs;
	rank = resident->rank;
	score = resident->score;
	return 1;
}

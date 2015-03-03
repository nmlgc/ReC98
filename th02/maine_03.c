/* ReC98
 * -----
 * Code segment #3 of TH02's MAINE.EXE
 */

#include <stddef.h>
#include "th02\th02.h"

char rank = RANK_NORMAL;
char unused_1 = 0;

mikoconfig_t *mikoconfig;
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
	int mikoconfig_sgm;

	file_ropen("huuma.cfg");
	file_seek(offsetof(huuma_cfg_t, mikoconfig_sgm), 0);
	file_read(&mikoconfig_sgm, sizeof(mikoconfig_sgm));
	file_close();
	if(!mikoconfig_sgm) {
		return 0;
	}
	mikoconfig = MK_FP(mikoconfig_sgm, 0);
	rem_lives = mikoconfig->rem_lives;
	rem_bombs = mikoconfig->rem_bombs;
	rank = mikoconfig->rank;
	score = mikoconfig->score;
	return 1;
}

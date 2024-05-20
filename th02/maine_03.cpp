/* ReC98
 * -----
 * Code segment #3 of TH02's MAINE.EXE
 */

#include <stddef.h>
#include "platform.h"
#include "libs/master.lib/master.hpp"
#include "th02/resident.hpp"
#include "th02/core/globals.hpp"
#include "th02/formats/cfg.hpp"

int cfg_load(void)
{
	resident_t __seg *resident_seg;

	file_ropen(CFG_FN);
	file_seek(offsetof(cfg_t, resident), 0);
	file_read(&resident_seg, sizeof(resident_seg));
	file_close();
	if(!resident_seg) {
		return 0;
	}
	resident = resident_seg;
	lives = resident->rem_lives;
	bombs = resident->rem_bombs;
	rank = resident->rank;
	score = resident->score;
	return 1;
}

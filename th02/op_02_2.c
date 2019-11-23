/* ReC98
 * -----
 * 2nd part of code segment #2 of TH02's OP.EXE
 */

#include "th02/th02.h"
#include "th02/mem.h"

#pragma codeseg op_02_TEXT
#pragma option -3

const char pf_fn[] = PF_FN;
#include "th02/snd/data.c"
#include "th02/snd/se_data.c"

#include "th02/hardware/input.c"

int game_init_op(void)
{
	if(mem_assign_dos(MEM_ASSIGN_PARAS_OP)) {
		return 1;
	}
	vram_planes_set();
	graph_start();
	graph_clear_both();
	vsync_start();
	key_beep_off();
	text_systemline_off();
	text_cursor_off();
	egc_start();
	pfkey = PF_KEY;
	pfstart(pf_fn);
	return 0;
}

#include "th02/exit.c"

#pragma codestring "\x00"

#include "th02/snd/mmd_res.c"
#include "th02/snd/detmode.c"
#include "th02/snd/pmd_res.c"
#include "th02/snd/load.c"
#include "th02/formats/pi_put.c"
#include "th02/snd/kajaint.c"
#include "th02/snd/delaymea.c"
#include "th02/snd/se.c"
#include "th02/hardware/frmdely1.c"

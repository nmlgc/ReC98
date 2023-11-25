#include "platform.h"
#include "pc98.h"
#include "master.hpp"
#include "th01/rank.h"
#include "th02/formats/pi.h"
#include "th04/common.h"
#include "th04/playchar.h"
#include "th04/score.h"
#include "th04/resident.hpp"
extern "C" {
#include "th04/op/op.hpp"
}
#include "th04/op/start.hpp"

void near start_game(void)
{
	resident->stage = 0;
	resident->credit_lives = resident->cfg_lives;
	resident->credit_bombs = resident->cfg_bombs;

	// ZUN bloat: Not read in playchar_menu(), and overwritten on return.
	resident->playchar_ascii = ('0' + PLAYCHAR_REIMU);

	resident->stage_ascii = ('0' + 0);

	if(playchar_menu()) {
		return;
	}
	resident->demo_num = 0;
	op_exit_into_main(true, true);
}

void near start_extra(void)
{
	resident->stage = STAGE_EXTRA;
	resident->credit_lives = 3;
	resident->credit_bombs = 2;

	// ZUN bloat: Not read in playchar_menu(), and overwritten on return.
	resident->playchar_ascii = ('0' + PLAYCHAR_REIMU);

	resident->stage_ascii = ('0' + STAGE_EXTRA);
	if(playchar_menu()) {
		return;
	}
	resident->demo_num = 0;
	op_exit_into_main(true, false);
}

inline void resident_set_demo(
	int stage, playchar_t playchar, shottype_t shottype
) {
	resident->playchar_ascii = ('0' + playchar);
	resident->stage_ascii = ('0' + stage);
	resident->shottype = shottype;
	resident->demo_stage = stage;
}

void near start_demo(void)
{
	// ZUN bloat: This is reassigned to [resident->demo_stage] shortly after
	// the start of MAIN.EXE. Would be cleaner to do it here, which would even
	// avoid the need for a distinct demo stage field altogether.
	resident->stage = 0;

	resident->credit_lives = 3;
	resident->credit_bombs = 3;

	resident->demo_num++;
	if(resident->demo_num > 4) {
		resident->demo_num = 1;
	}

	switch(resident->demo_num) {
	case 1:
		resident_set_demo(3, PLAYCHAR_REIMU, SHOTTYPE_A);
		break;
	case 2:
		resident_set_demo(0, PLAYCHAR_MARISA, SHOTTYPE_A);
		break;
	case 3:
		resident_set_demo(2, PLAYCHAR_REIMU, SHOTTYPE_B);
		break;
	case 4:
		resident_set_demo(1, PLAYCHAR_MARISA, SHOTTYPE_B);
		break;
	}
	palette_black_out(1);
	super_free();
	pi_free(0); // ZUN bloat: OP.EXE doesn't leave any .PI image in memory.
	op_exit_into_main(false, false);
}

/* ReC98
 * -----
 * 5th part of code segment #1 of TH05's MAIN.EXE
 */

#pragma option -zCmain_01_TEXT -zPmain_01 -d-

#include "libs/master.lib/master.hpp"
#include "libs/master.lib/pc98_gfx.hpp"
#include "th03/formats/cdg.h"
#include "th04/main/null.hpp"
#include "th04/main/rank.hpp"
#include "th04/main/score.hpp"
#include "th04/main/item/item.hpp"
#include "th04/main/stage/stage.hpp"
#include "th05/formats/bb.h"
#include "th05/main/boss/bosses.hpp"

#include "th04/main/boss/reset.cpp"
#include "th04/formats/bb_boss.cpp"
#include "th05/main/stage/setup.cpp"

void pascal score_delta_commit(void)
{
	while(score_delta > 0) {
		score_update_and_render();
	}
}

static int unused_6CAC[3]; // ZUN bloat

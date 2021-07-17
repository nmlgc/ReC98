/* ReC98
 * -----
 * 4th part of code segment #1 of TH05's MAIN.EXE
 */

#pragma option -zCmain_01_TEXT -zPmain_01

extern "C" {
#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "th01/math/area.hpp"
#include "th01/math/subpixel.hpp"
#include "th03/formats/cdg.h"
#include "th04/math/motion.hpp"
#include "th04/main/null.hpp"
#include "th04/main/score.h"
#include "th04/main/rank.hpp"
#include "th04/main/item/items.hpp"
#include "th04/main/stage/stage.hpp"
#include "th05/formats/bb.h"
#include "th05/main/playfld.hpp"
#include "th05/main/boss/boss.hpp"

#include "th04/main/boss/end.cpp"
#include "th04/main/boss/reset.cpp"
#include "th04/formats/bb_stage.c"
#include "th05/main/stage/setup.cpp"

void pascal score_delta_commit(void)
{
	while(score_delta > 0) {
		score_update_and_render();
	}
}

static int unused_6CAC[3];

}

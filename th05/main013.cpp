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
#include "th04/shared.hpp"
#include "th04/main/null.hpp"
#include "th04/main/rank.hpp"
#include "th04/main/item/items.hpp"
#include "th05/formats/bb.h"
#include "th05/main/boss/boss.hpp"

void pascal near playfield_fillm_32_0_320_192(void);
void pascal near playfield_fillm_0_0_384_192__2(void);
void pascal near playfield_fillm_0_205_384_163(void);
void pascal near playfield_fillm_64_56_256_256(void);
void pascal near playfield_fillm_0_0_384_192__1(void);
void pascal near playfield_fillm_0_104_384_192(void);

#include "th04/main/boss/end.cpp"
#include "th04/main/boss/reset.cpp"
#include "th04/formats/bb_stage.c"
#include "th05/main/stage/setup.cpp"

// Adds the entire score delta at once to the current score.
void pascal score_delta_commit(void)
{
	while(score_delta > 0) {
		score_update_and_render();
	}
}

static int unused_6CAC[3];

}

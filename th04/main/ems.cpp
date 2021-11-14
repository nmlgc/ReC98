#pragma option -zPmain_01

extern "C" {
#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "th03/formats/cdg.h"
#include "th04/common.h"
#include "th04/score.h"
#include "th04/main/playfld.hpp"
#include "th04/main/stage/stage.hpp"
#include "th04/main/rank.hpp"
#include "th04/sprites/main_cdg.h"
}
#if (GAME == 5)
	#include "th05/resident.hpp"
	#include "th05/shiftjis/fns.hpp"
#else
	#include "th04/resident.hpp"
	#include "th04/shiftjis/fns.hpp"
#endif
#include "th04/main/ems.hpp"

extern char *eyename;	/* ZUN symbol [MAGNet2010] */

inline void ems_write_cdg_color_planes(
	seg_t &handle, long offset, main_cdg_slot_t slot
) {
	ems_write(
		handle,
		offset,
		cdg_slots[slot].seg_colors(),
		(cdg_slots[slot].bitplane_size * PLANE_COUNT)
	);
}

void near ems_allocate_and_preload_eyecatch(void)
{
	#undef EMS_NAME
	extern const char EMS_NAME[];

	// Luckily, these assignments are also done later, and the game doesn't
	// rely on them inbetween.
	stage_id = resident->stage;
	if(stage_id == STAGE_EXTRA) {
		rank = RANK_EXTRA;
	} else {
		rank = resident->rank;
	}

	#if (GAME == 4)
		eyename[3] = ('0' + rank);
	#endif

	Ems = NULL;
	if(!ems_exist() || (ems_space() < EMSSIZE)) {
		return;
	}
	Ems = ems_allocate(EMSSIZE);
	if(Ems) {
		ems_setname(Ems, EMS_NAME);
		cdg_load_single_noalpha(CDG_EYECATCH, eyename, 0);
		ems_write_cdg_color_planes(Ems, EMS_EYECATCH_OFFSET, CDG_EYECATCH);
		cdg_free(CDG_EYECATCH);
	}
}

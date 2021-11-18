#pragma option -zPmain_01

extern "C" {
#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "th03/formats/cdg.h"
#include "th04/main/playfld.hpp"
#include "th04/sprites/main_cdg.h"
}
#include "th04/shiftjis/fns.hpp"
#include "th04/chars.h"
#include "th04/main/ems.hpp"
#include "th04/main/dialog/dialog.hpp"

void near dialog_init(void)
{
	#undef FACESET_REIMU_FN
	#undef FACESET_MARISA_FN
	#define FACESET_REIMU_FN FACESET_REIMU_FN_1
	#define FACESET_MARISA_FN FACESET_MARISA_FN_1
	extern const char FACESET_REIMU_FN[];
	extern const char FACESET_MARISA_FN[];

	cdg_free(CDG_BG_PLAYCHAR_BOMB);

	if(Ems) {
		uint32_t offset = EMS_FACESET_PLAYCHAR_OFFSET;
		size_t size = cdg_slots[CDG_FACESET_PLAYCHAR].bitplane_size;
		int slot = CDG_FACESET_PLAYCHAR;
		while(slot < (CDG_FACESET_PLAYCHAR_last + 1)) {
			allocate_and_load_from_ems(
				cdg_slots[slot].seg_alpha(), offset, size
			);
			offset += size;
			size *= PLANE_COUNT;
			allocate_and_load_from_ems(
				cdg_slots[slot].seg_colors(), offset, size
			);
			offset += size;
			size /= PLANE_COUNT;
			slot++;
		}
	} else {
		main_cdg_load_faceset_playchar();
	}
}

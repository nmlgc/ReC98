#pragma option -zPmain_01

#include "th04/main/dialog/shared.hpp"
#include <stddef.h>
#include "master.hpp"
extern "C" {
#include "th03/formats/cdg.h"
}
#include "th04/common.h"
#include "th04/main/stage/stage.hpp"
#include "th04/shiftjis/fns.hpp"
#include "th04/playchar.h"
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

void near dialog_exit(void)
{
	#undef BOMB_BG_REIMU_FN
	#undef BOMB_BG_MARISA_FN
	#undef FACESET_MUGETSU_DEFEAT_FN
	#undef FACESET_GENGETSU_DEFEAT_FN
	extern const char BOMB_BG_REIMU_FN[];
	extern const char BOMB_BG_MARISA_FN[];
	extern const char FACESET_MUGETSU_DEFEAT_FN[];
	extern const char FACESET_GENGETSU_DEFEAT_FN[];

	int i;

	for(i = CDG_FACESET_PLAYCHAR; i < (CDG_FACESET_PLAYCHAR_last + 1); i++) {
		cdg_free(i);
	}
	if(stage_id == STAGE_EXTRA) {
		// MODDERS: This assumes that BSS6.CD2, BSS7.CD2, and BSS8.CD2 each
		// have at most 3 slots, rather than up to FACESET_BOSS_COUNT.
		for(i = CDG_FACESET_BOSS; i < (CDG_FACESET_BOSS + 3); i++) {
			cdg_free(i);
		}

		// What's a function parameter? :zunpet:
		extern uint8_t number_of_calls_to_this_function_during_extra;
		if((number_of_calls_to_this_function_during_extra++) == 0) {
			cdg_load_all(CDG_FACESET_BOSS, FACESET_MUGETSU_DEFEAT_FN);
		} else {
			cdg_load_all(CDG_FACESET_BOSS, FACESET_GENGETSU_DEFEAT_FN);
		}
	}

	if(Ems) {
		playchar_bomb_bg_load_from_ems();
	} else {
		if(playchar == PLAYCHAR_REIMU) {
			cdg_load_single_noalpha(CDG_BG_PLAYCHAR_BOMB, BOMB_BG_REIMU_FN, 0);
		} else {
			cdg_load_single_noalpha(CDG_BG_PLAYCHAR_BOMB, BOMB_BG_MARISA_FN, 0);
		}
	}
}

#pragma option -zPmain_01

#include "th04/main/dialog/shared.hpp"
#include "th04/main/ems.hpp"
#include "th05/playchar.h"
#include "th05/formats/dialog.hpp"
#include "th05/sprites/main_pat.h"
#include "th05/shiftjis/fns.hpp"

#pragma option -a2

extern char faceset_boss_format[];
extern char faceset_playchar_format[];

void pascal near dialog_face_load_unput_put_free_8(
	screen_x_t left, vram_y_t top, int face_id
)
{
	size_t size;
	uint32_t offset;
	char near *faceset_fn = faceset_boss_format;
	char near *faceset_playchar_fn = faceset_playchar_format;

	if(face_id != FACE_NONE) {
		if(Ems) {
			if(dialog_side == SIDE_PLAYCHAR) {
				offset = EMS_FACESET_PLAYCHAR_OFFSET;
			} else {
				offset = EMS_FACESET_BOSS_OFFSET;
			}
			size = cdg_slots[CDG_DIALOG_FACE].bitplane_size;
			offset += (face_id * size * (PLANE_COUNT + 1));
			allocate_and_load_from_ems(
				cdg_slots[CDG_DIALOG_FACE].seg_alpha(), offset, size
			);
			offset += size;
			size *= PLANE_COUNT;
			allocate_and_load_from_ems(
				cdg_slots[CDG_DIALOG_FACE].seg_colors(), offset, size
			);
			offset += size;
		} else {
			if(dialog_side != SIDE_PLAYCHAR) {
				faceset_fn[3] = ('0' + stage_id);
			} else {
				faceset_fn = faceset_playchar_fn;
				faceset_fn[3] = ('0' + playchar);
			}
			cdg_load_single(CDG_DIALOG_FACE, faceset_fn, face_id);
		}
	}
	frame_delay(1);
	dialog_face_unput_8(left, top);
	if(face_id != FACE_NONE) {
		cdg_put_8(left, top, CDG_DIALOG_FACE);
		cdg_free(CDG_DIALOG_FACE);
	}
}

void near dialog_exit(void)
{
	#undef BOMB_BG_REIMU_FN
	#undef BOMB_BG_MARISA_FN
	#undef BOMB_BG_MIMA_FN
	#undef BOMB_BG_YUUKA_FN
	extern const char BOMB_BG_REIMU_FN[];
	extern const char BOMB_BG_MARISA_FN[];
	extern const char BOMB_BG_MIMA_FN[];
	extern const char BOMB_BG_YUUKA_FN[];

	if(Ems) {
		playchar_bomb_bg_load_from_ems();
	} else {
		switch(playchar) {
		case PLAYCHAR_REIMU:
			cdg_load_single_noalpha(CDG_BG_PLAYCHAR_BOMB, BOMB_BG_REIMU_FN, 0);
			break;
		case PLAYCHAR_MARISA:
			cdg_load_single_noalpha(CDG_BG_PLAYCHAR_BOMB, BOMB_BG_MARISA_FN, 0);
			break;
		case PLAYCHAR_MIMA:
			cdg_load_single_noalpha(CDG_BG_PLAYCHAR_BOMB, BOMB_BG_MIMA_FN, 0);
			break;
		case PLAYCHAR_YUUKA:
			cdg_load_single_noalpha(CDG_BG_PLAYCHAR_BOMB, BOMB_BG_YUUKA_FN, 0);
			break;
		}
	}
}

void near main_pat_exalice_override_and_super_clean_stage(void)
{
	#undef BOMB_SHAPE_FN
	#undef BOMB_SHAPE_YUUKA_FN
	#define BOMB_SHAPE_FN      	 BOMB_SHAPE_FN_2
	#define BOMB_SHAPE_YUUKA_FN	 BOMB_SHAPE_YUUKA_FN_2
	extern const char BOMB_SHAPE_FN[];
	extern const char BOMB_SHAPE_YUUKA_FN[];
	extern const char MIKO16_EXALICE_FN[];

	super_clean(TINY_MIKO16_START, PAT_MAX);
	super_entry_bfnt(MIKO16_EXALICE_FN);
	for(int i = TINY_MIKO16_START; i < TINY_MIKO16_END; i++) {
		super_convert_tiny(i);
	}
	main_pat_bomb_shape_load();
}

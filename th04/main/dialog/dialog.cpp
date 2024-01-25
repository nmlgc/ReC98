#pragma option -zPmain_01

#include "th04/formats/dialog.hpp"
#include "th04/main/dialog/shared.cpp"
#include "decomp.hpp"
#include "th04/main/ems.hpp"
#include "th04/main/tile/tile.hpp"
#include "th04/sprites/main_pat.h"
#include "th04/shiftjis/fns.hpp"

#define script_p dialog_p
#include "th03/formats/script.hpp"

// Called with [dialog_p] at the character past [c].
script_ret_t pascal near dialog_op(unsigned char c)
{
	// ZUN quirk: All commands that affect the graphics layer are preceded by a
	// 1-frame delay. This was likely done because dialogs are single-buffered,
	// and prevents tearing on the first frame by ensuring that the CRT beam
	// has returned to the top-left corner before any pixels are changed.

	int i;
	int p1;
	screen_x_t left;
	screen_y_t top;

	// ZUN bloat: PF_FN_LEN on its own is enough, it already includes the \0
	// terminator.
	char fn[PF_FN_LEN + 3];

	c = tolower(c);
	switch(c) {
	case 'n':
		dialog_op_linebreak();
		break;

	case 't':
		// ZUN bloat: Copy-pasted from the TH03 cutscene script parser, and not
		// used in any of TH04's original scripts.
		script_param_read_number_first(p1, 100);
		frame_delay(1);
		palette_settone(p1);
		break;

	case 'f':
		// ZUN bloat: Copy-pasted from the TH03 cutscene script parser, and not
		// used in any of TH04's original scripts.
		c = *dialog_p;
		if((c == 'i') || (c == 'o')) {
			script_op_fade(c, palette_black_in, palette_black_out, p1);
		}
		break;

	case 'w':
		c = *dialog_p;
		if((c == 'i') || (c == 'o')) {
			script_op_fade(c, palette_white_in, palette_white_out, p1);
		}
		break;

	case 'g':
		if(*dialog_p != 'a') {
			// Actually used at the end of the dialog shown before the Bad
			// Ending.
			script_op_shake(false, i, p1);
		} else {
			dialog_p++;
			script_param_read_number_first(p1, 0);
			dialog_op_gaiji(p1);
		}
		break;

	case 'k':
		// ZUN bloat: Copy-pasted from the TH03 cutscene script parser, and not
		// used in any of TH04's original scripts.
		script_param_read_number_first(p1, 0);
		input_wait_for_change(p1);
		break;

	case '=':
		script_param_read_number_first(p1, 1);
		frame_delay(1);
		if(dialog_side == SIDE_PLAYCHAR) {
			dialog_face_unput_8(FACE_PLAYCHAR_LEFT, FACE_PLAYCHAR_TOP);
			if(p1 != 255) {
				p1 += CDG_FACESET_PLAYCHAR;
				cdg_put_8(FACE_PLAYCHAR_LEFT, FACE_PLAYCHAR_TOP, p1);
			}
		} else {
			dialog_face_unput_8(FACE_BOSS_LEFT, FACE_BOSS_TOP);
			if(p1 != 255) {
				p1 += CDG_FACESET_BOSS;
				cdg_put_8(FACE_BOSS_LEFT, FACE_BOSS_TOP, p1);
			}
		}
		break;

	case 'b':
		script_param_read_number_first(left, 0);
		script_param_read_number_second(top);
		script_param_read_number_second(p1);
		frame_delay(1);
		super_roll_put(left, top, p1);
		break;

	case 'm':
		// TH04's implementation of snd_load() automatically stops any playing
		// BGM, so it's not necessary here.
		// ZUN bloat: '$' and '*' are not used in any of TH04's original
		// scripts.
		script_op_bgm(false, c, fn, p1);
		break;

	// ZUN bloat: Copy-pasted from the TH03 cutscene script parser, and not
	// used in any of TH04's original scripts.
	case 'e':
		script_param_read_number_first(p1);
		snd_se_play_force(p1);
		break;

	case 'c':
		dialog_op_super_clean_stage();
		break;

	case 'l':
		// ZUN landmine: See the comment about manual sprite memory management
		// for dialog_op_super_clean_stage().
		c = *script_p;
		if(c == ',') {
			script_p++;
			script_param_read_fn(fn, p1, c);
			super_entry_bfnt(fn);
		}
		break;

	case 'd': {
		// The only .CDG slot not covered here is CDG_BG_PLAYCHAR_BOMB, which
		// was freed before in dialog_init().
		for(int i = CDG_PER_STAGE; i < CDG_COUNT; i++) {
			cdg_free(i);
		}
		break;
	}

	case '$':
		input_wait_for_change(0);
		return STOP;

	case '#':
		return STOP;
	}
	return CONTINUE;
}

void near dialog_run(void)
{
	unsigned char c;

	// ZUN bloat: An obvious remnant from the cutscene code introduced in TH03;
	// unused here.
	uint8_t speedup_cycle;

	extern shiftjis_t near dialog_kanji_buf[];
	shiftjis_t* kanji_str = dialog_kanji_buf;

	while(1) {
		// Same iteration code as in TH03's cutscene system.
		c = *(dialog_p++);
		if(str_sep_control_or_space(c)) {
			continue;
		}

		// Opcode?
		if(c == '\\') {
			c = *(dialog_p++);
			if(dialog_op(c) == STOP) {
				break;
			}
			continue;
		} else if((c == '0') || (c == '1')) {
			// Start a new dialog box by clearing it and rewinding the cursor
			if(c == '0') {
				dialog_cursor.x = to_dialog_x(TEXT_PLAYCHAR_LEFT);
				dialog_cursor.y = to_dialog_y(TEXT_PLAYCHAR_TOP);
				dialog_side = SIDE_PLAYCHAR;
			} else {
				dialog_cursor.x = to_dialog_x(TEXT_BOSS_LEFT);
				dialog_cursor.y = to_dialog_y(TEXT_BOSS_TOP);
				dialog_side = SIDE_BOSS;
			}

			dialog_box_wipe(dialog_cursor.x, dialog_cursor.y);
			speedup_cycle = 0;

			// Box loop
			while(1) {
				// ZUN bug: This would have only been necessary before, or,
				// better yet, inside dialog_delay(). It should have also been
				// the equivalent of TH05's input_reset_sense_held() instead,
				// which would have addressed the hardware quirk documented in
				// the `Research/HOLDKEY` example. Y'know, just to ensure that
				// held keys are always recognized as such, and don't cause a
				// sporadic 2-frame delay before the text is displayed
				// completely after all.
				input_reset_sense();

				// Again, same iteration code as in TH03's cutscene system.
				c = *(dialog_p++);
				if(str_sep_control_or_space(c)) {
					continue;
				}

				// Opcode?
				if(c == '\\') {
					c = *(dialog_p++);
					if(dialog_op(c) == STOP) {
						break;
					}
					continue;
				}

				// Regular kanji
				kanji_str[0] = c;
				c = *dialog_p;
				kanji_str[1] = c;
				dialog_p++;
				dialog_text_put(kanji_str);
				dialog_delay(speedup_cycle);
			}
		}
	}
	overlay_wipe();
}

void dialog_animate(void)
{
	dialog_init();
	dialog_pre();
	dialog_run();

	/* TODO: Replace with the decompiled call
	 * 	tiles_activate_and_render_all_for_next_N_frames(2);
	 * once that function is part of the same segment */
	_asm {
		push	2;
		nop;
		push 	cs;
		call	near ptr tiles_activate_and_render_all_for_next_N_frames;
	}

	dialog_exit();
	dialog_post();
}

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

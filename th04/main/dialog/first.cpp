#include "th04/main/dialog/shared.cpp"
#include "decomp.hpp"
#include "th04/formats/dialog.hpp"
#include "th04/main/tile/tile.hpp"
#include "th04/sprites/main_pat.h"

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

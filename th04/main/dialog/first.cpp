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

// Function ordering fails
// -----------------------

// Replaces the super_*() sprites loaded from MIKO16.BFT with the ones from
// ST06_16.BFT used in the EX-Alice fight, in addition to clearing all
// stage-specific sprites.
void near main_pat_exalice_override_and_super_clean_stage(void);
// -----------------------

#include <string.h>
#include "th04/main/dialog/shared.cpp"
#include "th05/playchar.h"
#include "th05/formats/dialog.hpp"
#include "th05/main/dialog/dialog.hpp"
#include "th05/sprites/main_pat.h"

#pragma option -a2

// Called with [dialog_p] at the character past [c]. Returns, um… whether the
// corresponding operation is allowed to be used while printing a box of text?
// ZUN landmine: This should have only returned `false` for values of [c] that
// don't correspond to commands. As a result, the `true`-returning gaiji and
// line break commands are the only ones that can be used within the box loop.
// For all other commands, the box loop will then also interpret [c] as a
// Shift-JIS lead byte and write it to TRAM, followed by what's next in
// [dialog_p] after this function returned. The text chip will then render [c]
// using the control character glyphs from the PC-98 font ROM.
bool pascal near dialog_op(uint8_t c)
{
	screen_x_t left;
	screen_y_t top;
	const unsigned char* fn;

	switch(c) {
	case 0x00:
		dialog_cursor.x = to_dialog_x(TEXT_PLAYCHAR_LEFT);
		dialog_cursor.y = to_dialog_y(TEXT_PLAYCHAR_TOP);
		dialog_side = SIDE_PLAYCHAR;
		break;

	case 0x01:
		dialog_cursor.x = to_dialog_x(TEXT_BOSS_LEFT);
		dialog_cursor.y = to_dialog_y(TEXT_BOSS_TOP);
		dialog_side = SIDE_BOSS;
		break;

	case 0x02:
		c = *(dialog_p++);

		// ZUN quirk: dialog_face_load_unput_put_free_8() already has a 1-frame
		// delay.
		frame_delay(1);

		if(dialog_side == SIDE_PLAYCHAR) {
			dialog_face_load_unput_put_free_8(
				FACE_PLAYCHAR_LEFT, FACE_PLAYCHAR_TOP, c
			);
		} else {
			dialog_face_load_unput_put_free_8(FACE_BOSS_LEFT, FACE_BOSS_TOP, c);
		}
		break;

	case 0x03:
		// ZUN landmine: See the comment about manual sprite memory management
		// for dialog_op_super_clean_stage().
		fn = reinterpret_cast<const unsigned char *>(dialog_p);
		super_entry_bfnt(fn);
		dialog_p += (strlen(fn) + 1);
		break;

	case 0x04:
		if(stage_id != STAGE_EXTRA) {
			dialog_op_super_clean_stage();
		} else {
			main_pat_exalice_override_and_super_clean_stage();
		}
		break;

	case 0x05:
		fn = reinterpret_cast<const unsigned char *>(dialog_p);
		if(fn[0] == '$') {
			snd_kaja_func(KAJA_SONG_STOP, 0);
		} else {
			// TH05's implementation of snd_load() automatically stops any
			// playing BGM, so it's not necessary here.
			snd_load(fn, SND_LOAD_SONG);
			snd_kaja_func(KAJA_SONG_PLAY, 0);
		}
		dialog_p += (strlen(fn) + 1);
		break;

	case 0x06:
		left = reinterpret_cast<tx2_op_06_params *>(dialog_p)->left;
		top = reinterpret_cast<tx2_op_06_params *>(dialog_p)->top;
		c = reinterpret_cast<tx2_op_06_params *>(dialog_p)->patnum;
		dialog_p += sizeof(tx2_op_06_params);
		super_roll_put(left, top, c);
		break;

	case 0x09:
		dialog_box_wipe(
			to_dialog_x(TEXT_BOSS_LEFT), to_dialog_y(TEXT_BOSS_TOP)
		);
		dialog_box_wipe(
			to_dialog_x(TEXT_PLAYCHAR_LEFT), to_dialog_y(TEXT_PLAYCHAR_TOP)
		);
		c = *(dialog_p++);
		palette_white_out(c);
		break;

	case 0x0A:
		c = *(dialog_p++);
		palette_white_in(c);
		break;

	case 0x0B: // That's one after the ASCII \n! Boo!
		dialog_op_linebreak();
		return true;

	case 0x0C:
		c = *(dialog_p++);
		dialog_op_gaiji(c);
		return true;

	case 0x0D:
		return true;

	case 0x0E:
		dialog_box_wipe(dialog_cursor.x, dialog_cursor.y);
		break;
	}
	return false;
}

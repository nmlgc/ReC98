#pragma option -zPmain_01

// Function ordering fails
// -----------------------

// Replaces the super_*() sprites loaded from MIKO16.BFT with the ones from
// ST06_16.BFT used in the EX-Alice fight, in addition to clearing all
// stage-specific sprites.
void near main_pat_exalice_override_and_super_clean_stage(void);
// -----------------------

#include <string.h>
#include "th02/main/execl.hpp"
#include "th04/main/dialog/shared.cpp"
#include "th04/main/demo.hpp"
#include "th04/main/ems.hpp"
#include "th05/resident.hpp"
#include "th05/formats/dialog.hpp"
#include "th05/main/dialog/dialog.hpp"
#include "th05/sprites/main_pat.h"
#include "th05/shiftjis/fns.hpp"

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

void near dialog_run(void)
{
	uint8_t c;

	// ZUN bloat: An obvious remnant from the cutscene code introduced in TH03;
	// unused here.
	uint8_t speedup_cycle;

	extern shiftjis_t near dialog_kanji_buf[];
	shiftjis_t* kanji_str = dialog_kanji_buf;

	while(1) {
		c = *(dialog_p++);
		if(c == 0xFF) {
			break;
		} else if(c == 0x0D) {
			// Start a new dialog box by clearing it and rewinding the cursor.
			// TH04 features separate '0' or '1' commands that include the side
			// in the command itself, whereas TH05 requires the script to use
			// separate 0x00 or 0x01 commands before this one. Thankfully, the
			// original scripts always call these before the first 0x0D command
			// and don't rely on [dialog_side]'s initial zero value.
			if(dialog_side == SIDE_PLAYCHAR) {
				dialog_cursor.x = to_dialog_x(TEXT_PLAYCHAR_LEFT);
				dialog_cursor.y = to_dialog_y(TEXT_PLAYCHAR_TOP);
			} else {
				dialog_cursor.x = to_dialog_x(TEXT_BOSS_LEFT);
				dialog_cursor.y = to_dialog_y(TEXT_BOSS_TOP);
			}

			// Technically, this only needs to be done for the other box
			// because the new one is immediately wiped below, but who cares.
			text_boxfilla(
				to_tram_x(to_dialog_x(TEXT_PLAYCHAR_LEFT)),
				to_tram_y(to_dialog_y(TEXT_PLAYCHAR_TOP)),
				to_tram_x(to_dialog_x(TEXT_PLAYCHAR_LEFT + TEXT_W)),
				to_tram_y(to_dialog_y(TEXT_PLAYCHAR_TOP + BOX_H)),
				TX_BLUE
			);
			text_boxfilla(
				to_tram_x(to_dialog_x(TEXT_BOSS_LEFT)),
				to_tram_y(to_dialog_y(TEXT_BOSS_TOP)),
				to_tram_x(to_dialog_x(TEXT_BOSS_LEFT + TEXT_W)),
				to_tram_y(to_dialog_y(TEXT_BOSS_TOP + BOX_H)),
				TX_BLUE
			);

			dialog_box_wipe(dialog_cursor.x, dialog_cursor.y);
			speedup_cycle = 0;

			// Box loop
			while(1) {
				// ZUN bloat: This would have only been necessary before, or,
				// better yet, inside dialog_delay(). It should have also been
				// input_reset_sense_held() instead, which would have addressed
				// the hardware quirk documented in the `Research/HOLDKEY`
				// example. Y'know, just to ensure that held keys are always
				// recognized as such, and don't cause a sporadic 2-frame delay
				// before the text is displayed completely after all.
				input_reset_sense();

				c = *(dialog_p++);
				// End of text box?
				if(c == 0xFF) {
					input_wait_for_change(0);
					break;
				} else if(!dialog_op(c)) {
					// Regular kanji
					kanji_str[0] = c;
					kanji_str[1] = *(dialog_p++);
					dialog_text_put(kanji_str);

					// ZUN bug: Is this supposed to be the second input sensing
					// call that addresses the aforementioned hardware quirk?
					// In most cases, this won't ever change the value of
					// [key_det] compared to the above call as it will take the
					// target hardware of this game much less than the PC-98
					// keyboard UART delay of ≈0.6ms to run from the above call
					// to this one. This call can only ever make a difference
					// if this box loop happens to run on a particularly
					// unlucky UART cycle where the value *did* change in the
					// meantime.
					input_sense();

					dialog_delay(speedup_cycle);
				}
			}
		} else {
			dialog_op(c);
		}
	}
	overlay_wipe();
}

void dialog_animate(void)
{
	// If we get here during a replay, we assume it's the hidden Extra Stage
	// one because it's the only one that's long enough, and then skip the
	// dialog.
	// You might argue that this is gross and ZUN should have just added a
	// proper skip feature that would still run through the script for its side
	// effects, but the only bad aspect I can see is that this happens here and
	// not at the call site. In regular gameplay, the (hardcoded) boss render
	// functions rely on the dialog scripts for loading their sprites at the
	// intended patnums, so it would have made much more sense to hardcode all
	// of these load calls and completely remove the dependency on game data.
	if(resident->demo_num != 0) {
		extern int8_t dialog_sequence_id;
		if(dialog_sequence_id == 0) {
			// Pre-boss. Replicate all asset load calls that would be done if
			// `_DM06.TX2` would run normally, ...
			#undef BGM_EXTRA_BOSS_FN
			#undef DEMO_EXTRA_PART_2_FN
			extern const char st06_bb1[];
			extern const char st06_bb2[];
			extern const char BGM_EXTRA_BOSS_FN[];
			extern const char DEMO_EXTRA_PART_2_FN[];

			main_pat_exalice_override_and_super_clean_stage();
			super_entry_bfnt(st06_bb1);
			super_entry_bfnt(st06_bb2);
			snd_load(BGM_EXTRA_BOSS_FN, SND_LOAD_SONG);
			snd_kaja_func(KAJA_SONG_PLAY, 0);

			// ... then load the second half of the replay.
			// ZUN bloat: This could have definitely been integrated into
			// demo_load(), including the avoided reallocation.
			file_ropen(DEMO_EXTRA_PART_2_FN);
			file_read(DemoBuf, (DEMO_N_EXTRA * sizeof(REC<1>)));
			file_close();
			stage_frame = 0; // This is actually the index into [DemoBuf].
			dialog_sequence_id++;
		} else {
			// Post-boss. Just return to the title screen.
			#undef BINARY_OP
			#define BINARY_OP DIALOG_BINARY_OP
			extern const char BINARY_OP[];
			demo_end();
		}
		return;
	}

	cdg_free(CDG_BG_PLAYCHAR_BOMB); // "dialog_init()"
	dialog_pre();
	dialog_run();
	dialog_exit();
	dialog_post();
}

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

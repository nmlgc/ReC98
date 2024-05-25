#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "libs/master.lib/master.hpp"
#include "libs/master.lib/pc98_gfx.hpp"
#include "th01/rank.h"
#include "th02/hardware/frmdelay.h"
#include "th02/core/initexit.h"
#include "th04/end/end.h"
#include "th05/formats/pi.hpp"
#include "th05/op/op.hpp"
#include "th05/hardware/input.h"
#include "th04/op/start.hpp"

#define resident_reset_last_highest_and_stage_scores() \
	int digit; \
	int stage; \
	for(digit = 0; digit < SCORE_DIGITS; digit++) { \
		resident->score_last.digits[digit] = 0; \
		resident->score_highest.digits[digit] = 0; \
		\
		for(stage = 0; stage < MAIN_STAGE_COUNT; stage++) { \
			resident->stage_score[stage].digits[digit] = 0; \
		} \
	}

#define resident_reset_last_and_highest_scores() \
	for(int digit = 0; digit < SCORE_DIGITS; digit++) { \
		resident->score_last.digits[digit] = 0; \
		resident->score_highest.digits[digit] = 0; \
	}

void near start_game(void)
{
	resident->end_sequence = ES_SCORE;
	resident->demo_num = 0;
	resident->stage = 0;
	resident->credit_lives = resident->cfg_lives;
	resident->credit_bombs = resident->cfg_bombs;

	if(playchar_menu()) {
		return;
	}
	resident_reset_last_highest_and_stage_scores();
	op_exit_into_main(true, true);
}

void near start_extra(void)
{
	resident->demo_num = 0;
	resident->stage = STAGE_EXTRA;
	resident->credit_lives = 3;
	resident->credit_bombs = 3;

	if(playchar_menu()) {
		return;
	}
	resident_reset_last_highest_and_stage_scores();
	op_exit_into_main(true, false);
}

void near start_demo(void)
{
	resident->end_sequence = ES_SCORE;
	resident->stage = 0;
	resident->credit_lives = 3;
	resident->credit_bombs = 3;

	resident->demo_num++;
	if(resident->demo_num > 4) {
		resident->demo_num = 1;
	}

	// Hidden Extra Stage Clear replay easter egg...
	if(key_det == (INPUT_LEFT | INPUT_RIGHT)) {
		// MODDERS: Loop over the characters instead.
		if(
			extra_playable_with[PLAYCHAR_REIMU] &&
			extra_playable_with[PLAYCHAR_MARISA] &&
			extra_playable_with[PLAYCHAR_MIMA] &&
			extra_playable_with[PLAYCHAR_YUUKA]
		) {
			resident->demo_num = 5;
		} else {
			resident->demo_num = 0;
			return;
		}
	}
	switch(resident->demo_num) {
	case 1:
		resident->playchar = PLAYCHAR_REIMU;
		resident->demo_stage = 3;
		break;
	case 2:
		resident->playchar = PLAYCHAR_MARISA;
		resident->demo_stage = 1;
		break;
	case 3:
		resident->playchar = PLAYCHAR_MIMA;
		resident->demo_stage = 2;
		break;
	case 4:
		resident->playchar = PLAYCHAR_YUUKA;
		resident->demo_stage = 4;
		break;
	case 5:
		resident->playchar = PLAYCHAR_MIMA;
		resident->demo_stage = STAGE_EXTRA;
		snd_kaja_func(KAJA_SONG_FADE, 8);
		break;
	}
	resident_reset_last_and_highest_scores();
	main_cdg_free();
	cfg_save();
	palette_black_out(1);
	game_exit();
	execl(BINARY_MAIN, BINARY_MAIN, 0, 0);
}

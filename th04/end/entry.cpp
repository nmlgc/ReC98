#include <process.h>
#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "libs/kaja/kaja.h"
#include "th01/rank.h"
#include "th02/hardware/frmdelay.h"
extern "C" {
#include "th03/formats/cdg.h"
}
#if (GAME == 4)
	#include "th03/formats/pi.hpp"
	#include "th04/hardware/input.h"
#endif
#include "th03/formats/cfg_impl.hpp"
#include "th03/core/initexit.h"
#include "th03/cutscene/cutscene.hpp"
#include "th04/score.h"
extern "C" {
#include "th04/snd/snd.h"
}
#include "th04/end/end.h"
#include "th04/end/staff.hpp"
#include "th04/end/verdict.hpp"
#include "th04/hiscore/regist.hpp"
#if (GAME == 5)
	#include "th04/shiftjis/fnshared.hpp"
	#include "th05/mem.h"
	#include "th05/resident.hpp"
	#include "th05/shiftjis/fns.hpp"
	#include "th05/end/allcast.hpp"
#else
	#include "th03/shiftjis/fnshared.hpp"
	#include "th04/mem.h"
	#include "th04/resident.hpp"
	#include "th04/shiftjis/fns.hpp"
#endif

resident_t far* resident;

// ZUN bloat: Should be its own translation unit.
resident_t __seg* near cfg_load_resident_ptr(void)
{
	cfg_t cfg;
	return cfg_load_and_set_resident(cfg, CFG_FN);
}

void pascal near game_exit_and_exec(char* fn)
{
	cdg_free_all();
	graph_hide();
	text_clear();
	#if (GAME != 5)
		gaiji_restore();
	#endif
	game_exit();
	execl(fn, fn, nullptr);
}

void near end_animate(void)
{
	#if (GAME == 5)
		static char* SCRIPT_FN = "_ED00.TXT";
		if(resident->end_sequence == ES_BAD) {
			SCRIPT_FN[3] = '0';
		} else if(resident->end_sequence == ES_EXTRA) {
			SCRIPT_FN[3] = '2';
		} else  {
			SCRIPT_FN[3] = '1';
		}
		SCRIPT_FN[4] = ('0' + resident->playchar);
	#else
		static char* SCRIPT_FN = "_ED000.TXT";
		SCRIPT_FN[3] = resident->playchar_ascii;
		SCRIPT_FN[4] = ('0' + resident->shottype);
		SCRIPT_FN[5] = resident->end_type_ascii;
	#endif
	cutscene_script_load(SCRIPT_FN);
	cutscene_animate();
	cutscene_script_free();
}

#define congratulations_animate(pic_fn) { \
	/* \
	 * ZUN bloat: The hardware palette is entirely black when we get here, and \
	 * we don't flip any pages, so the picture could have been just blitted to \
	 * VRAM page #0. \
	 * (Would have also been nice to add a palette_black() call here, as an \
	 * assert() of sorts.) \
	 */ \
	graph_accesspage(1); \
	pi_fullres_load_palette_apply_put_free(0, pic_fn); \
	graph_copy_page(0); \
	\
	palette_black_in(1); \
	input_wait_for_change(0); \
	palette_black_out(4); \
}

inline void delay_then_regist_menu(void) {
	#if (GAME == 4)
		frame_delay(100);
	#endif
	regist_menu();
}

void main(void)
{
	#if (GAME == 4)
		char* congratulations_pic_fn = "CONG00.pi";
	#endif

	if(!cfg_load_resident_ptr()) {
		return;
	}

	#if (GAME == 4)
		congratulations_pic_fn[4] = resident->playchar_ascii;
	#endif

	mem_assign_paras = MEM_ASSIGN_PARAS_MAINE;
	game_init_main(OP_AND_END_PF_FN);
	#if (GAME == 4)
		gaiji_backup();
		gaiji_entry_bfnt(GAIJI_FN);
	#endif
	snd_determine_modes(resident->bgm_mode, resident->se_mode);
	#if (GAME == 5)
		snd_load(SE_FN, SND_LOAD_SE);
		graph_show();
		random_seed = resident->rand;
		frame_delay(100);
	#else
		graph_show();
	#endif

	static_assert(ES_GOOD > ES_BAD);
	if(resident->end_sequence >= ES_BAD) {
		end_animate();
		staffroll_animate();
		#if (GAME == 4)
			verdict_animate();

			// The rank condition causes the congratulation image to be shown
			// for the enforced Bad Ending after clearing Stage 5 on Easy Mode,
			// regardless of whether the player continued or not. You might
			// consider it a quirk to show 「EASY ALL CLEAR!!」 for a ≥2CC, but
			// 「Try to Normal Rank!!」 could very well be ZUN's roundabout way
			// of implying "because this is how you avoid the Bad Ending".
			if(
				(resident->end_sequence == ES_GOOD) ||
				(resident->rank == RANK_EASY)
			) {
				congratulations_pic_fn[5] += resident->rank;
				congratulations_animate(congratulations_pic_fn);
			}
			snd_kaja_func(KAJA_SONG_FADE, 4);
		#endif
		delay_then_regist_menu();
	} else if(resident->end_sequence == ES_EXTRA) {
		#if (GAME == 5)
			end_animate();
			allcast_animate();
			verdict_animate();
			delay_then_regist_menu();
		#else
			delay_then_regist_menu();
			congratulations_pic_fn[5] = ('0' + RANK_EXTRA);
			palette_black();
			congratulations_animate(congratulations_pic_fn);
			verdict_animate();
		#endif
	} else { // resident->end_sequence == ES_SCORE
		delay_then_regist_menu();
		verdict_animate();
	}
	snd_kaja_func(KAJA_SONG_FADE, 4);
	game_exit_and_exec(BINARY_OP);
}

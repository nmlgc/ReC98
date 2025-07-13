#include <process.h>
#include "libs/master.lib/pc98_gfx.hpp"
#include "th01/rank.h"
#include "th01/pc98/entry.hpp"
#include "th02/hardware/frmdelay.h"
#include "th03/formats/cdg.h"
#if (GAME == 4)
#include "platform/grp_surf.hpp"
#include "th04/hardware/input.h"
#endif
#include "th03/formats/cfg_impl.hpp"
#include "th03/core/initexit.h"
#include "th03/cutscene/cutscene.hpp"
#include "th04/snd/snd.h"
#include "th04/end/end.h"
#include "th04/end/staff.hpp"
#include "th04/end/verdict.hpp"
#include "th04/hiscore/regist.hpp"
#if (GAME == 5)
#include "th04/shiftjis/fnshared.hpp"
#include "th05/resident.hpp"
#include "th05/shiftjis/fns.hpp"
#include "th05/end/allcast.hpp"
#else
#include "th03/shiftjis/fnshared.hpp"
#include "th04/resident.hpp"
#include "th04/shiftjis/fns.hpp"
#endif

#if (GAME == 5)
resident_t far* resident;
#endif

// ZUN bloat: Should be its own translation unit.
resident_t __seg* near cfg_load_resident_ptr(void)
{
	cfg_t cfg;
	return cfg_load_and_set_resident(cfg, CFG_FN);
}

#if (GAME == 5)
void pascal near game_exit_and_exec(char* fn)
#else
void pascal near game_exit_and_exec(entrypoint_t entrypoint)
#endif
{
	cdg_free_all();
	graph_hide();
	text_clear();
#if (GAME != 5)
	gaiji_restore();
#endif
	game_exit();
#if (GAME == 5)
	execl(fn, fn, nullptr);
#else
	entrypoint_exec(entrypoint);
#endif
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

#if (GAME == 4)
static void congratulations_animate(rank_t rank)
{
	char* pic_fn = "CONG00.pi";
	pic_fn[4] = resident->playchar_ascii;
	pic_fn[5] = ('0' + rank);

	palette_settone(0);
	graph_accesspage(0);
	GrpSurface_BlitBackgroundPI(&Palettes, pic_fn);
	palette_black_in(1);
	input_wait_for_change(0);
	palette_black_out(4);
}
#endif

inline void delay_then_regist_menu(void) {
#if (GAME == 4)
	frame_delay(100);
#endif
	regist_menu();
}

#if (GAME == 5)
int main(void)
#else
int main_cutscene(int, const char *[])
#endif
{
	if(!cfg_load_resident_ptr()) {
		return 1;
	}

	mem_assign_paras = (336000 >> 4);
	game_init_main(OP_AND_END_PF_FN);
#if (GAME == 4)
	gaiji_backup();
	gaiji_entry_bfnt(GAIJI_FN);
#endif
	snd_determine_modes(resident->bgm_mode, resident->se_mode);
#if (GAME == 5)
	extern bool in_maine;
	in_maine = true;
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
#if (GAME == 5)
		staffroll_animate_with_verdict_bitmap_on_heap();
#else
		staffroll_animate();
#endif
#if (GAME == 4)
		verdict_animate();

		// The rank condition causes the congratulation image to be shown for
		// the enforced Bad Ending after clearing Stage 5 on Easy Mode,
		// regardless of whether the player continued or not. You might
		// consider it a quirk to show 「EASY ALL CLEAR!!」 for a ≥2CC, but
		// 「Try to Normal Rank!!」 could very well be ZUN's roundabout way of
		// implying "because this is how you avoid the Bad Ending".
		if(
			(resident->end_sequence == ES_GOOD) || (resident->rank == RANK_EASY)
		) {
			congratulations_animate(static_cast<rank_t>(resident->rank));
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
		congratulations_animate(RANK_EXTRA);
		verdict_animate();
#endif
	} else { // resident->end_sequence == ES_SCORE
		delay_then_regist_menu();
		verdict_animate();
	}
	snd_kaja_func(KAJA_SONG_FADE, 4);
#if (GAME == 5)
	game_exit_and_exec(BINARY_OP);
#else
	game_exit_and_exec(EP_OP);
#endif

	return 0;
}

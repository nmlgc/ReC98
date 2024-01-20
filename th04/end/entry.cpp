#include <process.h>
#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
extern "C" {
#include "th03/formats/cdg.h"
}
#include "th03/formats/cfg_impl.hpp"
#include "th03/core/initexit.h"
#include "th03/cutscene/cutscene.hpp"
#include "th04/score.h"
#include "th04/end/end.h"
#if (GAME == 5)
	#include "th04/shiftjis/fnshared.hpp"
	#include "th05/resident.hpp"
	#include "th05/shiftjis/fns.hpp"
#else
	#include "th04/resident.hpp"
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
		static char* SCRIPT_FN = "_ED00.TXT\0" OP_AND_END_PF_FN "\0" SE_FN;
		if(resident->end_sequence == ES_CONTINUED) {
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

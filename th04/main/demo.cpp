#include <stddef.h>
#include "platform.h"
#include "master.hpp"
#include "th02/main/execl.hpp"
#include "th04/score.h"
#include "th04/hardware/inputvar.h"
#include "th04/main/frames.h"
#include "th04/main/demo.hpp"
#if (GAME == 5)
	#include "th04/common.h"
	#include "th05/mem.h"
	#include "th05/resident.hpp"
#else
	#include "th04/mem.h"
	#include "th04/resident.hpp"
#endif

void near DemoPlay(void)
{
	extern const char DEMO_OP[];

	#if (GAME == 5)
		size_t shift_offset = (resident->demo_num <= 4) ? DEMO_N : DEMO_N_EXTRA;
	#else
		#define shift_offset DEMO_N
	#endif

	// In TH04, replay playback ends by pressing anything. In TH05, only the
	// non-movement inputs (shot, bomb, cancel, OK, and Q) work.
	if(
		((GAME == 5) && ((key_det & ~INPUT_MOVEMENT) == 0)) ||
		((GAME == 4) && (key_det == INPUT_NONE))
	) {
		key_det = DemoBuf[stage_frame];
		shiftkey = DemoBuf[stage_frame + shift_offset];
		if(
			((GAME == 5) && (resident->demo_num > 4)) ||
			(stage_frame < (DEMO_N - 4))
		) {
			return;
		}
	}
	HMem<uint8_t>::free(DemoBuf);
	palette_black_out((GAME == 5) ? 8 : 10);
	/* TODO: Replace with the decompiled call
	 * 	GameExecl(DEMO_OP);
	 * once that function is part of the same segment */
	_asm {
		push	ds;
		push	offset DEMO_OP;
		nop;
		push 	cs;
		call	near ptr GameExecl;
	}
}

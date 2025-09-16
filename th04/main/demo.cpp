#include "libs/master.lib/master.hpp"
#include "libs/master.lib/pc98_gfx.hpp"
#include "th02/main/execl.hpp"
#include "th04/hardware/inputvar.h"
#include "th04/main/frames.h"
#include "th04/main/demo.hpp"
#if (GAME == 5)
#include "th05/resident.hpp"
#else
#include "th04/resident.hpp"
#endif

void near demo_load(void)
{
#if (GAME == 5)
	size_t size = ((resident->demo_num <= 4)
		? sizeof(REC<DEMO_N>)
		: sizeof(REC<DEMO_N_EXTRA>)
	);
#else
	#define size sizeof(REC<DEMO_N>)
#endif

	extern char near demo_fn[];
	DemoBuf = static_cast<uint8_t *>(hmem_allocbyte(size));
	char* fn = demo_fn;
	fn[4] = ('0' - (GAME == 5) + resident->demo_num);

	file_ropen(fn);
	file_read(DemoBuf, size);
	file_close();
}

void near DemoPlay(void)
{
	#undef BINARY_OP
	#define BINARY_OP DEMOPLAY_BINARY_OP
	extern const char BINARY_OP[];

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
	demo_end();
}

#pragma option -zCSHARED

extern "C" {
#include "platform.h"
#include "x86real.h"
#include "libs/kaja/kaja.h"
#if (GAME >= 4)
	#include "th04/snd/snd.h"
#else
	#include "th02/snd/snd.h"
#endif

int16_t DEFCONV snd_kaja_interrupt(int16_t ax)
{
	if(snd_bgm_active()) {
		_AX = ax;
		if(snd_bgm_is_fm()) {
			geninterrupt(PMD);
		} else {
			geninterrupt(MMD);
		}
	}
	return _AX;
}

}

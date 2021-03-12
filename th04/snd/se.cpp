#pragma codeseg SHARED_
#pragma option -k-

extern "C" {
#include "platform.h"
#include "x86real.h"
#include "master.hpp"
#include "libs/kaja/kaja.h"
#include "th04/snd/snd.h"

static const unsigned char SE_NONE = 0xFF;

extern unsigned char snd_se_playing;
extern unsigned char snd_se_priorities[];
extern unsigned char snd_se_priority_frames[];
extern unsigned char snd_se_frame;

static inline uint16_t for_current(void) {
	_BL = snd_se_playing;
	_BH ^= _BH;
	return _BX;
}

void snd_se_reset()
{
	snd_se_frame = 0;
	snd_se_playing = SE_NONE;
}
#pragma codestring "\x90"

void DEFCONV snd_se_play(int new_se)
{
	register int se;

	_BX = _SP;
	se = *reinterpret_cast<int *>(MK_FP(_SS, (_BX + 4))); /* = */ (new_se);

	if(snd_se_mode == SND_SE_OFF) {
		return;
	}
	if(snd_se_playing == SE_NONE) {
		snd_se_playing = se;
		return;
	}
	if(snd_se_priorities[for_current()] <= snd_se_priorities[se]) {
		snd_se_playing = se;
		snd_se_frame = 0;
	}
}
#pragma codestring "\x90"

void snd_se_update(void)
{
	if((snd_se_mode == SND_SE_OFF) || (snd_se_playing == SE_NONE)) {
		return;
	}
	if(snd_se_frame == 0) {
		_AL = snd_se_playing;
		if(snd_se_mode != SND_SE_BEEP) {
			_AH = PMD_SE_PLAY;
			geninterrupt(PMD);
		} else {
			_AH ^= _AH;
			bgm_sound(_AX);
		}
	}
	snd_se_frame++;
	if(snd_se_priority_frames[for_current()] < snd_se_frame) {
		snd_se_frame = 0;
		snd_se_playing = SE_NONE;
	}
}

}

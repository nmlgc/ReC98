#pragma option -zCSHARED -3 -Z-

#include "platform.h"
#include "x86real.h"
#include "master.hpp"
#include "libs/kaja/kaja.h"
extern "C" {
#include "th04/snd/snd.h"

extern char snd_load_fn[SND_FN_LEN];
extern const char *SND_LOAD_EXT[4];

void pascal snd_load(const char fn[SND_FN_LEN], snd_load_func_t func)
{
	int i;

	for(i = 0; i < SND_FN_LEN; i++) {
		snd_load_fn[i] = fn[i];
	}

	i = 0;
	do {
		i++;
	} while(snd_load_fn[i] != '\0');

	snd_load_fn[i + 4] = '\0';
	snd_load_fn[i++] = '.';

	if(func == SND_LOAD_SE) {
		snd_load_fn[i + 0] = 'e';
		snd_load_fn[i + 1] = 'f';
		if(snd_se_mode == SND_SE_OFF) {
			return;
		} else if(snd_se_mode == SND_SE_BEEP) {
			snd_load_fn[i + 2] = 's';
			bgm_read_sdata(snd_load_fn);
			return;
		} else {
			snd_load_fn[i + 2] = 'c';
		}
	} else {
		if(snd_bgm_mode == SND_BGM_OFF) {
			return;
		}
		snd_kaja_func(KAJA_SONG_STOP, 0);
		snd_load_fn[i + 0] = SND_LOAD_EXT[snd_bgm_mode][0];
		snd_load_fn[i + 1] = SND_LOAD_EXT[snd_bgm_mode][1];
		snd_load_fn[i + 2] = SND_LOAD_EXT[snd_bgm_mode][2];
	}

	_asm { push ds; }

	// DOS file open
	reinterpret_cast<char near *>(_DX) = snd_load_fn;
	_AX = 0x3D00;
	geninterrupt(0x21);
	_BX = _AX;
	// ZUN bug: No error handling

	// Using inline assembly rather than _AX to prevent parameters from being
	// moved to the DI register
	asm { mov ax, func; }
	if((_AH == KAJA_GET_SONG_ADDRESS) && (snd_bgm_mode == SND_BGM_MIDI)) {
		geninterrupt(MMD);
	} else {
		geninterrupt(PMD);
	}

	// DOS file read; song data address is in DS:DX
	_AX = 0x3F00;
	_CX = snd_load_size();
	geninterrupt(0x21);

	_asm { pop ds; }

	// DOS file close
	_AH = 0x3E;
	geninterrupt(0x21);
}

}

#pragma option -zCSHARED

extern "C" {
#include "platform.h"
#include "x86real.h"
#include "libs/kaja/kaja.h"
#include "th02/snd/snd.h"

extern char snd_load_fn[SND_FN_LEN];

void snd_load(const char fn[SND_FN_LEN], snd_load_func_t func)
{
	int i;
	__asm { push ds; }

	_CX = sizeof(snd_load_fn);
	i = 0;
	fn_copy: {
		snd_load_fn[i] = fn[i];
		i++;
		__asm { loop fn_copy; }
	}

	__asm { mov ax, func; }
	if((_AX == SND_LOAD_SONG) && snd_midi_active) {
		_BX = 0;
		do {
			_BX++;
		} while(snd_load_fn[_BX]);
		snd_load_fn[_BX+0] = 'm';
		snd_load_fn[_BX+1] = 'd';
		snd_load_fn[_BX+2] = 0;
	}

	// DOS file open
	(char near *)(_DX) = snd_load_fn;
	_AX = 0x3D00;
	geninterrupt(0x21);
	_BX = _AX;
	// ZUN bug: No error handling

	__asm { mov ax, func; }
	if((_AX == SND_LOAD_SONG) && snd_midi_active) {
		geninterrupt(MMD);
	} else {
		geninterrupt(PMD);
	}

	// DOS file read; song data address is in DS:DX
	_AX = 0x3F00;
	_CX = snd_load_size();
	geninterrupt(0x21);

	__asm { pop ds; }

	// DOS file close
	_AH = 0x3E;
	geninterrupt(0x21);
}

}

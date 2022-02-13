#pragma option -zCSHARED_ -3

extern "C" {
#include <errno.h>
#include "platform.h"
#include "x86real.h"
#include "decomp.hpp"
#include "master.hpp"
#include "libs/kaja/kaja.h"
#include "th05/snd/snd.h"

extern char snd_load_fn[SND_FN_LEN];
extern const char SND_LOAD_EXT[4][4];

void pascal snd_load(const char fn[SND_FN_LEN], snd_load_func_t func)
{
	#define _DI	reinterpret_cast<char near *>(_DI)
	#define func_local	_BP
	#define ext	_EAX

	_asm { mov	dx, ds; }

	// memcpy(snd_load_fn, fn, sizeof(SND_LOAD_FN));
	_ES = _DX;
	_DI = snd_load_fn;
	_DS = FP_SEG(fn);
	_SI = FP_OFF(fn);
	func_local = func;
	_CX = sizeof(snd_load_fn);
	_asm { rep movsb; }

	// _DI = strchr(str, '\0');
	_DS = _DX;
	_DI = snd_load_fn;
	_CX--;	// = -1
	_AX = '\0';
	_asm { repne scasb; }

	_DI--;
	*(_DI) = '.';
	_DI++;
	if(func_local == SND_LOAD_SE) {
		// Only not decompilable because the jump distance happens to exactly
		// be 127 bytes, for which Turbo C++ doesn't emit short jumps anymore.
		_asm {
			cmp	snd_se_mode, SND_SE_OFF;
			jz 	short ret;
		}
		_BX = 0;
		if(snd_se_mode == SND_SE_BEEP) {
			*reinterpret_cast<uint32_t near *>(_DI) = 0x00736665; // "efs\0"
			bgm_finish();
			bgm_init(2048);
			bgm_read_sdata(snd_load_fn);
			return;
		}
	} else {
		if(snd_bgm_mode == SND_BGM_OFF) {
			return;
		}
		/* TODO: Replace with the decompiled expressions
		* 	snd_kaja_func(KAJA_SONG_STOP, 0);
		* 	_BX = (snd_bgm_mode << 2);
		* Since snd_kaja_interrupt() is undecompilable, this can never work
		* with the original translation unit structure. */
		_asm {
			push	(KAJA_SONG_STOP shl 8);
			push	cs;
			call	near ptr snd_kaja_interrupt;
			db  	0x0F, 0xB6, 0x1E;   	// MOVZX BX,
			dw  	offset snd_bgm_mode;	//           snd_bgm_mode
			shl 	bx, 2
		}
	}
	ext = *reinterpret_cast<const int32_t *>(&SND_LOAD_EXT[0][_BX]);

	// ZUN bug: Infinite loop if neither the file for the current
	// [snd_bgm_mode] nor "[fn].m" exist.
	while(1) {
		*reinterpret_cast<uint32_t near *>(_DI) = ext;

		// DOS file open
		reinterpret_cast<char near *>(_DX) = snd_load_fn;
		_AX = 0x3D00;
		geninterrupt(0x21);
		if(!FLAGS_CARRY) {
			break;
		}
		if(_AX != ENOFILE) {
			return;
		}
		ext = *reinterpret_cast<const int32_t *>(SND_LOAD_EXT[SND_BGM_FM26]);
	}

	_BX = _AX;
	_AX = func_local;
	if((_AH == KAJA_GET_SONG_ADDRESS) && (snd_bgm_mode == SND_BGM_MIDI)) {
		geninterrupt(MMD);
	} else {
		geninterrupt(PMD);
	}

	// DOS file read; song data address is in DS:DX
	_AX = 0x3F00;
	_CX = snd_load_size();
	geninterrupt(0x21);

	// DOS file close
	_AH = 0x3E;
	geninterrupt(0x21);

	_asm { push	es; }
	_asm { pop 	ds; }

ret:
	#undef func_local
	#undef ext
	#undef _DI
}

}

#pragma codeseg SHARED

#include <dos.h>
#include "platform.h"
#include "libs/kaja/kaja.h"
#include "th02/snd/snd.h"

extern char snd_load_fn[13];

void snd_load(const char *fn, kaja_func_t func)
{
	int i;
	__asm	push ds;

	_CX = sizeof(snd_load_fn);
	i = 0;
fn_copy:
	snd_load_fn[i] = fn[i];
	i++;
	__asm	loop fn_copy;

	__asm	mov ax, func;
	if(_AX == SND_LOAD_SONG && snd_midi_active) {
		_BX = 0;
		do {
			_BX++;
		} while(snd_load_fn[_BX]);
		snd_load_fn[_BX+0] = 'm';
		snd_load_fn[_BX+1] = 'd';
		snd_load_fn[_BX+2] = 0;
	}
	__asm	mov dx, offset snd_load_fn;
	__asm	mov ax, 0x3D00;
	__asm	int 0x21;
	_BX = _AX;
	__asm	mov ax, func;
	if(_AX == SND_LOAD_SONG && snd_midi_active) {
		geninterrupt(MMD);
	} else {
		geninterrupt(PMD);
	}
	__asm	mov ax, 0x3F00;
	__asm	mov cx, 0x5000;
	__asm	int 0x21;
	__asm	pop ds;
	__asm	mov ah, 0x3E;
	__asm	int 0x21;
}

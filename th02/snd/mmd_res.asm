public _snd_mmd_resident
_snd_mmd_resident proc
	xor	ax, ax
	mov	es, ax
	les	bx, dword ptr es:[61h * 4]
	assume es:nothing
	cmp	byte ptr es:[bx+2], 'M'
	jnz	short @@nope
	cmp	byte ptr es:[bx+3], 'M'
	jnz	short @@nope
	cmp	byte ptr es:[bx+4], 'D'
	jnz	short @@nope
	mov	_snd_interrupt_if_midi, 61h
if GAME le 3
	mov	_snd_midi_active, 1
endif
	mov	_snd_midi_possible, 1
	mov	ax, 1
	ret

@@nope:
if GAME le 3
	mov	_snd_midi_possible, 0
endif
	xor	ax, ax
	ret
_snd_mmd_resident endp
	nop	; word alignment

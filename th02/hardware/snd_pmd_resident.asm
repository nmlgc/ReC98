; int __cdecl snd_pmd_resident(void)
snd_pmd_resident	proc
	mov	snd_interrupt_if_midi, 60h
	mov	snd_midi_active, 0
	mov	snd_fm_possible, 0
	mov	snd_midi_possible, 0
	xor	ax, ax
	mov	es, ax
	assume es:nothing
	les	bx, dword ptr es:[60h * 4]
	cmp	byte ptr es:[bx+2], 'P'
	jnz	short @@nope
	cmp	byte ptr es:[bx+3], 'M'
	jnz	short @@nope
	cmp	byte ptr es:[bx+4], 'D'
	jnz	short @@nope
	mov	ax, 1
	ret

@@nope:
	xor	ax, ax
	ret
snd_pmd_resident	endp
	nop	; word alignment

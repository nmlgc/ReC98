; int __cdecl snd_pmd_resident(void)
snd_pmd_resident	proc
	xor	ax, ax
	mov	snd_interrupt_if_midi, 60h
	mov	snd_midi_possible, al
	mov	snd_bgm_mode, al
	mov	snd_se_mode, al
	mov	es, ax
	assume es:nothing
	les	bx, dword ptr es:[60h * 4]
	cmp	byte ptr es:[bx+2], 'P'
	jnz	short @@ret
	cmp	byte ptr es:[bx+3], 'M'
	jnz	short @@ret
	cmp	byte ptr es:[bx+4], 'D'
	jnz	short @@ret
	inc	ax

@@ret:
	ret
snd_pmd_resident	endp

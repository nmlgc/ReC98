public _snd_determine_mode
_snd_determine_mode proc
	mov	ah, PMD_GET_DRIVER_VERSION
	int	60h
	xor	bx, bx
	cmp	al, -1
	jz	short @@set_to_MIDI_activity
	inc	bx
	mov	_snd_fm_possible, 1
	jmp	short @@set_and_ret

@@set_to_MIDI_activity:
	mov	bl, _snd_midi_active

@@set_and_ret:
	mov	_snd_active, bl
	mov	ax, bx
	ret
_snd_determine_mode endp
	nop	; word alignment

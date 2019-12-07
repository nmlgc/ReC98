public INPUT_WAIT_FOR_OK_OR_MEASURE
input_wait_for_ok_or_measure	proc far

@@frames 	= word ptr  6
@@measure	= word ptr  8

	push	bp
	mov	bp, sp
	cmp	_snd_active, 0
	jnz	short @@get_measure
	push	[bp+@@frames]
	nopcall	input_wait_for_ok
	pop	bp
	retf	4
; ---------------------------------------------------------------------------

@@get_measure:
	mov	ah, KAJA_GET_SONG_MEASURE
	cmp	_snd_midi_active, 1
	jz	short @@MIDI_is_active
	int	PMD
	jmp	short @@poll_input
; ---------------------------------------------------------------------------

@@MIDI_is_active:
	mov	dx, MMD_TICKS_PER_QUARTER_NOTE * 4	; yes, hardcoded to 4/4
	int	MMD

@@poll_input:
	nopcall	input_mode_interface
	test	_input_sp.lo, low INPUT_SHOT
	jnz	short @@got_input
	test	_input_sp.hi, high INPUT_OK
	jz	short @@measure_reached

@@got_input:
	mov	ax, 1
	pop	bp
	retf	4
; ---------------------------------------------------------------------------

@@measure_reached:
	cmp	ax, [bp+@@measure]
	jb	short @@get_measure
	xor	ax, ax
	pop	bp
	retf	4
input_wait_for_ok_or_measure	endp


public INPUT_WAIT_FOR_OK
input_wait_for_ok	proc far

@@frames	= word ptr  6

	push	bp
	mov	bp, sp
	mov	vsync_Count1, 0

@@poll_input:
	nopcall	input_mode_interface
	test	_input_sp.lo, low INPUT_SHOT
	jnz	short @@got_input
	test	_input_sp.hi, high INPUT_OK
	jz	short @@frames_reached?

@@got_input:
	mov	ax, 1
	pop	bp
	retf	2
; ---------------------------------------------------------------------------

@@frames_reached?:
	mov	ax, vsync_Count1
	cmp	ax, [bp+@@frames]
	jb	short @@poll_input
	xor	ax, ax
	pop	bp
	retf	2
input_wait_for_ok	endp

public SND_DELAY_UNTIL_MEASURE
snd_delay_until_measure	proc far

@@frames_if_no_bgm	= word ptr  6
@@measure		= word ptr  8

	push	bp
	mov	bp, sp
	push	si

@@retry:
	call	_snd_bgm_measure
	mov	si, ax
	or	si, si
	jge	short @@reached?
	push	[bp+@@frames_if_no_bgm]
	nopcall	frame_delay
	jmp	short @@ret

@@reached?:
	cmp	si, [bp+@@measure]
	jl	short @@retry

@@ret:
	pop	si
	pop	bp
	retf	4
snd_delay_until_measure	endp
	db 0

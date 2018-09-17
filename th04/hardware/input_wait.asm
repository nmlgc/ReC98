; Waits ≥1 frames for all held inputs to be released, then waits the given
; number of [frames] for an input to be pressed. Set [frames] to 0 or 9999
; to wait forever.
; void pascal input_wait_for_change(int frames);
_input_wait_for_change	proc far
@@frames		= word ptr  6

	push	bp
	mov	bp, sp
	push	si
	push	di
	mov	si, [bp+@@frames]
	xor	di, di

@@release_loop:
	nop
	call	_input_reset_sense
	push	1
	nopcall	frame_delay
	nopcall	_input_sense
	cmp	_input, INPUT_NONE
	jnz	short @@release_loop
	or	si, si
	jnz	short @@longer?
	mov	si, 9999
	jmp	short @@longer?

@@press_loop:
	nop
	call	_input_reset_sense
	push	1
	nopcall	frame_delay
	nopcall	_input_sense
	cmp	_input, INPUT_NONE
	jnz	short @@ret
	inc	di
	cmp	si, 9999
	jnz	short @@longer?
	xor	di, di

@@longer?:
	cmp	di, si
	jl	short @@press_loop

@@ret:
	pop	di
	pop	si
	pop	bp
	retf	2
_input_wait_for_change	endp

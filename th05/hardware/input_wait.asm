public INPUT_WAIT_FOR_CHANGE
input_wait_for_change	proc far
@@frames		= word ptr  6

	push	bp
	mov	bp, sp

@@release_loop:
	call	_input_reset_sense_held
	or	ax, ax
	jnz	short @@release_loop
	mov	bp, [bp+@@frames]

@@press_loop:
	call	_input_reset_sense_held
	or	ax, ax
	jnz	short @@ret
	mov	ax, vsync_Count1

@@vsync:
	cmp	ax, vsync_Count1
	jz	short @@vsync
	or	bp, bp
	jz	short @@press_loop
	dec	bp
	jnz	short @@press_loop

@@ret:
	pop	bp
	retf	2
input_wait_for_change	endp

public PLAYFIELD_FG_X_TO_SCREEN
playfield_fg_x_to_screen	proc far

@@pid	= word ptr  6
@@x  	= word ptr  8

	push	bp
	mov	bp, sp
	mov	ax, [bp+@@x]
	mov	bx, [bp+@@pid]
	sar	ax, 4
	or	bx, bx
	jz	short @@apply_shift
	add	ax, PLAYFIELD_W_BORDERED
	mov	bx, word

@@apply_shift:
	add	ax, _playfield_fg_shift_x[bx]
	add	ax, PLAYFIELD_LEFT
	pop	bp
	retf	4
playfield_fg_x_to_screen	endp
	even

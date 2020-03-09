; Special FUUIN.EXE version of frame_delay() that resets [vsync_frame] first.
public _frame_delay
_frame_delay	proc far

@@frames	= word ptr  6

	push	bp
	mov	bp, sp
	mov	_vsync_frame, 0

@@loop:
	mov	ax, _vsync_frame
	cmp	ax, [bp+@@frames]
	jnb	short @@ret
	jmp	short @@loop
; ---------------------------------------------------------------------------

@@ret:
	pop	bp
	retf
_frame_delay	endp

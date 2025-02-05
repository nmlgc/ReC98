public @nullfunc_void$qv
@nullfunc_void$qv proc far
	push	bp
	mov	bp, sp
	pop	bp
	retf
@nullfunc_void$qv endp

public @nullfunc_false$qv
@nullfunc_false$qv proc far
	push	bp
	mov	bp, sp
	xor	ax, ax
	pop	bp
	retf
@nullfunc_false$qv endp

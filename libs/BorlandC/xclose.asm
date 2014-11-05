; void _xclose(void)
__xclose	proc
@@i		= word ptr -2

		push	bp
		mov	bp, sp
		sub	sp, 2
		push	si
		push	di
		mov	[bp+@@i], 2
		jmp	short @@check

@@loop:
		push	[bp+@@i]
		nopcall	_close
		pop	cx
		inc	[bp+@@i]

@@check:
		mov	ax, [bp+@@i]
		cmp	ax, __nfile
		jb	short @@loop
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret
__xclose	endp

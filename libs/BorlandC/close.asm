; int __cdecl close(int	handle)
_close		proc
@@handle		= word ptr (cPtrSize + 2)

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	dx, [bp+@@handle]
		cmp	dx, __nfile
		jb	short @@close
		mov	ax, e_badHandle
		push	ax
		call	__IOERROR
		jmp	short @@ret

@@close:
		mov	bx, dx
		add	bx, bx
		mov	_openfd[bx], 0
		push	dx
		nopcall	__rtl_close
		pop	cx

@@ret:
		pop	di
		pop	si
		pop	bp
		ret
_close		endp

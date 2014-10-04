; int _CType _FARFUNC _close( register int fd )
__rtl_close	proc DIST
@@fd		= word ptr cPtrSize + 2

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	ah, 3Eh
		mov	bx, [bp+@@fd]
		int	21h
		jb	short @@_closeFailed
		add	bx, bx
		mov	_openfd[bx], 0
		xor	ax, ax
		jmp	short @@_closeRet

@@_closeFailed:
		push	ax
		call	__IOERROR

@@_closeRet:
		pop	di
		pop	si
		pop	bp
		retf
__rtl_close	endp

; int __cdecl _close(int fd)
__close		proc DIST
@@fd		= word ptr cPtrSize + 2

		push	bp
		mov	bp, sp
		push	si
		push	di
		push	[bp+@@fd]
		call	__rtl_close
		pop	cx
		pop	di
		pop	si
		pop	bp
		ret
__close		endp

; int _chmod(const char	*pathname, int func, ...)
public __chmod
__chmod		proc

pathname	= dword	ptr  6
_func		= byte ptr  0Ah
attrib		= word ptr  0Ch

		push	bp
		mov	bp, sp
		push	si
		push	di
		push	ds
		mov	cx, [bp+attrib]
		mov	ah, 43h	; 'C'
		mov	al, [bp+_func]
		lds	dx, [bp+pathname]
		int	21h		; DOS -
		pop	ds
		jb	short @@_chmodFailed
		xchg	ax, cx
		jmp	short @@_chmodRet
; ---------------------------------------------------------------------------

@@_chmodFailed:
		push	ax
		call	__IOERROR

@@_chmodRet:
		pop	di
		pop	si
		pop	bp
		ret
__chmod		endp

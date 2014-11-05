; int __cdecl unlink(const char	*path)
_unlink		proc
@@path		= DPTR_ 2 + dPtrSize

		push	bp
		mov	bp, sp
		push	si
		push	di
		pushDS_
		mov	ah, 41h
		LDS_	dx, [bp+@@path]
		int	21h	
		popDS_
		jb	short @@unlinkFailed
		xor	ax, ax
		jmp	short @@ret

@@unlinkFailed:
		push	ax
		call	__IOERROR

@@ret:
		pop	di
		pop	si
		pop	bp
		ret
_unlink		endp

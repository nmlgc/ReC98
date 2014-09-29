; int __cdecl __far eof(int handle)
_eof		proc DIST
@@endPosn	= DPTR_ -(dPtrSize)
@@handle	= word ptr 2 + dPtrSize

		push	bp
		mov	bp, sp
		sub	sp, dPtrSize
		push	si
		push	di
		mov	ax, [bp+@@handle]
		cmp	ax, __nfile
		jb	short @@eofSeen?
		mov	ax, 6
		push	ax
		jmp	short @@IOError

@@eofSeen?:
		mov	bx, [bp+@@handle]
		add	bx, bx
		test	byte ptr (_openfd+1)[bx], 2
		jz	short @@check
		mov	ax, 1
		jmp	short @@ret

@@check:
		mov	ax, 4400h
		mov	bx, [bp+@@handle]
		int	21h
		jb	short @@eofFailed
		test	dl, 80h
		jnz	short @@NotEof
		mov	ax, 4201h
		xor	cx, cx
		mov	dx, cx
		int	21h
		jb	short @@eofFailed
		push	dx
		push	ax
		mov	ax, 4202h
		xor	cx, cx
		mov	dx, cx
		int	21h
		mov	word ptr [bp+@@endPosn], ax
		mov	word ptr [bp+@@endPosn+2], dx
		pop	dx
		pop	cx
		jb	short @@eofFailed
		mov	ax, 4200h
		int	21h
		jb	short @@eofFailed
		cmp	dx, word ptr [bp+@@endPosn+2]
		jb	short @@NotEof
		ja	short @@IsEof
		cmp	ax, word ptr [bp+@@endPosn]
		jb	short @@NotEof

@@IsEof:
		mov	ax, 1
		jmp	short @@ret

@@NotEof:
		xor	ax, ax
		jmp	short @@ret

@@eofFailed:
		push	ax

@@IOError:
		call	__IOERROR

@@ret:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret
_eof		endp

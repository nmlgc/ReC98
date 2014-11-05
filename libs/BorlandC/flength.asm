; long __cdecl __far filelength(int handle)
_filelength	proc
@@Position	= dword	ptr -4
@@handle	= word ptr dPtrSize + 2

		push	bp
		mov	bp, sp
		sub	sp, 4
		push	si
		push	di
		mov	ax, 4201h
		mov	bx, [bp+@@handle]
		xor	cx, cx
		xor	dx, dx
		int	21h
		jb	short @@filelengthFailed
		push	dx
		push	ax
		mov	ax, 4202h
		xor	cx, cx
		xor	dx, dx
		int	21h
		mov	word ptr [bp+@@Position], ax
		mov	word ptr [bp+@@Position+2], dx
		pop	dx
		pop	cx
		jb	short @@filelengthFailed
		mov	ax, 4200h
		int	21h
		jb	short @@filelengthFailed
		mov	dx, word ptr [bp+@@Position+2]
		mov	ax, word ptr [bp+@@Position]
		jmp	short @@ret

@@filelengthFailed:
		push	ax
		call	__IOERROR
		cwd

@@ret:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
_filelength	endp

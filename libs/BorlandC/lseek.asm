; long _CType lseek(int fd, long ofs, int kind)
public _lseek
_lseek		proc DIST
@@fd		= word ptr dPtrSize + 2
@@ofs		= dword ptr dPtrSize + 4
@@kind	= byte ptr dPtrSize + 8

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	bx, [bp+@@fd]
		add	bx, bx
		and	_openfd[bx], 0FDFFh
		mov	ah, 42h
		mov	al, [bp+@@kind]
		mov	bx, [bp+@@fd]
		mov	cx, word ptr [bp+@@ofs+2]
		mov	dx, word ptr [bp+@@ofs]
		int	21h
		jb	short @@lseekFailed
		jmp	short @@lseekRet
; ---------------------------------------------------------------------------

@@lseekFailed:
		push	ax
		call	__IOERROR
		cwd

@@lseekRet:
		pop	di
		pop	si
		pop	bp
		ret
_lseek		endp

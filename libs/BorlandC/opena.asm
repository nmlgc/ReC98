; int __cdecl __far _rtl_open(const char *filename, int oflag)
__rtl_open	proc DIST
@@fd		= word ptr -2
@@filename	= DPTR_ (cPtrSize + 2)
@@oflag		= word ptr (cPtrSize + 2 + dPtrSize)

		push	bp
		mov	bp, sp
		sub	sp, 2
		push	si
		push	di
		mov	al, 1
		mov	cx, [bp+@@oflag]
		test	cx, O_WRONLY
		jnz	short @@ready
		mov	al, 2
		test	cx, O_RDWR
		jnz	short @@ready
		mov	al, 0

@@ready:
		pushDS_
		LDS_	dx, [bp+@@filename]
		mov	cl, 0F0h
		and	cl, byte ptr [bp+@@oflag]
		or	al, cl
		mov	ah, 3Dh
		int	21h
		popDS_
		jb	short @@_openFailed
		mov	[bp+@@fd], ax
		mov	ax, [bp+@@oflag]
		and	ax, not	(_O_RUNFLAGS or	O_TEXT)
		or	ax, O_BINARY
		mov	bx, [bp+@@fd]
		add	bx, bx
		mov	_openfd[bx], ax
		mov	ax, [bp+@@fd]
		jmp	short @@ret

@@_openFailed:
		push	ax
		call	__IOERROR

@@ret:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret
__rtl_open	endp

; int __cdecl _open(const char *path, int oflags)
__open		proc DIST
@@filename	= DPTR_ (cPtrSize + 2)
@@oflag		= word ptr (cPtrSize + 2 + dPtrSize)

		push	bp
		mov	bp, sp
		push	si
		push	di
		push	[bp+@@oflag]
if LDATA
		push	word ptr [bp+@@filename+2]
endif
		push	word ptr [bp+@@filename]
		call	__rtl_open
		add	sp, (2 + dPtrSize)
		pop	di
		pop	si
		pop	bp
		ret
__open		endp

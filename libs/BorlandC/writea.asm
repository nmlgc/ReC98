; int _CType _FARFUNC _write(int fd, const void *buf, unsigned len)
public __rtl_write
__rtl_write	proc DIST
@@fd		= word ptr dPtrSize + 2
@@buf		= DPTR_ dPtrSize + 4
@@len		= word ptr dPtrSize + 4 + dPtrSize

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	bx, [bp+@@fd]
		add	bx, bx
		test	byte ptr _openfd[bx], 1
		jz	short @@writeDo
		mov	ax, 5
		push	ax
		jmp	short @@writeDenied

@@writeDo:
		pushDS_
		mov	ah, 40h
		mov	bx, [bp+@@fd]
		mov	cx, [bp+@@len]
		LDS_	dx, [bp+@@buf]
		int	21h
		popDS_
		jb	short @@writeFailed
		push	ax
		mov	bx, [bp+@@fd]
		add	bx, bx
		or	_openfd[bx], 1000h
		pop	ax
		jmp	short @@writeRet

@@writeFailed:
		push	ax

@@writeDenied:
		call	__IOERROR

@@writeRet:
		pop	di
		pop	si
		pop	bp
		ret
__rtl_write	endp

; int __cdecl _write(int fd, const void *buf, unsigned len)
public __write
__write	proc DIST
@@fd		= word ptr dPtrSize + 2
@@buf		= DPTR_ dPtrSize + 4
@@len		= word ptr dPtrSize + 4 + dPtrSize

		push	bp
		mov	bp, sp
		push	si
		push	di
		push	[bp+@@len]
if LDATA
		push	word ptr [bp+@@buf+2]
		push	word ptr [bp+@@buf]
else
		push	[bp+buf]
endif
		push	[bp+@@fd]
		call	__rtl_write
		add	sp, 4 + dPtrSize
		pop	di
		pop	si
		pop	bp
		ret
__write		endp

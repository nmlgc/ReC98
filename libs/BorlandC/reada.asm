; int _CType _read( int fd, void *buf, unsigned len )
public __rtl_write
__rtl_read	proc
@@fd		= word ptr dPtrSize + 2
@@buf		= DPTR_ dPtrSize + 4
@@len		= word ptr dPtrSize + 4 + dPtrSize

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	bx, [bp+@@fd]
		add	bx, bx
		test	byte ptr _openfd[bx], 2
		jz	short @@readDo
		mov	ax, 5
		push	ax
		jmp	short @@readDenied

@@readDo:
		pushDS_
		mov	ah, 3Fh
		mov	bx, [bp+@@fd]
		mov	cx, [bp+@@len]
		LDS_	dx, [bp+@@buf]
		int	21h
		popDS_
		jb	short @@readFailed
		jmp	short @@readRet

@@readFailed:
		push	ax

@@readDenied:
		call	__IOERROR

@@readRet:
		pop	di
		pop	si
		pop	bp
		ret
__rtl_read	endp

; int __cdecl _read(int fd, const void *buf, unsigned len)
public __read
__read		proc
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
endif
		push	word ptr [bp+@@buf]
		push	[bp+@@fd]
		call	__rtl_read
		add	sp, 4 + dPtrSize
		pop	di
		pop	si
		pop	bp
		ret
__read		endp

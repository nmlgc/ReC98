___WRITE_CHUNK_SIZE equ 128

; int __cdecl __write(int fd, const void *buf, unsigned int len)
___write	proc
if LDATA
___WRITE_CRBUF_OFFSET equ 10h + ___WRITE_CHUNK_SIZE

@@sbuf		= DPTR_ -0Eh
@@c		= byte ptr -9
@@remainder	= word ptr -8
@@tbuf		= DPTR_ -6
else
___WRITE_CRBUF_OFFSET equ 0Ah + ___WRITE_CHUNK_SIZE

@@sbuf		= word ptr -8
@@c		= byte ptr -5
@@remainder		= word ptr -4
endif
@@crbuf		= byte ptr -___WRITE_CRBUF_OFFSET
@@chunk		= word ptr -2
@@fd		= word ptr dPtrSize + 2
@@buf		= dword	ptr dPtrSize + 4
@@len		= word ptr dPtrSize + 4 + dPtrSize

		push	bp
		mov	bp, sp
		sub	sp, ___WRITE_CRBUF_OFFSET
		push	si
		push	di
		mov	ax, [bp+@@fd]
		cmp	ax, __nfile
		jb	short @@writeCheckLen
		mov	ax, 6
		push	ax
		call	__IOERROR
		jmp	@@writeRet

@@writeCheckLen:
		mov	ax, [bp+@@len]
		inc	ax
		cmp	ax, 2
		jnb	short @@writeSeek
		xor	ax, ax
		jmp	@@writeRet

@@writeSeek:
		mov	bx, [bp+@@fd]
		add	bx, bx
		test	byte ptr (_openfd+1)[bx], 8
		jz	short @@writeBinary
		mov	ax, 2
		push	ax
		xor	ax, ax
		push	ax
		push	ax
		push	[bp+@@fd]
		nopcall	_lseek
		add	sp, 8

@@writeBinary:
		mov	bx, [bp+@@fd]
		add	bx, bx
		test	byte ptr (_openfd+1)[bx], 40h
		jnz	short @@writeFlipEOF
		push	[bp+@@len]
if LDATA
		push	word ptr [bp+@@buf+2]
endif
		push	word ptr [bp+@@buf]
		push	[bp+@@fd]
		nopcall	__rtl_write
		add	sp, 4 + dPtrSize
		jmp	@@writeRet

@@writeFlipEOF:
		mov	bx, [bp+@@fd]
		add	bx, bx
		and	_openfd[bx], 0FDFFh
if LDATA
		mov	dx, word ptr [bp+@@buf+2]
endif
		mov	ax, word ptr [bp+@@buf]
if LDATA
		mov	word ptr [bp+@@sbuf+2],	dx
endif
		mov	word ptr [bp+@@sbuf], ax
		mov	ax, [bp+@@len]
		mov	[bp+@@remainder], ax
		jmp	short @@writeSetTBuf

@@writeCRLF:
		dec	[bp+@@remainder]
		LES_	bx, [bp+@@sbuf]
		inc	word ptr [bp+@@sbuf]
if LDATA
		mov	al, es:[bx]
		mov	[bp+@@c], al
		cmp	al, 0Ah
		jnz	short @@writeCopy
		les	bx, [bp+@@tbuf]
		mov	byte ptr es:[bx], 0Dh
		inc	word ptr [bp+@@tbuf]

@@writeCopy:
		les	bx, [bp+@@tbuf]
		mov	al, [bp+@@c]
		mov	es:[bx], al
		inc	word ptr [bp+@@tbuf]
		lea	ax, [bp+@@crbuf]
		mov	dx, word ptr [bp+@@tbuf]
		xor	bx, bx
		sub	dx, ax
		sbb	bx, 0
		or	bx, bx
		jl	short @@writeLoopCheck
		jnz	short @@writeChunk
		cmp	dx, ___WRITE_CHUNK_SIZE
		jb	short @@writeLoopCheck

@@writeChunk:
		lea	ax, [bp+@@crbuf]
		mov	dx, word ptr [bp+@@tbuf]
		xor	bx, bx
		sub	dx, ax
		sbb	bx, 0
else
		mov	al, [bx]
		mov	[bp+@@c], al
		cmp	al, 0Ah
		jnz	short @@writeCopy
		mov	bx, cx
		mov	byte ptr [bx], 0Dh
		inc	cx

@@writeCopy:
		mov	bx, cx
		mov	al, [bp+@@c]
		mov	[bx], al
		inc	cx
		lea	ax, [bp+@@crbuf]
		mov	dx, cx
		sub	dx, ax
		cmp	dx, ___WRITE_CHUNK_SIZE
		jl	short @@writeLoopCheck
		mov	dx, cx
		sub	dx, ax
endif
		mov	[bp+@@chunk], dx
		push	dx
		pushSS_
		push	ax
		push	[bp+@@fd]
		nopcall	__rtl_write
		add	sp, 4 + dPtrSize
		mov	dx, ax
		cmp	ax, [bp+@@chunk]
		jz	short @@writeSetTBuf
		cmp	dx, 0FFFFh
		jnz	short @@writeRetLRRC
		mov	ax, -1
		jmp	short @@writeRetJump

@@writeRetLRRC:
		mov	ax, [bp+@@len]
		sub	ax, [bp+@@remainder]
		jmp	short @@writeRetRC

@@writeSetTBuf:
if LDATA
		lea	ax, [bp+@@crbuf]
		mov	word ptr [bp+@@tbuf+2],	ss
		mov	word ptr [bp+@@tbuf], ax

@@writeLoopCheck:
		cmp	[bp+@@remainder], 0
		jz	short @@writeRest
		jmp	@@writeCRLF

@@writeRest:
		lea	ax, [bp+@@crbuf]
		mov	dx, word ptr [bp+@@tbuf]
		xor	bx, bx
		sub	dx, ax
		sbb	bx, 0
else
		lea	cx, [bp+@@crbuf]

@@writeLoopCheck:
		cmp	[bp+@@remainder], 0
		jnz	short @@writeCRLF
		lea	ax, [bp+@@crbuf]
		mov	dx, cx
		sub	dx, ax
endif
		mov	[bp+@@chunk], dx
		mov	ax, dx
		or	ax, ax
		jbe	short @@writeRetL
		push	dx
		pushSS_
		lea	ax, [bp+@@crbuf]
		push	ax
		push	[bp+@@fd]
		nopcall	__rtl_write
		add	sp, 4 + dPtrSize
		mov	dx, ax
		cmp	ax, [bp+@@chunk]
		jz	short @@writeRetL
		cmp	dx, 0FFFFh
		jnz	short @@writeRetLRC
		mov	ax, -1
		jmp	short @@writeRetJump

@@writeRetLRC:
		mov	ax, [bp+@@len]

@@writeRetRC:
		add	ax, dx
		sub	ax, [bp+@@chunk]

@@writeRetJump:
		jmp	short @@writeRet

@@writeRetL:
		mov	ax, [bp+@@len]

@@writeRet:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret
___write	endp

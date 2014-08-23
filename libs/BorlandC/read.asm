_ctlZ equ 26

; int __cdecl __far __read(int fd, void *buf, unsigned int len)
___read		proc DIST
public ___read
@@c		= byte ptr -3
@@dlen		= word ptr -2
@@fd		= word ptr dPtrSize + 2
@@buf		= dword	ptr dPtrSize + 4
@@len		= word ptr dPtrSize + 4 + dPtrSize

		push	bp
		mov	bp, sp
		sub	sp, 4
		push	si
		push	di
		mov	ax, [bp+@@fd]
		cmp	ax, __nfile
		jb	short @@readCheckLen
		mov	ax, 6
		push	ax
		call	__IOERROR
		jmp	@@readRet

@@readCheckLen:
		mov	ax, [bp+@@len]
		inc	ax
		cmp	ax, 2
		jb	short @@readTooShort
		mov	bx, [bp+@@fd]
		add	bx, bx
		test	byte ptr (_openfd+1)[bx], 2
		jz	short @@readDo

@@readTooShort:
		xor	ax, ax
		jmp	@@readRet

@@readDo:
		push	[bp+@@len]
if LDATA
		push	word ptr [bp+@@buf+2]
endif
		push	word ptr [bp+@@buf]
		push	[bp+@@fd]
		nopcall	__rtl_read
		add	sp, 4 + dPtrSize
		mov	[bp+@@dlen], ax
		inc	ax
		cmp	ax, 2
		jb	short @@readBinary
		mov	bx, [bp+@@fd]
		add	bx, bx
		test	byte ptr (_openfd+1)[bx], 40h
		jnz	short @@readSqueezeCR

@@readBinary:
		mov	ax, [bp+@@dlen]
		jmp	short @@readRet

@@readSqueezeCR:
		mov	cx, [bp+@@dlen]
		les	si, [bp+@@buf]
ife LDATA
		push	ds
		pop	es
endif
		mov	di, si
		mov	bx, si
		cld

@@squeeze:
		lods	byte ptr es:[si]
		cmp	al, _ctlZ
		jz	short @@endSeen
		cmp	al, 0Dh
		jz	short @@elseSqueeze
		stosb
		loop	@@squeeze
		jmp	short @@squeezeBreak

@@elseSqueeze:
		loop	@@squeeze
		push	es
		push	bx
		mov	ax, 1
		push	ax
		lea	ax, [bp+@@c]
		pushSS_
		push	ax
		push	[bp+@@fd]
		nopcall	__read
		add	sp, 8
		pop	bx
		pop	es
		cld
		mov	al, [bp+@@c]
		stosb

@@squeezeBreak:
		cmp	di, bx
		jnz	short @@doneTextJump
		jmp	short @@readDo

@@doneTextJump:
		jmp	short @@doneText

@@endSeen:
		push	bx
		mov	ax, 1
		push	ax
		neg	cx
		sbb	ax, ax
		push	ax
		push	cx
		push	[bp+@@fd]
		nopcall	_lseek
		add	sp, 8
		mov	bx, [bp+@@fd]
		add	bx, bx
		or	_openfd[bx], 200h
		pop	bx

@@doneText:
		sub	di, bx
		xchg	ax, di

@@readRet:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret
___read		endp

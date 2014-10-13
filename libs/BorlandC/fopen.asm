; unsigned int __pascal __near CheckOpenType(const char *type, unsigned int *oflagsP, unsigned int *modeP)
CheckOpenType	proc near
@@flags		= word ptr -4
@@mode		= word ptr -2
@@modeP		= DPTR_ (cPtrSize)
@@oflagsP	= DPTR_ (cPtrSize + dPtrSize)
@@type		= DPTR_ (cPtrSize + dPtrSize + dPtrSize)

		push	bp
		mov	bp, sp
		sub	sp, 4
		push	si
		push	di
		mov	[bp+@@mode], 0
		LES_	bx, [bp+@@type]
		inc	word ptr [bp+@@type]
		mov	cl, ES_[bx]
		mov	al, cl
		cmp	al, 'r'
		jnz	short @@w?
		mov	dx, O_RDONLY
		mov	[bp+@@flags], _F_READ
		jmp	short @@secondary

@@w?:
		cmp	cl, 'w'
		jnz	short @@a?
		mov	dx, 302h
		jmp	short @@write

@@a?:
		cmp	cl, 'a'
		jnz	short @@ret0
		mov	dx, 902h

@@write:
		mov	[bp+@@mode], S_IWRITE
		mov	[bp+@@flags], _F_WRIT
		jmp	short @@secondary

@@ret0:
		xor	ax, ax
		jmp	@@ret

@@secondary:
		LES_	bx, [bp+@@type]
		mov	cl, ES_[bx]
		inc	word ptr [bp+@@type]
		cmp	cl, '+'
		jz	short @@same?
		LES_	bx, [bp+@@type]
		cmp	byte ptr ES_[bx], '+'
		jnz	short @@t?
		cmp	cl, 't'
		jz	short @@same?
		cmp	cl, 'b'
		jnz	short @@t?

@@same?:
		cmp	cl, '+'
		jnz	short @@same
		LES_	bx, [bp+@@type]
		mov	cl, ES_[bx]

@@same:
		and	dx, 0FFFCh
		or	dx, O_RDWR
		mov	[bp+@@mode], 180h
		mov	[bp+@@flags], _F_RDWR

@@t?:
		cmp	cl, 't'
		jnz	short @@b?
		or	dx, O_TEXT
		jmp	short @@success

@@b?:
		cmp	cl, 'b'
		jnz	short @@binary?
		or	dx, O_BINARY
		jmp	short @@setBinFlag

@@binary?:
		mov	ax, __fmode
		and	ax, 0C000h
		or	dx, ax
		mov	ax, dx
		test	ah, 80h
		jz	short @@success

@@setBinFlag:
		or	[bp+@@flags], _F_BIN

@@success:
		mov	word ptr _exitfopen+2, seg __xfclose
		mov	word ptr _exitfopen, offset __xfclose
		LES_	bx, [bp+@@oflagsP]
		mov	ES_[bx], dx
		LES_	bx, [bp+@@modeP]
		mov	ax, [bp+@@mode]
		mov	ES_[bx], ax
		mov	ax, [bp+@@flags]

@@ret:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret	(cPtrSize + dPtrSize + dPtrSize)
CheckOpenType	endp

; FILE *__pascal __near _openfp(FILE *fp, const char *filename, const char *type, int shflag)
__openfp	proc near
@@mode		= word ptr -4
@@oflag		= word ptr -2
@@shflag	= word ptr (cPtrSize)
@@type		= DPTR_ (cPtrSize + 2)
@@filename	= DPTR_ (cPtrSize + 2 + dPtrSize)
@@fp		= DPTR_ (cPtrSize + 2 + dPtrSize + dPtrSize)

		push	bp
		mov	bp, sp
		sub	sp, 4
		push	si
		push	di
		push	word ptr [bp+@@type+2]
		push	word ptr [bp+@@type]
		push	ss
		lea	ax, [bp+@@oflag]
		push	ax
		push	ss
		lea	ax, [bp+@@mode]
		push	ax
		call	CheckOpenType
		LES_	bx, [bp+@@fp]
		mov	ES_[bx+FILE.flags], ax
		or	ax, ax
		jz	short @@resetFP
		cmp	ES_[bx+FILE.fd], 0
		jge	short @@isatty?
		push	[bp+@@mode]
		mov	ax, [bp+@@oflag]
		or	ax, [bp+@@shflag]
		push	ax	
		push	word ptr [bp+@@filename+2]
		push	word ptr [bp+@@filename]
		nopcall	_open
		add	sp, (2 + 2 + dPtrSize)
		LES_	bx, [bp+@@fp]
		mov	ES_[bx+FILE.fd], al
		or	al, al
		jge	short @@isatty?

@@resetFP:
		LES_	bx, [bp+@@fp]
		mov	ES_[bx+FILE.fd], -1
		mov	ES_[bx+FILE.flags], 0
		jmp	short @@ret0

@@isatty?:
		LES_	bx, [bp+@@fp]
		mov	al, ES_[bx+FILE.fd]
		cbw
		push	ax
		nopcall	_isatty
		pop	cx
		or	ax, ax
		jz	short @@term?
		LES_	bx, [bp+@@fp]
		or	ES_[bx+FILE.flags], _F_TERM

@@term?:
		mov	ax, STDIO_BUFSIZ
		push	ax
		LES_	bx, [bp+@@fp]
		test	byte ptr ES_[bx+FILE.flags+1], 2
		jz	short @@noterm
		mov	ax, _IOLBF
		jmp	short @@setvbuf

@@noterm:
		xor	ax, ax

@@setvbuf:
		push	ax
		xor	ax, ax
		push	ax
		push	ax
		push	word ptr [bp+@@fp+2]
		push	word ptr [bp+@@fp]
		nopcall	_setvbuf
		add	sp, 0Ch
		or	ax, ax
		jz	short @@success
		push	word ptr [bp+@@fp+2]
		push	word ptr [bp+@@fp]
		nopcall	_fclose
		pop	cx
		pop	cx

@@ret0:
		xor	dx, dx
		xor	ax, ax
		jmp	short @@ret

@@success:
		LES_	bx, [bp+@@fp]
		mov	ES_[bx+FILE.istemp], 0
		mov	dx, word ptr [bp+@@fp+2]
		mov	ax, word ptr [bp+@@fp]

@@ret:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret	(cPtrSize + 2 + dPtrSize + dPtrSize)
__openfp	endp

; FILE *__pascal __near _getfp()
__getfp		proc near
@@fp		= DPTR_ -(dPtrSize)

		push	bp
		mov	bp, sp
		sub	sp, dPtrSize
		push	si
		push	di
		mov	word ptr [bp+@@fp+2], ds
		mov	word ptr [bp+@@fp], offset _streams

@@loop:
		LES_	bx, [bp+@@fp]
		cmp	ES_[bx+FILE.fd], 0
		jl	short @@valid?
		mov	ax, word ptr [bp+@@fp]
		add	word ptr [bp+@@fp], size FILE
		push	ax
		mov	ax, size FILE
		imul	__nfile
		add	ax, offset _streams
		pop	dx
		cmp	dx, ax
		jb	short @@loop

@@valid?:
		LES_	bx, [bp+@@fp]
		cmp	ES_[bx+FILE.fd], 0
		jl	short @@retFP
		xor	dx, dx
		xor	ax, ax
		jmp	short @@ret

@@retFP:
		mov	dx, word ptr [bp+@@fp+2]
		mov	ax, word ptr [bp+@@fp]

@@ret:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret
__getfp		endp

; FILE *__cdecl fopen(const char *filename, const char *type)
_fopen		proc DIST
@@fp		= DPTR_ -4
@@filename	= DPTR_ (2 + cPtrSize)
@@type		= DPTR_ (2 + cPtrSize + dPtrSize)

		push	bp
		mov	bp, sp
		sub	sp, dPtrSize
		push	si
		push	di
		call	__getfp
		mov	word ptr [bp+@@fp+2], dx
		mov	word ptr [bp+@@fp], ax
		or	ax, dx
		jnz	short @@openfp
		xor	dx, dx
		xor	ax, ax
		jmp	short @@ret

@@openfp:
		push	word ptr [bp+@@fp+2]
		push	word ptr [bp+@@fp]
		push	word ptr [bp+@@filename+2]
		push	word ptr [bp+@@filename]
		push	word ptr [bp+@@type+2]
		push	word ptr [bp+@@type]
		xor	ax, ax
		push	ax
		call	__openfp

@@ret:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret
_fopen		endp

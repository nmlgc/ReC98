; int __pascal __near dosCreat(char *pathP, unsigned int attrib)
dosCreat	proc near
@@attrib	= word ptr 4
@@pathP		= DPTR_ 6

		push	bp
		mov	bp, sp
		push	si
		push	di
		pushDS_
		mov	cx, [bp+@@attrib]
		mov	ah, 3Ch
		LDS_	dx, [bp+@@pathP]
		int	21h
		popDS_
		jb	short @@dosCreatFailed
		jmp	short @@ret

@@dosCreatFailed:
		push	ax
		call	__IOERROR

@@ret:
		pop	di
		pop	si
		pop	bp
		ret	6
dosCreat	endp

; void __pascal __near dosWriteNone(int handle)
dosWriteNone	proc near
@@handle	= word ptr  4

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	bx, [bp+@@handle]
		sub	cx, cx
		sub	dx, dx
		mov	ah, 40h
		int	21h
		pop	di
		pop	si
		pop	bp
		ret	2
dosWriteNone	endp

; int __cdecl open(const char *pathP, int oflag, unsigned int mode)
_open		proc DIST
@@fildes	= word ptr -8
@@errno_copy	= word ptr -6
@@devstat	= word ptr -4
@@attrib	= word ptr -2
@@pathP		= DPTR_ (2 + cPtrSize)
@@oflag		= word ptr (2 + cPtrSize + dPtrSize)
@@mode		= word ptr (2 + cPtrSize + dPtrSize + 2)

		push	bp
		mov	bp, sp
		sub	sp, 8
		push	si
		push	di
		test	byte ptr [bp+@@oflag+1], (O_TEXT or O_BINARY) shr 8
		jnz	short @@chmod
		mov	ax, __fmode
		and	ax, O_TEXT or O_BINARY
		or	[bp+@@oflag], ax

@@chmod:
		mov	ax, _errno
		mov	[bp+@@errno_copy], ax
		xor	ax, ax
		push	ax
if LDATA
		push	word ptr [bp+@@pathP+2]
endif
		push	word ptr [bp+@@pathP]
		nopcall	__chmod
		add	sp, 2 + dPtrSize
		mov	[bp+@@attrib], ax
		mov	ax, [bp+@@errno_copy]
		mov	_errno,	ax
		test	byte ptr [bp+@@oflag+1], O_CREAT shr 8
		jnz	short @@umask
		jmp	@@OpenExisting

@@umask:
		mov	ax, __notUmask
		and	[bp+@@mode], ax
		mov	ax, [bp+@@mode]
		test	ax, S_IREAD or S_IWRITE
		jnz	short @@gotAttribs?
		mov	ax, 1
		push	ax
		call	__IOERROR

@@gotAttribs?:
		cmp	[bp+@@attrib], not 0
		jnz	short @@excl?
		cmp	__doserrno, e_fileNotFound
		jz	short @@write?
		push	__doserrno
		jmp	short @@retIOERROR

@@write?:
		test	byte ptr [bp+@@mode], S_IWRITE
		jz	short @@readOnly
		xor	ax, ax
		jmp	short @@sharing?

@@readOnly:
		mov	ax, _A_RDONLY

@@sharing?:
		mov	[bp+@@attrib], ax
		test	byte ptr [bp+@@oflag], 0F0h
		jz	short @@noSharing
if LDATA
		push	word ptr [bp+@@pathP+2]
endif
		push	word ptr [bp+@@pathP]
		xor	ax, ax
		push	ax
		call	dosCreat
		mov	[bp+@@fildes], ax
		or	ax, ax
		jge	short @@creatError
		jmp	@@retFD

@@excl?:
		test	byte ptr [bp+@@oflag+1], O_EXCL	shr 8
		jz	short @@OpenExisting
		mov	ax, e_fileExists
		push	ax

@@retIOERROR:
		call	__IOERROR
		jmp	@@ret

@@creatError:
		push	[bp+@@fildes]
		nopcall	__rtl_close
		pop	cx
		jmp	short @@OpenExisting

@@noSharing:
if LDATA
		push	word ptr [bp+@@pathP+2]
endif
		push	word ptr [bp+@@pathP]
		push	[bp+@@attrib]
		call	dosCreat
		mov	[bp+@@fildes], ax
		or	ax, ax
		jl	short @@retFD_j
		jmp	@@set_openfd

@@retFD_j:
		jmp	@@retFD

@@OpenExisting:
		push	[bp+@@oflag]
if LDATA
		push	word ptr [bp+@@pathP+2]
endif
		push	word ptr [bp+@@pathP]
		nopcall	__rtl_open
		add	sp, 2 + dPtrSize
		mov	[bp+@@fildes], ax
		or	ax, ax
		jl	short @@set_openfd
		xor	ax, ax
		push	ax
		push	[bp+@@fildes]
		nopcall	_ioctl
		pop	cx
		pop	cx
		mov	[bp+@@devstat],	ax
		test	al, 80h
		jz	short @@trunc?
		or	[bp+@@oflag], O_DEVICE
		test	byte ptr [bp+@@oflag+1], O_BINARY shr 8
		jz	short @@setReadOnly?
		and	ax, 0FFh
		or	ax, 20h
		xor	dx, dx
		push	dx
		push	ax
		mov	ax, 1
		push	ax
		push	[bp+@@fildes]
		nopcall	_ioctl
		add	sp, 8
		jmp	short @@setReadOnly?

@@trunc?:
		test	byte ptr [bp+@@oflag+1], O_TRUNC shr 8
		jz	short @@setReadOnly?
		push	[bp+@@fildes]
		call	dosWriteNone

@@setReadOnly?:
		test	byte ptr [bp+@@attrib],	_A_RDONLY
		jz	short @@set_openfd
		test	byte ptr [bp+@@oflag+1], O_CREAT shr 8
		jz	short @@set_openfd
		test	byte ptr [bp+@@oflag], 0F0h
		jz	short @@set_openfd
		mov	ax, 1
		push	ax
		push	ax
if LDATA
		push	word ptr [bp+@@pathP+2]
endif
		push	word ptr [bp+@@pathP]
		nopcall	__chmod
		add	sp, 4 + dPtrSize

@@set_openfd:
		cmp	[bp+@@fildes], 0
		jl	short @@retFD
		mov	word ptr _exitopen+2, seg __xclose
		mov	word ptr _exitopen, offset __xclose
		test	byte ptr [bp+@@oflag+1], (O_CREAT or O_TRUNC) shr 8
		jz	short @@notChanged
		mov	ax, O_CHANGED
		jmp	short @@notRunflags?

@@notChanged:
		xor	ax, ax

@@notRunflags?:
		mov	dx, [bp+@@oflag]
		and	dx, not	_O_RUNFLAGS
		or	ax, dx
		push	ax
		test	byte ptr [bp+@@attrib],	_A_RDONLY
		jz	short @@_fdWritable
		xor	ax, ax
		jmp	short @@_fdReadOnly

@@_fdWritable:
		mov	ax, _O_WRITABLE

@@_fdReadOnly:
		pop	dx
		or	dx, ax
		mov	bx, [bp+@@fildes]
		add	bx, bx
		mov	_openfd[bx], dx

@@retFD:
		mov	ax, [bp+@@fildes]

@@ret:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret
_open		endp

; static int pascal near Displacement (FILE *fp)
Displacement	proc near
@@P		= dword	ptr -6
@@disp		= word ptr -2
@@fp		= DPTR_ 4
if LDATA
	@@local_stack = 6
else
	@@local_stack = 2
endif

		push	bp
		mov	bp, sp
		sub	sp, @@local_stack
		push	si
		push	di
		LES_	bx, [bp+@@fp]
		cmp	ES_[bx+FILE.level], 0
		jge	short @@absLevel
if LDATA
		mov	cx, ES_[bx+FILE._bsize]
		add	cx, ES_[bx+FILE.level]
		inc	cx
		mov	ax, cx
else
		mov	dx, ES_[bx+FILE._bsize]
		add	dx, ES_[bx+FILE.level]
		inc	dx
		mov	ax, dx
endif
		jmp	short @@bin?

@@absLevel:
		LES_	bx, [bp+@@fp]
		mov	ax, ES_[bx+FILE.level]
		cwd
		xor	ax, dx
		sub	ax, dx
if LDATA
		mov	cx, ax
else
		mov	dx, ax
endif

@@bin?:
		mov	[bp+@@disp], ax
		LES_	bx, [bp+@@fp]
		test	byte ptr ES_[bx+FILE.flags], 40h
		jnz	short @@ret
		LES_	bx, [bp+@@fp]
if LDATA
		mov	dx, word ptr ES_[bx+FILE.curp+2]
		mov	ax, word ptr ES_[bx+FILE.curp]
		mov	word ptr [bp+@@P+2], dx
		mov	word ptr [bp+@@P], ax
else
		mov	cx, [bx+FILE.curp]
endif
		cmp	ES_[bx+FILE.level], 0
		jge	short @@readLoop
		jmp	short @@writeLoop

@@write:
if LDATA
		dec	word ptr [bp+@@P]
		LES_	bx, [bp+@@P]
else
		dec	cx
		mov	bx, cx
endif
		cmp	byte ptr ES_[bx], 0Ah
		jnz	short @@writeLoop
		inc	[bp+@@disp]

@@writeLoop:
if LDATA
		mov	ax, cx
		dec	cx
else
		mov	ax, dx
		dec	dx
endif
		or	ax, ax
		jnz	short @@write
		jmp	short @@ret

@@read:
if LDATA
		les	bx, [bp+@@P]
		inc	word ptr [bp+@@P]
else
		mov	bx, cx
		inc	cx
endif
		cmp	byte ptr ES_[bx], 0Ah
		jnz	short @@readLoop
		inc	[bp+@@disp]

@@readLoop:
if LDATA
		mov	ax, cx
		dec	cx
else
		mov	ax, dx
		dec	dx
endif
		or	ax, ax
		jnz	short @@read

@@ret:
		mov	ax, [bp+@@disp]
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret	dPtrSize
Displacement	endp

; int __cdecl fseek(FILE *fp, __int32 ofs, int whence)
_fseek		proc
@@fp		= DPTR_ 2 + dPtrSize
@@ofs		= dword	ptr 2 + dPtrSize + dPtrSize
@@whence	= word ptr 2 + dPtrSize + dPtrSize + 4

		push	bp
		mov	bp, sp
		push	si
		push	di
if LDATA
		push	word ptr [bp+@@fp+2]
endif
		push	word ptr [bp+@@fp]
		nopcall	_fflush
		popCX_
		pop	cx
		or	ax, ax
		jz	short @@fromCur?
		mov	ax, 0FFFFh
		jmp	short @@ret

@@fromCur?:
		cmp	[bp+@@whence],	1
		jnz	short @@set
		LES_	bx, [bp+@@fp]
		cmp	ES_[bx+FILE.level], 0
		jle	short @@set
if LDATA
		push	word ptr [bp+@@fp+2]
endif
		push	bx
		call	Displacement
		cwd
		sub	word ptr [bp+@@ofs], ax
		sbb	word ptr [bp+@@ofs+2], dx

@@set:
		LES_	bx, [bp+@@fp]
		and	ES_[bx+FILE.flags], 0FE5Fh
		mov	ES_[bx+FILE.level], 0
if LDATA
		mov	dx, word ptr ES_[bx+FILE.buffer+2]
endif
		mov	ax, word ptr ES_[bx+FILE.buffer]
if LDATA
		mov	word ptr ES_[bx+FILE.curp+2], dx
endif
		mov	word ptr ES_[bx+FILE.curp], ax
		push	[bp+@@whence]
		push	word ptr [bp+@@ofs+2]
		push	word ptr [bp+@@ofs]
		mov	al, ES_[bx+FILE.fd]
		cbw
		push	ax
		nopcall	_lseek
		add	sp, 8
		cmp	dx, -1
		jnz	short @@ret0
		cmp	ax, -1
		jnz	short @@ret0
		mov	ax, 0FFFFh
		jmp	short @@ret

@@ret0:
		xor	ax, ax

@@ret:
		pop	di
		pop	si
		pop	bp
		ret
_fseek		endp

; __int32 __cdecl ftell(FILE *fp)
_ftell		proc
@@l		= dword	ptr -8
@@a		= dword	ptr -4
@@fp		= DPTR_	2 + dPtrSize

		push	bp
		mov	bp, sp
		sub	sp, 8
		push	si
		push	di
		mov	ax, 1
		push	ax
		xor	ax, ax
		push	ax
		push	ax
		LES_	bx, [bp+@@fp]
		mov	al, ES_[bx+FILE.fd]
		cbw
		push	ax
		nopcall	_lseek
		add	sp, 8
		mov	word ptr [bp+@@a+2], dx
		mov	word ptr [bp+@@a], ax
		cmp	dx, -1
		jnz	short @@writing?
		cmp	ax, -1
		jnz	short @@writing?
		jmp	@@retA

@@writing?:
		LES_	bx, [bp+@@fp]
		cmp	ES_[bx+FILE.level], 0
if LDATA
		jl	short @@appending?
		jmp	@@subDisplacement
else
		jge	short @@subDisplacement
endif

@@appending?:
		mov	al, ES_[bx+FILE.fd]
		cbw
		add	ax, ax
		mov	bx, ax
		test	byte ptr (_openfd+1)[bx], 8
		jz	short @@addDisplacement
		mov	ax, 2
		push	ax
		xor	ax, ax
		push	ax
		push	ax
		mov	bx, word ptr [bp+@@fp]
		mov	al, ES_[bx+FILE.fd]
		cbw
		push	ax
		nopcall	_lseek
		add	sp, 8
		mov	word ptr [bp+@@l+2], dx
		mov	word ptr [bp+@@l], ax
		cmp	dx, -1
		jnz	short @@restore
		cmp	ax, -1
		jnz	short @@restore
		jmp	short @@ret

@@restore:
		xor	ax, ax
		push	ax
		push	word ptr [bp+@@a+2]
		push	word ptr [bp+@@a]
		LES_	bx, [bp+@@fp]
		mov	al, ES_[bx+FILE.fd]
		cbw
		push	ax
		nopcall	_lseek
		add	sp, 8
		cmp	dx, -1
		jnz	short @@setAToL
		cmp	ax, -1
		jnz	short @@setAToL
		mov	dx, -1
		mov	ax, -1
		jmp	short @@ret

@@setAToL:
		mov	dx, word ptr [bp+@@l+2]
		mov	ax, word ptr [bp+@@l]
		mov	word ptr [bp+@@a+2], dx
		mov	word ptr [bp+@@a], ax

@@addDisplacement:
if LDATA
		push	word ptr [bp+@@fp+2]
endif
		push	word ptr [bp+@@fp]
		call	Displacement
		cwd
		add	word ptr [bp+@@a], ax
		adc	word ptr [bp+@@a+2], dx
		jmp	short @@retA

@@subDisplacement:
if LDATA
		push	word ptr [bp+@@fp+2]
endif
		push	word ptr [bp+@@fp]
		call	Displacement
		cwd
		sub	word ptr [bp+@@a], ax
		sbb	word ptr [bp+@@a+2], dx

@@retA:
		mov	dx, word ptr [bp+@@a+2]
		mov	ax, word ptr [bp+@@a]

@@ret:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret
_ftell		endp
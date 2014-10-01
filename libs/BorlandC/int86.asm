; int __cdecl int86(int intno, union REGS *inregs, union REGS *outregs)
_int86		proc DIST
@@segp		= SREGS	ptr -(size SREGS)
@@intno		= word ptr (dPtrSize + 2)
@@inregs	= DPTR_ (dPtrSize + 4)
@@outregs	= DPTR_ (dPtrSize + 4 + dPtrSize)

		push	bp
		mov	bp, sp
		sub	sp, size SREGS
		push	si
		push	di
		push	ss
		lea	ax, [bp+@@segp]
		push	ax
		nopcall	_segread
		pop	cx
		pop	cx
		push	ss
		lea	ax, [bp+@@segp]
		push	ax
		push	word ptr [bp+@@outregs+2]
		push	word ptr [bp+@@outregs]
		push	word ptr [bp+@@inregs+2]
		push	word ptr [bp+@@inregs]
		push	[bp+@@intno]
		call	_int86x
		add	sp, (dPtrSize * 2) + 6
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret
_int86		endp

; int __cdecl int86x(int intno, union REGS *inregs, union REGS *outregs, struct SREGS *segregs)
_int86x		proc DIST
@@Code		= byte ptr -(4 + 10)
@@Vector	= dword	ptr -4
@@intno		= word ptr (dPtrSize + 2)
@@inregs	= DPTR_ (dPtrSize + 4)
@@outregs	= DPTR_ (dPtrSize + 4 + dPtrSize)
@@segregs	= DPTR_ (dPtrSize + 4 + dPtrSize + dPtrSize)

		push	bp
		mov	bp, sp
		sub	sp, (4 + 10)
		push	si
		push	di
		push	ds
		lea	cx, [bp+@@Code]
		mov	word ptr [bp+@@Vector],	cx
		mov	word ptr [bp+@@Vector+2], ss
		mov	[bp+@@Code], 55h
		mov	[bp+@@Code+1], 0CDh
		mov	ax, [bp+@@intno]
		mov	[bp+@@Code+2], al
		mov	word ptr [bp+@@Code+3],	0CB5Dh
		cmp	al, 25h
		jb	short @@SetRegs
		cmp	al, 26h
		ja	short @@SetRegs
		mov	[bp+@@Code+3], 36h
		mov	word ptr [bp+@@Code+4],	68Fh
		mov	word ptr [bp+@@Code+6],	cx
		mov	word ptr [bp+@@Code+8],	0CB5Dh

@@SetRegs:
		LDS_	si, [bp+@@segregs]
		push	[si+SREGS._es]
		push	[si+SREGS._ds]
		LDS_	si, [bp+@@inregs]
		mov	ax, [si+WORDREGS._ax]
		mov	bx, [si+WORDREGS._bx]
		mov	cx, [si+WORDREGS._cx]
		mov	dx, [si+WORDREGS._dx]
		mov	di, [si+WORDREGS._di]
		mov	si, [si+WORDREGS._si]
		pop	ds
		pop	es
		clc
		call	[bp+@@Vector]
		pushf
		pushf
		push	si
		push	ds
		push	es
ife	LDATA
		mov	ds, [bp-20]
endif
		LDS_	si, [bp+@@segregs]
		pop	[si+SREGS._es]
		pop	[si+SREGS._ds]
		LDS_	si, [bp+@@outregs]
		pop	[si+WORDREGS._si]
		pop	[si+WORDREGS._flags]
		pop	[si+WORDREGS._cflags]
		and	[si+WORDREGS._cflags], 1
		mov	[si+WORDREGS._di], di
		mov	[si+WORDREGS._dx], dx
		mov	[si+WORDREGS._cx], cx
		mov	[si+WORDREGS._bx], bx
		mov	[si+WORDREGS._ax], ax
		pop	ds
		jz	short @@int86Ok
		push	ax
		push	ax
		call	__IOERROR
		pop	ax

@@int86Ok:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret
_int86x		endp

; int __cdecl intdos(union REGS *inregs, union REGS *outregs)
_intdos		proc DIST
@@segp		= SREGS	ptr -(size SREGS)
@@inregs	= DPTR_ (dPtrSize + 2)
@@outregs	= DPTR_ (dPtrSize + 2 + dPtrSize)

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
		call	_intdosx
		add	sp, (dPtrSize * 2) + 4
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret
_intdos		endp

; int __cdecl intdosx(union REGS *inregs, union REGS *outregs, struct SREGS *segregs)
_intdosx	proc DIST
@@inregs	= DPTR_ (2 + dPtrSize)
@@outregs	= DPTR_ (2 + dPtrSize + dPtrSize)
@@segregs	= DPTR_ (2 + dPtrSize + dPtrSize + dPtrSize)

		push	bp
		mov	bp, sp
		push	si
		push	di
		push	ds
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
		push	bp
		int	21h
		pop	bp
		pushf
		pushf
		push	si
		push	ds
		push	es
ife	LDATA
		mov	ds, [bp-6]
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
		jz	short @@intdosOK
		push	ax
		push	ax
		call	__IOERROR
		pop	ax

@@intdosOK:
		pop	di
		pop	si
		pop	bp
		ret
_intdosx	endp

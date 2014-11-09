; double __pascal __near _ldtrunc(int flag, long double x, double xhuge)
__ldtrunc	proc near
@@xfloat	= qword	ptr -0Ch
@@cword2	= word ptr -4
@@cword		= word ptr -2
@@xhuge		= qword	ptr  4
@@x		= tbyte	ptr  0Ch
@@flag		= word ptr  16h

		push	bp
		mov	bp, sp
		sub	sp, 0Ch
		xor	cx, cx
		mov	ax, 43FEh
		mov	bx, 3BCDh
		cmp	[bp+@@flag], 0
		jnz	short @@start
		mov	ax, 407Eh
		mov	bx, 3F6Ah

@@start:
		mov	dx, word ptr [bp+@@x+8]
		shl	dx, 1
		rcl	cx, 1
		shr	dx, 1
		cmp	dx, 7FFFh
		jz	short @@ret
		cmp	dx, ax
		jz	short @@hugex
		jle	short @@notinf
		fld	[bp+@@xhuge]
		jmp	short @@ret1

@@hugex:
		fstcw	[bp+@@cword]
		mov	ax, 0C00h
		fwait
		or	ax, [bp+@@cword]
		mov	[bp+@@cword2], ax
		fldcw	[bp+@@cword2]
		fld	[bp+@@x]
		cmp	[bp+@@flag], 0
		jnz	short @@s1
		fstp	dword ptr [bp+@@xhuge]
		fld	dword ptr [bp+@@xhuge]
		jmp	short @@s2

@@s1:
		fstp	[bp+@@xhuge]
		fld	[bp+@@xhuge]

@@s2:
		fldcw	[bp+@@cword]
		mov	sp, bp
		pop	bp
		ret	14h

@@notinf:
		mov	ax, dx
		or	ax, word ptr [bp+@@x+6]
		or	ax, word ptr [bp+@@x+4]
		or	ax, word ptr [bp+@@x+2]
		or	ax, word ptr [bp+@@x]
		jz	short @@ret
		cmp	dx, bx
		jge	short @@ret
		fldz

@@ret1:
		or	cx, cx
		jz	short @@ret0
		fchs

@@ret0:
		mov	_errno,	ERANGE
		mov	sp, bp
		pop	bp
		ret	14h

@@ret:
		cmp	[bp+@@flag], 0
		jz	short @@single
		fld	[bp+@@x]
		fstp	[bp+@@xfloat]
		fld	[bp+@@xfloat]
		jmp	short @@end

@@single:
		fld	[bp+@@x]
		fstp	dword ptr [bp+@@xfloat]
		fld	dword ptr [bp+@@xfloat]

@@end:
		mov	sp, bp
		pop	bp
		ret	14h
__ldtrunc	endp

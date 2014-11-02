; long double __pascal __near _pow10(int p)
		public __pow10
__pow10		proc near

MAX_87_EXP	 = 4932
p		= word ptr  4

		push	bp
		mov	bp, sp
		push	si
ifdef __HUGE__
		mov	ax, seg e0to7
		mov	ds, ax
endif
		mov	ax, [bp+p]
		cmp	ax, -MAX_87_EXP
		jge	short @@tooLarge?
		fldz
		jmp	@@p10_end

@@tooLarge?:
		cmp	ax, MAX_87_EXP
		jle	short @@10pow0
		fld	eINF
		jmp	@@p10_end

@@10pow0:
		or	ax, ax
		jnz	short @@nontrivial
		fld1
		jmp	@@p10_end

@@nontrivial:
		or	ax, ax
		jge	short @@p10_abs
		neg	ax

@@p10_abs:
		mov	si, 7
		and	si, ax
		shl	si, 1
		shl	si, 1
		fld	e0to7[si]
		shr	ax, 1
		shr	ax, 1
		shr	ax, 1
		shr	ax, 1
		jnb	short @@p10_maybe16
		fmul	e8

@@p10_maybe16:
		jnz	short @@keep_going
		jmp	short @@p10_checkSign

@@keep_going:
		shr	ax, 1
		jnb	short @@p10_maybe32
		fmul	e16

@@p10_maybe32:
		shr	ax, 1
		jnb	short @@p10_maybe64
		fld	tbyte ptr e32
		fmulp	st(1), st

@@p10_maybe64:
		shr	ax, 1
		jnb	short @@p10_maybe128
		fld	tbyte ptr e64
		fmulp	st(1), st

@@p10_maybe128:
		shr	ax, 1
		jnb	short @@p10_maybe256
		fld	tbyte ptr e128
		fmulp	st(1), st

@@p10_maybe256:
		shr	ax, 1
		jnb	short @@p10_maybe512
		fld	tbyte ptr e256
		fmulp	st(1), st

@@p10_maybe512:
		shr	ax, 1
		jnb	short @@p10_maybe1024
		fld	tbyte ptr e512
		fmulp	st(1), st

@@p10_maybe1024:
		shr	ax, 1
		jnb	short @@p10_maybe2048
		fld	tbyte ptr e1024
		fmulp	st(1), st

@@p10_maybe2048:
		shr	ax, 1
		jnb	short @@p10_maybe4096
		fld	tbyte ptr e2048
		fmulp	st(1), st

@@p10_maybe4096:
		shr	ax, 1
		jnb	short @@p10_checkSign
		fld	tbyte ptr e4096
		fmulp	st(1), st

@@p10_checkSign:
		test	byte ptr [bp+p+1], 80h
		jz	short @@p10_end
		fdivr	e0to7

@@p10_end:
		pop	si
		pop	bp
		ret	2
__pow10		endp

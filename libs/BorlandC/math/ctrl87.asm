; unsigned int __cdecl _control87(unsigned int new, unsigned int mask)
		public __control87
__control87	proc
@@Control	= word ptr -2
@@new		= word ptr (cPtrSize + 2)
@@mask		= word ptr (cPtrSize + 4)

		push	bp
		mov	bp, sp
		sub	sp, 2
		emul
		fstcw	[bp+@@Control]
		mov	ax, [bp+@@new]
		mov	bx, [bp+@@mask]
		and	ax, bx
		not	bx
		fwait
		mov	dx, [bp+@@Control]
		and	dx, bx
		or	dx, ax
		mov	cl, dl
		and	cl, 3Fh
		mov	ss:__emu+2, cl
		mov	ax, dx
		cmp	ss:__emu+6, 0
		jz	short @@ctrl
		mov	ax, dx
ifdef DeepStack
		and	ax, not (EM_DENORMAL | EM_INVALID)
else
		and	ax, not EM_DENORMAL
endif
		cmp	ss:__emu+6, 3
		jl	short @@ctrl
		or	al, 2

@@ctrl:
		mov	[bp+@@Control],	ax
		fldcw	[bp+@@Control]
		xchg	ax, dx
		mov	sp, bp
		pop	bp
		ret
__control87	endp

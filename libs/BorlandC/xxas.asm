; __RefDestructorCount(void)
		public @__RefDestructorCount$qv
@__RefDestructorCount$qv proc far	; CODE XREF: ___InitExceptBlocks+42p
		mov	dx, ss
		mov	ax, 10h
		retf
@__RefDestructorCount$qv endp

; __RefExceptionList(void)
		public @__RefExceptionList$qv
@__RefExceptionList$qv proc far		; CODE XREF: ___InitExceptBlocks+5Cp
					; ___ExitExceptBlocks+4p
		mov	dx, ss
		mov	ax, 14h
		retf
@__RefExceptionList$qv endp

		public ___InitExceptBlocks
___InitExceptBlocks proc far
		mov	es, ax
		mov	dx, bx
		mov	cx, bp
		mov	bx, es:[bx+4]
		add	bx, cx
		mov	ss:[bx+6], dx
		mov	ss:[bx+8], ax
		mov	ax, sp
		add	ax, 4
		mov	ss:[bx+0Ah], ax
		mov	ax, seg	DGROUP
		mov	ss:[bx+0Eh], ax
		mov	ss:[bx+10h], si
		mov	word ptr ss:[bx+2], offset __ExceptionHandler
		mov	word ptr ss:[bx+4], seg	__ExceptionHandler
		mov	word ptr ss:[bx+0Ch], 0
		mov	word ptr ss:[bx+12h], 0
		push	bx
		call	@__RefDestructorCount$qv ; __RefDestructorCount(void)
		pop	bx
		xchg	ax, bx
		mov	es, dx
		mov	cx, es:[bx]
		mov	dx, es:[bx+2]
		mov	bx, ax
		mov	ss:[bx+1Ah], cx
		mov	ss:[bx+1Ch], dx
		push	bx
		call	@__RefExceptionList$qv	; __RefExceptionList(void)
		pop	bx
		xchg	ax, bx
		mov	es, dx
		mov	cx, es:[bx]
		mov	es:[bx], ax
		mov	bx, ax
		mov	ss:[bx], cx
		retf
___InitExceptBlocks endp

		public ___ExitExceptBlocks
___ExitExceptBlocks proc far

arg_0		= word ptr  6

		push	bp
		mov	bp, sp
		call	@__RefExceptionList$qv	; __RefExceptionList(void)
		mov	bx, [bp+arg_0]
		xchg	ax, bx
		mov	es, dx
		mov	es:[bx], ax
		pop	bp
		retf	2
___ExitExceptBlocks endp

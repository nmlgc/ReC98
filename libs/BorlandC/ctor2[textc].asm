; string::string(string	const &)
		public @string@$bctr$qmx6string
@string@$bctr$qmx6string proc far

@@var_1E		= word ptr -1Eh
@@arg_0		= dword	ptr  6
@@arg_4		= dword	ptr  0Ah

		push	bp
		mov	bp, sp
		sub	sp, 1Eh
		push	si
		push	di
		mov	ax, seg	ctor2_1002D
		mov	bx, offset ctor2_1002D
		call	___InitExceptBlocks
		mov	ax, word ptr [bp+@@arg_0]
		or	ax, word ptr [bp+@@arg_0+2]
		jnz	short @@ctor2_100CF
		mov	ax, 4
		push	ax
		call	@$bnew$qui	; operator new(uint)
		pop	cx
		mov	word ptr [bp+@@arg_0+2], dx
		mov	word ptr [bp+@@arg_0], ax
		or	ax, dx
		jz	short @@ctor2_100E9

@@ctor2_100CF:
		les	bx, [bp+@@arg_4]
		mov	dx, es:[bx+2]
		mov	ax, es:[bx]
		les	bx, [bp+@@arg_0]
		mov	es:[bx+2], dx
		mov	es:[bx], ax
		les	bx, es:[bx]
		inc	word ptr es:[bx]

@@ctor2_100E9:
		call	@__RefDestructorCount$qv ; __RefDestructorCount(void)
		mov	bx, ax
		mov	es, dx
		add	word ptr es:[bx], 1
		adc	word ptr es:[bx+2], 0
		push	[bp+@@var_1E]
		call	___ExitExceptBlocks
		mov	dx, word ptr [bp+@@arg_0+2]
		mov	ax, word ptr [bp+@@arg_0]
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
@string@$bctr$qmx6string endp

ctor2_1010F	db 6, 0, 3, 0, 26h, 0, 2 dup(0FFh), 7, 0, 2Eh, 0, 3Ah
		db 0Dh dup(0), 2, 0, 2,	0
		dd ctor2_10033
		dw 5
		dw 3Eh
		db 'xalloc',0
		db    0
		dd ctor2_10151
		db 2 dup(0), 3,	0Dh dup(0)
ctor2_10151	db 4, 0, 3, 0, 26h, 0, 2 dup(0FFh), 3, 0, 2Ch, 0, 30h
		db 0Dh dup(0), 1, 0, 1,	0
		dd @xmsg@$bdtr$qv	; xmsg::~xmsg(void)
		dw 5
		dw 34h
		db 'xmsg',0
		dd 0
		dd 0
		dd 0
		db 0

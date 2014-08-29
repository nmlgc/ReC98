new_10020	dd new_1024B
		db 4, 0, 0FAh, 0FFh, 6 dup(0)
new_1002E	db 4 dup(0), 0DCh, 0FFh, 2 dup(0), 5, 3	dup(0)
		dw offset new_10020

; xnew_handler(void)
		public @xnew_handler$qv
@xnew_handler$qv proc far

@@var_6		= byte ptr -6
@@var_2		= word ptr -2

		push	bp
		mov	bp, sp
		sub	sp, 24h
		push	si
		push	di
		mov	ax, seg	new_1002E
		mov	bx, offset new_1002E
		nopcall	___InitExceptBlocks
		xor	ax, ax
		push	ax
		push	ax
		push	ax
		push	ax
		mov	ax, 5
		push	ax
		mov	ax, seg	new_10126
		push	ax
		mov	ax, offset new_10126
		push	ax
		xor	ax, ax
		push	ax
		push	ax
		push	ds
		mov	ax, offset ___xalloc
		push	ax
		push	ss
		lea	ax, [bp+@@var_6]
		push	ax
		nopcall	@xmsg@$bctr$qmx4xmsg ; xmsg::xmsg(xmsg &)
		add	sp, 8
		mov	ax, ds:new_10324
		mov	[bp+@@var_2], ax
		nopcall	@__RefDestructorCount$qv ; __RefDestructorCount(void)
		mov	bx, ax
		mov	es, dx
		add	word ptr es:[bx], 1
		adc	word ptr es:[bx+2], 0
		lea	ax, [bp+@@var_6]
		push	ss
		push	ax
		push	cs
		mov	ax, offset new_1024B
		push	ax
		nopcall	@_ThrowException$qnvt1t1t1uiuiuinuc ; _ThrowException(void *,void *,void *,void	*,uint,uint,uint,uchar *)
		add	sp, 1Ah
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
@xnew_handler$qv endp


; set_new_handler(void (*)(void))
		public @set_new_handler$qnqv$v
@set_new_handler$qnqv$v	proc far

@@var_4		= word ptr -4
@@var_2		= word ptr -2
@@arg_0		= word ptr  6
@@arg_2		= word ptr  8

		push	bp
		mov	bp, sp
		sub	sp, 4
		push	si
		push	di
		mov	dx, word ptr ds:__new_handler+2
		mov	ax, word ptr ds:__new_handler
		mov	[bp+@@var_2], dx
		mov	[bp+@@var_4], ax
		mov	dx, [bp+@@arg_2]
		mov	ax, [bp+@@arg_0]
		mov	word ptr ds:__new_handler+2, dx
		mov	word ptr ds:__new_handler, ax
		mov	dx, [bp+@@var_2]
		mov	ax, [bp+@@var_4]
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
@set_new_handler$qnqv$v	endp


; int __cdecl __far operator new(size_t	size)
		public @$bnew$qui
@$bnew$qui	proc far

@@var_4		= word ptr -4
@@var_2		= word ptr -2
@@size		= word ptr  6

		push	bp
		mov	bp, sp
		sub	sp, 4
		push	si
		push	di
		mov	[bp+@@var_2], 0
		mov	[bp+@@var_4], 0
		cmp	[bp+@@size], 0
		jz	short @@new_100F2
		mov	ax, [bp+@@size]
		jmp	short @@new_100F5

@@new_100F2:
		mov	ax, 1

@@new_100F5:
		mov	[bp+@@size], ax
		jmp	short @@new_100FE

@@new_100FA:
		call	ds:__new_handler ; xnew_handler(void)

@@new_100FE:
		push	[bp+@@size]	; size
		nopcall	_malloc
		pop	cx
		mov	[bp+@@var_2], dx
		mov	[bp+@@var_4], ax
		or	ax, dx
		jnz	short @@new_1011A
		mov	ax, word ptr ds:__new_handler
		or	ax, word ptr ds:__new_handler+2
		jnz	short @@new_100FA

@@new_1011A:
		mov	dx, [bp+@@var_2]
		mov	ax, [bp+@@var_4]
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
@$bnew$qui	endp


new_10126	proc far

@@arg_0		= dword	ptr  6
@@arg_4		= dword	ptr  0Ah

		push	bp
		mov	bp, sp
		push	si
		push	di
		push	word ptr [bp+@@arg_4+2]
		push	word ptr [bp+@@arg_4]
		push	word ptr [bp+@@arg_0+2]
		push	word ptr [bp+@@arg_0]
		nopcall	@xmsg@$bctr$qmx4xmsg ; xmsg::xmsg(xmsg &)
		add	sp, 8
		les	bx, [bp+@@arg_4]
		mov	ax, es:[bx+4]
		les	bx, [bp+@@arg_0]
		mov	es:[bx+4], ax
		nopcall	@__RefDestructorCount$qv ; __RefDestructorCount(void)
		mov	bx, ax
		mov	es, dx
		add	word ptr es:[bx], 1
		adc	word ptr es:[bx+2], 0
		mov	dx, word ptr [bp+@@arg_0+2]
		mov	ax, word ptr [bp+@@arg_0]
		pop	di
		pop	si
		pop	bp
		retf
new_10126	endp

new_10169	dd new_1024B
		db 2 dup(0)
		dd ___xalloc
		dd new_10211
		db 4, 0, 0FCh, 0FFh, 6 dup(0)
new_10181	db 4 dup(0), 0DEh, 0FFh, 2 dup(0), 5, 3	dup(0)
		dw offset new_10169

new_1018F	proc far

@@var_22		= word ptr -22h
@@var_16		= word ptr -16h
@@var_4		= byte ptr -4

		push	bp
		mov	bp, sp
		sub	sp, 22h
		push	si
		push	di
		mov	ax, seg	new_10181
		mov	bx, offset new_10181
		nopcall	___InitExceptBlocks
		mov	[bp+@@var_16], 6
		xor	ax, ax
		push	ax
		push	ds
		mov	ax, offset aOutOfMemory	; "Out of memory"
		push	ax
		push	ss
		lea	ax, [bp+@@var_4]
		push	ax
		call	@string@$bctr$qnxc ; string::string(char *)
		add	sp, 8
		lea	ax, [bp+@@var_4]
		push	ss
		push	ax
		push	ds
		mov	ax, offset ___xalloc
		push	ax
		nopcall	@xalloc@$bctr$qmx6stringui ; xalloc::xalloc(string &,uint)
		mov	ax, 2
		push	ax
		push	ss
		lea	ax, [bp+@@var_4]
		push	ax
		call	@string@$bdtr$qv ; string::~string(void)
		add	sp, 10h
		push	[bp+@@var_22]
		nopcall	___ExitExceptBlocks
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
new_1018F	endp



new_101EA	proc far
		push	si
		push	di
		nopcall	@__RefDestructorCount$qv ; __RefDestructorCount(void)
		mov	bx, ax
		mov	es, dx
		sub	word ptr es:[bx], 1
		sbb	word ptr es:[bx+2], 0
		xor	ax, ax
		push	ax
		push	ds
		mov	ax, offset ___xalloc
		push	ax
		nopcall	@xmsg@$bdtr$qv	; xmsg::~xmsg(void)
		add	sp, 6
		pop	di
		pop	si
		retf
new_101EA	endp

new_10211	db 4, 0, 3, 0, 26h, 0, 2 dup(0FFh), 3, 0, 2Eh, 0, 32h
		db 0Dh dup(0), 1, 0, 1,	0
		dd @string@$bdtr$qv	; string::~string(void)
		dw 5
		dw 36h
		db 'string',0
		dd 0
		dd 0
		dd 0
		db 0
new_1024B	db 6, 0, 3, 0, 26h, 0, 2 dup(0FFh), 7, 0, 2Eh, 0, 3Ah
		db 0Dh dup(0), 2, 0, 2,	0
		dd new_1028D
		dw 5
		dw 3Eh
		db 'xalloc',0
		db    0
		dd new_102DA
		db 2 dup(0), 3,	0Dh dup(0)

new_1028D	proc far

@@arg_0		= word ptr  6
@@arg_2		= word ptr  8
@@arg_4		= byte ptr  0Ah

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	ax, [bp+@@arg_0]
		or	ax, [bp+@@arg_2]
		jz	short @@new_102D4
		nopcall	@__RefDestructorCount$qv ; __RefDestructorCount(void)
		mov	bx, ax
		mov	es, dx
		sub	word ptr es:[bx], 1
		sbb	word ptr es:[bx+2], 0
		xor	ax, ax
		push	ax
		push	[bp+@@arg_2]
		push	[bp+@@arg_0]
		nopcall	@xmsg@$bdtr$qv	; xmsg::~xmsg(void)
		add	sp, 6
		test	[bp+@@arg_4], 1
		jz	short @@new_102D2
		push	[bp+@@arg_2]
		push	[bp+@@arg_0]	; void *
		nopcall	@$bdele$qnv	; operator delete(void *)
		pop	cx
		pop	cx
		jmp	short @@new_102D6

@@new_102D2:
		jmp	short @@new_102D6

@@new_102D4:
		xor	ax, ax

@@new_102D6:
		pop	di
		pop	si
		pop	bp
		retf
new_1028D	endp

new_102DA	db 4, 0, 3, 0, 26h, 0, 2 dup(0FFh), 3, 0, 2Ch, 0, 30h
		db 0Dh dup(0), 1, 0, 1,	0
		dd @xmsg@$bdtr$qv	; xmsg::~xmsg(void)
		dw 5
		dw 34h
		db 'xmsg',0
		dd 0
		dd 0
		dd 0
		db 0

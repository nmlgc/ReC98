strings_10030	proc far
		push	si
		push	di
		pop	di
		pop	si
		retf
strings_10030	endp

strings_10035	dd 0
strings_10039	dd strings_10035
		db 0E2h, 0FFh
strings_1003F	dd strings_10BF5
		dd 0
strings_10047	dd strings_10BBB
		db 4, 0, 0FCh, 0FFh, 2 dup(0)
		dd strings_10BF5
		db 4, 0, 0F8h, 0FFh, 6 dup(0)
strings_1005F	dd strings_10B83
		db    0
		db 2 dup(1), 7 dup(0)
strings_1006D	dd strings_1003F
		db 0DAh, 0FFh, 2 dup(0), 5, 3 dup(0)
		dw offset strings_10047
		db 6, 0, 5, 0, 1, 0
		dw offset strings_1005F
strings_10083	dd strings_10BF5
		dd 0
strings_1008B	dd strings_10BBB
		db 4, 0, 0FCh, 0FFh, 2 dup(0)
		dd strings_10BF5
		db 4, 0, 0F8h, 0FFh, 6 dup(0)
strings_100A3	dd strings_10B83
		db 0
		db 2 dup(1), 7 dup(0)
strings_100B1	dd strings_10083
		db 0DAh, 0FFh, 2 dup(0), 5, 3 dup(0)
		dw offset strings_1008B
		db 6, 0, 5, 0, 1, 0
		dw offset strings_100A3
strings_100C7	dd strings_10BF5
		dd 0
strings_100CF	dd strings_10BBB
		db 4, 0, 0FCh, 0FFh, 2 dup(0)
		dd strings_10BF5
		db 4, 0, 0F8h, 0FFh, 6 dup(0)
strings_100E7	dd strings_10B83
		db 0
		db 2 dup(1), 7 dup(0)
strings_100F5	dd strings_100C7
		db 0DAh, 0FFh, 2 dup(0), 5, 3 dup(0)
		dw offset strings_100CF
		db 6, 0, 5, 0, 1, 0
		dw offset strings_100E7
strings_1010B	dd 0
strings_1010F	dd strings_1010B
		db 0E2h, 0FFh
strings_10115	dd strings_10B41
		dd strings_10BF5
		dd 0
strings_10121	dd strings_10115
strings_10125	db 0E2h, 0FFh, 4 dup(0)
strings_1012B	dd strings_10125+2
		db 0E2h, 0FFh
strings_10131	dd strings_10B41
		dd strings_10AF3
		dd 0
strings_1013D	dd strings_10131
strings_10141	db 0E2h, 0FFh, 4 dup(0)
strings_10147	dd strings_10141+2
		db 0E2h, 0FFh
strings_1014D	dd strings_10B41
		dd strings_10AF3
		dd 0
strings_10159	dd strings_1014D
		db 0E2h, 0FFh


strings_1015F	proc far

@@arg_0		= word ptr  6
@@arg_2		= word ptr  8
@@arg_4		= word ptr  0Ah
@@arg_6		= word ptr  0Ch

		push	bp
		mov	bp, sp
		push	si
		push	di
		push	[bp+@@arg_6]
		push	[bp+@@arg_4]
		push	[bp+@@arg_2]
		push	[bp+@@arg_0]
		nopcall	@xmsg@$bctr$qmx4xmsg ; xmsg::xmsg(xmsg &)
		add	sp, 8
		nopcall	@__RefDestructorCount$qv ; __RefDestructorCount(void)
		mov	bx, ax
		mov	es, dx
		add	word ptr es:[bx], 1
		adc	word ptr es:[bx+2], 0
		mov	dx, [bp+@@arg_2]
		mov	ax, [bp+@@arg_0]
		pop	di
		pop	si
		pop	bp
		retf
strings_1015F	endp


strings_10194	proc far

@@arg_0		= word ptr  6
@@arg_2		= word ptr  8
@@arg_4		= byte ptr  0Ah

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	ax, [bp+@@arg_0]
		or	ax, [bp+@@arg_2]
		jz	short @@strings_101DB
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
		jz	short @@strings_101D9
		push	[bp+@@arg_2]
		push	[bp+@@arg_0]	; void *
		nopcall	@$bdele$qnv	; operator delete(void *)
		pop	cx
		pop	cx
		jmp	short @@strings_101DD

@@strings_101D9:
		jmp	short @@strings_101DD

@@strings_101DB:
		xor	ax, ax

@@strings_101DD:
		pop	di
		pop	si
		pop	bp
		retf
strings_10194	endp


strings_101E1	proc far

@@arg_0		= word ptr  6
@@arg_2		= word ptr  8
@@arg_4		= byte ptr  0Ah

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	ax, [bp+@@arg_0]
		or	ax, [bp+@@arg_2]
		jz	short @@strings_10228
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
		jz	short @@strings_10226
		push	[bp+@@arg_2]
		push	[bp+@@arg_0]	; void *
		nopcall	@$bdele$qnv	; operator delete(void *)
		pop	cx
		pop	cx
		jmp	short @@strings_1022A

@@strings_10226:
		jmp	short @@strings_1022A

@@strings_10228:
		xor	ax, ax

@@strings_1022A:
		pop	di
		pop	si
		pop	bp
		retf
strings_101E1	endp


strings_1022E	proc far

@@arg_0		= word ptr  6
@@arg_2		= word ptr  8
@@arg_4		= byte ptr  0Ah

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	ax, [bp+@@arg_0]
		or	ax, [bp+@@arg_2]
		jz	short @@strings_10275
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
		jz	short @@strings_10273
		push	[bp+@@arg_2]
		push	[bp+@@arg_0]	; void *
		nopcall	@$bdele$qnv	; operator delete(void *)
		pop	cx
		pop	cx
		jmp	short @@strings_10277

@@strings_10273:
		jmp	short @@strings_10277

@@strings_10275:
		xor	ax, ax

@@strings_10277:
		pop	di
		pop	si
		pop	bp
		retf
strings_1022E	endp

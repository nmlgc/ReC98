ctor3_10020	proc far
		push	si
		push	di
		pop	di
		pop	si
		retf
ctor3_10020	endp

ctor3_10025	dd ctor3_1023E
		dd ctor3_101F0
		db 4 dup(0)
ctor3_10031	dd ctor3_101D9
		db 87h,	20h, 0FCh, 0FFh, 6 dup(0)
ctor3_1003F	dd ctor3_10025
		db 0DEh, 0FFh, 2 dup(0), 5, 3 dup(0), 2	dup(0FFh), 6, 0
		db 5, 3	dup(0)
		dw offset ctor3_10031

ctor3_10055	proc far

@@arg_0		= word ptr  6
@@arg_2		= word ptr  8
@@arg_4		= byte ptr  0Ah

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	ax, [bp+@@arg_0]
		or	ax, [bp+@@arg_2]
		jz	short @@ctor3_1009C
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
		jz	short @@ctor3_1009A
		push	[bp+@@arg_2]
		push	[bp+@@arg_0]	; void *
		nopcall	@$bdele$qnv	; operator delete(void *)
		pop	cx
		pop	cx
		jmp	short @@ctor3_1009E

@@ctor3_1009A:
		jmp	short @@ctor3_1009E

@@ctor3_1009C:
		xor	ax, ax

@@ctor3_1009E:
		pop	di
		pop	si
		pop	bp
		retf
ctor3_10055	endp


ctor3_100A2	proc far

@@arg_0		= word ptr  6
@@arg_2		= word ptr  8
@@arg_4		= byte ptr  0Ah

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	ax, [bp+@@arg_0]
		or	ax, [bp+@@arg_2]
		jz	short @@ctor3_100E9
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
		jz	short @@ctor3_100E7
		push	[bp+@@arg_2]
		push	[bp+@@arg_0]	; void *
		nopcall	@$bdele$qnv	; operator delete(void *)
		pop	cx
		pop	cx
		jmp	short @@ctor3_100EB

@@ctor3_100E7:
		jmp	short @@ctor3_100EB

@@ctor3_100E9:
		xor	ax, ax

@@ctor3_100EB:
		pop	di
		pop	si
		pop	bp
		retf
ctor3_100A2	endp

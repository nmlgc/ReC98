ctor2_10020	proc far
		push	si
		push	di
		pop	di
		pop	si
		retf
ctor2_10020	endp

ctor2_10025	dd ctor2_1010F
		db 4 dup(0)
ctor2_1002D	dd ctor2_10025
		db 0E2h, 0FFh

ctor2_10033	proc far

@@arg_0		= word ptr  6
@@arg_2		= word ptr  8
@@arg_4		= byte ptr  0Ah

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	ax, [bp+@@arg_0]
		or	ax, [bp+@@arg_2]
		jz	short @@ctor2_1007A
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
		jz	short @@ctor2_10078
		push	[bp+@@arg_2]
		push	[bp+@@arg_0]	; void *
		nopcall	@$bdele$qnv	; operator delete(void *)
		pop	cx
		pop	cx
		jmp	short @@ctor2_1007C

@@ctor2_10078:
		jmp	short @@ctor2_1007C

@@ctor2_1007A:
		xor	ax, ax

@@ctor2_1007C:
		pop	di
		pop	si
		pop	bp
		retf
ctor2_10033	endp

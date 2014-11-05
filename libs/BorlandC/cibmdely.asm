cibmdely_10030	proc near
		push	si
		push	di
		pop	di
		pop	si
		retn
cibmdely_10030	endp

cibmdely_10035	proc near
		push	si
		push	di
		pushf
		cli
		mov	al, 0
		out	43h, al
		call	cibmdely_10030
		in	al, 40h
		mov	bl, al
		call	cibmdely_10030
		in	al, 40h
		mov	bh, al
		not	bx
		popf
		mov	ax, bx
		pop	di
		pop	si
		retn
cibmdely_10035	endp

cibmdely_10053	proc
@@var_2		= word ptr -2

		push	bp
		mov	bp, sp
		sub	sp, 2
		push	si
		push	di
		cmp	word ptr ds:___conio_type, 1
		jnz	short @@loc_10085
		mov	[bp+@@var_2], 0

@@loc_10067:
		call	cibmdely_10035
		test	al, 1
		jnz	short @@loc_1007C
		mov	cibmdely_100F2, 0
		mov	cibmdely_100F0, 4A9h
		jmp	short @@loc_10085

@@loc_1007C:
		inc	[bp+@@var_2]
		cmp	[bp+@@var_2], 64h	; 'd'
		jl	short @@loc_10067

@@loc_10085:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret
cibmdely_10053	endp

		public ___ibm_delay
___ibm_delay	proc
@@var_6		= word ptr -6
@@var_4		= word ptr -4
@@var_2		= word ptr -2
@@arg_0		= word ptr cPtrSize + 2

		push	bp
		mov	bp, sp
		sub	sp, 6
		push	si
		push	di
		call	cibmdely_10035
		mov	[bp+@@var_6], ax
		xor	dx, dx
		mov	bx, [bp+@@arg_0]
		xor	cx, cx
		push	ax
		push	dx
		mov	dx, cibmdely_100F2
		mov	ax, cibmdely_100F0
		call	N_LXMUL@
		pop	bx
		pop	cx
		add	cx, ax
		adc	bx, dx
		mov	[bp+@@var_2], bx
		mov	[bp+@@var_4], cx
		jmp	short @@loc_100D3

@@loc_100BA:
		cmp	bx, [bp+@@var_6]
		jnb	short @@loc_100D0
		cmp	[bp+@@var_2], 1
		ja	short @@loc_100CD
		jb	short @@loc_100E6
		cmp	[bp+@@var_4], 0
		jb	short @@loc_100E6

@@loc_100CD:
		dec	[bp+@@var_2]

@@loc_100D0:
		mov	[bp+@@var_6], bx

@@loc_100D3:
		call	cibmdely_10035
		mov	bx, ax
		xor	dx, dx
		cmp	dx, [bp+@@var_2]
		jb	short @@loc_100BA
		jnz	short @@loc_100E6
		cmp	ax, [bp+@@var_4]
		jb	short @@loc_100BA

@@loc_100E6:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret
___ibm_delay	endp

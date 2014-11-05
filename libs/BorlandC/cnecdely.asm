cnecdely_10010	proc near
@@arg_0		= word ptr  4

		push	bp
		mov	bp, sp
		push	si
		push	di
		xor	ax, ax
		mov	es, ax
		assume es:nothing
		test	byte ptr es:501h, 8
		jz	short @@loc_10039
		mov	ax, 0CD4h
		test	byte ptr es:54Ch, 20h
		jz	short @@loc_10052
		test	byte ptr es:459h, 8
		jz	short @@loc_10052
		mov	ax, 1388h
		jmp	short @@loc_10052

@@loc_10039:
		mov	ax, 0C4Bh
		test	byte ptr es:54Ch, 20h
		jnz	short @@loc_10052
		mov	ax, 9B3h
		test	byte ptr es:53Ch, 80h
		jnz	short @@loc_10052
		mov	ax, 627h

@@loc_10052:
		mov	dx, [bp+@@arg_0]
		cmp	dx, 1
		jb	short @@loc_10085
		jz	short @@loc_1005F
		mul	dx
		inc	dx

@@loc_1005F:
		dec	dx
		mov	bx, 64h
		xchg	ax, cx
		xchg	ax, dx
		xor	dx, dx
		div	bx
		xchg	ax, cx
		div	bx
		mov	bx, cx
		inc	bx
		mov	cx, ax
		mov	dx, 60h
		mov	ah, 40h

@@loc_10076:
		in	al, dx
		test	al, ah
		jz	short @@loc_10076

@@loc_1007B:
		in	al, dx
		test	al, ah
		jnz	short @@loc_1007B
		loop	@@loc_10076
		dec	bx
		jnz	short @@loc_10076

@@loc_10085:
		pop	di
		pop	si
		pop	bp
		ret
cnecdely_10010	endp

cnecdely_10089	proc near
@@arg_0		= word ptr  4

		push	bp
		mov	bp, sp
		push	si
		push	di

@@loc_1008E:
		pushf
		cli
		in	ax, 5Eh
		xchg	ax, cx
		in	ax, 5Ch
		xchg	ax, bx
		in	ax, 5Eh
		popf
		cmp	cx, ax
		jnz	short @@loc_1008E
		mov	cl, ch
		xor	ch, ch
		xor	si, si
		mov	di, 133h
		mov	ax, [bp+@@arg_0]
		cmp	ax, 1
		jb	short @@loc_100F5
		jz	short @@loc_100CB
		cmp	ax, 2
		jnz	short @@loc_100B9
		shl	di, 1
		jmp	short @@loc_100CB

@@loc_100B9:
		mov	si, 0C00h
		mul	si
		xchg	ax, si
		xchg	ax, dx
		xor	dx, dx
		mov	di, 0Ah
		div	di
		xchg	ax, si
		div	di
		xchg	ax, di

@@loc_100CB:
		mov	dx, cx
		add	bx, di
		adc	cx, si

@@loc_100D1:
		pushf
		cli
		in	ax, 5Eh
		xchg	ax, si
		in	ax, 5Ch
		xchg	ax, di
		in	ax, 5Eh
		popf
		cmp	si, ax
		jnz	short @@loc_100D1
		mov	al, ah
		mov	ah, dh
		cmp	al, dl
		mov	dl, al
		adc	dh, 0
		cmp	dx, cx
		jb	short @@loc_100D1
		ja	short @@loc_100F5
		cmp	di, bx
		jb	short @@loc_100D1

@@loc_100F5:
		pop	di
		pop	si
		pop	bp
		ret
cnecdely_10089	endp

		public ___nec_delay
___nec_delay	proc
@@arg_0		= word ptr cPtrSize + 2

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	dx, [bp+@@arg_0]
		xor	ax, ax
		mov	es, ax
		test	byte ptr es:458h, 80h
		jnz	short @@loc_10117
		mov	es, ax
		test	byte ptr es:45Bh, 4
		jz	short @@loc_1011D

@@loc_10117:
		push	dx
		call	cnecdely_10089
		jmp	short @@loc_10121

@@loc_1011D:
		push	dx
		call	cnecdely_10010

@@loc_10121:
		pop	cx
		pop	di
		pop	si
		pop	bp
		ret
___nec_delay	endp

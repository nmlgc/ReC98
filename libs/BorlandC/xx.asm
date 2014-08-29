		public ___JumpToCatch__
___JumpToCatch__ proc far
		push	si
		push	di
		mov	sp, bx
		mov	bp, cx
		push	dx
		push	ax
		retf
___JumpToCatch__ endp

		pop	di
		pop	si
		retf


xx_1003C	proc far

@@arg_0		= dword	ptr  6

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	ax, word ptr [bp+@@arg_0]
		or	ax, word ptr [bp+@@arg_0+2]
		jnz	short xx_10050
		mov	dx, ds
		mov	ax, offset aNotype ; "<notype>"
		jmp	short xx_1005D

xx_10050:
		les	bx, [bp+@@arg_0]
		mov	dx, word ptr [bp+@@arg_0+2]
		mov	ax, word ptr [bp+@@arg_0]
		add	ax, es:[bx+4]

xx_1005D:
		pop	di
		pop	si
		pop	bp
		retf
xx_1003C	endp



xx_10061	proc far

@@var_A		= word ptr -0Ah
@@var_8		= dword	ptr -8
@@var_4		= dword	ptr -4
@@arg_0		= dword	ptr  6
@@arg_4		= dword	ptr  0Ah

		push	bp
		mov	bp, sp
		sub	sp, 0Ah
		push	si
		push	di
		mov	dx, word ptr [bp+@@arg_0+2]
		mov	ax, word ptr [bp+@@arg_0]
		cmp	dx, word ptr [bp+@@arg_4+2]
		jnz	short xx_10079
		cmp	ax, word ptr [bp+@@arg_4]
		jz	short xx_100F5

xx_10079:
		les	bx, [bp+@@arg_0]
		mov	ax, es:[bx+2]
		les	bx, [bp+@@arg_4]
		cmp	ax, es:[bx+2]
		jnz	short xx_100ED
		les	bx, [bp+@@arg_0]
		mov	ax, es:[bx]
		les	bx, [bp+@@arg_4]
		cmp	ax, es:[bx]
		jnz	short xx_100ED
		les	bx, [bp+@@arg_0]
		mov	ax, es:[bx+2]
		les	bx, [bp+@@arg_4]
		or	ax, es:[bx+2]
		test	al, 80h
		jnz	short xx_100ED
		les	bx, [bp+@@arg_0]
		mov	dx, word ptr [bp+@@arg_0+2]
		mov	ax, word ptr [bp+@@arg_0]
		add	ax, es:[bx+4]
		mov	word ptr [bp+@@var_4+2], dx
		mov	word ptr [bp+@@var_4], ax
		les	bx, [bp+@@arg_4]
		mov	dx, word ptr [bp+@@arg_4+2]
		mov	ax, word ptr [bp+@@arg_4]
		add	ax, es:[bx+4]
		mov	word ptr [bp+@@var_8+2], dx
		mov	word ptr [bp+@@var_8], ax

xx_100CF:
		les	bx, [bp+@@var_4]
		mov	al, es:[bx]
		cbw
		mov	dx, ax
		inc	word ptr [bp+@@var_4]
		les	bx, [bp+@@var_8]
		mov	al, es:[bx]
		cbw
		mov	[bp+@@var_A], ax
		inc	word ptr [bp+@@var_8]
		cmp	dx, [bp+@@var_A]
		jz	short xx_100F1

xx_100ED:
		xor	ax, ax
		jmp	short xx_100F8

xx_100F1:
		or	dx, dx
		jnz	short xx_100CF

xx_100F5:
		mov	ax, 1

xx_100F8:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
xx_10061	endp



xx_100FE	proc near

@@var_A		= dword	ptr -0Ah
@@var_6		= word ptr -6
@@var_4		= dword	ptr -4
@@arg_0		= dword	ptr  4
@@arg_4		= word ptr  8
@@arg_6		= word ptr  0Ah
@@arg_8		= word ptr  0Ch
@@arg_A		= word ptr  0Eh
@@arg_C		= word ptr  10h

		push	bp
		mov	bp, sp
		sub	sp, 0Ah
		push	si
		push	di
		les	bx, [bp+@@arg_0]
		mov	dx, word ptr [bp+@@arg_0+2]
		mov	ax, word ptr [bp+@@arg_0]
		add	ax, es:[bx+0Ch]
		mov	word ptr [bp+@@var_4+2], dx
		mov	word ptr [bp+@@var_4], ax

xx_10119:
		les	bx, [bp+@@var_4]
		mov	dx, es:[bx+2]
		mov	ax, es:[bx]
		mov	word ptr [bp+@@var_A+2], dx
		mov	word ptr [bp+@@var_A], ax
		mov	ax, word ptr [bp+@@var_A]
		or	ax, word ptr [bp+@@var_A+2]
		jz	short xx_101AD
		les	bx, [bp+@@var_4]
		test	byte ptr es:[bx+6], 8
		jnz	short xx_101A6
		cmp	[bp+@@arg_C], 0
		jz	short xx_10155
		les	bx, [bp+@@var_4]
		mov	ax, es:[bx+6]
		and	ax, 3
		cmp	ax, 3
		jnz	short xx_10155
		mov	ax, 1
		jmp	short xx_10157

xx_10155:
		xor	ax, ax

xx_10157:
		mov	[bp+@@var_6], ax
		push	word ptr [bp+@@var_A+2]
		push	word ptr [bp+@@var_A]
		push	[bp+@@arg_6]
		push	[bp+@@arg_4]
		call	xx_10061
		add	sp, 8
		or	ax, ax
		jz	short xx_1017A
		cmp	[bp+@@var_6], 0
		jz	short xx_1017A
		jmp	xx_1023D

xx_1017A:
		les	bx, [bp+@@var_A]
		test	byte ptr es:[bx+8], 4
		jz	short xx_101A6
		push	[bp+@@var_6]
		push	[bp+@@arg_A]
		push	[bp+@@arg_8]
		push	[bp+@@arg_6]
		push	[bp+@@arg_4]
		push	word ptr [bp+@@var_A+2]
		push	word ptr [bp+@@var_A]
		call	xx_100FE
		add	sp, 0Eh
		or	ax, ax
		jz	short xx_101A6
		jmp	xx_1023D

xx_101A6:
		add	word ptr [bp+@@var_4], 8
		jmp	xx_10119

xx_101AD:
		les	bx, [bp+@@arg_0]
		mov	dx, word ptr [bp+@@arg_0+2]
		mov	ax, word ptr [bp+@@arg_0]
		add	ax, es:[bx+0Ah]
		mov	word ptr [bp+@@var_4+2], dx
		mov	word ptr [bp+@@var_4], ax

xx_101C0:
		les	bx, [bp+@@var_4]
		mov	dx, es:[bx+2]
		mov	ax, es:[bx]
		mov	word ptr [bp+@@var_A+2], dx
		mov	word ptr [bp+@@var_A], ax
		mov	ax, word ptr [bp+@@var_A]
		or	ax, word ptr [bp+@@var_A+2]
		jz	short xx_10249
		cmp	[bp+@@arg_C], 0
		jz	short xx_101F2
		les	bx, [bp+@@var_4]
		mov	ax, es:[bx+6]
		and	ax, 3
		cmp	ax, 3
		jnz	short xx_101F2
		mov	ax, 1
		jmp	short xx_101F4

xx_101F2:
		xor	ax, ax

xx_101F4:
		mov	[bp+@@var_6], ax
		push	word ptr [bp+@@var_A+2]
		push	word ptr [bp+@@var_A]
		push	[bp+@@arg_6]
		push	[bp+@@arg_4]
		call	xx_10061
		add	sp, 8
		or	ax, ax
		jz	short xx_10214
		cmp	[bp+@@var_6], 0
		jnz	short xx_1023D

xx_10214:
		les	bx, [bp+@@var_A]
		test	byte ptr es:[bx+8], 4
		jz	short xx_10242
		push	[bp+@@var_6]
		push	[bp+@@arg_A]
		push	[bp+@@arg_8]
		push	[bp+@@arg_6]
		push	[bp+@@arg_4]
		push	word ptr [bp+@@var_A+2]
		push	word ptr [bp+@@var_A]
		call	xx_100FE
		add	sp, 0Eh
		or	ax, ax
		jz	short xx_10242

xx_1023D:
		mov	ax, 1
		jmp	short xx_1024B

xx_10242:
		add	word ptr [bp+@@var_4], 8
		jmp	xx_101C0

xx_10249:
		xor	ax, ax

xx_1024B:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retn
xx_100FE	endp



xx_10251	proc near

@@var_4		= word ptr -4
@@var_2		= word ptr -2
@@arg_0		= dword	ptr  4
@@arg_4		= dword	ptr  8
@@arg_8		= word ptr  0Ch
@@arg_A		= word ptr  0Eh
@@arg_C		= word ptr  10h

		push	bp
		mov	bp, sp
		sub	sp, 4
		push	si
		push	di
		mov	cx, [bp+@@arg_8]

xx_1025C:
		mov	dx, word ptr [bp+@@arg_0+2]
		mov	ax, word ptr [bp+@@arg_0]
		cmp	dx, word ptr [bp+@@arg_4+2]
		jnz	short xx_1026F
		cmp	ax, word ptr [bp+@@arg_4]
		jnz	short xx_1026F
		jmp	xx_10384

xx_1026F:
		les	bx, [bp+@@arg_0]
		mov	ax, es:[bx+2]
		mov	[bp+@@var_2], ax
		les	bx, [bp+@@arg_4]
		mov	ax, es:[bx+2]
		mov	[bp+@@var_4], ax
		mov	ax, [bp+@@var_2]
		and	ax, [bp+@@var_4]
		test	al, 10h
		jz	short xx_102FF
		and	[bp+@@var_2], 3300h
		and	[bp+@@var_4], 3300h
		mov	ax, [bp+@@var_2]
		cmp	ax, [bp+@@var_4]
		jnz	short xx_102A2
		jmp	xx_10345

xx_102A2:
		or	cx, cx
		jz	short xx_102A9
		jmp	xx_103BD

xx_102A9:
		mov	ax, [bp+@@var_2]
		and	ax, 300h
		mov	dx, [bp+@@var_4]
		and	dx, 300h
		cmp	ax, dx
		jz	short xx_102DF
		mov	ax, [bp+@@var_4]
		and	ax, 300h
		not	ax
		and	ax, [bp+@@var_2]
		test	ah, 3
		jz	short xx_102CD
		jmp	xx_103BD

xx_102CD:
		or	[bp+@@var_2], 300h
		or	[bp+@@var_4], 300h
		mov	ax, [bp+@@var_2]
		cmp	ax, [bp+@@var_4]
		jz	short xx_10345

xx_102DF:
		mov	ax, [bp+@@var_2]
		or	ax, 3000h
		mov	dx, [bp+@@var_4]
		or	dx, 3000h
		cmp	ax, dx
		jz	short xx_102F3
		jmp	xx_103BD

xx_102F3:
		test	byte ptr [bp+@@var_2+1], 10h
		jnz	short xx_102FC
		jmp	xx_103BD

xx_102FC:
		jmp	xx_10384

xx_102FF:
		mov	ax, [bp+@@var_2]
		and	ax, [bp+@@var_4]
		test	ah, 4
		jz	short xx_1036D
		les	bx, [bp+@@arg_0]
		mov	dx, es:[bx+0Ch]
		mov	ax, es:[bx+0Ah]
		les	bx, [bp+@@arg_4]
		cmp	dx, es:[bx+0Ch]
		jnz	short xx_10324
		cmp	ax, es:[bx+0Ah]
		jz	short xx_10345

xx_10324:
		or	cx, cx
		jz	short xx_1032B
		jmp	xx_103BD

xx_1032B:
		les	bx, [bp+@@arg_0]
		mov	dx, es:[bx+0Ch]
		mov	ax, es:[bx+0Ah]
		les	bx, [bp+@@arg_4]
		or	ax, es:[bx+0Ah]
		or	dx, es:[bx+0Ch]
		or	ax, dx
		jnz	short xx_103BD

xx_10345:
		mov	cx, 1
		les	bx, [bp+@@arg_0]
		mov	dx, es:[bx+8]
		mov	ax, es:[bx+6]
		mov	word ptr [bp+@@arg_0+2], dx
		mov	word ptr [bp+@@arg_0], ax
		les	bx, [bp+@@arg_4]
		mov	dx, es:[bx+8]
		mov	ax, es:[bx+6]
		mov	word ptr [bp+@@arg_4+2], dx
		mov	word ptr [bp+@@arg_4], ax
		jmp	xx_1025C

xx_1036D:
		push	word ptr [bp+@@arg_4+2]
		push	word ptr [bp+@@arg_4]
		push	word ptr [bp+@@arg_0+2]
		push	word ptr [bp+@@arg_0]
		call	xx_10061
		add	sp, 8
		or	ax, ax
		jz	short xx_10389

xx_10384:
		mov	ax, 1
		jmp	short xx_103BF

xx_10389:
		test	byte ptr [bp+@@var_2], 2
		jz	short xx_103BD
		test	byte ptr [bp+@@var_4], 1
		jz	short xx_103BD
		les	bx, [bp+@@arg_0]
		test	byte ptr es:[bx+8], 4
		jz	short xx_103BD
		mov	ax, 1
		push	ax
		push	[bp+@@arg_C]
		push	[bp+@@arg_A]
		push	word ptr [bp+@@arg_4+2]
		push	word ptr [bp+@@arg_4]
		push	word ptr [bp+@@arg_0+2]
		push	word ptr [bp+@@arg_0]
		call	xx_100FE
		add	sp, 0Eh
		jmp	short xx_103BF

xx_103BD:
		xor	ax, ax

xx_103BF:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retn
xx_10251	endp



; int __cdecl __far xx_103C5(size_t size)
xx_103C5	proc far

@@var_4		= word ptr -4
@@var_2		= word ptr -2
@@size		= word ptr  6

		push	bp
		mov	bp, sp
		sub	sp, 4
		push	si
		push	di
		push	[bp+@@size]	; size
		nopcall	_malloc
		pop	cx
		mov	[bp+@@var_2], dx
		mov	[bp+@@var_4], ax
		mov	ax, [bp+@@var_4]
		or	ax, [bp+@@var_2]
		jnz	short xx_10415
		cmp	[bp+@@size], 80h ; '€'
		ja	short xx_103F7
		les	bx, ss:16h
		test	byte ptr es:[bx+4], 1
		jz	short xx_103FC

xx_103F7:
		nopcall	_abort

xx_103FC:
		les	bx, ss:16h
		or	word ptr es:[bx+4], 1
		les	bx, ss:16h
		mov	dx, es:[bx+22h]
		mov	ax, es:[bx+20h]
		jmp	short xx_1041B

xx_10415:
		mov	dx, [bp+@@var_2]
		mov	ax, [bp+@@var_4]

xx_1041B:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
xx_103C5	endp



xx_10421	proc far

block		= word ptr  6
@@arg_2		= word ptr  8

		push	bp
		mov	bp, sp
		push	si
		push	di
		les	bx, ss:16h
		mov	dx, es:[bx+22h]
		mov	ax, es:[bx+20h]
		cmp	dx, [bp+@@arg_2]
		jnz	short xx_10449
		cmp	ax, [bp+block]
		jnz	short xx_10449
		les	bx, ss:16h
		and	word ptr es:[bx+4], 0FFFEh
		jmp	short xx_10456

xx_10449:
		push	[bp+@@arg_2]
		push	[bp+block]	; block
		nopcall	_free
		pop	cx
		pop	cx

xx_10456:
		pop	di
		pop	si
		pop	bp
		retf
xx_10421	endp



xx_1045A	proc near

@@var_4		= word ptr -4
@@var_2		= word ptr -2
@@arg_0		= dword	ptr  4
@@arg_4		= word ptr  8
@@arg_6		= word ptr  0Ah
@@arg_8		= dword	ptr  0Ch
@@arg_C		= byte ptr  10h

		push	bp
		mov	bp, sp
		sub	sp, 4
		push	si
		push	di
		push	[bp+@@arg_6]
		push	[bp+@@arg_4]
		xor	ax, ax
		push	ax
		push	word ptr [bp+@@arg_8+2]
		push	word ptr [bp+@@arg_8]
		push	word ptr [bp+@@arg_0+2]
		push	word ptr [bp+@@arg_0]
		call	xx_10251
		add	sp, 0Eh
		or	ax, ax
		jz	short xx_10484
		jmp	xx_10520

xx_10484:
		les	bx, [bp+@@arg_0]
		mov	ax, es:[bx+2]
		mov	[bp+@@var_2], ax
		les	bx, [bp+@@arg_8]
		mov	ax, es:[bx+2]
		mov	[bp+@@var_4], ax
		test	byte ptr [bp+@@var_4], 20h
		jz	short xx_10514
		push	[bp+@@arg_6]
		push	[bp+@@arg_4]
		mov	ax, 1
		push	ax
		les	bx, [bp+@@arg_8]
		push	word ptr es:[bx+8]
		push	word ptr es:[bx+6]
		push	word ptr [bp+@@arg_0+2]
		push	word ptr [bp+@@arg_0]
		call	xx_10251
		add	sp, 0Eh
		or	ax, ax
		jnz	short xx_10520
		les	bx, [bp+@@arg_8]
		mov	dx, es:[bx+8]
		mov	ax, es:[bx+6]
		mov	word ptr [bp+@@arg_8+2], dx
		mov	word ptr [bp+@@arg_8], ax
		les	bx, [bp+@@arg_8]
		mov	ax, es:[bx+2]
		mov	[bp+@@var_4], ax
		test	byte ptr [bp+@@var_4], 10h
		jz	short xx_10557
		push	[bp+@@arg_6]
		push	[bp+@@arg_4]
		xor	ax, ax
		push	ax
		push	word ptr [bp+@@arg_8+2]
		push	word ptr [bp+@@arg_8]
		push	word ptr [bp+@@arg_0+2]
		push	word ptr [bp+@@arg_0]
		call	xx_10251
		add	sp, 0Eh
		or	ax, ax
		jnz	short xx_10520
		mov	ax, [bp+@@var_2]
		and	ax, 3000h
		mov	dx, [bp+@@var_4]
		and	dx, 3000h
		cmp	ax, dx
		jnz	short xx_10557

xx_10514:
		test	byte ptr [bp+@@var_4], 10h
		jz	short xx_10557
		test	[bp+@@arg_C], 1
		jz	short xx_10525

xx_10520:
		mov	ax, 1
		jmp	short xx_10559

xx_10525:
		test	byte ptr [bp+@@var_2], 10h
		jz	short xx_10557
		test	byte ptr [bp+@@var_2+1], 20h
		jz	short xx_10537
		test	byte ptr [bp+@@var_4+1], 20h
		jz	short xx_10557

xx_10537:
		test	byte ptr [bp+@@var_4], 40h
		jz	short xx_10557
		mov	ax, [bp+@@var_2]
		and	ax, 300h
		mov	dx, [bp+@@var_4]
		and	dx, 300h
		cmp	ax, dx
		jnz	short xx_10553
		mov	ax, 1
		jmp	short xx_10555

xx_10553:
		xor	ax, ax

xx_10555:
		jmp	short xx_10559

xx_10557:
		xor	ax, ax

xx_10559:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retn
xx_1045A	endp



xx_1055F	proc near

@@var_4		= word ptr -4
@@var_2		= word ptr -2
@@arg_0		= dword	ptr  4
@@arg_4		= word ptr  8
@@arg_6		= word ptr  0Ah
@@arg_8		= dword	ptr  0Ch
@@arg_C		= word ptr  10h

		push	bp
		mov	bp, sp
		sub	sp, 4
		push	si
		push	di
		les	bx, ss:16h
		mov	ax, es:[bx+6]
		mov	[bp+@@var_2], ax
		push	ds
		mov	ds, [bp+@@var_2]
		mov	ax, [bp+@@arg_C]
		and	ax, 1
		mov	[bp+@@var_4], ax
		test	byte ptr [bp+@@arg_C], 4
		jz	short xx_1058A
		or	[bp+@@var_4], 2

xx_1058A:
		test	byte ptr [bp+@@arg_C], 2
		jz	short xx_1059E
		or	[bp+@@var_4], 4
		test	byte ptr [bp+@@arg_C+1], 1
		jnz	short xx_1059E
		or	[bp+@@var_4], 20h

xx_1059E:
		test	byte ptr [bp+@@arg_C], 20h
		jz	short xx_105A8
		or	[bp+@@var_4], 8

xx_105A8:
		test	byte ptr [bp+@@arg_C], 80h
		jz	short xx_105B2
		or	[bp+@@var_4], 10h

xx_105B2:
		test	byte ptr [bp+@@arg_C+1], 10h
		jnz	short xx_105BB
		jmp	xx_10740

xx_105BB:
		mov	bx, [bp+@@var_4]
		cmp	bx, 17h
		jbe	short xx_105C6
		jmp	xx_10846

xx_105C6:
		add	bx, bx
		jmp	cs:xx_1087D[bx]

xx_105CD:
		push	[bp+@@arg_4]
		xor	ax, ax
		push	ax
		push	word ptr [bp+@@arg_0]
		call	word ptr [bp+@@arg_8]
		add	sp, 6
		jmp	xx_10846

xx_105DF:
		push	[bp+@@arg_4]
		xor	ax, ax
		push	ax
		push	word ptr [bp+@@arg_0]
		call	[bp+@@arg_8]
		add	sp, 6
		jmp	xx_10846

xx_105F1:
		push	[bp+@@arg_6]
		push	[bp+@@arg_4]
		xor	ax, ax
		push	ax
		push	word ptr [bp+@@arg_0+2]
		push	word ptr [bp+@@arg_0]
		call	word ptr [bp+@@arg_8]
		jmp	short xx_10617

xx_10605:
		push	[bp+@@arg_6]
		push	[bp+@@arg_4]
		xor	ax, ax
		push	ax
		push	word ptr [bp+@@arg_0+2]
		push	word ptr [bp+@@arg_0]
		call	[bp+@@arg_8]

xx_10617:
		add	sp, 0Ah
		jmp	xx_10846

xx_1061D:
		xor	ax, ax
		push	ax
		push	[bp+@@arg_4]
		push	word ptr [bp+@@arg_0]
		call	word ptr [bp+@@arg_8]
		jmp	xx_10846

xx_1062C:
		xor	ax, ax
		push	ax
		push	[bp+@@arg_4]
		push	word ptr [bp+@@arg_0]
		call	[bp+@@arg_8]
		jmp	xx_10846

xx_1063B:
		xor	ax, ax
		push	ax
		push	[bp+@@arg_6]
		push	[bp+@@arg_4]
		push	word ptr [bp+@@arg_0+2]
		push	word ptr [bp+@@arg_0]
		call	word ptr [bp+@@arg_8]
		jmp	short xx_10661

xx_1064F:
		xor	ax, ax
		push	ax
		push	[bp+@@arg_6]
		push	[bp+@@arg_4]
		push	word ptr [bp+@@arg_0+2]
		push	word ptr [bp+@@arg_0]
		call	[bp+@@arg_8]

xx_10661:
		jmp	xx_10846

xx_10664:
		mov	dx, word ptr [bp+@@arg_0]
		mov	bx, [bp+@@arg_4]
		xor	ax, ax
		push	bx
		pop	bx
		call	word ptr [bp+@@arg_8]
		jmp	xx_10846

xx_10674:
		mov	dx, word ptr [bp+@@arg_0]
		mov	bx, [bp+@@arg_4]
		xor	ax, ax

xx_1067C:
		push	bx
		pop	bx
		call	[bp+@@arg_8]
		jmp	xx_10846

xx_10684:
		push	[bp+@@arg_6]
		push	[bp+@@arg_4]
		push	word ptr [bp+@@arg_0+2]
		push	word ptr [bp+@@arg_0]
		xor	ax, ax

xx_10692:
		call	word ptr [bp+@@arg_8]
		jmp	short xx_106A8

xx_10697:
		push	[bp+@@arg_6]
		push	[bp+@@arg_4]
		push	word ptr [bp+@@arg_0+2]
		push	word ptr [bp+@@arg_0]
		xor	ax, ax

xx_106A5:
		call	[bp+@@arg_8]

xx_106A8:
		jmp	xx_10846

xx_106AB:
		mov	si, word ptr [bp+@@arg_0]
		push	[bp+@@arg_4]
		xor	ax, ax
		push	ax
		call	word ptr [bp+@@arg_8]
		jmp	short xx_106C5

xx_106B9:
		mov	si, word ptr [bp+@@arg_0]
		push	[bp+@@arg_4]
		xor	ax, ax
		push	ax

xx_106C2:
		call	[bp+@@arg_8]

xx_106C5:
		pop	cx
		pop	cx
		jmp	xx_10846

xx_106CA:
		push	ds
		lds	si, [bp+@@arg_0]
		push	[bp+@@arg_6]
		push	[bp+@@arg_4]
		xor	ax, ax
		push	ax
		call	word ptr [bp+@@arg_8]
		add	sp, 6
		pop	ds
		jmp	xx_10846

xx_106E1:
		push	ds
		lds	si, [bp+@@arg_0]
		push	[bp+@@arg_6]
		push	[bp+@@arg_4]
		xor	ax, ax
		push	ax
		call	[bp+@@arg_8]
		add	sp, 6
		pop	ds
		jmp	xx_10846

xx_106F8:
		mov	si, word ptr [bp+@@arg_0]
		xor	ax, ax
		push	ax
		push	[bp+@@arg_4]

xx_10701:
		call	word ptr [bp+@@arg_8]
		jmp	short xx_10712

xx_10706:
		mov	si, word ptr [bp+@@arg_0]
		xor	ax, ax
		push	ax
		push	[bp+@@arg_4]

xx_1070F:
		call	[bp+@@arg_8]

xx_10712:
		jmp	xx_10846

xx_10715:
		push	ds
		lds	si, [bp+@@arg_0]
		xor	ax, ax
		push	ax
		push	[bp+@@arg_6]
		push	[bp+@@arg_4]
		call	word ptr [bp+@@arg_8]
		pop	ds
		jmp	xx_10846

xx_10729:
		push	ds
		lds	si, [bp+@@arg_0]
		xor	ax, ax
		push	ax
		push	[bp+@@arg_6]
		push	[bp+@@arg_4]
		call	[bp+@@arg_8]
		pop	ds
		jmp	xx_10846

xx_1073D:
		jmp	xx_10846

xx_10740:
		mov	bx, [bp+@@var_4]
		cmp	bx, 17h
		jbe	short xx_1074B
		jmp	xx_10846

xx_1074B:
		add	bx, bx
		jmp	cs:xx_1084D[bx]

xx_10752:
		push	[bp+@@arg_4]
		push	word ptr [bp+@@arg_0]
		call	word ptr [bp+@@arg_8]
		jmp	xx_106C5

xx_1075E:
		push	[bp+@@arg_4]
		push	word ptr [bp+@@arg_0]
		jmp	xx_106C2

xx_10767:
		push	[bp+@@arg_6]
		push	[bp+@@arg_4]
		push	word ptr [bp+@@arg_0+2]
		push	word ptr [bp+@@arg_0]
		call	word ptr [bp+@@arg_8]
		jmp	short xx_10787

xx_10778:
		push	[bp+@@arg_6]
		push	[bp+@@arg_4]
		push	word ptr [bp+@@arg_0+2]
		push	word ptr [bp+@@arg_0]
		call	[bp+@@arg_8]

xx_10787:
		add	sp, 8
		jmp	xx_10846

xx_1078D:
		push	[bp+@@arg_4]
		push	word ptr [bp+@@arg_0]
		jmp	xx_10701

xx_10796:
		push	[bp+@@arg_4]
		push	word ptr [bp+@@arg_0]
		jmp	xx_1070F

xx_1079F:
		mov	ax, word ptr [bp+@@arg_0]
		mov	bx, [bp+@@arg_4]
		push	bx
		pop	bx
		call	word ptr [bp+@@arg_8]
		jmp	xx_10846

xx_107AD:
		mov	ax, word ptr [bp+@@arg_0]
		mov	bx, [bp+@@arg_4]
		jmp	xx_1067C

xx_107B6:
		push	[bp+@@arg_6]
		push	[bp+@@arg_4]
		push	word ptr [bp+@@arg_0+2]
		push	word ptr [bp+@@arg_0]
		jmp	xx_10692

xx_107C5:
		push	[bp+@@arg_6]
		push	[bp+@@arg_4]
		push	word ptr [bp+@@arg_0+2]
		push	word ptr [bp+@@arg_0]
		jmp	xx_106A5

xx_107D4:
		mov	si, word ptr [bp+@@arg_0]
		push	[bp+@@arg_4]
		call	word ptr [bp+@@arg_8]
		pop	cx
		jmp	short xx_10846

xx_107E0:
		mov	si, word ptr [bp+@@arg_0]
		push	[bp+@@arg_4]
		call	[bp+@@arg_8]
		pop	cx
		jmp	short xx_10846

xx_107EC:
		push	ds
		lds	si, [bp+@@arg_0]
		push	[bp+@@arg_6]
		push	[bp+@@arg_4]
		call	word ptr [bp+@@arg_8]
		pop	cx
		pop	cx
		pop	ds
		jmp	short xx_10846

xx_107FE:
		push	ds
		lds	si, [bp+@@arg_0]
		push	[bp+@@arg_6]
		push	[bp+@@arg_4]
		call	[bp+@@arg_8]
		pop	cx
		pop	cx
		pop	ds
		jmp	short xx_10846

xx_10810:
		mov	si, word ptr [bp+@@arg_0]
		push	[bp+@@arg_4]
		call	word ptr [bp+@@arg_8]
		jmp	short xx_10846

xx_1081B:
		mov	si, word ptr [bp+@@arg_0]
		push	[bp+@@arg_4]
		call	[bp+@@arg_8]
		jmp	short xx_10846

xx_10826:
		push	ds
		lds	si, [bp+@@arg_0]
		push	[bp+@@arg_6]
		push	[bp+@@arg_4]
		call	word ptr [bp+@@arg_8]
		pop	ds
		jmp	short xx_10846

xx_10836:
		push	ds
		lds	si, [bp+@@arg_0]
		push	[bp+@@arg_6]
		push	[bp+@@arg_4]
		call	[bp+@@arg_8]
		pop	ds
		jmp	short $+2

xx_10846:
		pop	ds
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retn
xx_1055F	endp

xx_1084D	dw offset xx_10752
		dw offset xx_1075E
		dw offset xx_10767
		dw offset xx_10778
		dw offset xx_1078D
		dw offset xx_10796
		dw offset xx_107B6
		dw offset xx_107C5
		dw offset xx_1079F
		dw offset xx_107AD
		dw offset xx_107B6
		dw offset xx_107C5
		dw offset xx_10846
		dw offset xx_10846
		dw offset xx_10846
		dw offset xx_10846
		dw offset xx_107D4
		dw offset xx_107E0
		dw offset xx_107EC
		dw offset xx_107FE
		dw offset xx_10810
		dw offset xx_1081B
		dw offset xx_10826
		dw offset xx_10836
xx_1087D	dw offset xx_105CD
		dw offset xx_105DF
		dw offset xx_105F1
		dw offset xx_10605
		dw offset xx_1061D
		dw offset xx_1062C
		dw offset xx_1063B
		dw offset xx_1064F
		dw offset xx_10664
		dw offset xx_10674
		dw offset xx_10684
		dw offset xx_10697
		dw offset xx_1073D
		dw offset xx_1073D
		dw offset xx_1073D
		dw offset xx_1073D
		dw offset xx_106AB
		dw offset xx_106B9
		dw offset xx_106CA
		dw offset xx_106E1
		dw offset xx_106F8
		dw offset xx_10706
		dw offset xx_10715
		dw offset xx_10729


xx_108AD	proc near

@@var_6		= word ptr -6
@@var_4		= word ptr -4
@@var_2		= word ptr -2
@@arg_0		= dword	ptr  4
@@arg_4		= dword	ptr  8
@@arg_8		= word ptr  0Ch
@@arg_A		= word ptr  0Eh

		push	bp
		mov	bp, sp
		sub	sp, 6
		push	si
		push	di
		cmp	[bp+@@arg_A], 0
		jz	short xx_108C0
		mov	ax, 2
		jmp	short xx_108C2

xx_108C0:
		xor	ax, ax

xx_108C2:
		mov	[bp+@@var_2], ax
		les	bx, ss:16h
		mov	ax, es:[bx+6]
		mov	[bp+@@var_4], ax
		push	ds
		mov	ds, [bp+@@var_4]
		mov	ax, [bp+@@arg_8]
		and	ax, 1
		mov	[bp+@@var_6], ax
		test	byte ptr [bp+@@arg_8], 4
		jz	short xx_108E8
		or	[bp+@@var_6], 2

xx_108E8:
		test	byte ptr [bp+@@arg_8], 2
		jz	short xx_108FC
		or	[bp+@@var_6], 4
		test	byte ptr [bp+@@arg_8+1], 1
		jnz	short xx_108FC
		or	[bp+@@var_6], 20h

xx_108FC:
		test	byte ptr [bp+@@arg_8], 20h
		jz	short xx_10906
		or	[bp+@@var_6], 8

xx_10906:
		test	byte ptr [bp+@@arg_8], 80h
		jz	short xx_10910
		or	[bp+@@var_6], 10h

xx_10910:
		mov	bx, [bp+@@var_6]
		cmp	bx, 17h
		jbe	short xx_1091B
		jmp	xx_10A2E

xx_1091B:
		add	bx, bx
		jmp	cs:xx_10A35[bx]

xx_10922:
		push	[bp+@@var_2]
		push	word ptr [bp+@@arg_0]
		call	word ptr [bp+@@arg_4]
		pop	cx
		pop	cx
		jmp	xx_10A2E

xx_10930:
		push	[bp+@@var_2]
		push	word ptr [bp+@@arg_0]
		call	[bp+@@arg_4]
		pop	cx
		pop	cx
		jmp	xx_10A2E

xx_1093E:
		push	[bp+@@var_2]
		push	word ptr [bp+@@arg_0+2]
		push	word ptr [bp+@@arg_0]
		call	word ptr [bp+@@arg_4]
		add	sp, 6
		jmp	xx_10A2E

xx_10950:
		push	[bp+@@var_2]
		push	word ptr [bp+@@arg_0+2]
		push	word ptr [bp+@@arg_0]
		call	[bp+@@arg_4]
		add	sp, 6
		jmp	xx_10A2E

xx_10962:
		push	[bp+@@var_2]
		push	word ptr [bp+@@arg_0]
		call	word ptr [bp+@@arg_4]
		jmp	short xx_109C8

xx_1096D:
		push	[bp+@@var_2]
		push	word ptr [bp+@@arg_0]
		jmp	short xx_109C5

xx_10975:
		push	[bp+@@var_2]
		push	word ptr [bp+@@arg_0+2]
		push	word ptr [bp+@@arg_0]
		call	word ptr [bp+@@arg_4]
		jmp	short xx_1098F

xx_10983:
		push	[bp+@@var_2]
		push	word ptr [bp+@@arg_0+2]
		push	word ptr [bp+@@arg_0]
		call	[bp+@@arg_4]

xx_1098F:
		jmp	xx_10A2E

xx_10992:
		mov	bx, word ptr [bp+@@arg_0]
		mov	ax, [bp+@@var_2]
		push	bx
		pop	bx
		call	word ptr [bp+@@arg_4]
		jmp	xx_10A2E

xx_109A0:
		mov	bx, word ptr [bp+@@arg_0]
		mov	ax, [bp+@@var_2]
		push	bx
		pop	bx
		call	[bp+@@arg_4]
		jmp	xx_10A2E

xx_109AE:
		push	word ptr [bp+@@arg_0+2]
		push	word ptr [bp+@@arg_0]
		mov	ax, [bp+@@var_2]
		call	word ptr [bp+@@arg_4]
		jmp	short xx_109C8

xx_109BC:
		push	word ptr [bp+@@arg_0+2]
		push	word ptr [bp+@@arg_0]
		mov	ax, [bp+@@var_2]

xx_109C5:
		call	[bp+@@arg_4]

xx_109C8:
		jmp	short xx_10A2E

xx_109CA:
		mov	si, word ptr [bp+@@arg_0]
		push	[bp+@@var_2]
		call	word ptr [bp+@@arg_4]
		pop	cx
		jmp	short xx_10A2E

xx_109D6:
		mov	si, word ptr [bp+@@arg_0]
		push	[bp+@@var_2]
		call	[bp+@@arg_4]
		pop	cx
		jmp	short xx_10A2E

xx_109E2:
		push	ds
		lds	si, [bp+@@arg_0]
		push	[bp+@@var_2]
		call	word ptr [bp+@@arg_4]
		pop	cx
		pop	ds
		jmp	short xx_10A2E

xx_109F0:
		push	ds
		lds	si, [bp+@@arg_0]
		push	[bp+@@var_2]
		call	[bp+@@arg_4]
		pop	cx
		pop	ds
		jmp	short xx_10A2E

xx_109FE:
		mov	si, word ptr [bp+@@arg_0]
		push	[bp+@@var_2]
		call	word ptr [bp+@@arg_4]
		jmp	short xx_10A2E

xx_10A09:
		mov	si, word ptr [bp+@@arg_0]
		push	[bp+@@var_2]
		call	[bp+@@arg_4]
		jmp	short xx_10A2E

xx_10A14:
		push	ds
		lds	si, [bp+@@arg_0]
		push	[bp+@@var_2]
		call	word ptr [bp+@@arg_4]
		pop	ds
		jmp	short xx_10A2E

xx_10A21:
		push	ds
		lds	si, [bp+@@arg_0]
		push	[bp+@@var_2]
		call	[bp+@@arg_4]
		pop	ds
		jmp	short $+2

xx_10A2E:
		pop	ds
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retn
xx_108AD	endp

xx_10A35	dw offset xx_10922
		dw offset xx_10930
		dw offset xx_1093E
		dw offset xx_10950
		dw offset xx_10962
		dw offset xx_1096D
		dw offset xx_10975
		dw offset xx_10983
		dw offset xx_10992
		dw offset xx_109A0
		dw offset xx_109AE
		dw offset xx_109BC
		dw offset xx_10A2E
		dw offset xx_10A2E
		dw offset xx_10A2E
		dw offset xx_10A2E
		dw offset xx_109CA
		dw offset xx_109D6
		dw offset xx_109E2
		dw offset xx_109F0
		dw offset xx_109FE
		dw offset xx_10A09
		dw offset xx_10A14
		dw offset xx_10A21


xx_10A65	proc near

@@var_4		= word ptr -4
@@var_2		= word ptr -2
@@arg_0		= word ptr  4
@@arg_2		= word ptr  6
@@arg_4		= dword	ptr  8
@@arg_8		= word ptr  0Ch

		push	bp
		mov	bp, sp
		sub	sp, 4
		push	si
		push	di
		les	bx, ss:16h
		mov	ax, es:[bx+6]
		mov	[bp+@@var_2], ax
		push	ds
		mov	ds, [bp+@@var_2]
		mov	ax, [bp+@@arg_8]
		and	ax, 1
		mov	[bp+@@var_4], ax
		test	byte ptr [bp+@@arg_8], 4
		jz	short xx_10A90
		or	[bp+@@var_4], 2

xx_10A90:
		test	byte ptr [bp+@@arg_8], 2
		jz	short xx_10A9A
		or	[bp+@@var_4], 4

xx_10A9A:
		test	byte ptr [bp+@@arg_8], 20h
		jz	short xx_10AA4
		or	[bp+@@var_4], 8

xx_10AA4:
		mov	bx, [bp+@@var_4]
		cmp	bx, 0Bh
		ja	short xx_10B17
		add	bx, bx
		jmp	cs:xx_10B1E[bx]

xx_10AB3:
		push	[bp+@@arg_0]
		call	word ptr [bp+@@arg_4]
		pop	cx
		jmp	short xx_10B17

xx_10ABC:
		push	[bp+@@arg_0]
		call	[bp+@@arg_4]
		pop	cx
		jmp	short xx_10B17

xx_10AC5:
		push	[bp+@@arg_2]
		push	[bp+@@arg_0]
		call	word ptr [bp+@@arg_4]
		jmp	short xx_10AD9

xx_10AD0:
		push	[bp+@@arg_2]
		push	[bp+@@arg_0]
		call	[bp+@@arg_4]

xx_10AD9:
		pop	cx
		pop	cx
		jmp	short xx_10B17

xx_10ADD:
		push	[bp+@@arg_0]
		call	word ptr [bp+@@arg_4]
		jmp	short xx_10AEB

xx_10AE5:
		push	[bp+@@arg_0]
		call	[bp+@@arg_4]

xx_10AEB:
		jmp	short xx_10B17

xx_10AED:
		mov	bx, [bp+@@arg_0]
		push	bx
		pop	bx
		call	word ptr [bp+@@arg_4]
		jmp	short xx_10B17

xx_10AF7:
		mov	bx, [bp+@@arg_0]
		push	bx
		pop	bx
		call	[bp+@@arg_4]
		jmp	short xx_10B17

xx_10B01:
		push	[bp+@@arg_2]
		push	[bp+@@arg_0]
		call	word ptr [bp+@@arg_4]
		jmp	short xx_10B15

xx_10B0C:
		push	[bp+@@arg_2]
		push	[bp+@@arg_0]
		call	[bp+@@arg_4]

xx_10B15:
		jmp	short $+2

xx_10B17:
		pop	ds
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retn
xx_10A65	endp

xx_10B1E	dw offset xx_10AB3
		dw offset xx_10ABC
		dw offset xx_10AC5
		dw offset xx_10AD0
		dw offset xx_10ADD
		dw offset xx_10AE5
		dw offset xx_10B01
		dw offset xx_10B0C
		dw offset xx_10AED
		dw offset xx_10AF7
		dw offset xx_10B01
		dw offset xx_10B0C
xx_10B36	db 4 dup(0)
		dd xx_10DF4
xx_10B3E	db 14h dup(0)
		dd xx_10E4D
		db 10h dup(0)
xx_10B66	db 4 dup(0), 0E2h, 0FFh, 2 dup(0), 3, 0
		dd xx_10B36
		db 2 dup(0), 4,	3 dup(0), 3, 0
		dd xx_10B3E+10h
		db 2 dup(0), 4,	0


; int __cdecl __far xx_10B84(int, int,	size_t n, int, int, int, int, int, int,	int, int, int, int, int, int, int)
xx_10B84	proc far

@@var_48		= word ptr -48h
@@var_46		= word ptr -46h
@@var_44		= word ptr -44h
@@var_42		= word ptr -42h
@@var_40		= word ptr -40h
@@var_3E		= word ptr -3Eh
@@var_3C		= word ptr -3Ch
@@var_3A		= word ptr -3Ah
@@var_38		= dword	ptr -38h
@@var_34		= dword	ptr -34h
@@src		= word ptr -30h
@@var_2C		= word ptr -2Ch
@@var_2A		= word ptr -2Ah
@@var_28		= word ptr -28h
@@var_26		= dword	ptr -26h
@@var_22		= dword	ptr -22h
@@var_1E		= word ptr -1Eh
@@var_12		= word ptr -12h
@@arg_0		= word ptr  6
@@arg_2		= word ptr  8
n		= word ptr  0Ah
@@arg_6		= word ptr  0Ch
@@arg_8		= word ptr  0Eh
@@arg_A		= word ptr  10h
@@arg_C		= word ptr  12h
@@arg_E		= word ptr  14h
@@arg_10		= word ptr  16h
@@arg_12		= word ptr  18h
@@arg_14		= word ptr  1Ah
@@arg_16		= word ptr  1Ch
@@arg_18		= word ptr  1Eh
@@arg_1A		= word ptr  20h
@@arg_1C		= word ptr  22h
@@arg_1E		= word ptr  24h

		push	bp
		mov	bp, sp
		sub	sp, 48h
		push	si
		push	di
		mov	ax, seg	xx_10B66
		mov	bx, offset xx_10B66
		nopcall	___InitExceptBlocks
		mov	dx, [bp+@@arg_2]
		mov	ax, [bp+@@arg_0]
		mov	word ptr [bp+@@var_22+2],	dx
		mov	word ptr [bp+@@var_22], ax
		les	bx, ss:16h
		mov	word ptr es:[bx+6], ds
		mov	dx, ss:18h
		mov	ax, ss:16h
		add	ax, 28h	; '('
		les	bx, ss:16h
		mov	es:[bx+1Eh], dx
		mov	es:[bx+1Ch], ax
		les	bx, [bp+@@var_22]
		mov	dx, word ptr [bp+@@var_22+2]
		mov	ax, word ptr [bp+@@var_22]
		add	ax, es:[bx+4]
		mov	word ptr [bp+@@var_34+2],	dx
		mov	word ptr [bp+@@var_34], ax
		les	bx, ss:16h
		mov	dx, es:[bx+1Eh]
		mov	ax, es:[bx+1Ch]
		mov	word ptr [bp+@@var_38+2],	dx
		mov	word ptr [bp+@@var_38], ax
		jmp	short xx_10C10

xx_10BED:
		les	bx, ss:16h
		mov	ax, es:[bx+1Ch]
		add	ax, 7Fh	; ''
		cmp	ax, word ptr [bp+@@var_38]
		jbe	short xx_10C0D
		les	bx, [bp+@@var_34]
		mov	al, es:[bx]
		les	bx, [bp+@@var_38]
		mov	es:[bx], al
		inc	word ptr [bp+@@var_38]

xx_10C0D:
		inc	word ptr [bp+@@var_34]

xx_10C10:
		les	bx, [bp+@@var_34]
		cmp	byte ptr es:[bx], 0
		jnz	short xx_10BED
		les	bx, [bp+@@var_38]
		mov	byte ptr es:[bx], 0
		les	bx, ss:16h
		mov	ax, [bp+@@arg_14]
		mov	es:[bx+1Ah], ax
		les	bx, ss:16h
		mov	dx, [bp+@@arg_18]
		mov	ax, [bp+@@arg_16]
		mov	es:[bx+18h], dx
		mov	es:[bx+16h], ax
		mov	dx, word ptr [bp+@@var_22+2]
		mov	ax, word ptr [bp+@@var_22]
		mov	word ptr [bp+@@var_26+2],	dx
		mov	word ptr [bp+@@var_26], ax
		les	bx, [bp+@@var_22]
		mov	ax, es:[bx]
		mov	[bp+@@var_28], ax
		les	bx, [bp+@@var_22]
		mov	ax, es:[bx+2]
		mov	[bp+@@var_2A], ax
		test	byte ptr [bp+@@var_2A], 2
		jz	short xx_10C6D
		les	bx, [bp+@@var_22]
		mov	ax, es:[bx+8]
		jmp	short xx_10C6F

xx_10C6D:
		xor	ax, ax

xx_10C6F:
		mov	[bp+@@var_2C], ax
		test	byte ptr [bp+@@var_2A], 30h
		jz	short xx_10C89
		les	bx, [bp+@@var_26]
		mov	dx, es:[bx+8]
		mov	ax, es:[bx+6]
		mov	word ptr [bp+@@var_26+2],	dx
		mov	word ptr [bp+@@var_26], ax

xx_10C89:
		mov	ax, [bp+@@var_28]
		add	ax, 3Ah	; ':'
		push	ax		; size
		call	xx_103C5
		pop	cx
		mov	[bp+@@src+2], dx
		mov	[bp+@@src], ax
		les	bx, ss:16h
		mov	dx, es:[bx+2]
		mov	ax, es:[bx]
		les	bx, dword ptr [bp+@@src]
		mov	es:[bx+2], dx
		mov	es:[bx], ax
		les	bx, ss:16h
		mov	dx, [bp+@@src+2]
		mov	ax, [bp+@@src]
		mov	es:[bx+2], dx
		mov	es:[bx], ax
		les	bx, dword ptr [bp+@@src]
		mov	dx, word ptr [bp+@@var_22+2]
		mov	ax, word ptr [bp+@@var_22]
		mov	es:[bx+6], dx
		mov	es:[bx+4], ax
		les	bx, dword ptr [bp+@@src]
		mov	ax, [bp+@@arg_12]
		mov	es:[bx+0Ch], ax
		les	bx, dword ptr [bp+@@src]
		mov	ax, [bp+@@var_28]
		mov	es:[bx+0Eh], ax
		les	bx, dword ptr [bp+@@src]
		mov	ax, [bp+@@var_2A]
		mov	es:[bx+14h], ax
		les	bx, dword ptr [bp+@@src]
		mov	ax, [bp+@@var_2C]
		mov	es:[bx+16h], ax
		les	bx, dword ptr [bp+@@src]
		mov	dx, word ptr [bp+@@var_26+2]
		mov	ax, word ptr [bp+@@var_26]
		mov	es:[bx+12h], dx
		mov	es:[bx+10h], ax
		les	bx, dword ptr [bp+@@src]
		mov	dx, [bp+@@arg_A]
		mov	ax, [bp+@@arg_8]
		mov	es:[bx+0Ah], dx
		mov	es:[bx+8], ax
		les	bx, dword ptr [bp+@@src]
		mov	word ptr es:[bx+24h], 0
		les	bx, dword ptr [bp+@@src]
		mov	word ptr es:[bx+28h], 0
		mov	word ptr es:[bx+26h], 0
		les	bx, dword ptr [bp+@@src]
		mov	word ptr es:[bx+18h], ds
		les	bx, dword ptr [bp+@@src]
		mov	word ptr es:[bx+1Ch], seg xx_10421
		mov	word ptr es:[bx+1Ah], offset xx_10421
		les	bx, dword ptr [bp+@@src]
		mov	ax, [bp+@@arg_14]
		mov	es:[bx+2Ch], ax
		les	bx, dword ptr [bp+@@src]
		mov	dx, [bp+@@arg_18]
		mov	ax, [bp+@@arg_16]
		mov	es:[bx+30h], dx
		mov	es:[bx+2Eh], ax
		les	bx, dword ptr [bp+@@src]
		mov	dx, [bp+@@arg_E]
		mov	ax, [bp+@@arg_C]
		mov	es:[bx+20h], dx
		mov	es:[bx+1Eh], ax
		les	bx, dword ptr [bp+@@src]
		mov	ax, [bp+@@arg_10]
		mov	es:[bx+22h], ax
		les	bx, dword ptr [bp+@@src]
		mov	byte ptr es:[bx+39h], 0
		les	bx, dword ptr [bp+@@src]
		mov	byte ptr es:[bx+38h], 1
		push	[bp+@@var_28]
		push	[bp+@@arg_6]
		push	[bp+n]		; n
		mov	ax, [bp+@@src]
		add	ax, 3Ah	; ':'
		push	[bp+@@src+2]	; src
		push	ax		; dest
		nopcall	_memcpy
		add	sp, 0Ah
		test	byte ptr [bp+@@var_2C], 1
		jz	short xx_10E13
		nopcall	@__RefDestructorCount$qv ; __RefDestructorCount(void)
		mov	bx, ax
		mov	es, dx
		mov	dx, es:[bx+2]
		mov	ax, es:[bx]
		mov	[bp+@@var_3A], dx
		mov	[bp+@@var_3C], ax
		mov	[bp+@@var_12], 6
		push	[bp+@@arg_10]
		push	[bp+@@arg_E]
		push	[bp+@@arg_C]
		push	[bp+@@arg_6]
		push	[bp+n]
		mov	ax, [bp+@@src]
		add	ax, 3Ah	; ':'
		push	[bp+@@src+2]
		push	ax
		call	xx_1055F
		add	sp, 0Eh
		mov	[bp+@@var_12], 0
		jmp	short xx_10DFE

xx_10DF4:
		nopcall	___call_terminate
		nopcall	@_CatchCleanup$qv ; _CatchCleanup(void)

xx_10DFE:
		nopcall	@__RefDestructorCount$qv ; __RefDestructorCount(void)
		mov	bx, [bp+@@var_3A]
		mov	cx, [bp+@@var_3C]
		mov	es, dx
		xchg	ax, bx
		mov	es:[bx+2], ax
		mov	es:[bx], cx

xx_10E13:
		cmp	[bp+@@arg_1E], 0
		jnz	short xx_10E57
		test	byte ptr [bp+@@var_2C], 2
		jz	short xx_10E57
		mov	[bp+@@var_12], 12h
		mov	ax, 1
		push	ax
		les	bx, [bp+@@var_22]
		push	word ptr es:[bx+22h]
		les	bx, [bp+@@var_22]
		push	word ptr es:[bx+20h]
		push	word ptr es:[bx+1Eh]
		push	[bp+@@arg_6]
		push	[bp+n]
		call	xx_108AD
		add	sp, 0Ch
		mov	[bp+@@var_12], 0
		jmp	short xx_10E57

xx_10E4D:
		nopcall	___call_terminate
		nopcall	@_CatchCleanup$qv ; _CatchCleanup(void)

xx_10E57:
		les	bx, ss:16h
		mov	dx, es:[bx+1Eh]
		mov	ax, es:[bx+1Ch]
		mov	[bp+@@var_46], dx
		mov	[bp+@@var_48], ax
		mov	dx, [bp+@@arg_1C]
		mov	ax, [bp+@@arg_1A]
		mov	[bp+@@var_42], dx
		mov	[bp+@@var_44], ax
		mov	dx, [bp+@@src+2]
		mov	ax, [bp+@@src]
		mov	[bp+@@var_3E], dx
		mov	[bp+@@var_40], ax
		push	ss
		lea	ax, [bp+@@var_48]
		push	ax
		xor	ax, ax
		mov	dx, 3
		push	ax
		push	dx
		xor	ax, ax
		mov	dx, 1
		push	ax
		push	dx
		mov	ax, 0EEFh
		mov	dx, 0FACEh
		push	ax
		push	dx
		nopcall	_RaiseException
		add	sp, 10h
		push	[bp+@@var_1E]
		nopcall	___ExitExceptBlocks
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
xx_10B84	endp



; int __cdecl __far _ThrowException(int, int, size_t n,	int, int, int, int, int, int, int, int,	int, int)
		public @_ThrowException$qnvt1t1t1uiuiuinuc
@_ThrowException$qnvt1t1t1uiuiuinuc proc far

@@var_6		= word ptr -6
@@var_4		= word ptr -4
@@var_2		= word ptr -2
@@arg_0		= word ptr  6
@@arg_2		= word ptr  8
n		= word ptr  0Ah
@@arg_6		= word ptr  0Ch
@@arg_8		= word ptr  0Eh
@@arg_A		= word ptr  10h
@@arg_C		= word ptr  12h
@@arg_E		= word ptr  14h
@@arg_10		= word ptr  16h
@@arg_12		= word ptr  18h
@@arg_14		= word ptr  1Ah
@@arg_16		= word ptr  1Ch
@@arg_18		= word ptr  1Eh

		push	bp
		mov	bp, sp
		sub	sp, 6
		push	si
		push	di
		mov	[bp+@@var_6], bp
		mov	bx, [bp+@@var_6]
		mov	dx, ss:[bx+4]
		mov	ax, ss:[bx+2]
		mov	[bp+@@var_2], dx
		mov	[bp+@@var_4], ax
		xor	ax, ax
		push	ax		; int
		push	[bp+@@var_2]	; int
		push	[bp+@@var_4]	; int
		push	[bp+@@arg_18]	; int
		push	[bp+@@arg_16]	; int
		push	[bp+@@arg_14]	; int
		push	[bp+@@arg_12]	; int
		push	[bp+@@arg_10]	; int
		push	[bp+@@arg_E]	; int
		push	[bp+@@arg_C]	; int
		push	[bp+@@arg_A]	; int
		push	[bp+@@arg_8]	; int
		push	[bp+@@arg_6]	; int
		push	[bp+n]		; n
		push	[bp+@@arg_2]	; int
		push	[bp+@@arg_0]	; int
		call	xx_10B84
		add	sp, 20h
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
@_ThrowException$qnvt1t1t1uiuiuinuc endp



; _ReThrowException(unsigned int, unsigned char	*)
		public @_ReThrowException$quinuc
@_ReThrowException$quinuc proc far

@@var_A		= word ptr -0Ah
@@var_8		= word ptr -8
@@var_4		= word ptr -4
@@var_2		= word ptr -2
@@arg_0		= word ptr  6
@@arg_2		= word ptr  8
@@arg_4		= word ptr  0Ah

		push	bp
		mov	bp, sp
		sub	sp, 0Ah
		push	si
		push	di
		mov	[bp+@@var_A], bp
		mov	bx, [bp+@@var_A]
		mov	dx, ss:[bx+4]
		mov	ax, ss:[bx+2]
		mov	[bp+@@var_2], dx
		mov	[bp+@@var_4], ax
		les	bx, ss:16h
		mov	dx, es:[bx+2]
		mov	ax, es:[bx]
		mov	[bp+@@var_8+2], dx
		mov	[bp+@@var_8], ax
		mov	ax, [bp+@@var_8]
		or	ax, [bp+@@var_8+2]
		jnz	short xx_10F47
		nopcall	___call_terminate

xx_10F47:
		mov	ax, 1
		push	ax		; int
		push	[bp+@@var_2]	; int
		push	[bp+@@var_4]	; int
		push	[bp+@@arg_4]	; int
		push	[bp+@@arg_2]	; int
		push	[bp+@@arg_0]	; int
		les	bx, dword ptr [bp+@@var_8]
		push	word ptr es:[bx+0Ch] ; int
		les	bx, dword ptr [bp+@@var_8]
		push	word ptr es:[bx+22h] ; int
		les	bx, dword ptr [bp+@@var_8]
		push	word ptr es:[bx+20h] ; int
		push	word ptr es:[bx+1Eh] ; int
		les	bx, dword ptr [bp+@@var_8]
		push	word ptr es:[bx+0Ah] ; int
		push	word ptr es:[bx+8] ; int
		les	bx, dword ptr [bp+@@var_8]
		cmp	byte ptr es:[bx+38h], 0
		jz	short xx_10F93
		mov	dx, [bp+@@var_8+2]
		mov	ax, [bp+@@var_8]
		add	ax, 3Ah	; ':'
		jmp	short xx_10F9C

xx_10F93:
		les	bx, dword ptr [bp+@@var_8]
		mov	ax, es:[bx+36h]
		mov	dx, ss

xx_10F9C:
		push	dx		; int
		push	ax		; n
		les	bx, dword ptr [bp+@@var_8]
		push	word ptr es:[bx+6] ; int
		push	word ptr es:[bx+4] ; int
		call	xx_10B84
		add	sp, 20h
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
@_ReThrowException$quinuc endp


xx_10FB6	proc far
		push	si
		push	di
		pop	di
		pop	si
		retf
xx_10FB6	endp



xx_10FBB	proc far

@@var_6		= word ptr -6
@@var_4		= word ptr -4
@@var_2		= word ptr -2
@@arg_0		= word ptr  6
@@arg_2		= word ptr  8
@@arg_4		= word ptr  0Ah
@@arg_6		= word ptr  0Ch

		push	bp
		mov	bp, sp
		sub	sp, 6
		push	si
		push	di
		mov	[bp+@@var_4], 0
		mov	bx, [bp+@@arg_0]
		test	byte ptr ss:[bx+4], 6
		jz	short xx_10FD5
		inc	[bp+@@var_4]

xx_10FD5:
		mov	ax, ss:14h
		mov	[bp+@@var_2], ax
		call	xx_10FB6
		jmp	short xx_11023

xx_10FE2:
		mov	ax, [bp+@@var_2]
		mov	[bp+@@var_6], ax
		xor	ax, ax
		push	ax
		push	ax
		push	[bp+@@arg_4]
		push	[bp+@@arg_2]
		push	[bp+@@var_2]
		push	ss
		push	[bp+@@arg_0]
		mov	bx, [bp+@@var_6]
		call	dword ptr ss:[bx+2]
		add	sp, 0Eh
		mov	dx, ax
		or	dx, dx
		jnz	short xx_1100D
		mov	ax, dx
		jmp	short xx_11041

xx_1100D:
		cmp	[bp+@@var_4], 0
		jz	short xx_1101A
		mov	ax, [bp+@@var_2]
		mov	ss:14h,	ax

xx_1101A:
		mov	bx, [bp+@@var_2]
		mov	ax, ss:[bx]
		mov	[bp+@@var_2], ax

xx_11023:
		cmp	[bp+@@var_2], 0FFFFh
		jz	short xx_11031
		mov	ax, [bp+@@var_2]
		cmp	ax, [bp+@@arg_6]
		jnz	short xx_10FE2

xx_11031:
		cmp	[bp+@@var_4], 0
		jz	short xx_1103E
		mov	ax, [bp+@@var_2]
		mov	ss:14h,	ax

xx_1103E:
		mov	ax, 1

xx_11041:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
xx_10FBB	endp



		public __Global_unwind
__Global_unwind	proc far

@@var_4C		= word ptr -4Ch
@@var_4A		= word ptr -4Ah
@@var_48		= word ptr -48h
@@var_46		= word ptr -46h
@@var_3E		= word ptr -3Eh
@@arg_0		= word ptr  6
@@arg_2		= word ptr  8

		push	bp
		mov	bp, sp
		sub	sp, 4Ch
		push	si
		push	di
		mov	dx, [bp+@@arg_2]
		or	dx, dx
		jnz	short xx_11072
		mov	[bp+@@var_4A], 0
		mov	[bp+@@var_4C], 26h ; '&'
		mov	[bp+@@var_46], 0
		mov	[bp+@@var_48], 2
		mov	[bp+@@var_3E], 0
		lea	dx, [bp+@@var_4C]

xx_11072:
		mov	bx, dx
		or	word ptr ss:[bx+4], 2
		push	[bp+@@arg_0]
		xor	ax, ax
		push	ax
		push	ax
		push	dx
		call	xx_10FBB
		add	sp, 8
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
__Global_unwind	endp


xx_1108E	proc far
		push	si
		push	di
		pop	di
		pop	si
		retf
xx_1108E	endp



		public _RaiseException
_RaiseException	proc far

dest		= word ptr -186h
@@var_184		= word ptr -184h
@@var_182		= word ptr -182h
@@var_180		= word ptr -180h
@@var_17E		= word ptr -17Eh
@@var_17C		= word ptr -17Ch
@@var_176		= word ptr -176h
@@var_174		= word ptr -174h
@@var_172		= word ptr -172h
@@var_170		= word ptr -170h
@@var_16E		= word ptr -16Eh
@@var_16C		= word ptr -16Ch
@@var_16A		= word ptr -16Ah
@@var_168		= word ptr -168h
@@var_166		= word ptr -166h
@@var_164		= word ptr -164h
@@var_162		= word ptr -162h
@@var_160		= word ptr -160h
@@var_15E		= word ptr -15Eh
@@var_15A		= word ptr -15Ah
@@var_158		= word ptr -158h
@@var_156		= word ptr -156h
@@var_154		= word ptr -154h
@@var_152		= byte ptr -152h
@@var_C6		= word ptr -0C6h
@@var_C4		= word ptr -0C4h
@@var_C2		= word ptr -0C2h
@@var_C0		= word ptr -0C0h
@@var_BE		= word ptr -0BEh
@@var_BC		= word ptr -0BCh
@@var_BA		= word ptr -0BAh
@@var_B8		= word ptr -0B8h
@@var_B6		= word ptr -0B6h
@@var_B4		= word ptr -0B4h
@@var_B2		= word ptr -0B2h
@@var_B0		= word ptr -0B0h
@@var_AE		= word ptr -0AEh
@@var_AC		= word ptr -0ACh
@@var_AA		= word ptr -0AAh
@@var_A8		= word ptr -0A8h
@@var_A6		= word ptr -0A6h
@@var_A4		= word ptr -0A4h
@@var_A2		= word ptr -0A2h
@@var_A0		= word ptr -0A0h
@@var_9E		= word ptr -9Eh
@@var_9C		= word ptr -9Ch
@@var_9A		= word ptr -9Ah
@@var_98		= word ptr -98h
@@var_96		= word ptr -96h
@@var_94		= word ptr -94h
@@var_92		= word ptr -92h
@@var_90		= word ptr -90h
@@var_8E		= word ptr -8Eh
@@var_8C		= word ptr -8Ch
@@var_8A		= word ptr -8Ah
@@var_88		= word ptr -88h
@@var_86		= byte ptr -86h
@@var_56		= word ptr -56h
@@var_54		= word ptr -54h
@@var_52		= word ptr -52h
@@var_50		= word ptr -50h
@@var_4E		= word ptr -4Eh
@@var_4C		= word ptr -4Ch
@@var_4A		= word ptr -4Ah
@@var_48		= word ptr -48h
@@var_46		= byte ptr -46h
n		= word ptr -0Ah
@@var_8		= word ptr -8
@@var_6		= word ptr -6
@@var_4		= word ptr -4
@@var_2		= word ptr -2
@@arg_0		= word ptr  18h
@@arg_2		= word ptr  1Ah
@@arg_4		= word ptr  1Ch
@@arg_6		= word ptr  1Eh
@@arg_8		= word ptr  20h
@@arg_A		= word ptr  22h
@@arg_C		= dword	ptr  24h

		push	ax
		push	cx
		push	dx
		push	bx
		push	sp
		push	bp
		push	si
		push	di
		push	ds
		push	es
		mov	bp, sp
		sub	sp, 186h
		lea	ax, [bp+@@var_86]
		push	ax
		call	xx_1108E
		pop	cx
		pushf
		pop	ax
		mov	[bp+@@var_8], ax
		cmp	byte ptr ds:__8086, 3
		jnb	short xx_110BC
		jmp	xx_11172

xx_110BC:
		pushad
		mov	[bp+n],	sp
		mov	ax, 20h	; ' '
		push	ax
		push	ss
		push	[bp+n]		; n
		push	ss		; src
		lea	ax, [bp+dest]
		push	ax		; dest
		nopcall	_memcpy
		add	sp, 0Ah
		popad
		mov	dx, [bp+@@var_184]
		mov	ax, [bp+dest]
		mov	[bp+@@var_B4], dx
		mov	[bp+@@var_B6], ax
		mov	dx, [bp+@@var_180]
		mov	ax, [bp+@@var_182]
		mov	[bp+@@var_B0], dx
		mov	[bp+@@var_B2], ax
		mov	dx, [bp+@@var_174]
		mov	ax, [bp+@@var_176]
		mov	[bp+@@var_AC], dx
		mov	[bp+@@var_AE], ax
		mov	dx, [bp+@@var_170]
		mov	ax, [bp+@@var_172]
		mov	[bp+@@var_A8], dx
		mov	[bp+@@var_AA], ax
		mov	dx, [bp+@@var_16C]
		mov	ax, [bp+@@var_16E]
		mov	[bp+@@var_A4], dx
		mov	[bp+@@var_A6], ax
		mov	dx, [bp+@@var_168]
		mov	ax, [bp+@@var_16A]
		mov	[bp+@@var_A0], dx
		mov	[bp+@@var_A2], ax
		mov	dx, [bp+@@var_17C]
		mov	ax, [bp+@@var_17E]
		mov	[bp+@@var_9C], dx
		mov	[bp+@@var_9E], ax
		pushfd
		pop	eax
		shr	eax, 10h
		mov	[bp+@@var_90], ax
		mov	ax, [bp+@@var_8]
		mov	[bp+@@var_92], ax
		mov	[bp+@@var_C0], 0
		mov	[bp+@@var_C2], fs
		mov	[bp+@@var_C4], 0
		mov	[bp+@@var_C6], gs
		jmp	short xx_111BB

xx_11172:
		xor	ax, ax
		xor	dx, dx
		mov	[bp+@@var_9C], ax
		mov	[bp+@@var_9E], dx
		mov	[bp+@@var_A0], ax
		mov	[bp+@@var_A2], dx
		mov	[bp+@@var_A4], ax
		mov	[bp+@@var_A6], dx
		mov	[bp+@@var_A8], ax
		mov	[bp+@@var_AA], dx
		mov	[bp+@@var_AC], ax
		mov	[bp+@@var_AE], dx
		mov	[bp+@@var_B0], ax
		mov	[bp+@@var_B2], dx
		mov	[bp+@@var_B4], ax
		mov	[bp+@@var_B6], dx
		mov	ax, [bp+@@var_8]
		mov	[bp+@@var_90], 0
		mov	[bp+@@var_92], ax

xx_111BB:
		mov	dx, [bp+@@var_9C]
		mov	ax, [bp+@@var_9E]
		add	ax, 18h
		adc	dx, 0
		mov	[bp+@@var_8C], dx
		mov	[bp+@@var_8E], ax
		cmp	[bp+@@arg_2], 0EEFh
		jnz	short xx_111EC
		cmp	[bp+@@arg_0], 0FACEh
		jnz	short xx_111EC
		les	bx, [bp+@@arg_C]
		mov	dx, es:[bx+6]
		mov	ax, es:[bx+4]
		jmp	short xx_111FA

xx_111EC:
		mov	[bp+n],	bp
		mov	bx, [bp+n]
		mov	dx, ss:[bx+16h]
		mov	ax, ss:[bx+14h]

xx_111FA:
		mov	[bp+@@var_4], dx
		mov	[bp+@@var_6], ax
		mov	ax, [bp+@@var_6]
		mov	[bp+@@var_98], 0
		mov	[bp+@@var_9A], ax
		mov	ax, [bp+@@var_4]
		mov	[bp+@@var_94], 0
		mov	[bp+@@var_96], ax
		mov	ax, 14h
		push	ax
		push	ss
		push	bp		; n
		push	ss		; src
		lea	ax, [bp+@@var_166]
		push	ax		; dest
		nopcall	_memcpy
		add	sp, 0Ah
		mov	ax, [bp+@@var_164]
		mov	[bp+@@var_B8], 0
		mov	[bp+@@var_BA], ax
		mov	ax, [bp+@@var_166]
		mov	[bp+@@var_BC], 0
		mov	[bp+@@var_BE], ax
		mov	[bp+@@var_88], 0
		mov	[bp+@@var_8A], ss
		mov	ax, [bp+@@var_154]
		mov	[bp+@@var_A2], ax
		mov	ax, [bp+@@var_15A]
		mov	[bp+@@var_AE], ax
		mov	ax, [bp+@@var_156]
		mov	[bp+@@var_A6], ax
		mov	ax, [bp+@@var_158]
		mov	[bp+@@var_AA], ax
		mov	ax, [bp+@@var_160]
		mov	[bp+@@var_B2], ax
		mov	ax, [bp+@@var_162]
		mov	[bp+@@var_B6], ax
		mov	ax, [bp+@@var_15E]
		mov	[bp+@@var_9E], ax
		mov	dx, [bp+@@arg_2]
		mov	ax, [bp+@@arg_0]
		and	dx, 0EFFFh
		mov	[bp+@@var_54], dx
		mov	[bp+@@var_56], ax
		mov	dx, [bp+@@arg_6]
		mov	ax, [bp+@@arg_4]
		mov	[bp+@@var_50], dx
		mov	[bp+@@var_52], ax
		mov	dx, [bp+@@var_4]
		mov	ax, [bp+@@var_6]
		mov	[bp+@@var_4A], dx
		mov	[bp+@@var_4C], ax
		mov	[bp+@@var_4E], 0
		mov	ax, word ptr [bp+@@arg_C]
		or	ax, word ptr [bp+@@arg_C+2]
		jnz	short xx_112CB
		mov	[bp+@@arg_A], 0
		mov	[bp+@@arg_8], 0

xx_112CB:
		cmp	[bp+@@arg_A], 0
		jb	short xx_112E3
		ja	short xx_112D9
		cmp	[bp+@@arg_8], 0Fh
		jbe	short xx_112E3

xx_112D9:
		mov	[bp+@@arg_A], 0
		mov	[bp+@@arg_8], 0Fh

xx_112E3:
		mov	ax, [bp+@@arg_8]
		mov	[bp+@@var_48], ax
		mov	[bp+@@var_2], 0
		jmp	short xx_11319

xx_112F0:
		mov	bx, [bp+@@var_2]
		mov	cl, 2
		shl	bx, cl
		lea	ax, [bp+@@var_46]
		add	bx, ax
		mov	ax, [bp+@@var_2]
		mov	cl, 2
		shl	ax, cl
		les	si, [bp+@@arg_C]
		add	si, ax
		mov	dx, es:[si+2]
		mov	ax, es:[si]
		mov	ss:[bx+2], dx
		mov	ss:[bx], ax
		inc	[bp+@@var_2]

xx_11319:
		mov	ax, [bp+@@var_2]
		xor	dx, dx
		cmp	dx, [bp+@@arg_A]
		jb	short xx_112F0
		jnz	short xx_1132A
		cmp	ax, [bp+@@arg_8]
		jb	short xx_112F0

xx_1132A:
		mov	ax, 0FFFFh
		push	ax
		push	ss
		lea	ax, [bp+@@var_152]
		push	ax
		lea	ax, [bp+@@var_56]
		push	ax
		call	xx_10FBB
		add	sp, 8
		or	ax, ax
		jnz	short xx_11375
		test	byte ptr [bp+@@arg_4], 1
		jz	short xx_11395
		mov	[bp+@@var_54], 0C000h
		mov	[bp+@@var_56], 25h ; '%'
		mov	dx, [bp+@@arg_6]
		mov	ax, [bp+@@arg_4]
		mov	[bp+@@var_50], dx
		mov	[bp+@@var_52], ax
		mov	[bp+@@var_4A], 0
		mov	[bp+@@var_4C], 0
		mov	[bp+@@var_4E], 0
		mov	[bp+@@var_48], 0
		jmp	short xx_1132A

xx_11375:
		or	[bp+@@var_52], 2
		mov	ax, 0FFFFh
		push	ax
		push	ss
		lea	ax, [bp+@@var_152]
		push	ax
		lea	ax, [bp+@@var_56]
		push	ax
		call	xx_10FBB
		add	sp, 8
		or	ax, ax
		jz	short xx_11395
		jmp	xx_11500

xx_11395:
		cmp	byte ptr ds:__8086, 3
		jnb	short xx_1139F
		jmp	xx_1147F

xx_1139F:
		mov	cx, [bp+@@var_8E]
		sub	cx, 30h	; '0'
		mov	es, [bp+@@var_8A]
		mov	bx, cx
		mov	ax, [bp+@@var_C6]
		mov	es:[bx], ax
		mov	ax, [bp+@@var_C2]
		mov	es:[bx+2], ax
		mov	ax, [bp+@@var_BE]
		mov	es:[bx+4], ax
		mov	ax, [bp+@@var_BA]
		mov	es:[bx+6], ax
		mov	dx, [bp+@@var_B4]
		mov	ax, [bp+@@var_B6]
		mov	es:[bx+0Ah], dx
		mov	es:[bx+8], ax
		mov	dx, [bp+@@var_B0]
		mov	ax, [bp+@@var_B2]
		mov	es:[bx+0Eh], dx
		mov	es:[bx+0Ch], ax
		mov	dx, [bp+@@var_9C]
		mov	ax, [bp+@@var_9E]
		mov	es:[bx+12h], dx
		mov	es:[bx+10h], ax
		mov	dx, [bp+@@var_8C]
		mov	ax, [bp+@@var_8E]
		mov	es:[bx+16h], dx
		mov	es:[bx+14h], ax
		mov	dx, [bp+@@var_AC]
		mov	ax, [bp+@@var_AE]
		mov	es:[bx+1Ah], dx
		mov	es:[bx+18h], ax
		mov	dx, [bp+@@var_A8]
		mov	ax, [bp+@@var_AA]
		mov	es:[bx+1Eh], dx
		mov	es:[bx+1Ch], ax
		mov	dx, [bp+@@var_A4]
		mov	ax, [bp+@@var_A6]
		mov	es:[bx+22h], dx
		mov	es:[bx+20h], ax
		mov	dx, [bp+@@var_A0]
		mov	ax, [bp+@@var_A2]
		mov	es:[bx+26h], dx
		mov	es:[bx+24h], ax
		mov	dx, [bp+@@var_90]
		mov	ax, [bp+@@var_92]
		mov	es:[bx+2Ah], dx
		mov	es:[bx+28h], ax
		mov	ax, [bp+@@var_9A]
		mov	es:[bx+2Ch], ax
		mov	ax, [bp+@@var_96]
		mov	es:[bx+2Eh], ax
		mov	ss, [bp+@@var_8A]
		mov	sp, bx
		pop	gs
		pop	fs
		pop	es
		pop	ds
		popad
		popfd
		retf
		jmp	xx_11505

xx_1147F:
		mov	cx, [bp+@@var_8E]
		sub	cx, 1Ah
		mov	es, [bp+@@var_8A]
		mov	bx, cx
		mov	ax, [bp+@@var_BE]
		mov	es:[bx], ax
		mov	ax, [bp+@@var_BA]
		mov	es:[bx+2], ax
		mov	ax, [bp+@@var_B6]
		mov	es:[bx+4], ax
		mov	ax, [bp+@@var_B2]
		mov	es:[bx+6], ax
		mov	ax, [bp+@@var_9E]
		mov	es:[bx+8], ax
		mov	ax, [bp+@@var_8E]
		mov	es:[bx+0Ah], ax
		mov	ax, [bp+@@var_AE]
		mov	es:[bx+0Ch], ax
		mov	ax, [bp+@@var_AA]
		mov	es:[bx+0Eh], ax
		mov	ax, [bp+@@var_A6]
		mov	es:[bx+10h], ax
		mov	ax, [bp+@@var_A2]
		mov	es:[bx+12h], ax
		mov	ax, [bp+@@var_92]
		mov	es:[bx+14h], ax
		mov	ax, [bp+@@var_9A]
		mov	es:[bx+16h], ax
		mov	ax, [bp+@@var_96]
		mov	es:[bx+18h], ax
		mov	ss, [bp+@@var_8A]
		mov	sp, bx
		pop	es
		pop	ds
		popa
		popf
		retf
		jmp	short xx_11505

xx_11500:
		nopcall	___call_terminate

xx_11505:
		mov	sp, bp
		pop	es
		pop	ds
		pop	di
		pop	si
		pop	bp
		pop	bx
		pop	bx
		pop	dx
		pop	cx
		pop	ax
		retf
_RaiseException	endp

xx_11512	db 4 dup(0)
		dd xx_11574
		db 10h dup(0)
xx_1152A	db 4 dup(0), 0E2h, 0FFh, 2 dup(0), 3, 0
		dd xx_11512
		db 2 dup(0), 4,	0


xx_1153C	proc near

@@var_1E		= word ptr -1Eh
@@var_12		= word ptr -12h
@@arg_0		= word ptr  4
@@arg_2		= word ptr  6
@@arg_4		= word ptr  8
@@arg_6		= word ptr  0Ah
@@arg_8		= word ptr  0Ch

		push	bp
		mov	bp, sp
		sub	sp, 1Eh
		push	si
		push	di
		mov	ax, seg	xx_1152A
		mov	bx, offset xx_1152A
		nopcall	___InitExceptBlocks
		mov	[bp+@@var_12], 6
		mov	ax, 1
		push	ax
		push	[bp+@@arg_8]
		push	[bp+@@arg_6]
		push	[bp+@@arg_4]
		push	[bp+@@arg_2]
		push	[bp+@@arg_0]
		call	xx_108AD
		add	sp, 0Ch
		mov	[bp+@@var_12], 0
		jmp	short xx_1157E

xx_11574:
		nopcall	___call_terminate
		nopcall	@_CatchCleanup$qv ; _CatchCleanup(void)

xx_1157E:
		push	[bp+@@var_1E]
		nopcall	___ExitExceptBlocks
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retn
xx_1153C	endp



xx_1158C	proc near

@@var_8		= dword	ptr -8
@@var_4		= dword	ptr -4
@@arg_0		= dword	ptr  4

		push	bp
		mov	bp, sp
		sub	sp, 8
		push	si
		push	di
		les	bx, [bp+@@arg_0]
		cmp	byte ptr es:[bx+38h], 0
		jz	short xx_11607
		les	bx, [bp+@@arg_0]
		test	byte ptr es:[bx+16h], 2
		jz	short xx_115FF
		nopcall	@__RefDestructorCount$qv ; __RefDestructorCount(void)
		mov	bx, ax
		mov	es, dx
		mov	dx, es:[bx+2]
		mov	ax, es:[bx]
		mov	word ptr [bp+@@var_8+2], dx
		mov	word ptr [bp+@@var_8], ax
		les	bx, [bp+@@arg_0]
		les	bx, es:[bx+4]
		mov	word ptr [bp+@@var_4+2], es
		mov	word ptr [bp+@@var_4], bx
		push	word ptr es:[bx+22h]
		les	bx, [bp+@@var_4]
		push	word ptr es:[bx+20h]
		push	word ptr es:[bx+1Eh]
		mov	ax, word ptr [bp+@@arg_0]
		add	ax, 3Ah	; ':'
		push	word ptr [bp+@@arg_0+2]
		push	ax
		call	xx_1153C
		add	sp, 0Ah
		nopcall	@__RefDestructorCount$qv ; __RefDestructorCount(void)
		mov	bx, word ptr [bp+@@var_8+2]
		mov	cx, word ptr [bp+@@var_8]
		mov	es, dx
		xchg	ax, bx
		mov	es:[bx+2], ax
		mov	es:[bx], cx

xx_115FF:
		les	bx, [bp+@@arg_0]
		mov	byte ptr es:[bx+38h], 0

xx_11607:
		les	bx, [bp+@@arg_0]
		cmp	byte ptr es:[bx+39h], 0
		jz	short xx_1165E
		les	bx, [bp+@@arg_0]
		mov	dx, es:[bx+34h]
		mov	ax, es:[bx+32h]
		mov	word ptr [bp+@@var_8+2], dx
		mov	word ptr [bp+@@var_8], ax
		les	bx, [bp+@@var_8]
		test	byte ptr es:[bx+2], 2
		jz	short xx_11656
		les	bx, [bp+@@var_8]
		test	byte ptr es:[bx+8], 2
		jz	short xx_11656
		les	bx, [bp+@@var_8]
		push	word ptr es:[bx+22h]
		les	bx, [bp+@@var_8]
		push	word ptr es:[bx+20h]
		push	word ptr es:[bx+1Eh]
		push	ss
		les	bx, [bp+@@arg_0]
		push	word ptr es:[bx+36h]
		call	xx_1153C
		add	sp, 0Ah

xx_11656:
		les	bx, [bp+@@arg_0]
		mov	byte ptr es:[bx+39h], 0

xx_1165E:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retn
xx_1158C	endp



; _CatchCleanup(void)
		public @_CatchCleanup$qv
@_CatchCleanup$qv proc far

@@var_6		= word ptr -6
@@var_4		= dword	ptr -4
@@arg_0		= dword	ptr  6
@@arg_6		= word ptr  0Ch

		push	bp
		mov	bp, sp
		sub	sp, 6
		push	si
		push	di
		les	bx, ss:16h
		mov	dx, es:[bx+2]
		mov	ax, es:[bx]
		mov	word ptr [bp+@@var_4+2], dx
		mov	word ptr [bp+@@var_4], ax
		les	bx, [bp+@@var_4]
		mov	dx, es:[bx+2]
		mov	ax, es:[bx]
		les	bx, ss:16h
		mov	es:[bx+2], dx
		mov	es:[bx], ax
		les	bx, [bp+@@var_4]
		mov	ax, es:[bx+24h]
		mov	[bp+@@var_6], ax
		mov	bx, [bp+@@var_6]
		les	ax, ss:[bx+@@arg_0]
		mov	bx, [bp+@@var_6]
		add	ax, ss:[bx+@@arg_6]
		mov	bx, ax
		mov	ax, es:[bx]
		mov	bx, [bp+@@var_6]
		mov	ss:[bx+@@arg_6], ax
		push	word ptr [bp+@@var_4+2]
		push	word ptr [bp+@@var_4]
		call	xx_1158C
		pop	cx
		pop	cx
		push	ds
		les	bx, [bp+@@var_4]
		mov	ds, word ptr es:[bx+18h]
		push	word ptr [bp+@@var_4+2]
		push	word ptr [bp+@@var_4]
		les	bx, [bp+@@var_4]
		call	dword ptr es:[bx+1Ah]
		pop	cx
		pop	cx
		pop	ds
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
@_CatchCleanup$qv endp



xx_116E1	proc near

@@var_C		= word ptr -0Ch
@@var_A		= word ptr -0Ah
@@var_8		= dword	ptr -8
@@var_4		= dword	ptr -4
@@arg_0		= dword	ptr  4
@@arg_4		= word ptr  8
@@arg_6		= word ptr  0Ah
@@arg_8		= word ptr  0Ch
@@arg_A		= word ptr  0Eh

		push	bp
		mov	bp, sp
		sub	sp, 0Ch
		push	si
		push	di

xx_116E9:
		les	bx, [bp+@@arg_0]
		mov	dx, es:[bx+2]
		mov	ax, es:[bx]
		mov	word ptr [bp+@@var_4+2], dx
		mov	word ptr [bp+@@var_4], ax
		mov	ax, word ptr [bp+@@var_4]
		or	ax, word ptr [bp+@@var_4+2]
		jnz	short xx_11706
		xor	ax, ax
		jmp	xx_117A7

xx_11706:
		mov	bx, [bp+@@arg_A]
		mov	dx, ss:[bx+2]
		mov	ax, ss:[bx]
		les	bx, [bp+@@arg_0]
		add	ax, es:[bx+4]
		mov	word ptr [bp+@@var_8+2], dx
		mov	word ptr [bp+@@var_8], ax
		cmp	[bp+@@arg_4], 0
		jz	short xx_11732
		les	bx, [bp+@@var_8]
		mov	ax, es:[bx]
		mov	dx, word ptr [bp+@@var_8+2]
		mov	word ptr [bp+@@var_8+2], dx
		mov	word ptr [bp+@@var_8], ax

xx_11732:
		push	[bp+@@arg_8]
		push	[bp+@@arg_6]
		push	word ptr [bp+@@var_4+2]
		push	word ptr [bp+@@var_4]
		call	xx_10061
		add	sp, 8
		or	ax, ax
		jnz	short xx_1178B
		les	bx, [bp+@@var_4]
		test	byte ptr es:[bx+2], 2
		jz	short xx_117A0
		les	bx, [bp+@@var_4]
		mov	dx, word ptr [bp+@@var_4+2]
		mov	ax, word ptr [bp+@@var_4]
		add	ax, es:[bx+0Ah]
		mov	[bp+@@var_A], dx
		mov	[bp+@@var_C], ax
		mov	ax, [bp+@@var_C]
		or	ax, [bp+@@var_A]
		jz	short xx_117A0
		lea	ax, [bp+@@var_8]
		push	ax
		push	[bp+@@arg_8]
		push	[bp+@@arg_6]
		xor	ax, ax
		push	ax
		push	[bp+@@var_A]
		push	[bp+@@var_C]
		call	xx_116E1
		add	sp, 0Ch
		or	ax, ax
		jz	short xx_117A0

xx_1178B:
		mov	bx, [bp+@@arg_A]
		mov	dx, word ptr [bp+@@var_8+2]
		mov	ax, word ptr [bp+@@var_8]
		mov	ss:[bx+2], dx
		mov	ss:[bx], ax
		mov	ax, 1
		jmp	short xx_117A7

xx_117A0:
		add	word ptr [bp+@@arg_0], 8
		jmp	xx_116E9

xx_117A7:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retn
xx_116E1	endp



xx_117AD	proc far

@@var_4		= word ptr -4
@@var_2		= word ptr -2
@@arg_0		= word ptr  6
@@arg_2		= word ptr  8
@@arg_4		= dword	ptr  0Ah
@@arg_8		= word ptr  0Eh
@@arg_A		= word ptr  10h

		push	bp
		mov	bp, sp
		sub	sp, 4
		push	si
		push	di
		mov	ax, [bp+@@arg_0]
		or	ax, [bp+@@arg_2]
		jz	short xx_1181E
		les	bx, [bp+@@arg_4]
		mov	dx, word ptr [bp+@@arg_4+2]
		mov	ax, word ptr [bp+@@arg_4]
		add	ax, es:[bx+0Ah]
		mov	[bp+@@var_2], dx
		mov	[bp+@@var_4], ax
		lea	ax, [bp+@@arg_0]
		push	ax
		push	[bp+@@arg_A]
		push	[bp+@@arg_8]
		xor	ax, ax
		push	ax
		push	[bp+@@var_2]
		push	[bp+@@var_4]
		call	xx_116E1
		add	sp, 0Ch
		or	ax, ax
		jnz	short xx_1181E
		les	bx, [bp+@@arg_4]
		mov	dx, word ptr [bp+@@arg_4+2]
		mov	ax, word ptr [bp+@@arg_4]
		add	ax, es:[bx+0Ch]
		mov	[bp+@@var_2], dx
		mov	[bp+@@var_4], ax
		lea	ax, [bp+@@arg_0]
		push	ax
		push	[bp+@@arg_A]
		push	[bp+@@arg_8]
		mov	ax, 1
		push	ax
		push	[bp+@@var_2]
		push	[bp+@@var_4]
		call	xx_116E1
		add	sp, 0Ch
		or	ax, ax
		jz	short xx_11826

xx_1181E:
		mov	dx, [bp+@@arg_2]
		mov	ax, [bp+@@arg_0]
		jmp	short xx_1182A

xx_11826:
		xor	dx, dx
		xor	ax, ax

xx_1182A:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
xx_117AD	endp



; int __fastcall xx_11830(int,	int, int, __int32, int,	__int32, __int32, int)
xx_11830	proc near

@@var_18		= word ptr -18h
@@var_16		= word ptr -16h
@@var_14		= word ptr -14h
@@var_12		= word ptr -12h
@@var_10		= word ptr -10h
n		= word ptr -0Eh
@@var_A		= word ptr -0Ah
@@var_8		= dword	ptr -8
@@var_4		= word ptr -4
@@var_2		= word ptr -2
@@arg_0		= word ptr  4
@@arg_6		= dword	ptr  0Ah
@@arg_A		= word ptr  0Eh
@@arg_E		= word ptr  12h

		push	bp
		mov	bp, sp
		sub	sp, 18h
		push	si
		push	di
		les	bx, dword ptr [bp+@@arg_0]
		mov	dx, es:[bx+6]
		mov	ax, es:[bx+4]
		mov	[bp+@@var_2], dx
		mov	[bp+@@var_4], ax
		les	bx, [bp+@@arg_6]
		mov	es:[bx+34h], dx
		mov	es:[bx+32h], ax
		mov	ax, [bp+@@var_4]
		or	ax, [bp+@@var_2]
		jnz	short xx_1185F
		jmp	xx_11AD0

xx_1185F:
		les	bx, dword ptr [bp+@@arg_0]
		test	byte ptr es:[bx+8], 80h
		jz	short xx_1186C
		jmp	xx_11AD0

xx_1186C:
		les	bx, dword ptr [bp+@@arg_0]
		mov	ax, es:[bx+8]
		and	ax, 1
		neg	ax
		sbb	ax, ax
		inc	ax
		mov	[bp+@@var_14], ax
		mov	dx, word ptr [bp+@@arg_6+2]
		mov	ax, word ptr [bp+@@arg_6]
		add	ax, 3Ah	; ':'
		mov	[bp+n+2], dx
		mov	[bp+n],	ax
		les	bx, [bp+@@arg_6]
		mov	byte ptr es:[bx+39h], 1
		les	bx, dword ptr [bp+@@arg_A]
		mov	ax, es:[bx]
		add	ax, [bp+@@arg_E]
		les	bx, [bp+@@arg_6]
		mov	es:[bx+36h], ax
		mov	dx, [bp+@@var_2]
		mov	ax, [bp+@@var_4]
		mov	word ptr [bp+@@var_8+2], dx
		mov	word ptr [bp+@@var_8], ax
		les	bx, [bp+@@var_8]
		mov	ax, es:[bx]
		mov	[bp+@@var_A], ax
		les	bx, [bp+@@var_8]
		mov	cx, es:[bx+2]
		mov	dx, cx
		test	cl, 30h
		jz	short xx_118E0
		les	bx, [bp+@@var_8]
		mov	dx, es:[bx+8]
		mov	ax, es:[bx+6]
		mov	word ptr [bp+@@var_8+2], dx
		mov	word ptr [bp+@@var_8], ax
		les	bx, [bp+@@var_8]
		mov	dx, es:[bx+2]

xx_118E0:
		test	cl, 10h
		jz	short xx_11908
		les	bx, [bp+@@arg_6]
		test	byte ptr es:[bx+0Ch], 1
		jz	short xx_11908
		push	[bp+@@var_A]
		xor	ax, ax
		push	ax		; n
		push	ss		; c
		les	bx, [bp+@@arg_6]
		push	word ptr es:[bx+36h] ; s
		nopcall	_memset
		add	sp, 8
		jmp	xx_11A33

xx_11908:
		test	dl, 1
		jnz	short xx_11910
		jmp	xx_119B4

xx_11910:
		test	cl, 30h
		jnz	short xx_11918
		jmp	xx_119B4

xx_11918:
		test	cl, 20h
		jz	short xx_1191F
		jmp	short xx_11942

xx_1191F:
		les	bx, dword ptr [bp+n]
		mov	dx, es:[bx+2]
		mov	ax, es:[bx]
		mov	[bp+n+2], dx
		mov	[bp+n],	ax
		les	bx, [bp+@@arg_6]
		test	byte ptr es:[bx+15h], 10h
		jz	short xx_11949
		mov	ax, [bp+n]
		mov	[bp+n+2], ds
		mov	[bp+n],	ax

xx_11942:
		mov	[bp+@@var_14], 1
		jmp	short $+2

xx_11949:
		push	word ptr [bp+@@var_8+2]
		push	word ptr [bp+@@var_8]
		les	bx, [bp+@@arg_6]
		push	word ptr es:[bx+12h]
		push	word ptr es:[bx+10h]
		call	xx_10061
		add	sp, 8
		or	ax, ax
		jnz	short xx_119AA
		mov	dx, [bp+n+2]
		mov	ax, [bp+n]
		mov	[bp+@@var_16], dx
		mov	[bp+@@var_18], ax
		push	word ptr [bp+@@var_8+2]
		push	word ptr [bp+@@var_8]
		les	bx, [bp+@@arg_6]
		push	word ptr es:[bx+12h]
		push	word ptr es:[bx+10h]
		push	[bp+n+2]
		push	[bp+n]
		call	xx_117AD
		add	sp, 0Ch
		mov	[bp+n+2], dx
		mov	[bp+n],	ax
		mov	dx, [bp+n+2]
		mov	ax, [bp+n]
		cmp	dx, [bp+@@var_16]
		jnz	short xx_119A5
		cmp	ax, [bp+@@var_18]
		jz	short xx_119AA

xx_119A5:
		mov	[bp+@@var_14], 1

xx_119AA:
		push	[bp+@@var_A]
		push	ss
		lea	ax, [bp+n]
		jmp	xx_11A7E

xx_119B4:
		les	bx, [bp+@@arg_6]
		test	byte ptr es:[bx+14h], 1
		jz	short xx_11A3A
		push	word ptr [bp+@@var_8+2]
		push	word ptr [bp+@@var_8]
		les	bx, [bp+@@arg_6]
		push	word ptr es:[bx+12h]
		push	word ptr es:[bx+10h]
		call	xx_10061
		add	sp, 8
		or	ax, ax
		jnz	short xx_11A03
		push	word ptr [bp+@@var_8+2]
		push	word ptr [bp+@@var_8]
		les	bx, [bp+@@arg_6]
		push	word ptr es:[bx+12h]
		push	word ptr es:[bx+10h]
		push	[bp+n+2]
		push	[bp+n]
		call	xx_117AD
		add	sp, 0Ch
		mov	[bp+n+2], dx
		mov	[bp+n],	ax
		mov	[bp+@@var_14], 1

xx_11A03:
		les	bx, [bp+@@var_8]
		test	byte ptr es:[bx+8], 1
		jz	short xx_11A81
		les	bx, dword ptr [bp+@@arg_0]
		push	word ptr es:[bx+0Eh]
		les	bx, dword ptr [bp+@@arg_0]
		push	word ptr es:[bx+0Ch]
		push	word ptr es:[bx+0Ah]
		push	[bp+n+2]
		push	[bp+n]
		push	ss
		les	bx, [bp+@@arg_6]
		push	word ptr es:[bx+36h]
		call	xx_1055F
		add	sp, 0Eh

xx_11A33:
		mov	[bp+@@var_14], 1
		jmp	short xx_11A9A

xx_11A3A:
		test	cl, 20h
		jz	short xx_11A59
		push	[bp+@@var_A]
		push	ss
		lea	ax, [bp+n]
		push	ax		; n
		push	ss		; src
		les	bx, [bp+@@arg_6]
		push	word ptr es:[bx+36h] ; dest
		nopcall	_memcpy
		add	sp, 0Ah
		jmp	short xx_11A33

xx_11A59:
		test	cl, 10h
		jz	short xx_11A81
		les	bx, [bp+@@arg_6]
		mov	ax, es:[bx+0Eh]
		cmp	ax, [bp+@@var_A]
		jz	short xx_11A81
		les	bx, dword ptr [bp+n]
		mov	ax, es:[bx]
		mov	[bp+@@var_10], ds
		mov	[bp+@@var_12], ax
		mov	ax, 4
		push	ax
		push	ss
		lea	ax, [bp+@@var_12]

xx_11A7E:
		push	ax
		jmp	short xx_11A8A

xx_11A81:
		push	[bp+@@var_A]
		push	[bp+n+2]
		push	[bp+n]		; n

xx_11A8A:
		push	ss		; src
		les	bx, [bp+@@arg_6]
		push	word ptr es:[bx+36h] ; dest
		nopcall	_memcpy
		add	sp, 0Ah

xx_11A9A:
		cmp	[bp+@@var_14], 0
		jnz	short xx_11AD0
		les	bx, [bp+@@var_8]
		test	byte ptr es:[bx+8], 2
		jz	short xx_11AC8
		les	bx, [bp+@@var_8]
		push	word ptr es:[bx+22h]
		les	bx, [bp+@@var_8]
		push	word ptr es:[bx+20h]
		push	word ptr es:[bx+1Eh]
		push	[bp+n+2]
		push	[bp+n]
		call	xx_1153C
		add	sp, 0Ah

xx_11AC8:
		les	bx, [bp+@@arg_6]
		mov	byte ptr es:[bx+38h], 0

xx_11AD0:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retn
xx_11830	endp



xx_11AD6	proc near

@@var_20		= word ptr -20h
@@var_1E		= word ptr -1Eh
@@var_1C		= word ptr -1Ch
@@var_1A		= dword	ptr -1Ah
@@var_16		= dword	ptr -16h
@@var_12		= word ptr -12h
@@var_10		= word ptr -10h
@@var_E		= word ptr -0Eh
@@var_C		= word ptr -0Ch
@@var_A		= word ptr -0Ah
@@var_8		= word ptr -8
@@var_6		= word ptr -6
@@var_4		= dword	ptr -4
@@arg_0		= word ptr  4
@@arg_2		= word ptr  6
@@arg_4		= word ptr  8
@@arg_8		= word ptr  0Ch
@@arg_A		= word ptr  0Eh
@@arg_C		= word ptr  10h
@@arg_E		= word ptr  12h

		push	bp
		mov	bp, sp
		sub	sp, 20h
		push	si
		push	di
		mov	[bp+@@var_E], 0
		les	bx, ss:16h
		mov	si, [bp+@@arg_0]
		mov	ax, ss:[si+@@arg_A]
		mov	es:[bx+6], ax
		mov	[bp+@@var_C], ax
		les	bx, ss:16h
		mov	si, [bp+@@arg_0]
		mov	ax, ss:[si+@@arg_C]
		mov	es:[bx+8], ax
		mov	bx, [bp+@@arg_0]
		mov	dx, ss:[bx+@@arg_4]
		mov	ax, ss:[bx+@@arg_2]
		mov	word ptr [bp+@@var_4+2], dx
		mov	word ptr [bp+@@var_4], ax
		les	bx, [bp+@@var_4]
		mov	ax, [bp+@@arg_0]
		sub	ax, es:[bx+4]
		mov	[bp+@@var_A], ax
		mov	bx, [bp+@@arg_0]
		mov	ax, ss:[bx+@@arg_8]
		jmp	xx_11C7B

xx_11B2E:
		mov	ax, [bp+@@var_6]
		mov	[bp+@@var_12], ax
		les	bx, [bp+@@var_4]
		add	bx, [bp+@@var_12]
		mov	ax, es:[bx]
		mov	[bp+@@var_8], ax
		add	[bp+@@var_12], 2
		les	bx, [bp+@@var_4]
		add	bx, [bp+@@var_12]
		mov	ax, es:[bx]
		mov	[bp+@@var_10], ax
		add	[bp+@@var_12], 2
		mov	bx, [bp+@@arg_0]
		mov	ax, [bp+@@var_8]
		mov	ss:[bx+@@arg_8], ax
		mov	bx, [bp+@@var_10]
		cmp	bx, 5
		jbe	short xx_11B69
		jmp	xx_11C78

xx_11B69:
		add	bx, bx
		jmp	cs:xx_11C95[bx]

xx_11B70:
		les	bx, [bp+@@var_4]
		add	bx, [bp+@@var_12]
		mov	dx, es:[bx+6]
		mov	ax, es:[bx+4]
		mov	word ptr xx_131A0+2, dx
		mov	word ptr xx_131A0, ax
		mov	bx, [bp+@@arg_0]
		mov	ss:[bx+@@arg_E], 1
		push	ds
		pop	es
		assume es:DGROUP
		push	ds
		mov	ds, [bp+@@var_C]
		push	bp
		mov	bp, [bp+@@var_A]
		call	es:xx_131A0
		pop	bp
		pop	ds
		mov	bx, [bp+@@arg_0]
		mov	ss:[bx+@@arg_E], 0
		jmp	xx_11C78

xx_11BAB:
		add	[bp+@@var_12], 4
		mov	dx, ss:18h
		mov	ax, ss:16h
		jmp	short xx_11BDA

xx_11BBA:
		les	bx, [bp+@@var_16]
		assume es:nothing
		mov	ax, es:[bx+24h]
		cmp	ax, [bp+@@arg_0]
		jnz	short xx_11BD4
		les	bx, [bp+@@var_16]
		mov	ax, es:[bx+2Ah]
		cmp	ax, [bp+@@var_6]
		jnz	short xx_11BD4
		jmp	short xx_11BF4

xx_11BD4:
		mov	dx, word ptr [bp+@@var_16+2]
		mov	ax, word ptr [bp+@@var_16]

xx_11BDA:
		mov	word ptr [bp+@@var_1A+2],	dx
		mov	word ptr [bp+@@var_1A], ax
		les	bx, [bp+@@var_1A]
		mov	dx, es:[bx+2]
		mov	ax, es:[bx]
		mov	word ptr [bp+@@var_16+2],	dx
		mov	word ptr [bp+@@var_16], ax
		or	ax, dx
		jnz	short xx_11BBA

xx_11BF4:
		les	bx, [bp+@@var_16]
		mov	dx, es:[bx+2]
		mov	ax, es:[bx]
		les	bx, [bp+@@var_1A]
		mov	es:[bx+2], dx
		mov	es:[bx], ax
		push	word ptr [bp+@@var_16+2]
		push	word ptr [bp+@@var_16]
		call	xx_1158C
		pop	cx
		pop	cx
		push	ds
		les	bx, [bp+@@var_16]
		mov	ds, word ptr es:[bx+18h]
		push	word ptr [bp+@@var_16+2]
		push	word ptr [bp+@@var_16]
		les	bx, [bp+@@var_16]
		call	dword ptr es:[bx+1Ah]
		pop	cx
		pop	cx
		pop	ds
		jmp	short xx_11C78

xx_11C2D:
		les	bx, [bp+@@var_4]
		add	bx, [bp+@@var_12]
		mov	ax, es:[bx]
		mov	[bp+@@var_1C], ax
		add	[bp+@@var_12], 2
		les	bx, [bp+@@var_4]
		add	bx, [bp+@@var_12]
		mov	ax, es:[bx]
		mov	[bp+@@var_1E], ds
		mov	[bp+@@var_20], ax
		mov	ax, word ptr [bp+@@var_4+2]
		mov	dx, [bp+@@var_20]
		mov	[bp+@@var_1E], ax
		mov	[bp+@@var_20], dx
		push	[bp+@@var_A]
		push	[bp+@@arg_0]
		mov	ax, [bp+@@var_1C]
		add	ax, [bp+@@var_E]
		cwd
		push	dx
		push	ax
		push	[bp+@@var_1E]
		push	[bp+@@var_20]
		call	xx_126AC
		add	sp, 0Ch
		mov	[bp+@@var_E], ax
		jmp	short $+2

xx_11C78:
		mov	ax, [bp+@@var_8]

xx_11C7B:
		mov	[bp+@@var_6], ax
		cmp	[bp+@@var_6], 0
		jz	short xx_11C8F
		mov	ax, [bp+@@var_6]
		cmp	ax, [bp+@@arg_2]
		jz	short xx_11C8F
		jmp	xx_11B2E

xx_11C8F:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retn
xx_11AD6	endp

xx_11C95	dw offset xx_11B70
		dw offset xx_11C78
		dw offset xx_11C78
		dw offset xx_11C78
		dw offset xx_11BAB
		dw offset xx_11C2D


		public __Local_unwind
__Local_unwind	proc far

@@var_2		= word ptr -2
@@arg_0		= word ptr  6

		push	bp
		mov	bp, sp
		sub	sp, 2
		push	si
		push	di
		mov	ax, ss:14h
		mov	[bp+@@var_2], ax
		push	[bp+@@arg_0]
		push	[bp+@@var_2]
		call	xx_11AD6
		pop	cx
		pop	cx
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
__Local_unwind	endp



		public __Return_unwind
__Return_unwind	proc far

@@var_2		= word ptr -2

		push	bp
		mov	bp, sp
		sub	sp, 2
		push	si
		push	di
		mov	ax, ss:14h
		mov	[bp+@@var_2], ax
		xor	ax, ax
		push	ax
		push	[bp+@@var_2]
		call	xx_11AD6
		pop	cx
		pop	cx
		mov	bx, [bp+@@var_2]
		mov	ax, ss:[bx]
		mov	ss:14h,	ax
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
__Return_unwind	endp



xx_11CEB	proc near

@@var_8		= word ptr -8
@@var_6		= word ptr -6
@@var_4		= dword	ptr -4
@@arg_0		= word ptr  4
@@arg_2		= word ptr  6
@@arg_4		= dword	ptr  8

		push	bp
		mov	bp, sp
		sub	sp, 8
		push	si
		push	di
		mov	dx, [bp+@@arg_2]
		mov	ax, [bp+@@arg_0]
		add	ax, 4
		mov	word ptr [bp+@@var_4+2], dx
		mov	word ptr [bp+@@var_4], ax
		jmp	short xx_11D59

xx_11D04:
		les	bx, [bp+@@var_4]
		mov	dx, es:[bx+6]
		mov	ax, es:[bx+4]
		mov	[bp+@@var_6], dx
		mov	[bp+@@var_8], ax
		mov	ax, [bp+@@var_8]
		or	ax, [bp+@@var_6]
		jz	short xx_11D4D
		xor	ax, ax
		push	ax
		les	bx, [bp+@@arg_4]
		push	word ptr es:[bx+0Ch]
		push	[bp+@@var_6]
		push	[bp+@@var_8]
		les	bx, [bp+@@arg_4]
		push	word ptr es:[bx+0Ah]
		push	word ptr es:[bx+8]
		les	bx, [bp+@@arg_4]
		push	word ptr es:[bx+6]
		push	word ptr es:[bx+4]
		call	xx_1045A
		add	sp, 10h
		or	ax, ax
		jz	short xx_11D55

xx_11D4D:
		mov	dx, word ptr [bp+@@var_4+2]
		mov	ax, word ptr [bp+@@var_4]
		jmp	short xx_11D69

xx_11D55:
		add	word ptr [bp+@@var_4], 10h

xx_11D59:
		les	bx, [bp+@@var_4]
		mov	ax, es:[bx]
		or	ax, es:[bx+2]
		jnz	short xx_11D04
		xor	dx, dx
		xor	ax, ax

xx_11D69:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retn
xx_11CEB	endp

		db 2 dup(2Ah), 42h, 2 dup(43h),	78h, 68h, 31h


		public __ExceptionHandler
__ExceptionHandler proc	far

@@var_38		= word ptr -38h
@@var_36		= word ptr -36h
@@var_34		= word ptr -34h
@@var_32		= word ptr -32h
@@var_30		= word ptr -30h
@@var_2E		= word ptr -2Eh
@@var_2C		= word ptr -2Ch
@@var_2A		= word ptr -2Ah
@@var_28		= word ptr -28h
@@var_26		= dword	ptr -26h
@@var_20		= dword	ptr -20h
@@var_1C		= word ptr -1Ch
@@var_1A		= word ptr -1Ah
@@var_18		= word ptr -18h
@@var_16		= word ptr -16h
@@var_14		= word ptr -14h
@@var_12		= word ptr -12h
@@var_10		= dword	ptr -10h
@@var_C		= dword	ptr -0Ch
@@var_8		= word ptr -8
@@var_6		= word ptr -6
@@var_4		= word ptr -4
@@var_2		= word ptr -2
@@arg_0		= word ptr  6
@@arg_2		= word ptr  8
@@arg_4		= word ptr  0Ah
@@arg_6		= word ptr  0Ch
@@arg_8		= word ptr  0Eh
@@arg_A		= word ptr  10h
@@arg_E		= word ptr  14h
@@arg_10		= word ptr  16h
@@arg_12		= word ptr  18h
@@arg_14		= word ptr  1Ah

		push	bp
		mov	bp, sp
		sub	sp, 38h
		push	si
		push	di
		mov	ax, [bp+@@arg_0]
		mov	[bp+@@var_2], ax
		mov	ax, [bp+@@arg_4]
		mov	[bp+@@var_4], ax
		mov	dx, [bp+@@arg_8]
		mov	ax, [bp+@@arg_6]
		mov	[bp+@@var_6], dx
		mov	[bp+@@var_8], ax
		mov	bx, [bp+@@var_2]
		mov	dx, ss:[bx+@@arg_14]
		mov	ax, ss:[bx+@@arg_12]
		mov	word ptr [bp+@@var_C+2], dx
		mov	word ptr [bp+@@var_C], ax
		mov	bx, [bp+@@var_4]
		mov	dx, ss:[bx+@@arg_2]
		mov	ax, ss:[bx+@@arg_0]
		mov	word ptr [bp+@@var_10+2],	dx
		mov	word ptr [bp+@@var_10], ax
		les	bx, [bp+@@var_10]
		mov	ax, [bp+@@var_4]
		sub	ax, es:[bx+4]
		mov	[bp+@@var_16], ax
		mov	bx, [bp+@@var_4]
		mov	ax, ss:[bx+@@arg_4]
		mov	[bp+@@var_18], ax
		les	bx, ss:16h
		mov	si, [bp+@@var_4]
		mov	ax, ss:[si+@@arg_8]
		mov	es:[bx+6], ax
		mov	[bp+@@var_1A], ax
		les	bx, ss:16h
		mov	si, [bp+@@var_4]
		mov	ax, ss:[si+@@arg_A]
		mov	es:[bx+8], ax
		mov	[bp+@@var_1C], ax
		mov	bx, [bp+@@var_2]
		test	byte ptr ss:[bx+4], 6
		jnz	short xx_11E03
		jmp	xx_11EAB

xx_11E03:
		xor	ax, ax
		push	ax
		push	[bp+@@var_4]
		call	xx_11AD6
		pop	cx
		pop	cx
		mov	bx, [bp+@@var_2]
		cmp	word ptr ss:[bx+2], 0EEFh
		jz	short xx_11E1C
		jmp	xx_120DE

xx_11E1C:
		cmp	word ptr ss:[bx], 0FACEh
		jz	short xx_11E26
		jmp	xx_120DE

xx_11E26:
		les	bx, [bp+@@var_10]
		mov	dx, es:[bx+2]
		mov	ax, es:[bx]
		mov	word ptr [bp+@@var_20+2],	dx
		mov	word ptr [bp+@@var_20], ax
		mov	ax, word ptr [bp+@@var_20]
		or	ax, word ptr [bp+@@var_20+2]
		jnz	short xx_11E41
		jmp	xx_120DE

xx_11E41:
		jmp	short xx_11E7F

xx_11E43:
		mov	ax, 1
		push	ax
		les	bx, [bp+@@var_C]
		push	word ptr es:[bx+0Ch]
		les	bx, [bp+@@var_20]
		push	word ptr es:[bx+2]
		push	word ptr es:[bx]
		les	bx, [bp+@@var_C]
		push	word ptr es:[bx+0Ah]
		push	word ptr es:[bx+8]
		les	bx, [bp+@@var_C]
		push	word ptr es:[bx+6]
		push	word ptr es:[bx+4]
		call	xx_1045A
		add	sp, 10h
		or	ax, ax
		jz	short xx_11E7B
		jmp	xx_120DE

xx_11E7B:
		add	word ptr [bp+@@var_20], 4

xx_11E7F:
		les	bx, [bp+@@var_20]
		mov	ax, es:[bx]
		or	ax, es:[bx+2]
		jnz	short xx_11E43
		mov	ax, ss:14h
		mov	[bp-22h], ax
		mov	bx, [bp+@@var_4]
		mov	ax, ss:[bx]
		mov	ss:14h,	ax
		nopcall	___call_unexpected
		mov	ax, [bp-22h]
		mov	ss:14h,	ax
		jmp	xx_120DE

xx_11EAB:
		mov	bx, [bp+@@var_4]
		mov	ax, ss:[bx+@@arg_6]
		jmp	xx_120D2

xx_11EB5:
		mov	ax, [bp+@@var_12]
		mov	word ptr [bp+@@var_20], ax
		les	bx, [bp+@@var_10]
		add	bx, word ptr [bp+@@var_20]
		mov	ax, es:[bx]
		mov	[bp+@@var_14], ax
		add	word ptr [bp+@@var_20], 2
		les	bx, [bp+@@var_10]
		add	bx, word ptr [bp+@@var_20]
		mov	ax, es:[bx]
		mov	word ptr [bp+@@var_20+2],	ax
		add	word ptr [bp+@@var_20], 2
		mov	bx, word ptr [bp+@@var_20+2]
		cmp	bx, 5
		jbe	short xx_11EE6
		jmp	xx_120CF

xx_11EE6:
		add	bx, bx
		jmp	cs:xx_120E7[bx]

xx_11EED:
		mov	bx, [bp+@@var_2]
		cmp	word ptr ss:[bx+2], 0EEFh
		jz	short xx_11EFB
		jmp	xx_120CF

xx_11EFB:
		cmp	word ptr ss:[bx], 0FACEh
		jz	short xx_11F05
		jmp	xx_120CF

xx_11F05:
		les	bx, [bp+@@var_10]
		add	bx, word ptr [bp+@@var_20]
		mov	dx, es:[bx+2]
		mov	ax, es:[bx]
		mov	word ptr [bp+@@var_26], dx
		mov	[bp+@@var_28], ax
		add	word ptr [bp+@@var_20], 4
		push	word ptr [bp+@@var_C+2]
		push	word ptr [bp+@@var_C]
		push	word ptr [bp+@@var_26]
		push	[bp+@@var_28]
		call	xx_11CEB
		add	sp, 8
		mov	[bp-22h], dx
		mov	word ptr [bp+@@var_26+2],	ax
		mov	ax, word ptr [bp+@@var_26+2]
		or	ax, [bp-22h]
		jnz	short xx_11F3F
		jmp	xx_120CF

xx_11F3F:
		les	bx, [bp+@@var_C]
		mov	ax, [bp+@@var_4]
		mov	es:[bx+24h], ax
		les	bx, [bp+@@var_C]
		mov	dx, [bp-22h]
		mov	ax, word ptr [bp+@@var_26+2]
		mov	es:[bx+28h], dx
		mov	es:[bx+26h], ax
		les	bx, [bp+@@var_C]
		mov	ax, word ptr [bp+@@var_20]
		mov	es:[bx+2Ah], ax
		mov	ax, [bp+@@var_12]
		mov	[bp+@@var_30], ax
		mov	ax, word ptr [bp+@@var_20]
		mov	[bp+@@var_2E], ax
		les	bx, [bp+@@var_26+2]

xx_11F73:
		mov	dx, es:[bx+2]	; int
		mov	ax, es:[bx]
		mov	[bp+@@var_2A], dx
		mov	[bp+@@var_2C], ax
		push	[bp+@@var_2]
		push	[bp+@@var_4]
		call	__Global_unwind
		pop	cx
		pop	cx
		push	[bp+@@var_30]
		push	[bp+@@var_4]
		call	xx_11AD6
		pop	cx
		pop	cx
		mov	bx, [bp+@@var_4]
		mov	ax, [bp+@@var_2E]	; int
		mov	ss:[bx+@@arg_6], ax
		cmp	word ptr [bp+@@var_20+2],	3
		jnz	short xx_11FC5
		push	[bp+@@var_16]
		push	word ptr [bp+@@var_26] ; __int32
		push	[bp+@@var_28]	; int
		push	word ptr [bp+@@var_C+2]
		push	word ptr [bp+@@var_C] ; __int32
		push	[bp+@@var_4]
		push	word ptr [bp-22h] ; __int32
		push	word ptr [bp+@@var_26+2] ; int
		call	xx_11830
		add	sp, 10h

xx_11FC5:
		mov	dx, [bp+@@var_2A]
		mov	ax, [bp+@@var_2C]
		mov	si, [bp+@@var_1C]
		mov	ds, [bp+@@var_1A]
		mov	bx, [bp+@@var_18]
		mov	cx, [bp+@@var_16]
		call	___JumpToCatch__
		jmp	xx_120CF

xx_11FDE:
		mov	bx, [bp+@@var_2]
		cmp	word ptr ss:[bx+2], 0EEFh
		jnz	short xx_11FF3
		cmp	word ptr ss:[bx], 0FACEh
		jnz	short xx_11FF3
		jmp	xx_120CF

xx_11FF3:
		mov	ax, [bp+@@var_2]
		mov	[bp+@@var_36], ax
		mov	dx, [bp+@@var_6]
		mov	ax, [bp+@@var_8]
		mov	[bp+@@var_32], dx
		mov	[bp+@@var_34], ax
		mov	bx, [bp+@@var_2]
		mov	dx, ss:[bx+2]
		mov	ax, ss:[bx]
		mov	bx, [bp+@@var_4]
		mov	ss:[bx+@@arg_10],	dx
		mov	ss:[bx+@@arg_E], ax
		lea	ax, [bp+@@var_36]
		mov	bx, [bp+@@var_4]
		mov	ss:[bx+@@arg_12],	ax
		les	bx, [bp+@@var_10]
		add	bx, word ptr [bp+@@var_20]
		mov	dx, es:[bx+2]
		mov	ax, es:[bx]
		mov	word ptr xx_131A4+2, dx
		mov	word ptr xx_131A4, ax
		mov	ax, ds
		mov	es, ax
		assume es:DGROUP
		push	si
		mov	si, [bp+@@var_1C]
		push	ds
		mov	ds, [bp+@@var_1A]
		push	bp
		mov	bp, [bp+@@var_16]
		call	es:xx_131A4
		pop	bp
		pop	ds
		pop	si
		mov	[bp+@@var_38], ax
		jmp	short xx_1208A

xx_12055:
		mov	bx, [bp+@@var_2]
		cmp	word ptr ss:[bx+2], 0EEFh
		jnz	short xx_12069
		cmp	word ptr ss:[bx], 0FACEh
		jnz	short xx_12069
		jmp	short xx_120CF

xx_12069:
		mov	bx, [bp+@@var_2]
		mov	dx, ss:[bx+2]
		mov	ax, ss:[bx]
		mov	bx, [bp+@@var_4]
		mov	ss:[bx+@@arg_10],	dx
		mov	ss:[bx+@@arg_E], ax
		les	bx, [bp+@@var_10]
		assume es:nothing
		add	bx, word ptr [bp+@@var_20]
		mov	ax, es:[bx]
		mov	[bp+@@var_38], ax

xx_1208A:
		cmp	[bp+@@var_38], 0
		jge	short xx_120A8
		mov	bx, [bp+@@var_2]
		test	byte ptr ss:[bx+4], 1
		jz	short xx_120A4
		mov	bx, [bp+@@var_4]
		mov	ax, [bp+@@var_14]
		mov	ss:[bx+@@arg_6], ax

xx_120A4:
		xor	ax, ax
		jmp	short xx_120E1

xx_120A8:
		cmp	[bp+@@var_38], 0
		jnz	short xx_120B0
		jmp	short xx_120CF

xx_120B0:
		mov	bx, [bp+@@var_4]
		mov	ss:[bx+@@arg_12],	0
		add	word ptr [bp+@@var_20], 4
		mov	ax, [bp+@@var_14]
		mov	[bp+@@var_2E], ax
		mov	[bp+@@var_30], ax
		les	bx, [bp+@@var_10]
		add	bx, word ptr [bp+@@var_20]
		jmp	xx_11F73

xx_120CF:
		mov	ax, [bp+@@var_14]

xx_120D2:
		mov	[bp+@@var_12], ax
		cmp	[bp+@@var_12], 0
		jz	short xx_120DE
		jmp	xx_11EB5

xx_120DE:
		mov	ax, 1

xx_120E1:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
__ExceptionHandler endp

xx_120E7	dw offset xx_120CF
		dw offset xx_11FDE
		dw offset xx_12055
		dw offset xx_11EED
		dw offset xx_120CF
		dw offset xx_120CF
xx_120F3	db 4 dup(0)
		dd xx_12186
xx_120FB	db 14h dup(0)
		dd xx_12196
		db 10h dup(0)
xx_12123	db 4 dup(0), 0E2h, 0FFh, 2 dup(0), 3, 0
		dd xx_120FB+10h
		db 2 dup(0), 4,	0, 6, 0, 3, 0
		dd xx_120F3
		db 6, 0, 4, 0


xx_12141	proc far

@@var_1E		= word ptr -1Eh
@@var_12		= word ptr -12h
@@arg_0		= word ptr  6
@@arg_2		= word ptr  8
@@arg_4		= dword	ptr  0Ah
@@arg_8		= word ptr  0Eh

		push	bp
		mov	bp, sp
		sub	sp, 1Eh
		push	si
		push	di
		mov	ax, seg	xx_12123
		mov	bx, offset xx_12123
		nopcall	___InitExceptBlocks
		mov	[bp+@@var_12], 6
		mov	[bp+@@var_12], 12h
		push	[bp+@@arg_8]
		les	bx, [bp+@@arg_4]
		push	word ptr es:[bx+22h]
		les	bx, [bp+@@arg_4]
		push	word ptr es:[bx+20h]
		push	word ptr es:[bx+1Eh]
		push	[bp+@@arg_2]
		push	[bp+@@arg_0]
		call	xx_108AD
		add	sp, 0Ch
		mov	[bp+@@var_12], 6
		jmp	short xx_1218F

xx_12186:
		nopcall	___call_terminate
		call	@_CatchCleanup$qv ; _CatchCleanup(void)

xx_1218F:
		mov	[bp+@@var_12], 0
		jmp	short xx_1219F

xx_12196:
		nopcall	___call_terminate
		call	@_CatchCleanup$qv ; _CatchCleanup(void)

xx_1219F:
		push	[bp+@@var_1E]
		nopcall	___ExitExceptBlocks
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
xx_12141	endp



xx_121AD	proc far

@@var_8		= dword	ptr -8
@@var_4		= dword	ptr -4
@@arg_0		= word ptr  6
@@arg_2		= word ptr  8
@@arg_4		= dword	ptr  0Ah
@@arg_8		= word ptr  0Eh
@@arg_C		= word ptr  12h
@@arg_E		= word ptr  14h
@@arg_10		= word ptr  16h

		push	bp
		mov	bp, sp
		sub	sp, 8
		push	si
		push	di
		mov	cx, [bp+@@arg_C]
		jmp	short xx_1221C

xx_121BA:
		les	bx, [bp+@@arg_4]
		mov	dx, [bp+@@arg_2]
		mov	ax, [bp+@@arg_0]
		add	ax, es:[bx+4]
		mov	word ptr [bp+@@var_4+2], dx
		mov	word ptr [bp+@@var_4], ax
		cmp	[bp+@@arg_E], 0
		jz	short xx_121E2
		les	bx, [bp+@@var_4]
		mov	ax, es:[bx]
		mov	dx, word ptr [bp+@@var_4+2]
		mov	word ptr [bp+@@var_4+2], dx
		mov	word ptr [bp+@@var_4], ax

xx_121E2:
		les	bx, [bp+@@arg_4]
		mov	dx, es:[bx+2]
		mov	ax, es:[bx]
		mov	word ptr [bp+@@var_8+2], dx
		mov	word ptr [bp+@@var_8], ax
		les	bx, [bp+@@var_8]
		test	byte ptr es:[bx+8], 2
		jz	short xx_1221C
		push	[bp+@@arg_10]
		xor	ax, ax
		push	ax
		xor	ax, ax
		push	ax
		push	cx
		push	word ptr [bp+@@var_8+2]
		push	word ptr [bp+@@var_8]
		push	word ptr [bp+@@var_4+2]
		push	word ptr [bp+@@var_4]
		nopcall	xx_1222E
		add	sp, 10h
		xor	cx, cx

xx_1221C:
		sub	word ptr [bp+@@arg_4], 8
		mov	ax, word ptr [bp+@@arg_4]
		cmp	ax, [bp+@@arg_8]
		jnb	short xx_121BA
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
xx_121AD	endp



xx_1222E	proc far

@@var_2A		= word ptr -2Ah
@@var_28		= word ptr -28h
@@var_26		= word ptr -26h
@@var_24		= word ptr -24h
@@var_22		= dword	ptr -22h
@@var_1E		= word ptr -1Eh
@@var_1C		= word ptr -1Ch
@@var_1A		= word ptr -1Ah
@@var_18		= dword	ptr -18h
@@var_14		= word ptr -14h
@@var_12		= word ptr -12h
@@var_10		= dword	ptr -10h
@@var_C		= word ptr -0Ch
@@var_A		= word ptr -0Ah
@@var_8		= dword	ptr -8
@@var_4		= word ptr -4
@@var_2		= word ptr -2
@@arg_0		= word ptr  6
@@arg_2		= word ptr  8
@@arg_4		= dword	ptr  0Ah
@@arg_8		= word ptr  0Eh
@@arg_A		= word ptr  10h
@@arg_C		= word ptr  12h
@@arg_E		= word ptr  14h

		push	bp
		mov	bp, sp
		sub	sp, 2Ah
		push	si
		push	di
		cmp	[bp+@@arg_C], 0
		jz	short xx_12245
		les	bx, [bp+@@arg_4]
		mov	ax, es:[bx+1Ah]
		jmp	short xx_1224C

xx_12245:
		les	bx, [bp+@@arg_4]
		mov	ax, es:[bx+1Ch]

xx_1224C:
		mov	[bp+@@var_1A], 0
		mov	[bp+@@var_1C], ax
		mov	ax, [bp+@@arg_8]
		or	ax, [bp+@@arg_A]
		jz	short xx_1226E
		mov	dx, [bp+@@arg_A]
		mov	ax, [bp+@@arg_8]
		cmp	dx, [bp+@@var_1A]
		jb	short xx_12287
		jnz	short xx_1226E
		cmp	ax, [bp+@@var_1C]
		jb	short xx_12287

xx_1226E:
		push	[bp+@@arg_C]
		push	word ptr [bp+@@arg_4+2]
		push	word ptr [bp+@@arg_4]
		push	[bp+@@arg_2]
		push	[bp+@@arg_0]
		call	xx_12141
		add	sp, 0Ah
		jmp	xx_124F3

xx_12287:
		mov	dx, [bp+@@arg_A]
		mov	ax, [bp+@@arg_8]
		mov	[bp+@@var_1A], dx
		mov	[bp+@@var_1C], ax
		les	bx, [bp+@@arg_4]
		mov	dx, word ptr [bp+@@arg_4+2]
		mov	ax, word ptr [bp+@@arg_4]
		add	ax, es:[bx+0Ch]
		mov	word ptr [bp+@@var_10+2],	dx
		mov	word ptr [bp+@@var_10], ax
		mov	[bp+@@var_A], dx
		mov	[bp+@@var_C], ax
		cmp	[bp+@@arg_C], 0
		jz	short xx_12320

xx_122B2:
		les	bx, [bp+@@var_10]
		mov	dx, es:[bx+2]
		mov	ax, es:[bx]
		mov	[bp+@@var_1E], dx
		mov	word ptr [bp+@@var_22+2],	ax
		mov	ax, word ptr [bp+@@var_22+2]
		or	ax, [bp+@@var_1E]
		jz	short xx_12320
		les	bx, [bp+@@var_22+2]
		test	byte ptr es:[bx+8], 2
		jz	short xx_1231A
		les	bx, [bp+@@var_22+2]
		mov	bx, es:[bx+1Ch]
		xor	ax, ax
		cmp	ax, [bp+@@var_1A]
		jb	short xx_12313
		jnz	short xx_122E9
		cmp	bx, [bp+@@var_1C]
		jb	short xx_12313

xx_122E9:
		push	[bp+@@arg_E]
		mov	ax, 1
		push	ax
		push	[bp+@@var_1C]
		push	[bp+@@var_A]
		push	[bp+@@var_C]
		mov	ax, word ptr [bp+@@var_10]
		add	ax, 8
		push	word ptr [bp+@@var_10+2]
		push	ax

xx_12303:
		push	[bp+@@arg_2]
		push	[bp+@@arg_0]
		call	xx_121AD
		add	sp, 12h
		jmp	xx_124F3

xx_12313:
		sub	[bp+@@var_1C], bx
		sbb	[bp+@@var_1A], 0

xx_1231A:
		add	word ptr [bp+@@var_10], 8
		jmp	short xx_122B2

xx_12320:
		les	bx, [bp+@@arg_4]
		mov	dx, word ptr [bp+@@arg_4+2]
		mov	ax, word ptr [bp+@@arg_4]
		add	ax, es:[bx+0Ah]
		mov	word ptr [bp+@@var_8+2], dx
		mov	word ptr [bp+@@var_8], ax
		mov	[bp+@@var_2], dx
		mov	[bp+@@var_4], ax

xx_12339:
		les	bx, [bp+@@var_8]
		mov	dx, es:[bx+2]
		mov	ax, es:[bx]
		mov	[bp+@@var_1E], dx
		mov	word ptr [bp+@@var_22+2],	ax
		mov	ax, word ptr [bp+@@var_22+2]
		or	ax, [bp+@@var_1E]
		jz	short xx_123AF
		les	bx, [bp+@@var_22+2]
		test	byte ptr es:[bx+8], 2
		jz	short xx_123A9
		les	bx, [bp+@@var_22+2]
		mov	bx, es:[bx+1Ch]
		xor	ax, ax
		cmp	ax, [bp+@@var_1A]
		jb	short xx_123A2
		jnz	short xx_12370
		cmp	bx, [bp+@@var_1C]
		jb	short xx_123A2

xx_12370:
		push	[bp+@@arg_E]
		xor	ax, ax
		push	ax
		push	[bp+@@var_1C]
		push	[bp+@@var_2]
		push	[bp+@@var_4]
		mov	ax, word ptr [bp+@@var_8]
		add	ax, 8
		push	word ptr [bp+@@var_8+2]
		push	ax
		push	[bp+@@arg_2]
		push	[bp+@@arg_0]
		call	xx_121AD
		add	sp, 12h
		cmp	[bp+@@arg_C], 0
		jnz	short xx_1239F
		jmp	xx_124F3

xx_1239F:
		jmp	xx_124D3

xx_123A2:
		sub	[bp+@@var_1C], bx
		sbb	[bp+@@var_1A], 0

xx_123A9:
		add	word ptr [bp+@@var_8], 8
		jmp	short xx_12339

xx_123AF:
		les	bx, [bp+@@arg_4]
		mov	dx, word ptr [bp+@@arg_4+2]
		mov	ax, word ptr [bp+@@arg_4]
		add	ax, es:[bx+24h]
		mov	word ptr [bp+@@var_18+2],	dx
		mov	word ptr [bp+@@var_18], ax
		mov	[bp+@@var_12], dx
		mov	[bp+@@var_14], ax

xx_123C8:
		les	bx, [bp+@@var_18]
		mov	dx, es:[bx+2]
		mov	ax, es:[bx]
		mov	word ptr [bp+@@var_22+2],	dx
		mov	word ptr [bp+@@var_22], ax
		mov	[bp+@@var_1E], 1
		les	bx, [bp+@@var_22]
		test	byte ptr es:[bx+3], 4
		jz	short xx_12402
		les	bx, [bp+@@var_22]
		mov	ax, es:[bx+0Ah]
		mov	[bp+@@var_1E], ax
		les	bx, [bp+@@var_22]
		mov	dx, es:[bx+8]
		mov	ax, es:[bx+6]
		mov	word ptr [bp+@@var_22+2],	dx
		mov	word ptr [bp+@@var_22], ax

xx_12402:
		les	bx, [bp+@@var_22]
		mov	ax, es:[bx+1Ah]
		imul	[bp+@@var_1E]
		mov	bx, ax
		xor	ax, ax
		cmp	ax, [bp+@@var_1A]
		ja	short xx_12426
		jb	short xx_1241C
		cmp	bx, [bp+@@var_1C]
		jnb	short xx_12426

xx_1241C:
		sub	[bp+@@var_1C], bx
		sbb	[bp+@@var_1A], 0
		jmp	xx_124EC

xx_12426:
		les	bx, [bp+@@var_18]
		mov	dx, [bp+@@arg_2]
		mov	ax, [bp+@@arg_0]
		add	ax, es:[bx+4]
		mov	[bp+@@var_24], dx
		mov	[bp+@@var_26], ax
		les	bx, [bp+@@var_18]
		mov	dx, es:[bx+2]
		mov	ax, es:[bx]
		mov	[bp+@@var_28], dx
		mov	[bp+@@var_2A], ax
		cmp	[bp+@@var_1E], 1
		jbe	short xx_12472
		push	[bp+@@arg_E]
		push	[bp+@@var_1A]
		push	[bp+@@var_1C]
		les	bx, [bp+@@var_18]
		push	word ptr es:[bx+2]
		push	word ptr es:[bx]
		push	[bp+@@var_24]
		push	[bp+@@var_26]
		nopcall	xx_124F9
		add	sp, 0Eh
		jmp	short xx_12492

xx_12472:
		push	[bp+@@arg_E]
		mov	ax, 1
		push	ax
		push	[bp+@@var_1A]
		push	[bp+@@var_1C]
		push	[bp+@@var_28]
		push	[bp+@@var_2A]
		push	[bp+@@var_24]
		push	[bp+@@var_26]
		call	xx_1222E
		add	sp, 10h

xx_12492:
		mov	[bp+@@var_1A], 0
		mov	[bp+@@var_1C], 0
		sub	word ptr [bp+@@var_18], 6
		mov	ax, word ptr [bp+@@var_18]
		cmp	ax, [bp+@@var_14]
		jb	short xx_124AB
		jmp	xx_12426

xx_124AB:
		push	[bp+@@arg_E]
		xor	ax, ax
		push	ax
		xor	ax, ax
		push	ax
		push	[bp+@@var_2]
		push	[bp+@@var_4]
		push	word ptr [bp+@@var_8+2]
		push	word ptr [bp+@@var_8]
		push	[bp+@@arg_2]
		push	[bp+@@arg_0]
		call	xx_121AD
		add	sp, 12h
		cmp	[bp+@@arg_C], 0
		jz	short xx_124F3

xx_124D3:
		push	[bp+@@arg_E]
		mov	ax, 1
		push	ax
		xor	ax, ax
		push	ax
		push	[bp+@@var_A]
		push	[bp+@@var_C]
		push	word ptr [bp+@@var_10+2]
		push	word ptr [bp+@@var_10]
		jmp	xx_12303

xx_124EC:
		add	word ptr [bp+@@var_18], 6
		jmp	xx_123C8

xx_124F3:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
xx_1222E	endp



xx_124F9	proc far

@@var_E		= word ptr -0Eh
@@var_C		= word ptr -0Ch
@@var_A		= word ptr -0Ah
@@var_8		= word ptr -8
@@var_6		= word ptr -6
@@var_4		= dword	ptr -4
@@arg_0		= word ptr  6
@@arg_2		= word ptr  8
@@arg_4		= word ptr  0Ah
@@arg_6		= word ptr  0Ch
@@arg_8		= word ptr  0Eh
@@arg_A		= word ptr  10h
@@arg_C		= word ptr  12h

		push	bp
		mov	bp, sp
		sub	sp, 0Eh
		push	si
		push	di
		mov	dx, [bp+@@arg_6]
		mov	ax, [bp+@@arg_4]
		mov	word ptr [bp+@@var_4+2], dx
		mov	word ptr [bp+@@var_4], ax
		les	bx, [bp+@@var_4]
		mov	ax, es:[bx+0Ah]
		mov	[bp+@@var_6], ax
		les	bx, [bp+@@var_4]
		mov	dx, es:[bx+8]
		mov	ax, es:[bx+6]
		mov	word ptr [bp+@@var_4+2], dx
		mov	word ptr [bp+@@var_4], ax
		les	bx, [bp+@@var_4]
		mov	ax, es:[bx+1Ah]
		mov	[bp+@@var_8], 0
		mov	[bp+@@var_A], ax
		mov	ax, [bp+@@arg_8]
		or	ax, [bp+@@arg_A]
		jnz	short xx_12553
		mov	bx, [bp+@@var_6]
		xor	cx, cx
		mov	dx, [bp+@@var_8]
		mov	ax, [bp+@@var_A]
		call	N_LXMUL@
		mov	[bp+@@arg_A], dx
		mov	[bp+@@arg_8], ax

xx_12553:
		push	[bp+@@var_8]
		push	[bp+@@var_A]
		push	[bp+@@arg_A]
		push	[bp+@@arg_8]
		call	N_LUDIV@
		mov	[bp+@@var_C], dx
		mov	[bp+@@var_E], ax
		mov	cx, [bp+@@var_C]
		mov	bx, [bp+@@var_E]
		mov	dx, [bp+@@var_8]
		mov	ax, [bp+@@var_A]
		call	N_LXMUL@
		sub	[bp+@@arg_8], ax
		sbb	[bp+@@arg_A], dx
		les	bx, [bp+@@var_4]
		mov	bx, es:[bx]
		xor	cx, cx
		mov	dx, [bp+@@var_C]
		mov	ax, [bp+@@var_E]
		call	N_LXMUL@
		mov	dx, [bp+@@arg_2]
		add	ax, [bp+@@arg_0]
		mov	[bp+@@arg_2], dx
		mov	[bp+@@arg_0], ax
		mov	ax, [bp+@@arg_8]
		or	ax, [bp+@@arg_A]
		jz	short xx_125E3
		push	[bp+@@arg_C]
		mov	ax, 1
		push	ax
		push	[bp+@@arg_A]
		push	[bp+@@arg_8]
		jmp	short xx_125D0

xx_125B1:
		les	bx, [bp+@@var_4]
		mov	dx, [bp+@@arg_2]
		mov	ax, [bp+@@arg_0]
		sub	ax, es:[bx]
		mov	[bp+@@arg_2], dx
		mov	[bp+@@arg_0], ax
		push	[bp+@@arg_C]
		mov	ax, 1
		push	ax
		push	[bp+@@var_8]
		push	[bp+@@var_A]

xx_125D0:
		push	word ptr [bp+@@var_4+2]
		push	word ptr [bp+@@var_4]
		push	[bp+@@arg_2]
		push	[bp+@@arg_0]
		call	xx_1222E
		add	sp, 10h

xx_125E3:
		mov	ax, [bp+@@var_C]
		mov	dx, [bp+@@var_E]
		sub	[bp+@@var_E], 1
		sbb	[bp+@@var_C], 0
		or	dx, ax
		jnz	short xx_125B1
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
xx_124F9	endp



xx_125FB	proc far

@@var_8		= dword	ptr -8
@@var_4		= dword	ptr -4
@@arg_0		= word ptr  6
@@arg_2		= word ptr  8
@@arg_4		= word ptr  0Ah

		push	bp
		mov	bp, sp
		sub	sp, 8
		push	si
		push	di
		mov	cx, [bp+@@arg_4]
		mov	bx, cx
		mov	dx, ss:[bx+2]
		mov	ax, ss:[bx]
		mov	word ptr [bp+@@var_4+2], dx
		mov	word ptr [bp+@@var_4], ax
		les	bx, [bp+@@var_4]
		mov	ax, es:[bx+8]
		and	ax, 50h
		cmp	ax, 50h	; 'P'
		jnz	short xx_126A0
		les	bx, [bp+@@var_4]
		cmp	word ptr es:[bx+6], 0FFFFh
		jz	short xx_126A0
		les	bx, [bp+@@var_4]
		mov	dx, [bp+@@arg_2]
		mov	ax, [bp+@@arg_0]
		add	ax, es:[bx+6]
		mov	word ptr [bp+@@var_8+2], dx
		mov	word ptr [bp+@@var_8], ax
		les	bx, [bp+@@var_4]
		test	byte ptr es:[bx+9], 10h
		jz	short xx_1265A
		les	bx, [bp+@@var_8]
		mov	dx, es:[bx+2]
		mov	ax, es:[bx]
		mov	word ptr [bp+@@var_8+2], dx
		jmp	short xx_12663

xx_1265A:
		les	bx, [bp+@@var_8]
		mov	ax, es:[bx]
		mov	word ptr [bp+@@var_8+2], ds

xx_12663:
		mov	word ptr [bp+@@var_8], ax
		les	bx, [bp+@@var_8]
		mov	dx, [bp+@@arg_2]
		mov	ax, [bp+@@arg_0]
		sub	ax, es:[bx-4]
		mov	[bp+@@arg_2], dx
		mov	[bp+@@arg_0], ax
		les	bx, [bp+@@var_8]
		mov	dx, word ptr [bp+@@var_8+2]
		mov	ax, word ptr [bp+@@var_8]
		sub	ax, es:[bx-2]
		mov	word ptr [bp+@@var_8+2], dx
		mov	word ptr [bp+@@var_8], ax
		les	bx, [bp+@@var_8]
		mov	dx, es:[bx-6]
		mov	ax, es:[bx-8]
		mov	bx, cx
		mov	ss:[bx+2], dx
		mov	ss:[bx], ax

xx_126A0:
		mov	dx, [bp+@@arg_2]
		mov	ax, [bp+@@arg_0]
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
xx_125FB	endp



xx_126AC	proc near

@@var_20		= word ptr -20h
@@var_1C		= dword	ptr -1Ch
@@var_18		= word ptr -18h
@@var_16		= dword	ptr -16h
@@var_12		= dword	ptr -12h
@@var_E		= word ptr -0Eh
@@var_C		= dword	ptr -0Ch
@@var_8		= word ptr -8
@@var_6		= word ptr -6
@@var_4		= word ptr -4
@@var_2		= word ptr -2
@@arg_0		= dword	ptr  4
@@arg_4		= word ptr  8
@@arg_6		= word ptr  0Ah
@@arg_8		= word ptr  0Ch
@@arg_A		= word ptr  0Eh
@@arg_16		= word ptr  1Ah
@@arg_18		= word ptr  1Ch

		push	bp
		mov	bp, sp
		sub	sp, 20h
		push	si
		push	di
		mov	[bp+@@var_E], 0
		cmp	word ptr [bp+@@arg_0], 0FFFFh
		jnz	short xx_126C2
		jmp	xx_12AAF

xx_126C2:
		mov	bx, [bp+@@arg_8]
		mov	dx, ss:[bx+@@arg_18]
		mov	ax, ss:[bx+@@arg_16]
		mov	[bp+@@var_2], dx
		mov	[bp+@@var_4], ax
		nopcall	@__RefDestructorCount$qv ; __RefDestructorCount(void)
		mov	bx, ax
		mov	es, dx
		mov	dx, es:[bx+2]
		mov	ax, es:[bx]
		sub	ax, [bp+@@var_4]
		sbb	dx, [bp+@@var_2]
		mov	[bp+@@var_6], dx
		mov	[bp+@@var_8], ax
		mov	dx, [bp+@@arg_6]
		mov	ax, [bp+@@arg_4]
		sub	[bp+@@var_8], ax
		sbb	[bp+@@var_6], dx
		les	bx, [bp+@@arg_0]
		test	byte ptr es:[bx+4], 20h
		jz	short xx_1271B
		les	bx, [bp+@@arg_0]
		les	bx, es:[bx]
		les	bx, es:[bx+6]
		mov	ax, es:[bx+1Ah]
		mov	[bp+@@var_6], 0
		mov	[bp+@@var_8], ax

xx_1271B:
		les	bx, [bp+@@arg_0]
		test	byte ptr es:[bx+5], 1
		jz	short xx_12732
		les	bx, [bp+@@arg_0]
		les	bx, es:[bx]
		mov	ax, es:[bx+1Ch]
		jmp	xx_12AB1

xx_12732:
		cmp	[bp+@@var_6], 0
		jg	short xx_12764
		jnz	short xx_12740
		cmp	[bp+@@var_8], 0
		ja	short xx_12764

xx_12740:
		les	bx, [bp+@@arg_0]
		mov	ax, es:[bx+4]
		and	ax, 3
		cmp	ax, 3
		jz	short xx_12752
		jmp	xx_12AAF

xx_12752:
		mov	dx, word ptr [bp+@@arg_0+2]
		mov	ax, word ptr [bp+@@arg_0]
		mov	word ptr [bp+@@var_C+2], dx
		mov	word ptr [bp+@@var_C], ax
		inc	[bp+@@var_E]
		jmp	xx_128C9

xx_12764:
		mov	dx, word ptr [bp+@@arg_0+2]
		mov	ax, word ptr [bp+@@arg_0]
		mov	word ptr [bp+@@var_C+2], dx
		mov	word ptr [bp+@@var_C], ax

xx_12770:
		les	bx, [bp+@@var_C]
		mov	ax, es:[bx]
		or	ax, es:[bx+2]
		jnz	short xx_12783
		sub	word ptr [bp+@@var_C], 0Ah
		jmp	xx_128C9

xx_12783:
		les	bx, [bp+@@var_C]
		mov	dx, es:[bx+2]
		mov	ax, es:[bx]
		mov	word ptr [bp+@@var_16+2],	dx
		mov	word ptr [bp+@@var_16], ax
		mov	word ptr [bp+@@var_12+2],	dx
		mov	word ptr [bp+@@var_12], ax
		mov	[bp+@@var_18], 1
		les	bx, [bp+@@var_12]
		test	byte ptr es:[bx+2], 10h
		jnz	short xx_127AB
		jmp	xx_12875

xx_127AB:
		les	bx, [bp+@@var_12]
		mov	dx, es:[bx+8]
		mov	ax, es:[bx+6]
		mov	word ptr [bp+@@var_16+2],	dx
		mov	word ptr [bp+@@var_16], ax
		mov	word ptr [bp+@@var_12+2],	dx
		mov	word ptr [bp+@@var_12], ax
		les	bx, [bp+@@var_12]
		test	byte ptr es:[bx+2], 2
		jnz	short xx_127CF
		jmp	xx_12875

xx_127CF:
		les	bx, [bp+@@var_12]
		test	byte ptr es:[bx+8], 20h
		jnz	short xx_127DC
		jmp	xx_12875

xx_127DC:
		les	bx, [bp+@@var_C]
		test	byte ptr es:[bx+4], 8
		jnz	short xx_127E9
		jmp	xx_12875

xx_127E9:
		les	bx, [bp+@@var_C]
		test	byte ptr es:[bx+4], 4
		jz	short xx_12802
		les	bx, [bp+@@var_C]
		mov	ax, es:[bx+6]
		add	ax, [bp+@@arg_A]
		mov	word ptr [bp+@@var_1C+2],	ss
		jmp	short xx_12810

xx_12802:
		les	bx, [bp+@@var_C]
		mov	dx, es:[bx+8]
		mov	ax, es:[bx+6]
		mov	word ptr [bp+@@var_1C+2],	dx

xx_12810:
		mov	word ptr [bp+@@var_1C], ax
		mov	dx, word ptr [bp+@@var_1C+2]
		mov	ax, word ptr [bp+@@var_1C]
		mov	[bp+@@var_20+2], dx
		mov	[bp+@@var_20], ax
		les	bx, [bp+@@var_C]
		test	byte ptr es:[bx+4], 80h
		jz	short xx_12838
		les	bx, dword ptr [bp+@@var_20]
		mov	dx, es:[bx+2]
		mov	ax, es:[bx]
		mov	word ptr [bp+@@var_1C+2],	dx
		jmp	short xx_12841

xx_12838:
		les	bx, dword ptr [bp+@@var_20]
		mov	ax, es:[bx]
		mov	word ptr [bp+@@var_1C+2],	ds

xx_12841:
		mov	word ptr [bp+@@var_1C], ax
		les	bx, [bp+@@var_C]
		test	byte ptr es:[bx+4], 40h
		jz	short xx_12852
		add	word ptr [bp+@@var_1C], 4

xx_12852:
		lea	ax, [bp+@@var_12]
		push	ax
		push	word ptr [bp+@@var_1C+2]
		push	word ptr [bp+@@var_1C]
		call	xx_125FB
		add	sp, 6
		mov	word ptr [bp+@@var_1C+2],	dx
		mov	word ptr [bp+@@var_1C], ax
		mov	dx, word ptr [bp+@@var_12+2]
		mov	ax, word ptr [bp+@@var_12]
		mov	word ptr [bp+@@var_16+2],	dx
		mov	word ptr [bp+@@var_16], ax

xx_12875:
		les	bx, [bp+@@var_12]
		test	byte ptr es:[bx+3], 4
		jz	short xx_1289A
		les	bx, [bp+@@var_16]
		mov	ax, es:[bx+0Ah]
		mov	[bp+@@var_18], ax
		les	bx, [bp+@@var_16]
		mov	dx, es:[bx+8]
		mov	ax, es:[bx+6]
		mov	word ptr [bp+@@var_16+2],	dx
		mov	word ptr [bp+@@var_16], ax

xx_1289A:
		les	bx, [bp+@@var_16]
		mov	ax, es:[bx+1Ah]
		imul	[bp+@@var_18]
		mov	[bp+@@var_18], ax
		mov	ax, [bp+@@var_18]
		xor	dx, dx
		cmp	dx, [bp+@@var_6]
		jb	short xx_128B8
		jnz	short xx_128C9
		cmp	ax, [bp+@@var_8]
		jnb	short xx_128C9

xx_128B8:
		mov	ax, [bp+@@var_18]
		sub	[bp+@@var_8], ax
		sbb	[bp+@@var_6], 0
		add	word ptr [bp+@@var_C], 0Ah
		jmp	xx_12770

xx_128C9:
		les	bx, [bp+@@var_C]
		mov	dx, es:[bx+2]
		mov	ax, es:[bx]
		mov	word ptr [bp+@@var_12+2],	dx
		mov	word ptr [bp+@@var_12], ax
		les	bx, [bp+@@var_C]
		mov	ax, es:[bx+4]
		mov	word ptr [bp+@@var_16+2],	ax
		test	byte ptr [bp+@@var_16+2],	4
		jz	short xx_128F8
		les	bx, [bp+@@var_C]
		mov	ax, es:[bx+6]
		add	ax, [bp+@@arg_A]
		mov	word ptr [bp+@@var_16], ss
		jmp	short xx_12906

xx_128F8:
		les	bx, [bp+@@var_C]
		mov	dx, es:[bx+8]
		mov	ax, es:[bx+6]
		mov	word ptr [bp+@@var_16], dx

xx_12906:
		mov	[bp+@@var_18], ax
		test	byte ptr [bp+@@var_16+2],	11h
		jnz	short xx_12912
		jmp	xx_1299C

xx_12912:
		les	bx, [bp+@@var_12]
		mov	dx, es:[bx+8]
		mov	ax, es:[bx+6]
		mov	word ptr [bp+@@var_12+2],	dx
		mov	word ptr [bp+@@var_12], ax
		mov	dx, word ptr [bp+@@var_16]
		mov	ax, [bp+@@var_18]
		mov	word ptr [bp+@@var_1C+2],	dx
		mov	word ptr [bp+@@var_1C], ax
		test	byte ptr [bp+@@var_16+2],	80h
		jz	short xx_12944
		les	bx, [bp+@@var_1C]
		mov	dx, es:[bx+2]
		mov	ax, es:[bx]
		mov	word ptr [bp+@@var_16], dx
		jmp	short xx_1294D

xx_12944:
		les	bx, [bp+@@var_1C]
		mov	ax, es:[bx]
		mov	word ptr [bp+@@var_16], ds

xx_1294D:
		mov	[bp+@@var_18], ax
		mov	dx, word ptr [bp+@@var_16]
		mov	ax, [bp+@@var_18]
		mov	[bp+@@var_20+2], dx
		mov	[bp+@@var_20], ax
		mov	ax, word ptr [bp+@@var_16+2]
		and	ax, 48h
		cmp	ax, 40h	; '@'
		jnz	short xx_1296B
		add	[bp+@@var_18], 4

xx_1296B:
		les	bx, [bp+@@var_12]
		test	byte ptr es:[bx+2], 2
		jz	short xx_1299C
		les	bx, [bp+@@var_12]
		test	byte ptr es:[bx+8], 20h
		jz	short xx_1299C
		test	byte ptr [bp+@@var_16+2],	8
		jz	short xx_1299C
		lea	ax, [bp+@@var_12]
		push	ax
		push	word ptr [bp+@@var_16]
		push	[bp+@@var_18]
		call	xx_125FB
		add	sp, 6
		mov	word ptr [bp+@@var_16], dx
		mov	[bp+@@var_18], ax

xx_1299C:
		cmp	[bp+@@var_E], 0
		jnz	short xx_129EA
		les	bx, [bp+@@var_12]
		test	byte ptr es:[bx+3], 4
		jz	short xx_129CA
		push	[bp+@@arg_A]
		push	[bp+@@var_6]
		push	[bp+@@var_8]
		push	word ptr [bp+@@var_12+2]
		push	word ptr [bp+@@var_12]
		push	word ptr [bp+@@var_16]
		push	[bp+@@var_18]
		call	xx_124F9
		add	sp, 0Eh
		jmp	short xx_129EA

xx_129CA:
		push	[bp+@@arg_A]
		mov	ax, 1
		push	ax
		push	[bp+@@var_6]
		push	[bp+@@var_8]
		push	word ptr [bp+@@var_12+2]
		push	word ptr [bp+@@var_12]
		push	word ptr [bp+@@var_16]
		push	[bp+@@var_18]
		call	xx_1222E
		add	sp, 10h

xx_129EA:
		mov	ax, word ptr [bp+@@var_16+2]
		and	ax, 3
		cmp	ax, 3
		jz	short xx_129F8
		jmp	xx_12A96

xx_129F8:
		mov	ax, word ptr [bp+@@var_16+2]
		and	ax, 48h
		cmp	ax, 48h	; 'H'
		jnz	short xx_12A07
		sub	[bp+@@var_20], 4

xx_12A07:
		les	bx, [bp+@@var_12]
		test	byte ptr es:[bx+3], 4
		jz	short xx_12A56
		les	bx, [bp+@@var_12]
		mov	dx, es:[bx+8]
		mov	ax, es:[bx+6]
		mov	word ptr [bp+@@var_12+2],	dx
		mov	word ptr [bp+@@var_12], ax
		les	bx, [bp+@@var_12]
		mov	ax, es:[bx+16h]
		or	ax, es:[bx+18h]
		jz	short xx_12A43
		les	bx, [bp+@@var_12]
		push	word ptr es:[bx+14h]
		les	bx, [bp+@@var_12]
		push	word ptr es:[bx+18h]
		push	word ptr es:[bx+16h]
		jmp	short xx_12A75

xx_12A43:
		test	byte ptr [bp+@@var_16+2],	80h
		jz	short xx_12A96
		push	[bp+@@var_20+2]
		push	[bp+@@var_20]	; void *
		nopcall	@$bdla$qnv	; operator delete[](void *)
		jmp	short xx_12A94

xx_12A56:
		les	bx, [bp+@@var_12]
		mov	ax, es:[bx+0Eh]
		or	ax, es:[bx+10h]
		jz	short xx_12A83
		les	bx, [bp+@@var_12]
		push	word ptr es:[bx+12h]
		les	bx, [bp+@@var_12]
		push	word ptr es:[bx+10h]
		push	word ptr es:[bx+0Eh]

xx_12A75:
		push	[bp+@@var_20+2]
		push	[bp+@@var_20]
		call	xx_10A65
		add	sp, 0Ah
		jmp	short xx_12A96

xx_12A83:
		test	byte ptr [bp+@@var_16+2],	80h
		jz	short xx_12A96
		push	[bp+@@var_20+2]
		push	[bp+@@var_20]	; void *
		nopcall	@$bdele$qnv	; operator delete(void *)

xx_12A94:
		pop	cx
		pop	cx

xx_12A96:
		mov	[bp+@@var_6], 0
		mov	[bp+@@var_8], 0
		mov	ax, word ptr [bp+@@var_C]
		sub	word ptr [bp+@@var_C], 0Ah
		cmp	ax, word ptr [bp+@@arg_0]
		jbe	short xx_12AAF
		jmp	xx_128C9

xx_12AAF:
		xor	ax, ax

xx_12AB1:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retn
xx_126AC	endp



		public __CurrExcContext
__CurrExcContext proc far

@@s1		= word ptr -6
@@s2		= word ptr -4
@@var_2		= word ptr -2
@@arg_0		= word ptr  6
@@arg_6		= word ptr  0Ch

		push	bp
		mov	bp, sp
		sub	sp, 6
		push	si
		push	di
		mov	ax, [bp+@@arg_0]
		mov	[bp+@@var_2], ax
		cmp	[bp+@@var_2], 0FFFFh
		jz	short xx_12AFA
		mov	bx, [bp+@@var_2]
		mov	dx, ss:[bx+4]
		mov	ax, ss:[bx+2]
		add	ax, 0FFF8h
		mov	[bp+@@s2], dx
		mov	[bp+@@s1], ax
		mov	ax, 8
		push	ax
		push	ds
		mov	ax, offset aBccxh1 ; "**BCCxh1"
		push	ax		; n
		push	[bp+@@s2]		; s2
		push	[bp+@@s1]		; s1
		nopcall	_memcmp
		add	sp, 0Ah
		or	ax, ax
		jz	short xx_12AFF

xx_12AFA:
		mov	ax, 0FFFFh
		jmp	short xx_12B06

xx_12AFF:
		mov	bx, [bp+@@var_2]
		mov	ax, ss:[bx+@@arg_6]

xx_12B06:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
__CurrExcContext endp


; __ThrowFileName(void)
		public @__ThrowFileName$qv
@__ThrowFileName$qv proc far
		push	si
		push	di
		les	bx, ss:16h
		mov	dx, es:[bx+18h]
		mov	ax, es:[bx+16h]
		pop	di
		pop	si
		retf
@__ThrowFileName$qv endp


; __ThrowLineNumber(void)
		public @__ThrowLineNumber$qv
@__ThrowLineNumber$qv proc far
		push	si
		push	di
		les	bx, ss:16h
		mov	ax, es:[bx+1Ah]
		pop	di
		pop	si
		retf
@__ThrowLineNumber$qv endp


; __ThrowExceptionName(void)
		public @__ThrowExceptionName$qv
@__ThrowExceptionName$qv proc far
		push	si
		push	di
		les	bx, ss:16h
		mov	dx, es:[bx+1Eh]
		mov	ax, es:[bx+1Ch]
		pop	di
		pop	si
		retf
@__ThrowExceptionName$qv endp



; int __fastcall __far typeinfo__typeinfo(int, int, int, __int32)
		public @typeinfo@0$bctr$qmx8typeinfo
@typeinfo@0$bctr$qmx8typeinfo proc far

n		= word ptr -4
@@var_2		= word ptr -2
@@arg_0		= dword	ptr  6

		push	bp
		mov	bp, sp
		sub	sp, 4
		push	si
		push	di
		mov	ax, word ptr [bp+@@arg_0]
		or	ax, word ptr [bp+@@arg_0+2]
		jnz	short xx_12B62
		mov	ax, 8
		push	ax
		nopcall	@$bnew$qui	; operator new(uint)
		pop	cx
		mov	word ptr [bp+@@arg_0+2], dx
		mov	word ptr [bp+@@arg_0], ax
		or	ax, dx
		jz	short xx_12BA0

xx_12B62:
		les	bx, [bp+@@arg_0]
		mov	word ptr es:[bx+2], seg	xx_1313E
		mov	word ptr es:[bx], offset xx_1313E
		xor	ax, ax
		push	ax		; int
		push	ax		; int
		xor	ax, ax
		push	ax		; int
		xor	ax, ax
		push	ax		; int
		xor	ax, ax
		push	ax		; int
		xor	ax, ax
		push	ax		; int
		push	ax		; int
		xor	ax, ax
		push	ax		; int
		push	ax		; int
		mov	[bp+@@var_2], 0
		mov	[bp+n],	0
		lea	ax, [bp+n]
		push	ss		; int
		push	ax		; n
		push	cs		; int
		mov	ax, offset xx_13120
		push	ax		; int
		call	@_ThrowException$qnvt1t1t1uiuiuinuc ; _ThrowException(void *,void *,void *,void *,uint,uint,uint,uchar	*)
		add	sp, 1Ah

xx_12BA0:
		mov	dx, word ptr [bp+@@arg_0+2]
		mov	ax, word ptr [bp+@@arg_0]
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
@typeinfo@0$bctr$qmx8typeinfo endp



; typeinfo::operator=(typeinfo const &)
		public @typeinfo@0$basg$qmx8typeinfo
@typeinfo@0$basg$qmx8typeinfo proc far

@@arg_0		= word ptr  6
@@arg_2		= word ptr  8

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	dx, [bp+@@arg_2]
		mov	ax, [bp+@@arg_0]
		pop	di
		pop	si
		pop	bp
		retf
@typeinfo@0$basg$qmx8typeinfo endp



; int __cdecl __far typeinfo___typeinfo(void *,	int, int)
		public @typeinfo@0$bdtr$qv
@typeinfo@0$bdtr$qv proc far

@@arg_0		= word ptr  6
@@arg_4		= word ptr  0Ah

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	dx, [bp+@@arg_4]
		mov	ax, [bp+@@arg_0]
		or	ax, [bp+8]
		jz	short xx_12BEB
		les	bx, dword ptr [bp+@@arg_0]
		mov	word ptr es:[bx+2], seg	xx_1313E
		mov	word ptr es:[bx], offset xx_1313E
		test	dl, 1
		jz	short xx_12BEB
		push	word ptr [bp+8]
		push	[bp+@@arg_0]	; void *
		nopcall	@$bdele$qnv	; operator delete(void *)
		pop	cx
		pop	cx

xx_12BEB:
		pop	di
		pop	si
		pop	bp
		retf
@typeinfo@0$bdtr$qv endp



; typeinfo::operator==(typeinfo	const &)const
		public @typeinfo@0$beql$xqmx8typeinfo
@typeinfo@0$beql$xqmx8typeinfo proc far

@@arg_0		= dword	ptr  6
@@arg_4		= dword	ptr  0Ah

		push	bp
		mov	bp, sp
		push	si
		push	di
		les	bx, [bp+@@arg_4]
		push	word ptr es:[bx+6]
		push	word ptr es:[bx+4]
		les	bx, [bp+@@arg_0]
		push	word ptr es:[bx+6]
		push	word ptr es:[bx+4]
		call	xx_10061
		add	sp, 8
		pop	di
		pop	si
		pop	bp
		retf
@typeinfo@0$beql$xqmx8typeinfo endp



; typeinfo::operator!=(typeinfo	const &)const
		public @typeinfo@0$bneq$xqmx8typeinfo
@typeinfo@0$bneq$xqmx8typeinfo proc far

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
		call	@typeinfo@0$beql$xqmx8typeinfo	; typeinfo::operator==(typeinfo	&)
		add	sp, 8
		neg	ax
		sbb	ax, ax
		inc	ax
		pop	di
		pop	si
		pop	bp
		retf
@typeinfo@0$bneq$xqmx8typeinfo endp



; typeinfo::before(typeinfo const &)const
		public @typeinfo@0before$xqmx8typeinfo
@typeinfo@0before$xqmx8typeinfo	proc far

@@var_8		= dword	ptr -8
@@var_4		= dword	ptr -4
@@arg_0		= dword	ptr  6
@@arg_4		= dword	ptr  0Ah

		push	bp
		mov	bp, sp
		sub	sp, 8
		push	si
		push	di
		les	bx, [bp+@@arg_0]
		mov	ax, es:[bx+4]
		or	ax, es:[bx+6]
		jnz	short xx_12C4F
		xor	ax, ax
		jmp	short xx_12CA8

xx_12C4F:
		les	bx, [bp+@@arg_4]
		mov	ax, es:[bx+4]
		or	ax, es:[bx+6]
		jnz	short xx_12C61
		mov	ax, 1
		jmp	short xx_12CA8

xx_12C61:
		les	bx, [bp+@@arg_4]
		mov	dx, es:[bx+6]
		mov	word ptr [bp+@@var_4+2], dx
		mov	ax, es:[bx+4]
		mov	word ptr [bp+@@var_4], ax
		les	bx, [bp+@@var_4]
		add	ax, es:[bx+4]
		push	dx
		push	ax
		les	bx, [bp+@@arg_0]
		mov	dx, es:[bx+6]
		mov	word ptr [bp+@@var_8+2], dx
		mov	ax, es:[bx+4]
		mov	word ptr [bp+@@var_8], ax
		les	bx, [bp+@@var_8]
		add	ax, es:[bx+4]
		push	dx		; s2
		push	ax		; s1
		nopcall	_strcmp
		add	sp, 8
		or	ax, ax
		jge	short xx_12CA6
		mov	ax, 1
		jmp	short xx_12CA8

xx_12CA6:
		xor	ax, ax

xx_12CA8:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
@typeinfo@0before$xqmx8typeinfo	endp



; typeinfo::name(void)const
		public @typeinfo@0name$xqv
@typeinfo@0name$xqv proc far

@@arg_0		= dword	ptr  6

		push	bp
		mov	bp, sp
		push	si
		push	di
		les	bx, [bp+@@arg_0]
		push	word ptr es:[bx+6]
		push	word ptr es:[bx+4]
		call	xx_1003C
		pop	cx
		pop	cx
		pop	di
		pop	si
		pop	bp
		retf
@typeinfo@0name$xqv endp



; int __fastcall __far __GetTypeInfo(int, int, int, int, int, __int32, int, int, int, int)
		public @__GetTypeInfo$qnvt1t1t1
@__GetTypeInfo$qnvt1t1t1 proc far

@@var_8		= dword	ptr -8
@@var_4		= word ptr -4
@@var_2		= word ptr -2
@@arg_0		= word ptr  6
@@arg_2		= word ptr  8
@@arg_4		= word ptr  0Ah
@@arg_C		= word ptr  12h
@@arg_E		= word ptr  14h

		push	bp
		mov	bp, sp
		sub	sp, 8
		push	si
		push	di
		mov	dx, [bp+@@arg_E]
		mov	ax, [bp+@@arg_C]
		mov	word ptr [bp+@@var_8+2], dx
		mov	word ptr [bp+@@var_8], ax
		mov	ax, [bp+@@arg_0]
		or	ax, [bp+@@arg_2]
		jnz	short xx_12D0A
		xor	ax, ax
		push	ax		; int
		push	ax		; int
		xor	ax, ax
		push	ax		; int
		xor	ax, ax
		push	ax		; int
		xor	ax, ax
		push	ax		; int
		xor	ax, ax
		push	ax		; int
		push	ax		; int
		xor	ax, ax
		push	ax		; int
		push	ax		; int
		push	ds		; int
		mov	ax, offset xx_131A8
		push	ax		; n
		push	cs		; int
		mov	ax, offset xx_1310A
		push	ax		; int
		call	@_ThrowException$qnvt1t1t1uiuiuinuc ; _ThrowException(void *,void *,void *,void *,uint,uint,uint,uchar	*)
		add	sp, 1Ah

xx_12D0A:
		les	bx, dword ptr [bp+@@arg_4]
		mov	dx, [bp+@@arg_4+2]
		mov	ax, [bp+@@arg_4]
		sub	ax, es:[bx-2]
		mov	[bp+@@arg_4+2], dx
		mov	[bp+@@arg_4], ax
		les	bx, dword ptr [bp+@@arg_4]
		mov	dx, es:[bx-6]
		mov	ax, es:[bx-8]
		mov	[bp+@@var_2], dx
		mov	[bp+@@var_4], ax
		les	bx, [bp+@@var_8]
		mov	dx, [bp+@@var_2]
		mov	ax, [bp+@@var_4]
		mov	es:[bx+6], dx
		mov	es:[bx+4], ax
		mov	dx, word ptr [bp+@@var_8+2]
		mov	ax, word ptr [bp+@@var_8]
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
@__GetTypeInfo$qnvt1t1t1 endp



xx_12D4B	proc near

@@var_20		= word ptr -20h
@@var_1E		= word ptr -1Eh
@@var_1C		= dword	ptr -1Ch
@@var_18		= word ptr -18h
@@var_16		= word ptr -16h
@@var_14		= dword	ptr -14h
@@var_10		= word ptr -10h
@@var_E		= word ptr -0Eh
@@var_C		= word ptr -0Ch
@@var_A		= word ptr -0Ah
@@var_8		= word ptr -8
@@var_6		= word ptr -6
@@var_4		= dword	ptr -4
@@arg_0		= word ptr  4
@@arg_2		= word ptr  6
@@arg_4		= dword	ptr  8
@@arg_8		= word ptr  0Ch
@@arg_A		= word ptr  0Eh
@@arg_C		= word ptr  10h
@@arg_E		= word ptr  12h
@@arg_10		= word ptr  14h
@@arg_12		= word ptr  16h
@@arg_14		= word ptr  18h
@@arg_16		= word ptr  1Ah
@@arg_18		= word ptr  1Ch
@@arg_1A		= word ptr  1Eh
@@arg_1C		= word ptr  20h
@@arg_1E		= word ptr  22h

		push	bp
		mov	bp, sp
		sub	sp, 20h
		push	si
		push	di
		mov	[bp+@@var_8], 0
		mov	[bp+@@var_A], 0
		mov	[bp+@@var_C], 0
		mov	[bp+@@var_E], 0
		mov	ax, [bp+@@arg_14]
		or	ax, [bp+@@arg_16]
		jz	short xx_12D86
		push	word ptr [bp+@@arg_4+2]
		push	word ptr [bp+@@arg_4]
		push	[bp+@@arg_16]
		push	[bp+@@arg_14]
		call	xx_10061
		add	sp, 8
		or	ax, ax
		jnz	short xx_12D90

xx_12D86:
		les	bx, [bp+@@arg_4]
		test	byte ptr es:[bx+8], 4
		jnz	short xx_12D97

xx_12D90:
		xor	dx, dx
		xor	ax, ax
		jmp	xx_12F8B

xx_12D97:
		mov	[bp+@@var_6], 0
		les	bx, [bp+@@arg_4]
		mov	dx, word ptr [bp+@@arg_4+2]
		mov	ax, word ptr [bp+@@arg_4]
		add	ax, es:[bx+0Ch]

xx_12DA9:
		mov	word ptr [bp+@@var_4+2], dx
		mov	word ptr [bp+@@var_4], ax

xx_12DAF:
		les	bx, [bp+@@var_4]
		mov	dx, es:[bx+2]
		mov	ax, es:[bx]
		mov	word ptr [bp+@@var_1C+2],	dx
		mov	word ptr [bp+@@var_1C], ax
		mov	ax, word ptr [bp+@@var_1C]
		or	ax, word ptr [bp+@@var_1C+2]
		jnz	short xx_12DCA
		jmp	xx_12F53

xx_12DCA:
		les	bx, [bp+@@var_4]
		test	byte ptr es:[bx+6], 8
		jz	short xx_12DD7
		jmp	xx_12F4C

xx_12DD7:
		cmp	[bp+@@arg_1A], 0
		jz	short xx_12DF1
		les	bx, [bp+@@var_4]
		mov	ax, es:[bx+6]
		and	ax, 3
		cmp	ax, 3
		jnz	short xx_12DF1
		mov	ax, 1
		jmp	short xx_12DF3

xx_12DF1:
		xor	ax, ax

xx_12DF3:
		mov	[bp+@@var_10], ax
		les	bx, [bp+@@var_4]
		mov	dx, [bp+@@arg_2]
		mov	ax, [bp+@@arg_0]
		add	ax, es:[bx+4]
		mov	word ptr [bp+@@var_14+2],	dx
		mov	word ptr [bp+@@var_14], ax
		mov	dx, [bp+@@arg_1E]
		mov	ax, [bp+@@arg_1C]
		mov	[bp+@@var_16], dx
		mov	[bp+@@var_18], ax
		les	bx, [bp+@@var_4]
		test	byte ptr es:[bx+6], 4
		jz	short xx_12E3A
		les	bx, [bp+@@var_14]
		mov	ax, es:[bx]
		mov	dx, word ptr [bp+@@var_14+2]
		mov	word ptr [bp+@@var_14+2],	dx
		mov	word ptr [bp+@@var_14], ax
		mov	dx, word ptr [bp+@@var_1C+2]
		mov	ax, word ptr [bp+@@var_1C]
		mov	[bp+@@var_16], dx
		mov	[bp+@@var_18], ax

xx_12E3A:
		push	word ptr [bp+@@var_1C+2]
		push	word ptr [bp+@@var_1C]
		push	[bp+@@arg_E]
		push	[bp+@@arg_C]
		call	xx_10061
		add	sp, 8
		or	ax, ax
		jnz	short xx_12EBC
		les	bx, [bp+@@var_1C]
		test	byte ptr es:[bx+8], 4
		jnz	short xx_12E5E
		jmp	xx_12F4C

xx_12E5E:
		push	[bp+@@var_16]
		push	[bp+@@var_18]
		push	[bp+@@var_10]
		push	[bp+@@arg_18]
		push	[bp+@@arg_16]
		push	[bp+@@arg_14]
		push	[bp+@@arg_12]
		push	[bp+@@arg_10]
		push	[bp+@@arg_E]
		push	[bp+@@arg_C]
		push	[bp+@@arg_A]
		push	[bp+@@arg_8]
		push	word ptr [bp+@@var_1C+2]
		push	word ptr [bp+@@var_1C]
		push	word ptr [bp+@@var_14+2]
		push	word ptr [bp+@@var_14]
		call	xx_12D4B
		add	sp, 20h
		mov	[bp+@@var_1E], dx
		mov	[bp+@@var_20], ax
		mov	ax, [bp+@@var_20]
		or	ax, [bp+@@var_1E]
		jnz	short xx_12EA5
		jmp	xx_12F4C

xx_12EA5:
		mov	dx, [bp+@@var_1E]
		mov	ax, [bp+@@var_20]
		mov	word ptr [bp+@@var_14+2],	dx
		mov	word ptr [bp+@@var_14], ax
		mov	bx, [bp+@@arg_18]
		mov	ax, ss:[bx]
		mov	[bp+@@var_10], ax
		jmp	short xx_12F19

xx_12EBC:
		mov	ax, [bp+@@arg_8]
		or	ax, [bp+@@arg_A]
		jz	short xx_12EDD
		mov	dx, [bp+@@arg_A]
		mov	ax, [bp+@@arg_8]
		cmp	dx, word ptr [bp+@@var_14+2]
		jnz	short xx_12F4C
		cmp	ax, word ptr [bp+@@var_14]
		jnz	short xx_12F4C
		mov	dx, word ptr [bp+@@var_14+2]
		mov	ax, word ptr [bp+@@var_14]
		jmp	xx_12F8B

xx_12EDD:
		mov	ax, [bp+@@arg_10]
		or	ax, [bp+@@arg_12]
		jz	short xx_12F19
		xor	ax, ax
		push	ax
		push	ax
		xor	ax, ax
		push	ax
		push	[bp+@@arg_18]
		xor	ax, ax
		push	ax
		push	ax
		xor	ax, ax
		push	ax
		push	ax
		push	[bp+@@arg_16]
		push	[bp+@@arg_14]
		push	[bp+@@arg_12]
		push	[bp+@@arg_10]
		push	word ptr [bp+@@var_1C+2]
		push	word ptr [bp+@@var_1C]
		push	word ptr [bp+@@var_14+2]
		push	word ptr [bp+@@var_14]
		call	xx_12D4B
		add	sp, 20h
		or	ax, dx
		jz	short xx_12F4C

xx_12F19:
		cmp	[bp+@@var_E], 0
		jz	short xx_12F37
		mov	dx, word ptr [bp+@@var_14+2]
		mov	ax, word ptr [bp+@@var_14]
		cmp	dx, [bp+@@var_A]
		jnz	short xx_12F37
		cmp	ax, [bp+@@var_C]
		jnz	short xx_12F37
		mov	ax, [bp+@@var_10]
		or	[bp+@@var_8], ax
		jmp	short xx_12F4C

xx_12F37:
		inc	[bp+@@var_E]
		mov	dx, word ptr [bp+@@var_14+2]
		mov	ax, word ptr [bp+@@var_14]
		mov	[bp+@@var_A], dx
		mov	[bp+@@var_C], ax
		mov	ax, [bp+@@var_10]
		mov	[bp+@@var_8], ax

xx_12F4C:
		add	word ptr [bp+@@var_4], 8
		jmp	xx_12DAF

xx_12F53:
		cmp	[bp+@@var_6], 0
		jnz	short xx_12F6C
		inc	[bp+@@var_6]
		les	bx, [bp+@@arg_4]
		mov	dx, word ptr [bp+@@arg_4+2]
		mov	ax, word ptr [bp+@@arg_4]
		add	ax, es:[bx+0Ah]
		jmp	xx_12DA9

xx_12F6C:
		mov	bx, [bp+@@arg_18]
		mov	ax, [bp+@@var_8]
		mov	ss:[bx], ax
		cmp	[bp+@@var_E], 1
		jz	short xx_12F85
		mov	[bp+@@var_A], 0
		mov	[bp+@@var_C], 0

xx_12F85:
		mov	dx, [bp+@@var_A]
		mov	ax, [bp+@@var_C]

xx_12F8B:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retn
xx_12D4B	endp



; int __fastcall __far __DynamicCast(int, int, int, int, int, __int32, int, int, int, int, int)
		public @__DynamicCast$qnvt1t1t1i
@__DynamicCast$qnvt1t1t1i proc far

@@var_16		= word ptr -16h
@@var_14		= word ptr -14h
@@var_12		= word ptr -12h
@@var_10		= word ptr -10h
@@var_E		= word ptr -0Eh
@@var_C		= word ptr -0Ch
@@var_A		= word ptr -0Ah
@@var_8		= word ptr -8
@@var_6		= word ptr -6
@@var_4		= word ptr -4
@@var_2		= word ptr -2
@@arg_0		= word ptr  6
@@arg_2		= word ptr  8
@@arg_4		= word ptr  0Ah
@@arg_8		= word ptr  0Eh
@@arg_A		= word ptr  10h
@@arg_C		= word ptr  12h
@@arg_E		= word ptr  14h
@@arg_10		= word ptr  16h

		push	bp
		mov	bp, sp
		sub	sp, 16h
		push	si
		push	di
		mov	dx, [bp+@@arg_A]
		mov	ax, [bp+@@arg_8]
		mov	[bp+@@var_2], dx
		mov	[bp+@@var_4], ax
		mov	dx, [bp+@@arg_E]
		mov	ax, [bp+@@arg_C]
		mov	[bp+@@var_6], dx
		mov	[bp+@@var_8], ax
		mov	ax, [bp+@@arg_0]
		or	ax, [bp+@@arg_2]
		jnz	short @@xx_12FBC
		jmp	@@xx_130C0

@@xx_12FBC:
		les	bx, dword ptr [bp+@@arg_4]
		mov	dx, [bp+@@arg_2]
		mov	ax, [bp+@@arg_0]
		sub	ax, es:[bx-4]
		mov	[bp+@@var_E], dx
		mov	[bp+@@var_10], ax
		les	bx, dword ptr [bp+@@arg_4]
		mov	dx, [bp+@@arg_4+2]
		mov	ax, [bp+@@arg_4]
		sub	ax, es:[bx-2]
		mov	[bp+@@arg_4+2], dx
		mov	[bp+@@arg_4], ax
		les	bx, dword ptr [bp+@@arg_4]
		mov	dx, es:[bx-6]
		mov	ax, es:[bx-8]
		mov	[bp+@@var_A], dx
		mov	[bp+@@var_C], ax
		mov	ax, [bp+@@arg_C]
		or	ax, [bp+@@arg_E]
		jz	short @@xx_13012
		push	[bp+@@var_A]
		push	[bp+@@var_C]
		push	[bp+@@var_6]
		push	[bp+@@var_8]
		call	xx_10061
		add	sp, 8
		or	ax, ax
		jz	short @@xx_1301B

@@xx_13012:
		mov	dx, [bp+@@var_E]
		mov	ax, [bp+@@var_10]
		jmp	@@xx_130F0

@@xx_1301B:
		push	[bp+@@var_A]
		push	[bp+@@var_C]
		push	[bp+@@var_2]
		push	[bp+@@var_4]
		call	xx_10061
		add	sp, 8
		or	ax, ax
		jnz	short @@xx_13074
		xor	ax, ax
		push	ax
		push	ax
		mov	ax, 1
		push	ax
		lea	ax, [bp+@@var_16]
		push	ax
		push	[bp+@@var_2]
		push	[bp+@@var_4]
		push	[bp+@@arg_2]
		push	[bp+@@arg_0]
		push	[bp+@@var_6]
		push	[bp+@@var_8]
		xor	ax, ax
		push	ax
		push	ax
		push	[bp+@@var_A]
		push	[bp+@@var_C]
		push	[bp+@@var_E]
		push	[bp+@@var_10]
		call	xx_12D4B
		add	sp, 20h
		mov	[bp+@@var_12], dx
		mov	[bp+@@var_14], ax
		mov	ax, [bp+@@var_14]
		or	ax, [bp+@@var_12]
		jnz	short @@xx_130B8

@@xx_13074:
		xor	ax, ax
		push	ax
		push	ax
		mov	ax, 1
		push	ax
		lea	ax, [bp+@@var_16]
		push	ax
		xor	ax, ax
		push	ax
		push	ax
		xor	ax, ax
		push	ax
		push	ax
		push	[bp+@@var_6]
		push	[bp+@@var_8]
		xor	ax, ax
		push	ax
		push	ax
		push	[bp+@@var_A]
		push	[bp+@@var_C]
		push	[bp+@@var_E]
		push	[bp+@@var_10]
		call	xx_12D4B
		add	sp, 20h
		mov	[bp+@@var_12], dx
		mov	[bp+@@var_14], ax
		mov	ax, [bp+@@var_14]
		or	ax, [bp+@@var_12]
		jz	short @@xx_130C0
		cmp	[bp+@@var_16], 0
		jz	short @@xx_130C0

@@xx_130B8:
		mov	dx, [bp+@@var_12]
		mov	ax, [bp+@@var_14]
		jmp	short @@xx_130F0

@@xx_130C0:
		cmp	[bp+@@arg_10], 0
		jz	short @@xx_130EC
		xor	ax, ax
		push	ax		; int
		push	ax		; int
		xor	ax, ax
		push	ax		; int
		xor	ax, ax
		push	ax		; int
		xor	ax, ax
		push	ax		; int
		xor	ax, ax
		push	ax		; int
		push	ax		; int
		xor	ax, ax
		push	ax		; int
		push	ax		; int
		push	ds		; int
		mov	ax, offset xx_131A9
		push	ax		; n
		push	cs		; int
		mov	ax, offset xx_130F6
		push	ax		; int
		call	@_ThrowException$qnvt1t1t1uiuiuinuc ; _ThrowException(void *,void *,void *,void *,uint,uint,uint,uchar	*)
		add	sp, 1Ah

@@xx_130EC:
		xor	dx, dx
		xor	ax, ax

@@xx_130F0:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
@__DynamicCast$qnvt1t1t1i endp

xx_130F6	dw 1
		dw 1
		dw 0Ah
		db 0FFh
		db 0FFh
		dw 0
		db 'Bad_cast',0
		db 0
xx_1310A	dw 1
		dw 1
		dw 0Ah
		dw 0FFFFh
		dw 0
		db 'Bad_typeid',0
		db    0
xx_13120	db 4, 0, 10h, 20h, 0Ah,	0
		dd xx_13142
		db 'typeinfo *',0
		db 0
		dd xx_13142
		dd 0
xx_1313E	dd @typeinfo@0$bdtr$qv
					; typeinfo::~typeinfo(void)
xx_13142	db 8, 0, 3, 0, 26h, 3 dup(0), 73h, 10h,	30h, 0,	34h, 0Dh dup(0)
		db 1, 0, 1, 0
		dd @typeinfo@0$bdtr$qv	; typeinfo::~typeinfo(void)
		dw 5
		dw 38h
		db 'typeinfo',0
		dd 0
		dd 0
		dd 0
		db 0

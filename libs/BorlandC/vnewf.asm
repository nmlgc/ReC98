VFARCALL	 = 1
VPASCAL		 = 2
VFARPTR		 = 4
VDEALLOC	 = 8
VSTORECNT	 = 10h
VFASTCALL	 = 20h
VHUGEVECT	 = 40h
VFASTTHIS	 = 80h
VTHISLAST	 = 100h
VCALLTYPE	 = 1A7h

; void __far _vector_new_(void far *ptr, size_t size, unsigned __int32 count, unsigned int mode, ...)
		public @_vector_new_$qnvuiuluie
@_vector_new_$qnvuiuluie proc
@@Length	= dword	ptr -1Ch
@@PadFromZero	= word ptr -18h
@@Header	= word ptr -16h
@@var_14	= word ptr -14h
@@var_12	= dword	ptr -12h
@@Overhead	= word ptr -0Eh
@@construct	= word ptr -0Ch
@@fp		= dword	ptr -0Ah
@@np		= word ptr -6
@@ap		= dword	ptr -4
@@ptr		= dword	ptr  6
@@size		= word ptr  0Ah
@@count		= dword	ptr  0Ch
@@mode		= word ptr  10h
@@va		= byte ptr  12h

		push	bp
		mov	bp, sp
		sub	sp, 1Ch
		push	si
		push	di
		mov	[bp+@@construct], 1
		mov	[bp+@@Overhead], 0
		nopcall	@__RefDestructorCount$qv ; __RefDestructorCount(void)
		mov	bx, ax
		mov	es, dx
		mov	dx, es:[bx+2]
		mov	ax, es:[bx]
		mov	word ptr [bp+@@var_12+2], dx
		mov	word ptr [bp+@@var_12],	ax
		lea	ax, [bp+@@va]
		mov	word ptr [bp+@@ap+2], ss
		mov	word ptr [bp+@@ap], ax
		test	byte ptr [bp+@@mode], VFARCALL
		jz	short @@loc_10083
		add	word ptr [bp+@@ap], 4
		les	bx, [bp+@@ap]
		mov	dx, es:[bx-2]
		mov	ax, es:[bx-4]
		mov	word ptr [bp+@@fp+2], dx
		mov	word ptr [bp+@@fp], ax
		or	ax, word ptr [bp+@@fp+2]
		jnz	short @@storeCount?
		jmp	short @@loc_10097

@@loc_10083:
		add	word ptr [bp+@@ap], 2
		les	bx, [bp+@@ap]
		mov	ax, es:[bx-2]
		mov	[bp+@@np], ax
		cmp	[bp+@@np], 0
		jnz	short @@storeCount?

@@loc_10097:
		mov	[bp+@@construct], 0

@@storeCount?:
		test	byte ptr [bp+@@mode], VSTORECNT
		jz	short @@loc_100A7
		mov	[bp+@@Overhead], 4

@@loc_100A7:
		mov	ax, word ptr [bp+@@ptr]
		or	ax, word ptr [bp+@@ptr+2]
		jz	short @@hugeVect?
		jmp	@@loc_10179

@@hugeVect?:
		test	byte ptr [bp+@@mode], VHUGEVECT
		jz	short @@loc_10134
		add	[bp+@@Overhead], 2
		mov	bx, [bp+@@size]
		xor	cx, cx
		mov	dx, word ptr [bp+@@count+2]
		mov	ax, word ptr [bp+@@count]
		call	N_LXMUL@
		add	ax, [bp+@@Overhead]
		adc	dx, 0
		add	ax, [bp+@@size]
		adc	dx, 0
		push	dx
		push	ax
		nopcall	@$bnwa$qul	; operator new[](ulong)
		pop	cx
		pop	cx
		mov	word ptr [bp+@@ptr+2], dx
		mov	word ptr [bp+@@ptr], ax
		or	ax, word ptr [bp+@@ptr+2]
		jnz	short @@loc_100ED
		jmp	@@ret0

@@loc_100ED:
		xor	ax, ax
		push	ax
		push	[bp+@@size]
		mov	ax, 1
		xor	dx, dx
		push	ax
		push	dx
		call	N_LMOD@
		mov	[bp+@@PadFromZero], ax
		mov	ax, word ptr [bp+@@ptr]
		mov	[bp+@@Header], ax
		jmp	short @@loc_1010E

@@loc_10108:
		mov	ax, [bp+@@size]
		add	[bp+@@PadFromZero], ax

@@loc_1010E:
		mov	ax, [bp+@@Overhead]
		add	ax, [bp+@@Header]
		cmp	ax, [bp+@@PadFromZero]
		ja	short @@loc_10108
		mov	ax, [bp+@@PadFromZero]
		sub	ax, [bp+@@Header]
		sub	ax, [bp+@@Overhead]
		add	word ptr [bp+@@ptr], ax
		les	bx, [bp+@@ptr]
		mov	ax, [bp+@@Header]
		mov	es:[bx], ax
		add	word ptr [bp+@@ptr], 2
		jmp	short @@loc_10179

@@loc_10134:
		mov	bx, [bp+@@size]
		xor	cx, cx
		mov	dx, word ptr [bp+@@count+2]
		mov	ax, word ptr [bp+@@count]
		call	N_LXMUL@
		add	ax, [bp+@@Overhead]
		adc	dx, 0
		mov	word ptr [bp+@@Length+2], dx
		mov	word ptr [bp+@@Length],	ax
		cmp	word ptr [bp+@@Length+2], 0
		jb	short @@loc_1015E
		ja	short @@ret0
		cmp	word ptr [bp+@@Length],	0FFFFh
		jbe	short @@loc_1015E
		jmp	short @@ret0

@@loc_1015E:
		push	word ptr [bp+@@Length]
		nopcall	@$bnwa$qui	; operator new[](uint)
		pop	cx
		mov	word ptr [bp+@@ptr+2], dx
		mov	word ptr [bp+@@ptr], ax
		or	ax, word ptr [bp+@@ptr+2]
		jnz	short @@loc_10179

@@ret0:
		xor	dx, dx
		xor	ax, ax
		jmp	@@ret

@@loc_10179:
		test	byte ptr [bp+@@mode], VSTORECNT
		jz	short @@loc_10193
		les	bx, [bp+@@ptr]
		mov	dx, word ptr [bp+@@count+2]
		mov	ax, word ptr [bp+@@count]
		mov	es:[bx+2], dx
		mov	es:[bx], ax
		add	word ptr [bp+@@ptr], 4

@@loc_10193:
		cmp	[bp+@@construct], 0
		jnz	short @@loc_1019C
		jmp	@@loc_1028C

@@loc_1019C:
		mov	ax, [bp+@@mode]
		and	ax, VCALLTYPE
		mov	[bp+@@Header], ax
		test	byte ptr [bp+@@mode], VFASTTHIS
		jz	short @@loc_101B0
		and	[bp+@@Header], not VTHISLAST

@@loc_101B0:
		mov	dx, word ptr [bp+@@ptr+2]
		mov	ax, word ptr [bp+@@ptr]
		mov	[bp+@@PadFromZero], dx
		mov	word ptr [bp+@@Length+2], ax
		jmp	@@loc_1026E

@@loc_101BF:
		mov	ax, [bp+@@Header]
		mov	[bp+@@var_14], ax
		mov	cx, 10h		; switch 16 cases
		mov	bx, offset word_102B3

@@loc_101CB:
		mov	ax, cs:[bx]
		cmp	ax, [bp+@@var_14]
		jz	short @@loc_101DA
		add	bx, 2
		loop	@@loc_101CB
		jmp	short @@default	; default

@@loc_101DA:
		jmp	word ptr cs:[bx+20h] ; switch jump

vnewf_101DE:
		push	[bp+@@PadFromZero] ; jumptable 000101DA	case 4
		push	word ptr [bp+@@Length+2]
		call	[bp+@@np]
		jmp	short @@loc_101F2

vnewf_101E9:
		push	[bp+@@PadFromZero] ; jumptable 000101DA	case 5
		push	word ptr [bp+@@Length+2]
		call	[bp+@@fp]

@@loc_101F2:
		pop	cx
		pop	cx
		jmp	short @@loc_1025B

vnewf_101F6:
		push	[bp+@@PadFromZero] ; jumptable 000101DA	cases 6,36,262,292
		push	word ptr [bp+@@Length+2]
		call	[bp+@@np]
		jmp	short @@loc_1020A

vnewf_10201:
		push	[bp+@@PadFromZero] ; jumptable 000101DA	cases 7,37,263,293
		push	word ptr [bp+@@Length+2]
		call	[bp+@@fp]

@@loc_1020A:
		jmp	short @@loc_1025B

vnewf_1020C:
		push	ds		; jumptable 000101DA case 132
		push	si
		lds	si, [bp+@@Length+2]
		call	[bp+@@np]
		pop	si
		pop	ds
		jmp	short @@loc_1025B

vnewf_10218:
		push	ds		; jumptable 000101DA case 133
		push	si
		lds	si, [bp+@@Length+2]
		call	[bp+@@fp]
		pop	si
		pop	ds
		jmp	short @@loc_1025B

vnewf_10224:
		push	ds		; jumptable 000101DA case 134
		push	si
		lds	si, [bp+@@Length+2]
		call	[bp+@@np]
		pop	si
		pop	ds
		jmp	short @@loc_1025B

vnewf_10230:
		push	ds		; jumptable 000101DA case 135
		push	si
		lds	si, [bp+@@Length+2]
		call	[bp+@@fp]
		pop	si
		pop	ds
		jmp	short @@loc_1025B

vnewf_1023C:
		push	ds		; jumptable 000101DA case 164
		push	si
		lds	si, [bp+@@Length+2]
		call	[bp+@@np]
		pop	si
		pop	ds
		jmp	short @@loc_1025B

vnewf_10248:
		push	ds		; jumptable 000101DA case 165
		push	si
		lds	si, [bp+@@Length+2]
		push	bx
		pop	bx
		call	[bp+@@fp]
		pop	si
		pop	ds
		jmp	short @@loc_1025B

@@default:
		nopcall	_abort

@@loc_1025B:
		mov	ax, [bp+@@size]
		xor	dx, dx
		add	word ptr [bp+@@Length+2], ax
		adc	dx, 0
		mov	cx, offset __AHSHIFT
		shl	dx, cl
		add	[bp+@@PadFromZero], dx

@@loc_1026E:
		mov	ax, word ptr [bp+@@count+2]
		mov	dx, word ptr [bp+@@count]
		sub	word ptr [bp+@@count], 1
		sbb	word ptr [bp+@@count+2], 0
		or	ax, ax
		jbe	short @@loc_10283
		jmp	@@loc_101BF

@@loc_10283:
		jnz	short @@loc_1028C
		or	dx, dx
		jbe	short @@loc_1028C
		jmp	@@loc_101BF

@@loc_1028C:
		test	byte ptr [bp+@@mode+1],	2
		jz	short @@ret_ptr
		nopcall	@__RefDestructorCount$qv ; __RefDestructorCount(void)
		mov	bx, word ptr [bp+@@var_12+2]
		mov	cx, word ptr [bp+@@var_12]
		mov	es, dx
		xchg	ax, bx
		mov	es:[bx+2], ax
		mov	es:[bx], cx

@@ret_ptr:
		mov	dx, word ptr [bp+@@ptr+2]
		mov	ax, word ptr [bp+@@ptr]

@@ret:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret
@_vector_new_$qnvuiuluie endp

word_102B3	dw	4,     5,     6,     7
		dw    24h,   25h,   84h,   85h ; value table for switch	statement
		dw    86h,   87h,  0A4h,  0A5h
		dw   106h,  107h,  124h,  125h
		dw offset vnewf_101DE	; jump table for switch	statement
		dw offset vnewf_101E9
		dw offset vnewf_101F6
		dw offset vnewf_10201
		dw offset vnewf_101F6
		dw offset vnewf_10201
		dw offset vnewf_1020C
		dw offset vnewf_10218
		dw offset vnewf_10224
		dw offset vnewf_10230
		dw offset vnewf_1023C
		dw offset vnewf_10248
		dw offset vnewf_101F6
		dw offset vnewf_10201
		dw offset vnewf_101F6
		dw offset vnewf_10201

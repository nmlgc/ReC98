; int __pascal __near __XCVT(void *valP, int digits, int *signP, char *strP, int ftype)
___XCVT		proc near
@@frac		= tbyte	ptr -10h
@@SW		= word ptr -6
@@ten		= word ptr -4
@@Sign		= word ptr -2
@@ftype		= word ptr  4
@@strP		= DPTR_	(6)
@@signP		= DPTR_ (6 + dPtrSize)
@@digits	= word ptr (6 + dPtrSize + dPtrSize)
@@valP		= DPTR_ (6 + dPtrSize + dPtrSize + 2)

		push	bp
		mov	bp, sp
		sub	sp, 10h
		push	si
		push	di
		mov	[bp+@@Sign], 8000h
		mov	[bp+@@ten], 10
		push	es
		LES_	di, [bp+@@valP]
		mov	ax, 7FFFh
		mov	bx, [bp+@@ftype]
		mov	cx, es:[bx+di]
		and	[bp+@@Sign], cx
		and	es:[bx+di], ax
		shr	bx, 1
		shr	bx, 1
		shl	bx, 1
		jmp	word ptr cs:@@type_table[bx]

@@type_table:
		dw offset @@F4bytes
		dw offset @@F8bytes
		dw offset @@F10bytes

@@F4bytes:
		fld	dword ptr es:[di]
		jmp	short @@its_loaded

@@F8bytes:
		fld	qword ptr es:[di]
		jmp	short @@its_loaded

@@F10bytes:
		and	ax, es:[di+8]
		cmp	ax, 7FFFh
		jz	short @@F10bytesHacked
		and	byte ptr es:[di], 0F0h

@@F10bytesHacked:
		fld	tbyte ptr es:[di]

@@its_loaded:
		xor	bx, bx
		shl	cx, 1
		rcl	bx, 1
		les	di, [bp+@@signP]
		mov	es:[di], bx
		fxam
		fstsw	[bp+@@SW]
		db	0CDh, 03Dh	; Hack ('wait' is apparently not emulated?)
		mov	ax, [bp+@@SW]
		and	ah, 47h
		cmp	ah, 40h
		jz	short @@zero
		cmp	ah, 5
		jz	short @@its_infinity
		cmp	ah, 1
		jz	short @@its_NAN
		jmp	short @@normal

@@its_NAN:
		mov	dx, NAN_number
		jmp	short @@pop_and_go

@@its_infinity:
		mov	dx, INF_number
		jmp	short @@pop_and_go

@@zero:
		mov	dx, 1
		mov	al, '0'
		LES_	di, [bp+@@signP]
		mov	word ptr ES_[di], 0
		mov	cx, [bp+@@digits]
		or	cx, cx
		jg	short @@extSized
		neg	cx
		inc	cx

@@extSized:
		cmp	cx, __XCVTDIG__
		jbe	short @@extLimited
		mov	cx, __XCVTDIG__

@@extLimited:
		cld
		les	di, [bp+@@strP]
		rep stosb
		xor	al, al
		stosb

@@pop_and_go:
		fstp	st
		jmp	@@end

@@normal:
		fld	st
		fstp	[bp+@@frac]
		db	0CDh, 03Dh	; Hack ('wait' is apparently not emulated?)
		mov	ax, word ptr [bp+@@frac+8]
		sub	ax, 3FFFh
		mov	dx, 4D10h
		imul	dx
		xchg	ax, bx
		mov	ah, 4Dh
		mov	al, byte ptr [bp+@@frac+7]
		shl	al, 1
		mul	ah
		add	ax, bx
		adc	dx, 0
		neg	ax
		adc	dx, 0
		mov	ax, [bp+@@digits]
		or	ax, ax
		jg	short @@digitPlaces
		neg	ax
		add	ax, dx
		jl	short @@zero

@@digitPlaces:
		cmp	ax, MaxSigDigits
		jle	short @@defaultPlaces
		mov	ax, MaxSigDigits

@@defaultPlaces:
		mov	bx, ax
		sub	ax, dx

@@powloop:
		jz	short @@adjusted
		mov	si, ax
		jge	short @@power10
		neg	ax

@@power10:
		cmp	ax, 4932
		jle	short @@getpow
		mov	ax, 4932

@@getpow:
		push	ax
		nopcall	_pow10
		pop	ax
		or	si, si
		jg	short @@increase
		fdivp	st(1), st
		add	ax, si
		jmp	short @@powloop

@@increase:
		fmulp	st(1), st
		xchg	ax, si
		sub	ax, si
		jmp	short @@powloop

@@adjusted:
		push	bx
		nopcall	_pow10
		pop	ax
		fcomp	st(1)
		fstsw	[bp+@@SW]
		db	0CDh, 03Dh	; Hack ('wait' is apparently not emulated?)
		test	byte ptr [bp+@@SW+1], 45h
		jz	short @@notTooHigh
		inc	dx
		inc	bx
		cmp	bx, MaxSigDigits
		ja	short @@mustShorten
		cmp	[bp+@@digits], 0
		jle	short @@notTooLow

@@mustShorten:
		fidiv	[bp+@@ten]
		dec	bx
		jmp	short @@notTooLow

@@notTooHigh:
		mov	ax, bx
		dec	ax
		push	ax
		nopcall	_pow10
		pop	ax
		fcomp	st(1)
		fstsw	[bp+@@SW]
		db	0CDh, 03Dh	; Hack ('wait' is apparently not emulated?)
		test	byte ptr [bp+@@SW+1], 41h
		jnz	short @@notTooLow
		dec	dx
		dec	bx
		cmp	[bp+@@digits], 0
		jle	short @@notTooLow
		fimul	[bp+@@ten]
		inc	bx

@@notTooLow:
		or	bx, bx
		jl	short @@jmp_roundToZero
		frndint
		fbstp	[bp+@@frac]
		les	di, [bp+@@strP]
		add	di, bx
		push	di
		xor	al, al
		std
		stosb
		lea	si, [bp+@@frac]
		mov	cx, 4
		db	0CDh, 03Dh	; Hack ('wait' is apparently not emulated?)
		or	bx, bx
		jnz	short @@nextPair
		mov	ch, SS_[si]
		xor	ch, 1
		jz	short @@maybeRoundup

@@jmp_roundToZero:
		fldz
		pop	di
		jmp	@@zero

@@nextPair:
		mov	al, SS_[si]
		inc	si
		mov	ah, al
		shr	ah, cl
		and	al, 0Fh
		add	ax, '00'
		stosb
		or	ch, al
		dec	bx
		jz	short @@maybeRoundup
		mov	al, ah
		stosb
		or	ch, al
		dec	bx
		jnz	short @@nextPair

@@maybeRoundup:
		pop	bx
		and	ch, 0Fh
		jnz	short @@append
		inc	dx
		cmp	[bp+@@digits], 0
		jg	short @@put1
		mov	BY0 (ES_[bx]), '0'

@@put1:
		inc	bx
		mov	BY0 (ES_[di+1]), '1'

@@append:
		mov	cx, [bp+@@digits]
		or	cx, cx
		jg	short @@zMax
		neg	cx
		add	cx, dx

@@zMax:
		cmp	cx, __XCVTDIG__
		jbe	short @@zLimited
		mov	cx, __XCVTDIG__

@@zLimited:
		mov	BY0 (ES_[bx]), 0
		mov	ax, bx
		sub	ax, word ptr [bp+@@strP]
		sub	cx, ax
		jbe	short @@end

@@appendZloop:
		mov	W0 (ES_[bx]), '0'
		inc	bx
		loop	@@appendZloop

@@end:
		cld
		LES_	di, [bp+@@valP]
		mov	bx, [bp+@@ftype]
		mov	cx, [bp+@@Sign]
		or	es:[bx+di], cx
		pop	es
		mov	ax, dx
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret	10h
___XCVT		endp
		noemul

; enum flagBits
isSuppressed	 = 1
isHalf		 = 2
isLong		 = 4
isLongDouble	 = 8
isExclusive	 = 10h
isFarPtr	 = 20h

; int __cdecl _scantod(int *(__cdecl __near near *Get)(), int (__cdecl __near near *UnGet)(), const void *srceP, int width, int *countP, int *statusP)
__scantod	proc near
@@localeDot	= byte ptr -19h
@@frac		= tbyte	ptr -18h
@@status	= word ptr -0Eh
@@ct		= word ptr -0Ch
@@ExpOflow	= byte ptr -9
@@expSign	= byte ptr -8
@@saw_sign	= byte ptr -7
@@FirstDigit	= byte ptr -6
@@sign		= byte ptr -5
@@digits	= word ptr -4
@@decimals	= word ptr -2
@@Get		= word ptr 4
@@UnGet		= word ptr 6
@@srceP		= DPTR_ 8
@@width		= word ptr (8 + dPtrSize)
@@countP	= DPTR_ (8 + dPtrSize + 2)
@@statusP	= DPTR_ (8 + dPtrSize + 2 + dPtrSize)

		push	bp
		mov	bp, sp
		sub	sp, 1Ah
		push	si
		push	di
		mov	[bp+@@sign], 0
		mov	[bp+@@FirstDigit], 1
		mov	[bp+@@saw_sign], 0
		mov	[bp+@@expSign],	0
		mov	[bp+@@ExpOflow], 0
		mov	[bp+@@ct], 0
		mov	[bp+@@status], 1
		fldz
		fstp	[bp+@@frac]
		fwait
		les	bx, __localeconvention
		mov	al, es:[bx]
		mov	[bp+@@localeDot], al
		mov	si, 8000h
		mov	di, -2

std_nextBlank:
		inc	[bp+@@ct]
if LDATA
		push	word ptr [bp+@@srceP+2]
endif
		push	word ptr [bp+@@srceP]
		call	[bp+@@Get]
		popCX_
		pop	cx
		or	ax, ax
		jge	short not_instantEOF
		jmp	std_EOF

not_instantEOF:
		cbw
		xchg	ax, bx
		test	bl, 80h
		jnz	short std_notSpace
ifdef __HUGE__
		mov	ax, seg __ctype
		mov	es, ax
		test	es:(__ctype+1)[bx], _IS_SP
else
		test	(__ctype+1)[bx], _IS_SP
endif
		jnz	short std_nextBlank

std_notSpace:
		xchg	ax, bx
		dec	[bp+@@width]
		jl	short std_fractionLimited
		cmp	al, '+'
		jz	short std_signSeen
		cmp	al, '-'
		jnz	short std_fracChar
		inc	[bp+@@sign]

std_signSeen:
		inc	[bp+@@saw_sign]

std_fracLoop:
		dec	[bp+@@width]
		jl	short std_fractionLimited
		inc	[bp+@@ct]
if LDATA
		push	word ptr [bp+@@srceP+2]
endif
		push	word ptr [bp+@@srceP]
		call	[bp+@@Get]
		popCX_
		pop	cx
		cmp	[bp+@@FirstDigit], 1
		jnz	short std_fracChar
		cmp	[bp+@@saw_sign], 0
		jz	short std_fracChar
		cmp	al, 'I'
		jz	short relPossibleINF
		cmp	al, 'N'
		jz	short relPossibleNAN
		jmp	short std_fracChar

relPossibleINF:
		jmp	PossibleINF

relPossibleNAN:
		jmp	PossibleNAN

std_fracChar:
		mov	[bp+@@FirstDigit], 0
		cmp	al, [bp+@@localeDot]
		jz	short std_fracPoint
		cmp	al, '9'
		ja	short std_fracEndJmp
		cmp	al, '0'
		jb	short std_fracEndJmp
		sub	al, '0'
		cbw
		inc	di
		jg	short std_notFirst
		mov	byte ptr [bp+@@frac], al
		mov	di, 1
		or	al, al
		jnz	short std_fracLoop
		neg	di
		cmp	si, 8000h
		jz	short std_fracLoop
		dec	si
		jmp	short std_fracLoop

std_fractionLimited:
		mov	al, 'e'

jmp_to_fracEnd:
		jmp	std_fracEnd

std_EOF:
		mov	[bp+@@status], EOF
		jmp	short std_noResult

std_fracEndJmp:
		jmp	std_fracEnd

std_fracPoint:
		cmp	si, 8000h
		jnz	short jmp_to_fracEnd
		sub	si, si
		or	di, di
		jle	short std_fracLoop
		mov	si, di
		jmp	short std_fracLoop

std_notFirst:
		cmp	di, 5
		ja	short std_beyond5
		xchg	ax, bx
		mov	ax, 10
		mul	word ptr [bp+@@frac]
		add	ax, bx
		adc	dl, dh
		mov	word ptr [bp+@@frac], ax
		mov	word ptr [bp+@@frac+2],	dx
		jmp	std_fracLoop

std_beyond5:
		cmp	di, 18
		ja	short jmp_frac_loop
		xchg	ax, bx
		mov	ax, 10
		mul	word ptr [bp+@@frac+6]
		mov	word ptr [bp+@@frac+6],	ax
		mov	ax, 10
		mul	word ptr [bp+@@frac+4]
		mov	word ptr [bp+@@frac+4],	ax
		push	dx
		mov	ax, 10
		mul	word ptr [bp+@@frac+2]
		mov	word ptr [bp+@@frac+2],	ax
		push	dx
		mov	ax, 10
		mul	word ptr [bp+@@frac]
		add	ax, bx
		mov	word ptr [bp+@@frac], ax
		adc	word ptr [bp+@@frac+2],	dx
		pop	dx
		adc	word ptr [bp+@@frac+4],	dx
		pop	dx
		adc	word ptr [bp+@@frac+6],	dx

jmp_frac_loop:
		jmp	std_fracLoop

std_noDigitSeen:
		mov	[bp+@@status], 0

std_noResult:
		cmp	[bp+@@width], 0
		jl	short std_fldz
if LDATA
		push	word ptr [bp+@@srceP+2]
endif
		push	word ptr [bp+@@srceP]
		push	ax
		call	[bp+@@UnGet]
		add	sp, 2 + dPtrSize
		dec	[bp+@@ct]

std_fldz:
		fldz
		jmp	std_end

std_fracEnd:
		cmp	di, -2
		jz	short std_noDigitSeen
		cmp	si, 8000h
		jnz	short std_exponent
		mov	si, di

std_exponent:
		mov	[bp+@@digits], di
		mov	[bp+@@decimals], si
		sub	di, di
		cmp	al, 'E'
		jz	short std_present
		cmp	al, 'e'
		jnz	short std_combine

std_present:
		dec	[bp+@@width]
		jl	short std_exponentLimited
		inc	[bp+@@ct]
if LDATA
		push	word ptr [bp+@@srceP+2]
endif
		push	word ptr [bp+@@srceP]
		call	[bp+@@Get]
		popCX_
		pop	cx
		cmp	al, '+'
		jz	short std_expNext
		cmp	al, '-'
		jnz	short std_expGotNext
		inc	[bp+@@expSign]

std_expNext:
		dec	[bp+@@width]
		jl	short std_exponentLimited
		inc	[bp+@@ct]
if LDATA
		push	word ptr [bp+@@srceP+2]
endif
		push	word ptr [bp+@@srceP]
		call	[bp+@@Get]
		popCX_
		pop	cx

std_expGotNext:
		cmp	al, '9'
		ja	short std_combine
		sub	al, '0'
		jb	short std_expNonDigit
		cbw
		xchg	ax, di
		mov	dx, 10
		mul	dx
		add	di, ax
		cmp	di, 4932
		jle	short std_expNext
		xor	di, di
		mov	[bp+@@ExpOflow], 1
		jmp	short std_expNext

std_expNonDigit:
		add	al, '0'

std_combine:
if LDATA
		push	word ptr [bp+@@srceP+2]
endif
		push	word ptr [bp+@@srceP]
		push	ax
		call	[bp+@@UnGet]
		add	sp, 2 + dPtrSize
		dec	[bp+@@ct]

std_exponentLimited:
		test	[bp+@@expSign],	0FFh
		jz	short skip_neg
		neg	di
		neg	[bp+@@ExpOflow]

skip_neg:
		mov	bx, [bp+@@digits]
		or	bx, bx
		jge	short std_nonZero
		fldz
		jmp	short std_end

std_nonZero:
		mov	cx, [bp+@@decimals]
		mov	ax, cx
		add	ax, di
		cmp	[bp+@@ExpOflow], 1
		jz	short std_isInfinite
		cmp	[bp+@@ExpOflow], -1
		jnz	short std_isNormal
		fldz
		jmp	short status2

std_isInfinite:
		mov	ax, -1
		mov	word ptr [bp+@@frac], ax
		mov	word ptr [bp+@@frac+2],	ax
		mov	word ptr [bp+@@frac+4],	ax
		mov	word ptr [bp+@@frac+6],	ax
		mov	word ptr [bp+@@frac+8],	7FFEh
		fld	[bp+@@frac]

status2:
		mov	[bp+@@status], 2
		jmp	short std_end

std_isNormal:
		mov	ax, bx
		cmp	bx, 18
		jbe	short std_usualPoint
		mov	bx, 18

std_usualPoint:
		add	ax, cx
		sub	cx, bx
		add	di, cx
		fild	qword ptr [bp+@@frac]
		mov	ax, di
		or	ax, ax
		jz	short std_end
		jge	short std_pow
		neg	ax

std_pow:
		push	ax
		nopcall	_pow10
		pop	ax
		or	di, di
		jge	short std_expPlus
		fdivp	st(1), st
		jmp	short std_end

std_expPlus:
		fmulp	st(1), st

std_end:
		cmp	[bp+@@sign], 0
		jz	short std_exit
		fchs

std_exit:
		LES_	di, [bp+@@countP]
		mov	bx, [bp+@@ct]
		add	ES_[di], bx
		LES_	di, [bp+@@statusP]
		mov	bx, [bp+@@status]
		mov	ES_[di], bx
		jmp	@@end

PossibleINF:
		inc	[bp+@@ct]
if LDATA
		push	word ptr [bp+@@srceP+2]
endif
		push	word ptr [bp+@@srceP]
		call	[bp+@@Get]
		popCX_
		pop	cx
		dec	[bp+@@width]
		jl	short Didnt_pan_out
		cmp	al, 'N'
		jnz	short Didnt_pan_out
		inc	[bp+@@ct]
if LDATA
		push	word ptr [bp+@@srceP+2]
endif
		push	word ptr [bp+@@srceP]
		call	[bp+@@Get]
		popCX_
		pop	cx
		dec	[bp+@@width]
		jl	short Didnt_pan_out
		cmp	al, 'F'
		jnz	short Didnt_pan_out
		cmp	[bp+@@sign], 0
		jz	short positive_INF
		fld	INFM
		jmp	short std_exit

positive_INF:
		fld	INF
		jmp	short std_exit

PossibleNAN:
		inc	[bp+@@ct]
if LDATA
		push	word ptr [bp+@@srceP+2]
endif
		push	word ptr [bp+@@srceP]
		call	[bp+@@Get]
		popCX_
		pop	cx
		dec	[bp+@@width]
		jl	short Didnt_pan_out
		cmp	al, 'A'
		jnz	short Didnt_pan_out
		inc	[bp+@@ct]
if LDATA
		push	word ptr [bp+@@srceP+2]
endif
		push	word ptr [bp+@@srceP]
		call	[bp+@@Get]
		popCX_
		pop	cx
		dec	[bp+@@width]
		jl	short Didnt_pan_out
		cmp	al, 'N'
		jnz	short Didnt_pan_out
		cmp	[bp+@@sign], 0
		jz	short positive_NAN
		fld	NANM
		jmp	std_exit

positive_NAN:
		fld	NAN
		jmp	std_exit

Didnt_pan_out:
		mov	[bp+@@status], 0
		jmp	std_noDigitSeen

@@end:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret
__scantod	endp


; void __cdecl __near _scanpop()
__scanpop	proc near
		push	bp
		mov	bp, sp
		fstp	st
		pop	bp
		ret
__scanpop	endp


; void __cdecl __near _scanrslt(void *rsltP, int rsltType)
__scanrslt	proc near
@@tempQuad	= qword	ptr -20h
@@tempLong	= tbyte	ptr -18h
@@temp		= tbyte	ptr -0Ah
@@rsltP		= DPTR_ (4)
@@rsltType	= word ptr (4 + dPtrSize)

		push	bp
		mov	bp, sp
		sub	sp, 0Ah
		push	si
		mov	si, [bp+@@rsltType]
		fstp	[bp+@@temp]
		test	si, isLong
		jz	short @@longDouble?
		mov	ax, 1
		push	ax
		fld	[bp+@@temp]
		sub	sp, 0Ah
		fstp	[bp+@@tempLong]
		fld	qword ptr _huge_dble
		sub	sp, 8
		fstp	[bp+@@tempQuad]
		fwait
		call	__ldtrunc
		LES_	bx, [bp+@@rsltP]
		fstp	qword ptr ES_[bx]
		jmp	short @@ret

@@longDouble?:
		test	si, isLongDouble
		jz	short @@single
		LES_	bx, [bp+@@rsltP]
		fld	[bp+@@temp]
		fstp	tbyte ptr ES_[bx]
		jmp	short @@ret

@@single:
		xor	ax, ax
		push	ax
		fld	[bp+@@temp]
		sub	sp, 0Ah
		fstp	[bp+@@tempLong]
		fld	qword ptr INF_QUAD
		sub	sp, 8
		fstp	[bp+@@tempQuad]
		fwait
		call	__ldtrunc
		LES_	bx, [bp+@@rsltP]
		fstp	dword ptr ES_[bx]

@@ret:
		fwait
		pop	si
		mov	sp, bp
		pop	bp
		ret
__scanrslt	endp


_turboFloat	proc
		push	bp
		mov	bp, sp
		pop	bp
		ret
_turboFloat	endp

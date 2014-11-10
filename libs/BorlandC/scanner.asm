ScanNextArgPointer macro
		call	scn_NextArgPtr
ifdef __HUGE__
		jnc	$+5
		jmp	scn_END
endif
	endm

scn_pushSrceP	macro
if LDATA
		push	word ptr [bp+@@srceP+2]
endif
		push	word ptr [bp+@@srceP]
	endm

; int __cdecl scanner(int (__cdecl __near near *Get)(), void (__cdecl __near near *UnGet)(), void *srceP, const char *formP, va_list varPP)
_scanner	proc near
@@bitSet	= byte ptr -2Ah
@@width		= word ptr -0Ah
@@status	= word ptr -8
@@charCt	= word ptr -6
@@count		= word ptr -4
@@flags		= byte ptr -1
@@Get		= word ptr  4
@@UnGet		= word ptr  6
@@srceP		= DPTR_ (8)
@@formP		= DPTR_ (8 + dPtrSize)
@@varPP		= DPTR_ (8 + dPtrSize + dPtrSize)

		push	bp
		mov	bp, sp
		sub	sp, 2Ah
		push	si
		push	di
		mov	[bp+@@count], 0
		mov	[bp+@@charCt], 0
		jmp	short RealCodeStart

scn_NextArgPtr:
		LES_	di, [bp+@@varPP]
		test	[bp+@@flags], isFarPtr
		jz	short scn_nextNear
		les	di, ES_[di]
		add	word ptr [bp+@@varPP], 4
ifdef __HUGE__
		clc
endif
		retn

scn_nextNear:
ifdef __HUGE__
		stc
else
		mov	di, ES_[di]
		push	ds
		pop	es
		assume es:dseg
		add	word ptr [bp+@@varPP], 2
endif
		ret

RealCodeStart:
		push	es
		cld

scn_NEXT:
		mov	si, word ptr [bp+@@formP]

scn_nextChar:
if LDATA
		mov	es, word ptr [bp+@@formP+2]
endif
		assume es:nothing
		lods	byte ptr ES_[si]
		or	al, al
		jz	short scn_respondJmp
		cmp	al, '%'
		jz	short scn_CONV

scn_percent:
		xor	ah, ah
		xchg	ax, di
		inc	[bp+@@charCt]
		scn_pushSrceP
		call	[bp+@@Get]
		popCX_
		pop	cx
		or	ax, ax
		jl	short scn_EOFjmp
		xor	ah, ah
		test	di, 80h
		jnz	short scn_mustMatch
		cmp	scanCtype[di], 1
		jnz	short scn_mustMatch

scn_matchSpace:
		xchg	ax, bx
		or	bl, bl
		js	short scn_spaceEnded
		cmp	scanCtype[bx], 1
		jnz	short scn_spaceEnded
		inc	[bp+@@charCt]
		scn_pushSrceP
		call	[bp+@@Get]
		popCX_
		pop	cx
		or	ax, ax
		jg	short scn_matchSpace

scn_EOFjmp:
		jmp	scn_EOF

scn_spaceEnded:
		scn_pushSrceP
		push	bx
		call	[bp+@@UnGet]
		add	sp, 2 + dPtrSize
		dec	[bp+@@charCt]
		jmp	short scn_nextChar

scn_mustMatch:
		cmp	ax, di
		jz	short scn_nextChar
		scn_pushSrceP
		push	ax
		call	[bp+@@UnGet]
		add	sp, 2 + dPtrSize
		dec	[bp+@@charCt]
		jmp	scn_END

scn_respondJmp:
		jmp	scn_END

scn_CONV:
		mov	[bp+@@width], -1
if LDATA
		mov	es, word ptr [bp+@@formP+2]
		mov	[bp+@@flags], isFarPtr
else
		mov	[bp+@@flags], 0
endif

scn_convNext:
		lods	byte ptr ES_[si]
		xor	ah, ah
		mov	word ptr [bp+@@formP], si
		or	al, al
		xchg	ax, di
		jl	short scn_anyOther
		mov	bl, scanCtype[di]
		xor	bh, bh
		cmp	bx, 15h
		jbe	short scn_switch
		jmp	scn_EOF

scn_switch:
		add	bx, bx
		jmp	cs:scn_table[bx]

scn_case_pc:
		xchg	ax, di
		jmp	scn_percent

scn_anyOther:
		jmp	scn_END

scn_case_su:
		or	[bp+@@flags], isSuppressed
		jmp	short scn_convNext

scn_case_nu:
		sub	di, '0'
		xchg	di, [bp+@@width]
		or	di, di
		jl	short scn_convNext
		mov	ax, 10
		mul	di
		add	[bp+@@width], ax
		jmp	short scn_convNext

scn_case_ld:
		or	[bp+@@flags], isLongDouble
		jmp	short scn_convNext

scn_case_lo:
		or	[bp+@@flags], isLong
		jmp	short scn_convNext

scn_case_ha:
		or	[bp+@@flags], isHalf
		jmp	short scn_convNext

scn_case_ne:
		and	[bp+@@flags], not isFarPtr
		jmp	short scn_convNext

scn_case_fa:
		or	[bp+@@flags], isFarPtr
		jmp	short scn_convNext

scn_case_ct:
		mov	ax, [bp+@@charCt]
		sub	dx, dx
		test	[bp+@@flags], isSuppressed
		jz	short scn_PUTINT
		jmp	scn_NEXT

scn_case_oc:
		mov	si, 8
		jmp	short scn_INT

scn_case_un_de:
		mov	si, 10
		jmp	short scn_INT

scn_case_he:
		mov	si, 16
		jmp	short scn_INT

scn_case_in:
		xor	si, si

scn_INT:
		test	di, 20h
		jnz	short scn_scantol
		cmp	di, 'X'
		jz	short scn_scantol
		or	[bp+@@flags], isLong

scn_scantol:
		pushSS_
		lea	ax, [bp+@@status]
		push	ax
		pushSS_
		lea	ax, [bp+@@charCt]
		push	ax
		mov	ax, [bp+@@width]
		and	ax, 7FFFh
		push	ax
		push	si
		scn_pushSrceP
		push	[bp+@@UnGet]
		push	[bp+@@Get]
		call	__scantol
		add	sp, 8 + (dPtrSize * 3)
		cmp	[bp+@@status], 0
		jle	short scn_intEnd
		test	[bp+@@flags], isSuppressed
		jnz	short scn_intUpdated
		inc	[bp+@@count]

scn_PUTINT:
		ScanNextArgPointer
		stosw
		test	[bp+@@flags], isLong
		jz	short scn_intUpdated
		xchg	ax, dx
		stosw

scn_intUpdated:
		jmp	scn_NEXT

scn_intEnd:
		jl	short scn_intEOF
		jmp	scn_END

scn_intEOF:
		jmp	scn_EOF

scn_case_pt:
		call	$+3
		jmp	scn_SkipSpace
		scn_pushSrceP
		push	ax
		call	[bp+@@UnGet]
		add	sp, 2 + dPtrSize
		dec	[bp+@@charCt]
		and	[bp+@@width], 7FFFh
		call	$+3
		jmp	scn_InHex4
		push	dx
		cmp	al, ':'
		jz	short scn_ptrLSW
		or	ax, ax
		jle	short scn_noLookAhead
		scn_pushSrceP
		push	ax
		call	[bp+@@UnGet]
		add	sp, 2 + dPtrSize
		dec	[bp+@@charCt]

scn_noLookAhead:
		pop	dx
		mov	bx, ds
		jmp	short scn_pointerReady

scn_ptrLSW:
		call	$+3
		jmp	scn_InHex4
		pop	bx
		or	ax, ax
		jle	short scn_pointerReady
		push	dx
		push	bx
		scn_pushSrceP
		push	ax
		call	[bp+@@UnGet]
		add	sp, 2 + dPtrSize
		dec	[bp+@@charCt]
		pop	bx
		pop	dx

scn_pointerReady:
		test	[bp+@@flags], isSuppressed
		jnz	short scn_ptrUpdated
		ScanNextArgPointer
		inc	[bp+@@count]
		xchg	ax, dx
		stosw
		test	[bp+@@flags], isFarPtr
		jz	short scn_ptrUpdated
		xchg	ax, bx
		stosw

scn_ptrUpdated:
		jmp	scn_NEXT

scn_jmpEOF:
		jmp	scn_EOF

scn_case_fl:
		pushSS_
		lea	ax, [bp+@@status]
		push	ax
		pushSS_
		lea	ax, [bp+@@charCt]
		push	ax
		mov	ax, 7FFFh
		and	ax, [bp+@@width]
		push	ax
		scn_pushSrceP
		push	[bp+@@UnGet]
		push	[bp+@@Get]
		call	_scantod
		add	sp, (3 * dPtrSize) + 2 + (2 * 2)
		cmp	[bp+@@status], 0
		jle	short scn_endFloat
		mov	al, [bp+@@flags]
		cbw
		test	al, isSuppressed
		jnz	short scn_popFloat
		ScanNextArgPointer
		inc	[bp+@@count]
		test	[bp+@@flags], isLong
		jz	short test_longDOuble
		mov	ax, isLong
		jmp	short push_type

test_longDOuble:
		test	[bp+@@flags], isLongDouble
		jz	short its_default_float
		mov	ax, isLongDouble
		jmp	short push_type

its_default_float:
		xor	ax, ax

push_type:
		push	ax
		test	[bp+@@flags], isFarPtr
		jz	short push_far
		push	es
		jmp	short scn_scanrslt

push_far:
		push	ds

scn_scanrslt:
		push	di
		call	_scanrslt
		add	sp, 6
		jmp	scn_NEXT

scn_popFloat:
		call	_scanpop
		jmp	scn_NEXT

scn_endFloat:
		call	_scanpop
		jl	short scn_jmpEOF
		jmp	scn_END

scn_case_st:
		call	$+3
		jmp	scn_SkipSpace
		test	[bp+@@flags], isSuppressed
		jnz	short scn_tokenWidth
		ScanNextArgPointer
		inc	[bp+@@count]

scn_tokenWidth:
		and	[bp+@@width], 7FFFh
		jz	short scn_tokenEnd

scn_whileToken:
		test	[bp+@@flags], isSuppressed
		jnz	short scn_tokenNextCh
		stosb

scn_tokenNextCh:
		inc	[bp+@@charCt]
		push	es
		scn_pushSrceP
		call	[bp+@@Get]
		popCX_
		pop	cx
		pop	es
		or	ax, ax
		jle	short scn_tokenEnd
		or	al, al
		js	short scn_isToken
		xchg	ax, bx
		cmp	scanCtype[bx], 1
		xchg	ax, bx
		jle	short scn_tokenEnd

scn_isToken:
		dec	[bp+@@width]
		jg	short scn_whileToken

scn_tokenEnd:
		push	es
		scn_pushSrceP
		push	ax
		call	[bp+@@UnGet]
		add	sp, 2 + dPtrSize
		pop	es
		dec	[bp+@@charCt]
		test	[bp+@@flags], isSuppressed
		jnz	short scn_tokenUpdated
		mov	al, 0
		stosb

scn_tokenUpdated:
		jmp	scn_NEXT

scn_case_ch:
		test	[bp+@@flags], isSuppressed
		jnz	short scn_checkWidth
		ScanNextArgPointer

scn_checkWidth:
		mov	si, [bp+@@width]
		or	si, si
		jge	short scn_charWidened
		mov	si, 1

scn_charWidened:
		jz	short scn_charEnd

scn_charLoop:
		inc	[bp+@@charCt]
		push	es
		scn_pushSrceP
		call	[bp+@@Get]
		popCX_
		pop	cx
		pop	es
		or	ax, ax
		jl	short scn_charEOF
		test	[bp+@@flags], isSuppressed
		jnz	short scn_charNoPut
		stosb

scn_charNoPut:
		dec	si
		jg	short scn_charLoop

scn_charEnd:
		test	[bp+@@flags], isSuppressed
		jnz	short scn_charNext
		inc	[bp+@@count]

scn_charNext:
		jmp	scn_NEXT

scn_charEOF:
		jmp	scn_EOF

scn_case_sc:
if LDATA
		push	es
endif
		sub	ax, ax
		cld
		push	ss
		pop	es
		lea	di, [bp+@@bitSet]
		mov	cx, 16
		rep stosw
if LDATA
		pop	es
endif
		lods	byte ptr ES_[si]
		and	[bp+@@flags], not isExclusive
		cmp	al, '^'
		jnz	short scn_scanInc
		or	[bp+@@flags], isExclusive
		lods	byte ptr ES_[si]

scn_scanInc:
		mov	ah, 0

scn_scanSetBit:
		mov	dl, al
		mov	di, ax
		mov	cl, 3
		shr	di, cl
		mov	cx, 107h
		and	cl, dl
		shl	ch, cl
		or	[bp+di+@@bitSet], ch

scn_setNext:
		lods	byte ptr ES_[si]
		cmp	al, 0
		jz	short scn_scanOpen
		cmp	al, ']'
		jz	short scn_scanBounded
		cmp	al, '-'
		jnz	short scn_scanSetBit
		cmp	dl, ES_[si]
		ja	short scn_scanSetBit
		cmp	byte ptr ES_[si], ']'
		jz	short scn_scanSetBit
		lods	byte ptr ES_[si]
		sub	al, dl
		jz	short scn_setNext
		add	dl, al

scn_setRange:
		rol	ch, 1
		adc	di, 0
		or	[bp+di+@@bitSet], ch
		dec	al
		jnz	short scn_setRange
		jmp	short scn_setNext

scn_scanOpen:
		jmp	scn_END

scn_scanBounded:
		mov	word ptr [bp+@@formP], si
		and	[bp+@@width], 7FFFh
		mov	si, [bp+@@width]
		test	[bp+@@flags], isSuppressed
		jnz	short scn_scanLoop
		ScanNextArgPointer

scn_scanLoop:
		dec	si
		jl	short scn_scanLimited
		inc	[bp+@@charCt]
		push	es
		scn_pushSrceP
		call	[bp+@@Get]
		popCX_
		pop	cx
		pop	es
		or	ax, ax
		jl	short scn_scanEOF
		xchg	ax, si
		mov	bx, si
		mov	cl, 3
		shr	si, cl
		mov	cx, 107h
		and	cl, bl
		shl	ch, cl
		test	[bp+si+@@bitSet], ch
		xchg	ax, si
		xchg	ax, bx
		jz	short scn_scanNotIn
		test	[bp+@@flags], isExclusive
		jz	short scn_scanAccept
		jmp	short scn_scanTerminate

scn_scanNotIn:
		test	[bp+@@flags], isExclusive
		jz	short scn_scanTerminate

scn_scanAccept:
		test	[bp+@@flags], isSuppressed
		jnz	short scn_scanLoop
		stosb
		jmp	short scn_scanLoop

scn_scanTerminate:
		push	es
		scn_pushSrceP
		push	ax
		call	[bp+@@UnGet]
		add	sp, 2 + dPtrSize
		pop	es
		dec	[bp+@@charCt]
		inc	si
		cmp	si, [bp+@@width]
		jge	short scn_scanEND

scn_scanLimited:
		test	[bp+@@flags], isSuppressed
		jnz	short scn_scanUpdated
		inc	[bp+@@count]

scn_scanEND:
		test	[bp+@@flags], isSuppressed
		jnz	short scn_scanUpdated
		mov	al, 0
		stosb

scn_scanUpdated:
		jmp	scn_NEXT

scn_scanEOF:
		inc	si
		cmp	si, [bp+@@width]
		jge	short scn_EOF
		test	[bp+@@flags], isSuppressed
		jnz	short scn_EOF
		mov	al, 0
		stosb
		inc	[bp+@@count]

scn_EOF:
		scn_pushSrceP
		mov	ax, EOF
		push	ax
		call	[bp+@@UnGet]
		add	sp, 2 + dPtrSize
		cmp	[bp+@@count], 1
		sbb	[bp+@@count], 0

scn_END:
		pop	es
		mov	ax, [bp+@@count]
		jmp	scn_ret

scn_SkipSpace:
		inc	[bp+@@charCt]
		scn_pushSrceP
		call	[bp+@@Get]
		popCX_
		pop	cx
		or	ax, ax
		jle	short scn_skipEOF
		or	al, al
		js	short scn_skipEnd
		xchg	ax, bx
		cmp	scanCtype[bx], 1
		xchg	ax, bx
		jz	short scn_SkipSpace

scn_skipEnd:
		pop	cx
		add	cx, 3
		jmp	cx

scn_skipEOF:
		jz	short scn_skipEnd
		pop	cx
		jmp	short scn_EOF

scn_InHex4:
		sub	dx, dx
		mov	cx, 4

scn_h4loop:
		dec	[bp+@@width]
		jl	short scn_h4limited
		push	dx
		push	cx
		inc	[bp+@@charCt]
		scn_pushSrceP
		call	[bp+@@Get]
		popCX_
		pop	cx
		pop	cx
		pop	dx
		or	ax, ax
		jle	short scn_h4end
		dec	cl
		jl	short scn_h4end
		mov	ch, al
		sub	ch, '0'
		jb	short scn_h4end
		cmp	ch, 10
		jb	short scn_h4isDigit
		sub	ch, 'A' - '0'
		jb	short scn_h4end
		cmp	ch, 6
		jb	short scn_h4isHex
		sub	ch, 'a' - 'A'
		jb	short scn_h4end
		cmp	ch, 6
		jnb	short scn_h4end

scn_h4isHex:
		add	ch, 10

scn_h4isDigit:
		shl	dx, 1
		shl	dx, 1
		shl	dx, 1
		shl	dx, 1
		add	dl, ch
		jmp	short scn_h4loop

scn_h4limited:
		sub	ax, ax

scn_h4end:
		cmp	cl, 4
		jz	short scn_h4eof
		pop	cx
		add	cx, 3
		jmp	cx

scn_h4eof:
		pop	cx
		jmp	scn_EOF

scn_ret:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret
_scanner	endp

scn_table	dw offset scn_END
		dw offset scn_END
		dw offset scn_END
		dw offset scn_case_pc
		dw offset scn_case_su
		dw offset scn_case_nu
		dw offset scn_case_ch
		dw offset scn_case_un_de
		dw offset scn_case_un_de
		dw offset scn_case_in
		dw offset scn_case_fl
		dw offset scn_case_ld
		dw offset scn_case_ha
		dw offset scn_case_lo
		dw offset scn_case_oc
		dw offset scn_case_st
		dw offset scn_case_sc
		dw offset scn_case_ct
		dw offset scn_case_he
		dw offset scn_case_pt
		dw offset scn_case_ne
		dw offset scn_case_fa

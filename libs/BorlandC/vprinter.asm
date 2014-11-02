Ssize		 = 50h

; enum flagBits
altFormatBit	 = 1
leftJustBit	 = 2
notZeroBit	 = 4
fillZerosBit	 = 8
isLongBit	 = 10h
farPtrBit	 = 20h
alt0xBit	 = 40h
floatBit	 = 80h
LongDoubleBit	 = 100h

; enum syntaxStages
flagStage	 = 0
fillzStage	 = 1
wideStage	 = 2
dotStage	 = 3
precStage	 = 4
ellStage	 = 5
typeStage	 = 6

Hex4		proc near
		mov	al, dh
		call	Byte2Ascii
		mov	al, dl

Byte2Ascii:
		aam	10h
		xchg	ah, al
		call	Nibble2Ascii
		xchg	ah, al

Nibble2Ascii:
		add	al, 90h
		daa
		adc	al, 40h
		daa
		stosb
		ret
Hex4		endp

; int __pascal __near _vprinter(void * near *putter, void *outP, const char *formP, void *argP)
		public __vprinter
__vprinter	proc near
@@S		= byte ptr -(16h + __CVTMAX__ + Ssize)
@@tempStr	= byte ptr -(16h + __CVTMAX__)
@@eof_error	= word ptr -16h
@@Scount	= word ptr -14h
@@totalSent	= word ptr -12h
@@abandonP	= word ptr -10h
@@leadZ		= word ptr -0Eh
@@plusSign	= byte ptr -0Bh
@@precision	= word ptr -0Ah
@@width		= word ptr -8
@@isSigned	= byte ptr -6
@@fc		= byte ptr -5
@@aP		= word ptr -4
@@flagSet	= word ptr -2
@@argP		= word ptr  4
@@formP		= DPTR_ 6
@@outP		= DPTR_ (6 + dPtrSize)
@@putter	= word ptr (6 + dPtrSize + dPtrSize)

		push	bp
		mov	bp, sp
		sub	sp, (16h + __CVTMAX__ + Ssize)
		push	si
		push	di
		mov	[bp+@@totalSent], 0
		mov	[bp+@@Scount], Ssize
		mov	[bp+@@eof_error], 0
		jmp	short func_start

vpr_strlen:
		push	di
		mov	cx, -1
		xor	al, al
		repne scasb
		not	cx
		dec	cx
		pop	di
		retn

vpr_PutToS:
		mov	ss:[di], al
		inc	di
		dec	byte ptr [bp+@@Scount]
		jnz	short exit_PutToS

vpr_CallPutter:
		push	bx
		push	cx
		push	dx
		push	es
		lea	ax, [bp+@@S]
		sub	di, ax
		push	ss
		lea	ax, [bp+@@S]
		push	ax
		push	di
if LDATA
		push	word ptr [bp+@@outP+2]
endif
		push	word ptr [bp+@@outP]
		call	[bp+@@putter]
		or	ax, ax
		jnz	short vpr_CallPutter_end
		mov	[bp+@@eof_error], 1

vpr_CallPutter_end:
		mov	[bp+@@Scount], Ssize
		add	[bp+@@totalSent], di
		lea	di, [bp+@@S]
		pop	es
		pop	dx
		pop	cx
		pop	bx

exit_PutToS:
		retn

func_start:
		push	es
		cld
		lea	di, [bp+@@S]
		mov	[bp+@@aP], di

vpr_NEXTap:
		mov	di, [bp+@@aP]

vpr_NEXT:
		les	si, [bp+@@formP]

vpr_nextCh:
		lods	byte ptr ES_[si]
		or	al, al
		jz	short vpr_respondJmp
		cmp	al, '%'
		jz	short vpr_CONV

vpr_literal:
		mov	ss:[di], al
		inc	di
		dec	byte ptr [bp+@@Scount]
		jg	short vpr_nextCh
		call	vpr_CallPutter
		jmp	short vpr_nextCh

vpr_respondJmp:
		jmp	vpr_respond

vpr_CONV:
		mov	[bp+@@abandonP], si
		lods	byte ptr ES_[si]
		cmp	al, '%'
		jz	short vpr_literal
		mov	[bp+@@aP], di
		xor	cx, cx
		mov	[bp+@@leadZ], cx
if LDATA
		mov	[bp+@@flagSet],	farPtrBit
else
		mov	[bp+@@flagSet],	cx
endif
		mov	[bp+@@plusSign], cl
		mov	[bp+@@width], -1
		mov	[bp+@@precision], -1
		jmp	short vpr_doSwitch

vpr_nextSwitch:
		lods	byte ptr ES_[si]

vpr_doSwitch:
		xor	ah, ah
		mov	dx, ax
		mov	bx, ax
		sub	bl, ' '
		cmp	bl, 128	- ' '
		jnb	short vpr_jmpAbandon
		mov	bl, printCtype[bx]
		cmp	bx, 17h
		jbe	short vpr_switch
		jmp	vpr_abandon

vpr_switch:
		add	bx, bx
		jmp	cs:vpr_table[bx]

vpr_jmpAbandon:
		jmp	vpr_abandon

vpr_case_af:
		cmp	ch, 0
		ja	short vpr_jmpAbandon
		or	[bp+@@flagSet],	altFormatBit
		jmp	short vpr_nextSwitch

vpr_case_lj:
		cmp	ch, 0
		ja	short vpr_jmpAbandon
		or	[bp+@@flagSet],	leftJustBit
		jmp	short vpr_nextSwitch

vpr_case_si:
		cmp	ch, 0
		ja	short vpr_jmpAbandon
		cmp	[bp+@@plusSign], '+'
		jz	short gtvp_nxt_swit
		mov	[bp+@@plusSign], dl

gtvp_nxt_swit:
		jmp	short vpr_nextSwitch

vpr_case_ne:
		and	[bp+@@flagSet],	not farPtrBit
		jmp	short ell_stagetail

vpr_case_fa:
		or	[bp+@@flagSet],	farPtrBit

ell_stagetail:
		mov	ch, ellStage
		jmp	short vpr_nextSwitch

vpr_case_fz:
		cmp	ch, flagStage
		ja	short vpr_case_nu
		test	[bp+@@flagSet],	leftJustBit
		jnz	short vpr_nextSwitchJmp
		or	[bp+@@flagSet],	fillZerosBit
		mov	ch, fillzStage
		jmp	short vpr_nextSwitch

vpr_abandonJmp:
		jmp	vpr_abandon

vpr_case_ar:
		mov	di, [bp+@@argP]
		mov	ax, ss:[di]
		add	[bp+@@argP], 2
		cmp	ch, wideStage
		jnb	short vpr_argPrec
		or	ax, ax
		jns	short vpr_pos
		neg	ax
		or	[bp+@@flagSet],	leftJustBit

vpr_pos:
		mov	[bp+@@width], ax
		mov	ch, wideStage +	1

vpr_nextSwitchJmp:
		jmp	vpr_nextSwitch

vpr_argPrec:
		cmp	ch, precStage
		jnz	short vpr_abandonJmp
		mov	[bp+@@precision], ax
		inc	ch
		jmp	vpr_nextSwitch

vpr_case_pr:
		cmp	ch, precStage
		jnb	short vpr_abandonJmp
		mov	ch, precStage
		inc	[bp+@@precision]
		jmp	vpr_nextSwitch

vpr_case_nu:
		xchg	ax, dx
		sub	al, '0'
		cbw
		cmp	ch, wideStage
		ja	short vpr_precNumeral
		mov	ch, wideStage
		xchg	ax, [bp+@@width]
		or	ax, ax
		jl	short vpr_nextSwitchJmp
		shl	ax, 1
		mov	dx, ax
		shl	ax, 1
		shl	ax, 1
		add	ax, dx
		add	[bp+@@width], ax
		jmp	vpr_nextSwitch

vpr_precNumeral:
		cmp	ch, precStage
		jnz	short vpr_abandonJmp
		xchg	ax, [bp+@@precision]
		or	ax, ax
		jz	short vpr_nextSwitchJmp
		shl	ax, 1
		mov	dx, ax
		shl	ax, 1
		shl	ax, 1
		add	ax, dx
		add	[bp+@@precision], ax
		jmp	vpr_nextSwitch

vpr_case_lo:
		or	[bp+@@flagSet],	isLongBit
		jmp	ell_stagetail

vpr_case_ld:
		or	[bp+@@flagSet],	LongDoubleBit

vpr_case_sh:
		and	[bp+@@flagSet],	not isLongBit
		jmp	ell_stagetail

vpr_case_oc:
		mov	bh, 8
		jmp	short vpr_NoSign

vpr_case_un:
		mov	bh, 10
		jmp	short vpr_NoSign

vpr_case_he:
		mov	bh, 10h
		mov	bl, 'A' - 'X'
		add	bl, dl

vpr_NoSign:
		mov	[bp+@@plusSign], 0
		mov	[bp+@@fc], dl
		xor	dx, dx
		mov	[bp+@@isSigned], dl
		mov	di, [bp+@@argP]
		mov	ax, ss:[di]
		jmp	short vpr_toAscii

vpr_case_de:
		mov	bh, 10
		mov	[bp+@@isSigned], 1
		mov	[bp+@@fc], dl
		mov	di, [bp+@@argP]
		mov	ax, ss:[di]
		cwd

vpr_toAscii:
		inc	di
		inc	di
		mov	word ptr [bp+@@formP], si
		test	[bp+@@flagSet],	isLongBit
		jz	short vpr_shortInt
		mov	dx, ss:[di]
		inc	di
		inc	di

vpr_shortInt:
		mov	[bp+@@argP], di
		lea	di, [bp+@@tempStr+1]
		or	ax, ax
		jnz	short vpr_flag_nz
		or	dx, dx
		jnz	short vpr_flag_nz
		cmp	[bp+@@precision], 0
		jnz	short vpr_flag_zr
		mov	byte ptr ss:[di], 0
		mov	ax, di
		jmp	short vpr_converted

vpr_flag_nz:
		or	[bp+@@flagSet],	notZeroBit

vpr_flag_zr:
		push	dx
		push	ax
		push	ss
		push	di
		mov	al, bh
		cbw
		push	ax
		mov	al, [bp+@@isSigned]
		push	ax
		push	bx
		call	__LONGTOA

vpr_converted:
		push	ss
		pop	es
		mov	dx, [bp+@@precision]
		or	dx, dx
		jge	short vpr_countActualJmp
		jmp	vpr_testFillZeros

vpr_countActualJmp:
		jmp	vpr_countActual

vpr_case_at:
		mov	[bp+@@fc], dl
		mov	word ptr [bp+@@formP], si
		lea	di, [bp+@@tempStr]
		mov	bx, [bp+@@argP]
		push	word ptr ss:[bx]
		inc	bx
		inc	bx
		mov	[bp+@@argP], bx
		test	[bp+@@flagSet],	farPtrBit
		jz	short vpr_ptrLSW
		mov	dx, ss:[bx]
		inc	bx
		inc	bx
		mov	[bp+@@argP], bx
		push	ss
		pop	es
		call	Hex4
		mov	al, ':'
		stosb

vpr_ptrLSW:
		push	ss
		pop	es
		pop	dx
		call	Hex4
		mov	byte ptr ss:[di], 0
		mov	[bp+@@isSigned], 0
		and	[bp+@@flagSet],	not notZeroBit
		lea	cx, [bp+@@tempStr]
		sub	di, cx
		xchg	cx, di
		mov	dx, [bp+@@precision]
		cmp	dx, cx
		jg	short vpr_ptrEnd
		mov	dx, cx

vpr_ptrEnd:
		jmp	vpr_testFillZeros

vpr_case_ch:
		mov	word ptr [bp+@@formP], si
		mov	[bp+@@fc], dl
		mov	di, [bp+@@argP]
		mov	ax, ss:[di]
		add	[bp+@@argP], 2
		push	ss
		pop	es
		lea	di, [bp+@@tempStr+1]
		xor	ah, ah
		mov	ss:[di], ax
		mov	cx, 1
		jmp	vpr_CopyLen

vpr_case_st:
		mov	word ptr [bp+@@formP], si
		mov	[bp+@@fc], dl
		mov	di, [bp+@@argP]
		test	[bp+@@flagSet],	20h
		jnz	short vpr_farString
		mov	di, ss:[di]
		add	[bp+@@argP], 2
		push	ds
		pop	es
		assume es:DGROUP
		or	di, di
		jmp	short vpr_countString

vpr_farString:
		les	di, ss:[di]
		assume es:nothing
		add	[bp+@@argP], 4
		mov	ax, es
		or	ax, di

vpr_countString:
		jnz	short NotaNullPtr
		push	ds
		pop	es
		assume es:DGROUP
		mov	di, offset NullString

NotaNullPtr:
		call	vpr_strlen
		cmp	cx, [bp+@@precision]
		jbe	short vpr_CopyLenJmp
		mov	cx, [bp+@@precision]

vpr_CopyLenJmp:
		jmp	vpr_CopyLen

vpr_case_fl:
		mov	word ptr [bp+@@formP], si
		mov	[bp+@@fc], dl
		mov	di, [bp+@@argP]
		mov	cx, [bp+@@precision]
		or	cx, cx
		jge	short vpr_cvtReal
		mov	cx, 6

vpr_cvtReal:
		pushSS_
		push	di
		push	cx
		pushSS_
		lea	bx, [bp+@@tempStr+1]
		push	bx
		push	dx
		mov	ax, 1
		and	ax, [bp+@@flagSet]
		push	ax
		mov	ax, [bp+@@flagSet]
		test	ax, LongDoubleBit
		jz	short its_plain_double
		mov	ax, F_10byteFloat
		add	[bp+@@argP], 10
		jmp	short push_argtype

its_plain_double:
		add	[bp+@@argP], 8
		mov	ax, F_8ByteFloat

push_argtype:
		push	ax
		call	__realcvt
		push	ss
		pop	es
		assume es:nothing
		lea	di, [bp+@@tempStr+1]

vpr_testFillZeros:
		test	[bp+@@flagSet],	fillZerosBit
		jz	short vpr_NUMERIC
		mov	dx, [bp+@@width]
		or	dx, dx
		jle	short vpr_NUMERIC

vpr_countActual:
		call	vpr_strlen
		cmp	byte ptr es:[di], '-'
		jnz	short vpr_noSignAdjust
		dec	cx

vpr_noSignAdjust:
		sub	dx, cx
		jle	short vpr_NUMERIC
		mov	[bp+@@leadZ], dx

vpr_NUMERIC:
		cmp	byte ptr es:[di], '-'
		jz	short vpr_AdjustLeadZ
		mov	al, [bp+@@plusSign]
		or	al, al
		jz	short vpr_COPY
		dec	di
		mov	es:[di], al

vpr_AdjustLeadZ:
		cmp	[bp+@@leadZ], 0
		jle	short vpr_COPY
		mov	cx, [bp+@@precision]
		or	cx, cx
		jge	short vpr_COPY
		dec	[bp+@@leadZ]

vpr_COPY:
		call	vpr_strlen

vpr_CopyLen:
		mov	si, di
		mov	di, [bp+@@aP]
		mov	bx, [bp+@@width]
		mov	ax, notZeroBit + altFormatBit
		and	ax, [bp+@@flagSet]
		cmp	ax, notZeroBit + altFormatBit
		jnz	short goto_doLead
		mov	ah, [bp+@@fc]
		cmp	ah, 'o'
		jnz	short vpr_maybeAltHex
		cmp	[bp+@@leadZ], 0
		jg	short goto_doLead
		mov	[bp+@@leadZ], 1

goto_doLead:
		jmp	short vpr_doLead

vpr_maybeAltHex:
		cmp	ah, 'x'
		jz	short vpr_isAltHex
		cmp	ah, 'X'
		jnz	short vpr_doLead

vpr_isAltHex:
		or	[bp+@@flagSet],	alt0xBit
		dec	bx
		dec	bx
		sub	[bp+@@leadZ], 2
		jge	short vpr_doLead
		mov	[bp+@@leadZ], 0

vpr_doLead:
		add	cx, [bp+@@leadZ]
		test	[bp+@@flagSet],	leftJustBit
		jnz	short vpr_check0x
		jmp	short vpr_nextJust

vpr_justLoop:
		mov	al, ' '
		call	vpr_PutToS
		dec	bx

vpr_nextJust:
		cmp	bx, cx
		jg	short vpr_justLoop

vpr_check0x:
		test	[bp+@@flagSet],	alt0xBit
		jz	short vpr_checkLeadZ
		mov	al, '0'
		call	vpr_PutToS
		mov	al, [bp+@@fc]
		call	vpr_PutToS

vpr_checkLeadZ:
		mov	dx, [bp+@@leadZ]
		or	dx, dx
		jle	short vpr_actualCopy
		sub	cx, dx
		sub	bx, dx
		mov	al, es:[si]
		cmp	al, '-'
		jz	short vpr_leadSign
		cmp	al, ' '
		jz	short vpr_leadSign
		cmp	al, '+'
		jnz	short vpr_signedLead

vpr_leadSign:
		lods	byte ptr es:[si]
		call	vpr_PutToS
		dec	cx
		dec	bx

vpr_signedLead:
		xchg	cx, dx
		jcxz	short vpr_leadDone

vpr_leadZero:
		mov	al, '0'
		call	vpr_PutToS
		loop	vpr_leadZero

vpr_leadDone:
		xchg	cx, dx

vpr_actualCopy:
		jcxz	short vpr_copied
		sub	bx, cx

vpr_copyLoop:
		lods	byte ptr es:[si]
		mov	ss:[di], al
		inc	di
		dec	byte ptr [bp+@@Scount]
		jg	short vpr_loopTest
		call	vpr_CallPutter

vpr_loopTest:
		loop	vpr_copyLoop

vpr_copied:
		or	bx, bx
		jle	short vpr_done
		mov	cx, bx

vpr_rightLoop:
		mov	al, ' '
		call	vpr_PutToS
		loop	vpr_rightLoop

vpr_done:
		jmp	vpr_NEXT

vpr_case_ns:
		mov	word ptr [bp+@@formP], si
		mov	di, [bp+@@argP]
		test	[bp+@@flagSet],	farPtrBit
		jnz	short vpr_farCount
ifdef __HUGE__
		jmp	vpr_abandonJmp
else
		mov	di, ss:[di]
		add	[bp+@@argP], 2
		push	ds
		pop	es
		jmp	short vpr_makeCount
endif
vpr_farCount:
		les	di, ss:[di]
		assume es:nothing
		add	[bp+@@argP], 4

vpr_makeCount:
		mov	ax, Ssize
		sub	al, byte ptr [bp+@@Scount]
		add	ax, [bp+@@totalSent]
		mov	es:[di], ax
		test	[bp+@@flagSet],	isLongBit
		jz	short vpr_shortN
		inc	di
		inc	di
		mov	word ptr es:[di], 0

vpr_shortN:
		jmp	vpr_NEXTap

vpr_abandon:
		mov	si, [bp+@@abandonP]
if LDATA
endif
		mov	es, word ptr [bp+@@formP+2]
		mov	di, [bp+@@aP]
		mov	al, '%'

vpr_abandLoop:
		call	vpr_PutToS
		lods	byte ptr es:[si]
		or	al, al
		jnz	short vpr_abandLoop

vpr_respond:
		cmp	byte ptr [bp+@@Scount],	Ssize
		jge	short vpr_end
		call	vpr_CallPutter

vpr_end:
		pop	es
		cmp	[bp+@@eof_error], 0
		jz	short vpr_ret_totalSent
		mov	ax, EOF
		jmp	short vpr_ret

vpr_ret_totalSent:
		mov	ax, [bp+@@totalSent]

vpr_ret:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret	0Ch
__vprinter	endp

vpr_table	dw offset vpr_case_si
		dw offset vpr_case_af
		dw offset vpr_case_ar
		dw offset vpr_case_lj
		dw offset vpr_case_pr
		dw offset vpr_case_nu
		dw offset vpr_case_lo
		dw offset vpr_case_ld
		dw offset vpr_case_sh
		dw offset vpr_case_fz
		dw offset vpr_case_de
		dw offset vpr_case_oc
		dw offset vpr_case_un
		dw offset vpr_case_he
		dw offset vpr_case_at
		dw offset vpr_case_fl
		dw offset vpr_case_ch
		dw offset vpr_case_st
		dw offset vpr_case_ns
		dw offset vpr_abandon
		dw offset vpr_abandon
		dw offset vpr_abandon
		dw offset vpr_case_ne
		dw offset vpr_case_fa

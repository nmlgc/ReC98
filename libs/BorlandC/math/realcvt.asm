  __turboCvt   = 0
  public __turboCvt

; void __near TrimTrailing(void)
TrimTrailing	proc near
		push	bp
		mov	bp, sp
		mov	al, 5Fh
		and	al, dl
		cmp	al, 'G'
		jnz	short @@tt_trimPoint

@@tt_trimLoop:
		cmp	byte ptr ES_[bx-1], '0'
		jnz	short @@tt_trimPoint
		dec	bx
		cmp	bx, cx
		ja	short @@tt_trimLoop
		jmp	short @@tt_trimmed

@@tt_trimPoint:
		cmp	ES_[bx-1], ah
		jnz	short @@tt_trimmed
		dec	bx

@@tt_trimmed:
		pop	bp
		ret
TrimTrailing	endp

; void __pascal	__near __realcvt(void *valueP, int ndec, char *strP, char formCh, char altFormat, int type)
___realcvt	proc near
@@buf		= byte ptr -(6 + __XCVTDIG__ + 4)
@@localeDot	= byte ptr -5
@@realcnt	= word ptr -4
@@sign		= word ptr -2
@@type		= word ptr  4
@@altFormat	= byte ptr  6
@@formCh	= byte ptr  8
@@strP		= dword	ptr  0Ah
@@ndec		= word ptr  0Eh
@@valueP	= dword	ptr  10h

		push	bp
		mov	bp, sp
		sub	sp, 6 + __XCVTDIG__ + 4
		push	si
		push	di
		LES_	bx, __localeconvention
		mov	al, ES_[bx]
		mov	[bp+@@localeDot], al
		push	es
ife LDATA
		push	ds
		pop	es
endif
		mov	ax, [bp+@@ndec]
		cmp	ax, __XCVTDIG__
		jbe	short @@meaningful
		mov	ax, __XCVTDIG__
		mov	[bp+@@ndec], ax

@@meaningful:
		mov	[bp+@@realcnt],	ax
		mov	dl, [bp+@@formCh]
		and	dl, 0DFh
		cmp	dl, 'F'
		jnz	short @@overallDigits
		neg	ax
		jle	short @@bounded
		sub	ax, ax
		mov	[bp+@@ndec], ax
		jmp	short @@bounded

@@overallDigits:
		or	ax, ax
		jg	short @@bounded
		mov	ax, 1
		jmp	short @@decimalsDecided

@@bounded:
		cmp	dl, 'E'
		jnz	short @@decimalsDecided
		inc	ax
		inc	[bp+@@ndec]

@@decimalsDecided:
if LDATA
		push	word ptr [bp+@@valueP+2]
endif
		push	word ptr [bp+@@valueP]
		push	ax
		pushSS_
		lea	bx, [bp+@@sign]
		push	bx
		pushSS_
		lea	si, [bp+@@buf]
		push	si
		mov	ax, [bp+@@type]
		push	ax
		call	___xcvt
		xchg	ax, bx
		LES_	di, [bp+@@strP]
		cld
		cmp	bx, INF_number
		jz	short @@infinities
		cmp	bx, NAN_number
		jz	short @@NANs
		jmp	short @@regular_number

@@infinities:
		mov	ax, 492Bh
		cmp	[bp+@@sign], 0
		jz	short @@store_Isign
		inc	ax
		inc	ax

@@store_Isign:
		stosw
		mov	ax, 464Eh
		stosw
		jmp	@@end

@@NANs:
		mov	ax, 4E2Bh
		cmp	[bp+@@sign], 0
		jz	short @@store_Nsign
		inc	ax
		inc	ax

@@store_Nsign:
		stosw
		mov	al, 'A'
		stosw
		jmp	@@end

@@regular_number:
		cmp	byte ptr [bp+@@sign], 0
		jz	short @@signSet
		mov	al, '-'
		stosb

@@signSet:
		mov	dl, [bp+@@formCh]
		and	dl, 5Fh
		cmp	dl, 'F'
		jz	short @@F_format
		cmp	dl, 'E'
		jz	short @@E_format
		cmp	bx, -3
		jl	short @@E_format
		mov	ax, [bp+@@ndec]
		or	ax, ax
		jnz	short @@NotZero
		inc	ax

@@NotZero:
		cmp	bx, ax
		jg	short @@E_format

@@F_format:
		cmp	bx, __XCVTDIG__
		jg	short @@E_format
		or	bx, bx
		jg	short @@FdigitStart
		mov	ah, [bp+@@localeDot]
		mov	al, '0'
		stosw
		mov	cx, 1
		jz	short @@Fdigits
		mov	al, '0'

@@FleadZeroes:
		stosb
		inc	bx
		jnz	short @@FleadZeroes

@@FdigitStart:
		mov	cx, 0

@@Fdigits:
		lods	byte ptr SS_[si]
		or	al, al
		jz	short @@Fend
		stosb
		dec	bx
		jnz	short @@Fdigits
		mov	al, [bp+@@localeDot]
		stosb
		inc	cx
		jmp	short @@Fdigits

@@Fend:
		mov	ax, [bp+@@ndec]
		add	cx, [bp+@@realcnt]
		cmp	ax, cx
		jbe	short @@no_zero_pad
		sub	ax, cx
		mov	cx, ax
		add	bx, ax
		mov	al, '0'
		rep stosb
		dec	bx
		jz	short @@Fz

@@no_zero_pad:
		dec	bx
		jz	short @@Fz
		cmp	[bp+@@altFormat], 0
		jnz	short @@Fz
		mov	dl, [bp+@@formCh]
		mov	cx, word ptr [bp+@@strP]
		xchg	bx, di
		mov	ah, [bp+@@localeDot]
		call	TrimTrailing
		xchg	di, bx

@@Fz:
		cmp	di, word ptr [bp+@@strP]
		jnz	short @@goto_end
		mov	al, '0'
		stosb

@@goto_end:
		jmp	short @@end

@@E_format:
		lods	word ptr SS_[si]
		stosb
		mov	al, [bp+@@localeDot]
		or	ah, ah
		jnz	short @@Edecimal
		cmp	[bp+@@altFormat], 0
		jz	short @@Eexp
		stosb
		jmp	short @@Eexp

@@Edecimal:
		stosb
		mov	al, ah

@@Edigits:
		stosb
		lods	byte ptr SS_[si]
		or	al, al
		jnz	short @@Edigits
		cmp	[bp+@@altFormat], 0
		jnz	short @@Eexp
		mov	dl, [bp+@@formCh]
		mov	cx, word ptr [bp+@@strP]
		xchg	bx, di
		mov	ah, [bp+@@localeDot]
		call	TrimTrailing
		xchg	di, bx

@@Eexp:
		mov	al, 20h
		and	al, [bp+@@formCh]
		or	al, 'E'
		stosb
		mov	ax, '-+'
		dec	bx
		jge	short @@EexpSigned
		xchg	al, ah
		neg	bx

@@EexpSigned:
		stosb
		xchg	ax, bx
		mov	cx, '00'
		cmp	ax, 99
		jbe	short @@EtwoDigits
		cmp	ax, 999
		jbe	short @@EthreeDigits
		cwd
		mov	bx, 1000
		div	bx
		add	al, cl
		stosb
		xchg	ax, dx

@@EthreeDigits:
		mov	bl, 100
		div	bl
		add	al, cl
		stosb
		xchg	al, ah
		cbw

@@EtwoDigits:
		mov	bl, 10
		div	bl
		add	ax, cx
		stosw

@@end:
		xor	al, al
		stosb
		pop	es
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret	10h
___realcvt	endp

turboCvt	proc near
		push	bp
		mov	bp, sp
		pop	bp
		ret
turboCvt	endp

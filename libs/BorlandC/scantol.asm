; void __near stl_Digit(void)
stl_Digit	proc near
		push	si
		push	di
		push	bx
		sub	bl, '0'
		jb	short @@stld_badEnd
		cmp	bl, 9
		jbe	short @@stld_digitised
		cmp	bl, ('Z' - '0')
		ja	short @@stld_maybeLower
		sub	bl, ('A' - '0' - 10)
		jmp	short @@stld_extended

@@stld_maybeLower:
		sub	bl, ('a' - '0' - 10)

@@stld_extended:
		cmp	bl, 9
		jbe	short @@stld_badEnd

@@stld_digitised:
		cmp	bl, cl
		jnb	short @@stld_badEnd
		inc	sp
		inc	sp
		clc
		mov	bh, 0
		jmp	short @@stld_end

@@stld_badEnd:
		pop	bx
		stc

@@stld_end:
		pop	di
		pop	si
		ret
stl_Digit	endp

pushSrceP macro
if LDATA
	push	word ptr [bp+@@srceP+2]
endif
	push	word ptr [bp+@@srceP]
endm

; __int32 __cdecl __near _scantol(int (__cdecl __near *@@Get)(void *srceP, void (__cdecl __near *@@UnGet)(int ch, void *srceP), const void *@@srceP, int radix, int @@width, int *@@countP, int *@@statusP)
__scantol	proc near
@@status	= word ptr -6
@@ct		= word ptr -4
@@sign		= byte ptr -1
@@Get		= word ptr  4
@@UnGet		= word ptr  6
@@srceP		= DPTR_ 8
@@radix		= word ptr (8 + dPtrSize)
@@width		= word ptr (8 + dPtrSize + 2)
@@countP	= DPTR_ (8 + dPtrSize + 2 + 2)
@@statusP	= DPTR_  (8 + dPtrSize + 2 + 2 + dPtrSize)

		push	bp
		mov	bp, sp
		sub	sp, 6
		push	si
		push	di
		mov	[bp+@@sign], 0
		mov	[bp+@@ct], 0
		mov	[bp+@@status], 1

@@stl_skipSpace:
		inc	[bp+@@ct]
		pushSrceP
		call	[bp+@@Get]
		pop	cx
		popCX_
		or	ax, ax
		jl	short @@stl_EOF
		cbw
		xchg	ax, bx
		test	bl, 80h
		jnz	short @@stl_notSpace
		mov	di, (offset __ctype+1)
		test	BY0[bx+di], _IS_SP
		jnz	short @@stl_skipSpace

@@stl_notSpace:
		xchg	ax, bx
		dec	[bp+@@width]
		jl	short @@stl_noDigitSeen
		cmp	al, '+'
		jz	short @@stl_signSeen
		cmp	al, '-'
		jnz	short @@stl_signed
		inc	[bp+@@sign]

@@stl_signSeen:
		dec	[bp+@@width]
		jl	short @@stl_noDigitSeen
		inc	[bp+@@ct]
		pushSrceP
		call	[bp+@@Get]
		pop	cx
		popCX_
		or	ax, ax
		jl	short @@stl_EOF

@@stl_signed:
		sub	si, si
		mov	di, si
		mov	cx, [bp+@@radix]
		jcxz	short @@stl_autoRadix
		cmp	cx, 36
		ja	short @@stl_noDigitSeen
		cmp	cl, 2
		jb	short @@stl_noDigitSeen

@@stl_radixSet:
		cmp	al, '0'
		jnz	short @@stl_digitNeeded
		cmp	cl, 16
		jnz	short @@stl_nextWordDigitJmp
		dec	[bp+@@width]
		jl	short @@stl_resultJmp
		inc	[bp+@@ct]
		pushSrceP
		call	[bp+@@Get]
		pop	cx
		popCX_
		cmp	al, 'x'
		jz	short @@stl_nextWordDigitJmp
		cmp	al, 'X'
		jz	short @@stl_nextWordDigitJmp
		jmp	@@stl_inspectDigit

@@stl_EOF:
		mov	[bp+@@status], EOF
		jmp	short @@stl_backUp

@@stl_noDigitSeen:
		mov	[bp+@@status], 0

@@stl_backUp:
		pushSrceP
		push	ax
		call	[bp+@@UnGet]
if LDATA
		add	sp, 6
else
		pop	cx
		pop	cx
endif
		dec	[bp+@@ct]
		sub	ax, ax
		cwd
		jmp	@@stl_end

@@stl_resultJmp:
		jmp	@@stl_result

@@stl_autoRadix:
		cmp	al, '0'
		mov	[bp+@@radix], 10
		jnz	short @@stl_digitNeeded
		dec	[bp+@@width]
		jl	short @@stl_resultJmp
		inc	[bp+@@ct]
		pushSrceP
		call	[bp+@@Get]
		pop	cx
		popCX_
		mov	[bp+@@radix], 8
		cmp	al, 'x'
		jz	short @@stl_autoHex
		cmp	al, 'X'
		jnz	short @@stl_inspectDigit

@@stl_autoHex:
		mov	[bp+@@radix], 16

@@stl_nextWordDigitJmp:
		jmp	short @@stl_nextWordDigit

@@stl_digitNeeded:
		mov	cx, [bp+@@radix]
		xchg	ax, bx
		call	stl_Digit
		xchg	ax, bx
		jb	short @@stl_noDigitSeen
		xchg	ax, si
		jmp	short @@stl_nextWordDigit

@@stl_digitOnWord:
		xchg	ax, si
		mul	[bp+@@radix]
		add	si, ax
		adc	di, dx
		jnz	short @@stl_nextDigit

@@stl_nextWordDigit:
		dec	[bp+@@width]
		jl	short @@stl_result
		inc	[bp+@@ct]
		pushSrceP
		call	[bp+@@Get]
		pop	cx
		popCX_

@@stl_inspectDigit:
		mov	cx, [bp+@@radix]
		xchg	ax, bx
		call	stl_Digit
		xchg	ax, bx
		jnb	short @@stl_digitOnWord
		jmp	short @@stl_term

@@stl_digitOnLong:
		xchg	ax, si
		mul	cx
		xchg	ax, di
		xchg	cx, dx
		mul	dx
		add	si, di
		adc	ax, cx
		xchg	ax, di
		adc	dl, dh
		jnz	short @@stl_overflow

@@stl_nextDigit:
		dec	[bp+@@width]
		jl	short @@stl_result
		inc	[bp+@@ct]
		pushSrceP
		call	[bp+@@Get]
		pop	cx
		popCX_
		mov	cx, [bp+@@radix]
		xchg	ax, bx
		call	stl_Digit
		xchg	ax, bx
		jnb	short @@stl_digitOnLong

@@stl_term:
		pushSrceP
		push	ax
		call	[bp+@@UnGet]
if LDATA
		add	sp, 6
else
		pop	cx
		pop	cx
endif
		dec	[bp+@@ct]

@@stl_result:
		mov	dx, di
		xchg	ax, si
		cmp	[bp+@@sign], 0
		jz	short @@stl_end
		neg	dx
		neg	ax
		sbb	dx, 0

@@stl_end:
		LES_	di, [bp+@@countP]
		mov	bx, [bp+@@ct]
		add	ES_[di], bx
		LES_	di, [bp+@@statusP]
		mov	bx, [bp+@@status]
		mov	ES_[di], bx
		jmp	short @@stl_ret

@@stl_overflow:
		mov	ax, 0FFFFh
		mov	dx, 7FFFh
		add	al, [bp+@@sign]
		adc	ah, 0
		adc	dx, 0
		mov	[bp+@@status], 2
		jmp	short @@stl_end

@@stl_ret:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret
__scantol	endp

; __int32 __cdecl __far atol(const char *strP)
_atol		proc
@@strP		= DPTR_ 2 + dPtrSize

		push	bp
		mov	bp, sp
		push	si
		push	di
if LDATA
		push	es
endif
		push	bp
		LES_	si, [bp+@@strP]
ifdef __HUGE__
		mov	ax, seg __ctype
		mov	ds, ax
endif
		cld
		sub	ax, ax
		cwd
		mov	cx, 10
		mov	bh, 0
		mov	di, 1 + offset __ctype

@@atl_skipSpace:
		mov	bl, ES_[si]
		inc	si
		test	BY0[bx+di], 1
		jnz	short @@atl_skipSpace
		mov	bp, 0
		cmp	bl, '+'
		jz	short @@atl_digitOnWord
		cmp	bl, '-'
		jnz	short @@atl_inspectDigit
		inc	bp

@@atl_digitOnWord:
		mov	bl, ES_[si]
		inc	si

@@atl_inspectDigit:
		cmp	bl, '9'
		ja	short @@atl_end
		sub	bl, '0'
		jb	short @@atl_end
		mul	cx
		add	ax, bx
		adc	dl, dh
		jz	short @@atl_digitOnWord
		jmp	short @@atl_nextDigit

@@atl_digitOnLong:
		mov	di, dx
		mov	cx, 10
		mul	cx
		xchg	ax, di
		xchg	dx, cx
		mul	dx
		xchg	ax, dx
		xchg	ax, di
		add	ax, bx
		adc	dx, cx

@@atl_nextDigit:
		mov	bl, ES_[si]
		inc	si
		cmp	bl, '9'
		ja	short @@atl_end
		sub	bl, '0'
		jnb	short @@atl_digitOnLong

@@atl_end:
		dec	bp
		jl	short @@atl_exit
		neg	dx
		neg	ax
		sbb	dx, 0

@@atl_exit:
		pop	bp
if LDATA
		pop	es
endif
		pop	di
		pop	si
		pop	bp
		retf
_atol		endp

; int __cdecl __far atoi(const char *strP)
_atoi		proc
@@strP		= DPTR_ 2 + dPtrSize

		push	bp
		mov	bp, sp
		push	si
		push	di
		push	word ptr [bp+@@strP+2]
		push	word ptr [bp+@@strP]
		call	_atol
		pop	cx
		pop	cx
		pop	di
		pop	si
		pop	bp
		ret
_atoi		endp

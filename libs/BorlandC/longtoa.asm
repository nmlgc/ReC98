; char *__pascal __near	_LONGTOA(__int32 value, char *strP, int radix, char maybeSigned, char hexStyle)
__LONGTOA	proc near
@@buf		= byte ptr -22h
@@hexStyle	= byte ptr  4
@@maybeSigned	= byte ptr  6
@@radix		= word ptr  8
@@strP		= dword	ptr  0Ah
@@value		= dword	ptr  0Eh

		push	bp
		mov	bp, sp
		sub	sp, 22h
		push	si
		push	di
		push	es
		LES_	di, [bp+@@strP]
ife LDATA
		push	ds
		pop	es
endif
		mov	bx, [bp+@@radix]
		cmp	bx, 36
		ja	short @@lta_end
		cmp	bl, 2
		jb	short @@lta_end
		mov	ax, word ptr [bp+@@value]
		mov	cx, word ptr [bp+@@value+2]
		or	cx, cx
		jge	short @@lta_notSigned
		cmp	[bp+@@maybeSigned], 0
		jz	short @@lta_notSigned
		mov	byte ptr ES_[di], '-'
		inc	di
		neg	cx
		neg	ax
		sbb	cx, 0

@@lta_notSigned:
		lea	si, [bp+@@buf]
		jcxz	short @@lta_shortLoop

@@lta_longLoop:
		xchg	ax, cx
		sub	dx, dx
		div	bx
		xchg	ax, cx
		div	bx
		mov	SS_[si], dl
		inc	si
		jcxz	short @@lta_shortTest
		jmp	short @@lta_longLoop

@@lta_shortLoop:
		sub	dx, dx
		div	bx
		mov	SS_[si], dl
		inc	si

@@lta_shortTest:
		or	ax, ax
		jnz	short @@lta_shortLoop
		lea	cx, [bp+@@buf]
		neg	cx
		add	cx, si
		cld

@@lta_copyLoop:
		dec	si
		mov	al, SS_[si]
		sub	al, 10
		jnb	short @@lta_alphaDigit
		add	al, 10 + '0'
		jmp	short @@lta_storeDigit

@@lta_alphaDigit:
		add	al, [bp+@@hexStyle]

@@lta_storeDigit:
		stosb
		loop	@@lta_copyLoop

@@lta_end:
		mov	al, 0
		stosb
		pop	es
		mov	dx, word ptr [bp+@@strP+2]
		mov	ax, word ptr [bp+@@strP]
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retn	0Eh
__LONGTOA	endp

; char *__pascal __near	_UTOA(unsigned int value, char *buf)
__UTOA		proc near
@@buf		= dword	ptr  4
@@value		= word ptr  8

		push	bp
		mov	bp, sp
		push	si
		push	di
		xor	ax, ax
		push	ax
		push	[bp+@@value]
		push	word ptr [bp+@@buf+2]
		push	word ptr [bp+@@buf]
		mov	ax, 10
		push	ax
		mov	al, 0
		push	ax
		mov	al, 'a'
		push	ax
		call	__LONGTOA
		pop	di
		pop	si
		pop	bp
		retn	6
__UTOA		endp

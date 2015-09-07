		public __mbcjmstojis
__mbcjmstojis	proc
@@c		= word ptr 2 + dPtrSize

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	ax, [bp+@@c]
		cmp	ah, 81h
		jb	short @@_invalid_jms
		cmp	ah, 0A0h
		jb	short @@_ok_H
		cmp	ah, 0E0h
		jb	short @@_invalid_jms
		cmp	ah, 0F0h
		jnb	short @@_invalid_jms

@@_ok_H:
		cmp	al, 40h
		jb	short @@_invalid_jms
		cmp	al, 0FDh
		jnb	short @@_invalid_jms
		cmp	al, 7Fh
		jz	short @@_invalid_jms
		cmp	al, 80h
		adc	al, 61h
		jb	short @@_1
		sub	al, 0A2h

@@_1:
		rcl	ah, 1
		and	ah, 7Fh
		add	ax, 1F21h
		jmp	short @@_rts

@@_invalid_jms:
		xor	ax, ax

@@_rts:
		pop	di
		pop	si
		pop	bp
		ret
__mbcjmstojis	endp

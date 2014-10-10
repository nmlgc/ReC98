		public ___conio_type_init
___conio_type_init proc	near
		push	si
		push	di
		cmp	___conio_type, 0
		jnz	short @@ret
		mov	ah, 4
		xor	cx, cx
		int	1Ah
		cmp	ch, 19h
		jz	short @@IBM
		cmp	ch, 20h
		jz	short @@IBM
		mov	___conio_type, 2
		jmp	short @@ret

@@IBM:
		mov	___conio_type, 1

@@ret:
		pop	di
		pop	si
		ret
___conio_type_init endp

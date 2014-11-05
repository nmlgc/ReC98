		public _delay
_delay		proc
@@arg_0		= word ptr cPtrSize + 2

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	ax, [bp+@@arg_0]
		cmp	___conio_type, 2
		jnz	short @@IBM
		push	ax
		nopcall	___nec_delay
		jmp	short @@popCX

@@IBM:
		cmp	___conio_type, 1
		jnz	short @@ret
		push	ax
		nopcall	___ibm_delay

@@popCX:
		pop	cx

@@ret:
		pop	di
		pop	si
		pop	bp
		ret
_delay		endp

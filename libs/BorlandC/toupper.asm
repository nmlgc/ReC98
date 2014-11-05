; int __cdecl toupper(int ch)
_toupper	proc
@@ch		= word ptr dPtrSize + 2

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	dx, [bp+@@ch]
		cmp	dx, -1
		jnz	short @@islower
		mov	ax, -1
		jmp	short @@ret

@@islower:
		mov	al, dl
		mov	ah, 0
		mov	bx, ax
		test	(__ctype+1)[bx], 8
		jz	short @@ret_ch
		mov	al, dl
		mov	ah, 0
		add	ax, -20h
		jmp	short @@ret

@@ret_ch:
		mov	al, dl
		mov	ah, 0

@@ret:
		pop	di
		pop	si
		pop	bp
		ret
_toupper	endp

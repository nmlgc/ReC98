getch	proc DIST
		push	si
		push	di
		cmp	_cFlag, 0
		jz	short @@input
		mov	_cFlag, 0
		mov	al, _cChar
		jmp	short @@ret

@@input:
		mov	ax, 700h
		int	21h

@@ret:
		mov	ah, 0
		pop	di
		pop	si
		ret
getch	endp

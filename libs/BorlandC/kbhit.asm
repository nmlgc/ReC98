; int kbhit(void)
public _kbhit
_kbhit		proc DIST
		push	si
		push	di
		cmp	_cFlag, 0
		jz	short @@do
		mov	ax, 1
		jmp	short @@ret

@@do:
		mov	ah, 0Bh
		int	21h
		cbw

@@ret:
		pop	di
		pop	si
		ret
_kbhit		endp

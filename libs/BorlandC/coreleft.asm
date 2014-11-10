if LDATA
; unsigned __int32 coreleft(void)
_coreleft	proc
		push	si
		push	di
		nopcall	_farcoreleft
		pop	di
		pop	si
		ret
_coreleft	endp
else
; unsigned int coreleft(void)
_coreleft	proc
		push	si
		push	di
		mov	ax, sp
		sub	ax, word ptr _brklvl@
		sub	ax, MARGIN + 32
		jnb	short @@room_left
		xor	ax, ax

@@room_left:
		and	al, 0F0h
		pop	di
		pop	si
		ret
_coreleft	endp
endif

public __abort

ifdef __LARGE__

__abort	proc far
		push	si
		push	di
		push	ds
		mov	ax, offset aAbnormalProgra
		push	ax		; buf
		nop
		push	cs
		call	near ptr ___ErrorMessage
		mov	ax, 3
		push	ax		; status
		nop
		push	cs
		call	near ptr __exit
		add	sp, 6
		pop	di
		pop	si
		retf
__abort	endp

else

__abort	proc near
		push	si
		push	di
		mov	ax, offset aAbnormalProgra
		push	ax		; buf
		call	___ErrorMessage
		mov	ax, 3
		push	ax		; status
		call	__exit
		pop	cx
		pop	cx
		pop	di
		pop	si
		retn
__abort	endp

endif

public __abort
__abort	proc
		push	si
		push	di
if LDATA
		push	ds
		mov	ax, offset aAbnormalProgra
		push	ax		; buf
		nopcall	___ErrorMessage
		mov	ax, 3
		push	ax		; status
		nopcall	__exit
		add	sp, 6
else
		mov	ax, offset aAbnormalProgra
		push	ax		; buf
		call	___ErrorMessage
		mov	ax, 3
		push	ax		; status
		call	__exit
		pop	cx
		pop	cx
endif
		pop	di
		pop	si
		ret
__abort	endp

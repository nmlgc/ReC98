; void abort(void)
_abort		proc
		push	si
		push	di
		mov	ax, 16h
		push	ax
		nopcall	raise
		pop	cx
		nopcall	__abort
		pop	di
		pop	si
		ret
_abort		endp

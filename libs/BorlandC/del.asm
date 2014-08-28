; void operator delete( void _FAR *ptr )
public @$bdele$qnv
@$bdele$qnv	proc DIST
@@ptr		= DPTR_ 2 + dPtrSize

		push	bp
		mov	bp, sp
		push	si
		push	di
		push	word ptr [bp+@@ptr+2]
		push	word ptr [bp+@@ptr] ; block
		nopcall	_farfree
		pop	cx
		pop	cx
		pop	di
		pop	si
		pop	bp
		ret
@$bdele$qnv	endp

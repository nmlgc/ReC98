; void operator delete[]( void _FAR *ptr )
public @$bdla$qnv
@$bdla$qnv	proc
@@ptr		= DPTR_ 2 + dPtrSize

		push	bp
		mov	bp, sp
		push	si
		push	di
		push	word ptr [bp+@@ptr+2]
		push	word ptr [bp+@@ptr] ; block
		nopcall	@$bdele$qnv
		pop	cx
		pop	cx
		pop	di
		pop	si
		pop	bp
		ret
@$bdla$qnv	endp

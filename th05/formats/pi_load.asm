public PI_LOAD
func pi_load
	; (PASCAL calling convention, parameter list needs to be reversed here)
	arg @@fn:ptr, @@slot:word

	push	bp
	mov	bp, sp
	push	si
	push	di
	mov	di, @@slot
	push	di
	call	pi_free
	mov	si, di
	shl	si, 2
	add	si, offset _pi_buffers
	imul	di, size PiHeader
	add	di, offset _pi_headers
	push	word ptr @@fn+2
	push	word ptr @@fn
	push	ds
	push	di
	push	ds
	push	si
	call	graph_pi_load_pack
	pop	di
	pop	si
	pop	bp
	ret	6
endfunc

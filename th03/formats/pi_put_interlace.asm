public PI_PUT_INTERLACE_8
pi_put_interlace_8 proc pascal
	arg @@left:word, @@top:word, @@slot:word
	local @@row_num:word, @@row_buf:dword

	push	si
	push	di
	mov	si, @@top
	mov	di, @@slot
	mov	bx, di
	shl	bx, 2
	mov	ax, word ptr (_pi_buffers+2)[bx]
	mov	dx, word ptr _pi_buffers[bx]
	mov	word ptr @@row_buf+2, ax
	mov	word ptr @@row_buf, dx
	mov	@@row_num, 0
	jmp	short @@check

@@put:
	push	@@left
	push	si
	pushd	@@row_buf
	mov	bx, di
	imul	bx, size PiHeader
	push	_pi_headers.PiHeader._xsize[bx]
	call	graph_pack_put_8
	inc	si
	cmp	si, 400
	jl	short @@next_row
	sub	si, 400

@@next_row:
	mov	bx, di
	imul	bx, size PiHeader
	mov	ax, _pi_headers.PiHeader._xsize[bx]
	add	word ptr @@row_buf, ax
	mov	eax, @@row_buf
	shr	eax, 10h
	mov	dx, word ptr @@row_buf
	shr	dx, 4
	add	ax, dx
	mov	dx, word ptr @@row_buf
	and	dx, 0Fh
	mov	word ptr @@row_buf+2, ax
	mov	word ptr @@row_buf, dx
	add	@@row_num, 2

@@check:
	mov	bx, di
	imul	bx, size PiHeader
	mov	ax, _pi_headers.PiHeader._ysize[bx]
	cmp	ax, @@row_num
	ja	short @@put
	pop	di
	pop	si
	ret
pi_put_interlace_8 endp

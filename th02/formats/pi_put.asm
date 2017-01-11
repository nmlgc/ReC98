proc_defconv pi_put
	arg @@left:word, @@top:word, @@slot:word
if GAME ge 3
	local @@y:word, @@row_buf:dword
else
	local @@row_buf:dword, @@y:word
endif

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
	mov	@@y, 0
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
	shr	ax, 1
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
	inc	@@y

@@check:
	mov	bx, di
	imul	bx, size PiHeader
	mov	ax, _pi_headers.PiHeader._ysize[bx]
	cmp	ax, @@y
	ja	short @@put
	pop	di
	pop	si
	ret
endp_defconv

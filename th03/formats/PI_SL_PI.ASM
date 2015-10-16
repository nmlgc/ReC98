; Copy of pi_slot_put() that only displays every second row in the given PI.

; int DEFCONV pi_slot_put_interlace(int x, int y, int slot)
proc_defconv pi_slot_put_interlace
	arg @@x:word, @@y:word, @@slot:word
	local @@row_num:word, @@row_buf:dword

	push	si
	push	di
	mov	si, @@y
	mov	di, @@slot
	mov	bx, di
	shl	bx, 2
	mov	ax, word ptr (_pi_slot_buffers+2)[bx]
	mov	dx, word ptr _pi_slot_buffers[bx]
	mov	word ptr @@row_buf+2, ax
	mov	word ptr @@row_buf, dx
	mov	@@row_num, 0
	jmp	short @@check

@@put:
	push	@@x
	push	si
	pushd	@@row_buf
	mov	bx, di
	imul	bx, size PiHeader
	push	_pi_slot_headers.PiHeader._xsize[bx]
	call	graph_pack_put_8
	inc	si
	cmp	si, 400
	jl	short @@next_row
	sub	si, 400

@@next_row:
	mov	bx, di
	imul	bx, size PiHeader
	mov	ax, _pi_slot_headers.PiHeader._xsize[bx]
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
	mov	ax, _pi_slot_headers.PiHeader._ysize[bx]
	cmp	ax, @@row_num
	ja	short @@put
	pop	di
	pop	si
	ret
endp_defconv
